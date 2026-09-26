#!/usr/bin/env python3
"""Replace a TU-local shim class with the real header, where the layout matches.

WHY. "533 headers against the original's 1,471" is the usual way this tree's
unreadability is described, and it is the wrong description: the headers mostly
EXIST. `game/Libraries/Source/WWVegas/WWLib/ascii_string.h` is right there, 45
translation units include it -- and 1,342 declare their own `class AsciiString`
instead. `Object` is redeclared 1,317 times, `Coord3D` 484. What makes the tree
unnavigable is not that a type has no definition to jump to; it is that it has a
thousand. The work is adoption, not authorship.

WHAT IS SAFE. A shim is a candidate only when its layout IS the header's layout:
for AsciiString, exactly one scalar member and no array. 762 of the 1,342 qualify.
The rest declare an opaque pad or the four-field Counted heap block -- a different
claim wearing the same name -- and are left alone, because swapping those would
change the bytes rather than the spelling.

Layout is necessary and not sufficient. The header also defines `operator==`,
`operator!=` and `operator<` at namespace scope and pulls in `string_base.h`, so a
TU that spells any of those itself gets a redefinition error. 202 of the 762 do.
They are pre-filtered, and anything the pre-filter misses is caught by the
compiler and recorded in targets/game/reverse/header_adopt_blocked.tsv so the next run does
not pay for it again.

THE GATE IS THE PROOF, AND IT IS ASKED ONE FILE AT A TIME. `build.sh` raises
SystemExit on a compile error, so ONE uncompilable TU aborts the whole scoped
build and nothing in the batch gets verified -- batching turns a 30% reject rate
into a sequence of restarts. Gating each file alone, eight at a time, costs 0.6s
per file and attributes every rejection exactly. Why not predict the rejections
instead? Because the remaining ones are shims declaring methods the header does
not have (`releaseBuffer`, `freeBytes`), and telling those apart from calls
inside inline bodies means parsing C++ with regex. The compiler already knows.

An earlier version of this script parsed only stdout, never saw the `compile
failed:` lines that go to stderr, and reported "8 kept, 0 reverted" for a batch
in which five had not compiled at all. A gate that cannot explain a failure now
raises instead of guessing.

    python3 tools/adopt_header.py --type AsciiString --count 40
    python3 tools/adopt_header.py --type AsciiString --count 40 --commit
"""
import argparse
import concurrent.futures as cf
import functools
import re
import subprocess
import sys
from pathlib import Path
from typing import NamedTuple

ROOT = Path(__file__).resolve().parents[1]
BLOCKED = ROOT / "targets/game/reverse/header_adopt_blocked.tsv"

# The types this tool may touch, DERIVED rather than listed: a type qualifies
# when exactly ONE header in the tree defines it. Types with two or more are left
# out, and MEASURED, that costs nothing: `canonical_header.py` settles 18 of the
# 39 real ones mechanically, and all 39 hold 13 TU-local copies between them --
# KeyClass, the one this rule would newly admit, has zero. Multi-header ambiguity
# reads like the blocker here and is not one; those types are ambiguous BECAUSE
# they are rare enough that nobody ever copied them into a .cpp.
# The header's own scalar-member count is read from the header too, so adding a
# type is not a hand-edit of a table that can drift out of step with it.
AREAS = ("game/GameEngine", "game/GameEngineDevice", "game/Libraries")

# The gate REFUSES a commit only for these. Every type headers() derives is fair
# game for the batch tool, but demanding a swap at commit time is only fair when
# the swap actually works: measured, SubsystemInterface lands 1 of 20 and
# DX8Wrapper 0 of 12, because those headers drag in dependencies the TU cannot
# take. Blocking a commit to require a change that fails 95% of the time is pure
# friction for the fleet. These three are the ones with a real success rate --
# and they are also the bulk of the problem, at 1,342 / 430 / 313 TU-local copies.
ENFORCED = ("AsciiString", "UnicodeString", "StringBase")


CL_LINE = re.compile(r"^(//\s*cl:.*)$", re.M)
MEMBER = re.compile(r"^\s*[A-Za-z_][\w:<>*&\s]*?\b(m_\w+)\s*(\[[^\]]*\])?\s*;", re.M)
# Each shim carries a comment naming the layout it was copied from; the header
# carries the same one, so after the swap it would be stated twice.
PROVENANCE = re.compile(r"^//\s*upstream layout:.*\n", re.M)
TYPE_BODY = re.compile(r"^[ \t]*(?:class|struct)[ \t]+(\w+)\b[^{;]*\{", re.M)
NON_CODE = re.compile(
    r'R"|//(?:\\\r?\n|[^\n])*|/\*.*?(?:\*/|\Z)|'
    r'"(?:\\.|[^"\\])*(?:"|\Z)|\'(?:\\.|[^\'\\])*(?:\'|\Z)', re.S)


class Shim(NamedTuple):
    start: int
    end: int
    body: str


# The shim, with the `template <typename T>` line above it when there is one --
# StringBase is a template in all 431 of its TU-local copies, and replacing the
# class alone would leave that line hanging over an #include.
@functools.lru_cache(maxsize=1)
def headers():
    """type -> (include spelling, /I directory, scalar members the header has).

    Derived, not listed. A type qualifies only when exactly ONE header defines
    it; the member count comes from that header, so the two can never drift
    apart. `want` is the number of non-static, non-array data members the class
    declares at depth 1 -- the layout a TU-local shim has to agree with.
    """
    # These canonical string headers were settled by review; keep the selection
    # stable while duplicate definitions elsewhere are removed.
    out = {
        "AsciiString": ("ascii_string.h", "game/Libraries/Source/WWVegas/WWLib", 1),
        "UnicodeString": ("unicode_string.h", "game/Libraries/Source/WWVegas/WWLib", 1),
    }
    defining = {}
    for path in (ROOT / "game").rglob("*.h"):
        text = path.read_text(encoding="utf-8", errors="replace")
        for match in TYPE_BODY.finditer(text):
            defining.setdefault(match.group(1), []).append(path)
    for name, paths in defining.items():
        if name in out or len(paths) != 1:
            continue                       # two headers disagreeing is a judgement
        path = paths[0]
        body = shim(path.read_text(encoding="utf-8", errors="replace"), name)
        if not body:
            continue
        members = MEMBER.findall(body.body)
        # An ARRAY member is an opaque pad -- a claim about size, not about
        # fields -- so a shim matching one proves nothing. Any number of scalar
        # members is fine: blocker() makes the shim agree with this exact count,
        # and the byte gate verifies every file individually anyway.
        if not members or any(a for _, a in members):
            continue
        rel = path.relative_to(ROOT).as_posix()
        out[name] = (path.name, rel[:rel.rindex("/")], len(members))
    return out


def shim(text, name):
    def hide(match):
        if match.group() == 'R"':
            raise ValueError("header adoption does not support raw string literals")
        return re.sub(r"[^\r\n]", " ", match.group())

    # Preserve offsets while ignoring braces that cannot delimit a class.
    code = NON_CODE.sub(hide, text)
    head = re.search(rf"^[ \t]*(?P<declaration>(?:template[^\n]*\n\s*)?class {re.escape(name)}\s*\{{)",
                     code, re.M)
    if not head:
        return None
    if not head.group("declaration").startswith("template") and re.search(
            r"\btemplate\s*<[^;{}]*>\s*$", code[:head.start("declaration")]):
        return None  # Leaving an unsupported template prefix would corrupt the declaration.
    depth = 1
    for brace in re.compile(r"[{}]|^[ \t]*#", re.M).finditer(code, head.end()):
        if brace.group().lstrip() == "#":
            return None  # Conditional branches can describe incompatible class boundaries.
        depth += 1 if brace.group() == "{" else -1
        if depth == 0:
            tail = re.match(r"[ \t]*;(?:[ \t]*\r?\n)?", text[brace.end():])
            if tail:
                return Shim(head.start("declaration"), brace.end() + tail.end(),
                            text[head.end():brace.start()])
            return None
    return None


@functools.lru_cache(maxsize=None)
def brought_in(include, incdir):
    """Type names the header defines, its own quoted #includes included.

    A TU that already spells one of these collides with the header rather than
    adopting it: `ascii_string.h` pulls in `string_base.h`, so a TU carrying its
    own `class StringBase` cannot take it. Derived rather than listed, because the
    set differs per header and drifts when a header changes. Cached: the commit
    hook asks once per staged source, and there can be hundreds.
    """
    names, seen, todo = set(), set(), [include]
    while todo:
        this = todo.pop()
        if this in seen:
            continue
        seen.add(this)
        path = ROOT / incdir / this
        if not path.exists():
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        names |= {m.group(1) for m in TYPE_BODY.finditer(text)}
        todo += re.findall(r'^\s*#include\s+"([^"]+)"', text, re.M)
    return frozenset(names)


def blocker(text, name, want_members, partial=False):
    """Why this TU cannot take the header, or None when it can.

    `partial` accepts a shim that declares FEWER members than the header. 277
    shims are that shape: the TU declared only the fields it touched. Adopting
    there changes sizeof, so it is sound ONLY because the byte gate then rejects
    every TU where the size mattered -- an allocation, a by-value copy, a frame
    slot -- and keeps the ones that use nothing but pointers and references. It
    is opt-in rather than default because it trades a guaranteed-neutral edit for
    one the compiler has to adjudicate file by file.
    """
    found = shim(text, name)
    if not found:
        return "no complete supported local shim"
    members = MEMBER.findall(found.body)
    if any(a for _, a in members):
        return "shim declares an array: an opaque pad, not fields"
    if len(members) > want_members or (not partial and len(members) != want_members):
        return "layout is not the header's"
    if not members and not partial:
        # A zero-member shim is a pure facade -- `class DX8Wrapper { static void
        # Foo(); };` -- so it asserts no layout at all and adopting can only add
        # one. That makes it the SAFEST partial case, not the riskiest, but it is
        # still a size change and still the gate's call.
        return "shim declares no members"
    include, incdir, _ = headers()[name]
    clash = (brought_in(include, incdir) - {name}) & \
        {m.group(1) for m in TYPE_BODY.finditer(text)}
    if clash:
        return "also declares " + ", ".join(sorted(clash))
    # The header defines these three inline at namespace scope, so a TU that
    # spells one is a redefinition. Declaring them is fine; defining them is not.
    if re.search(rf"\boperator\s*(==|!=|<)\s*\(\s*const\s+{name}\b[^;]*\{{", text):
        return f"defines a free operator on {name}"
    return None


def rewrite(text, name, include, incdir):
    found = shim(text, name)
    if not found:
        raise ValueError(f"cannot locate a complete supported local {name} class")
    head, tail = text[:found.start], text[found.end:]
    note = PROVENANCE.search(head, max(0, len(head) - 400))
    if note and not head[note.end():].strip():
        head = head[:note.start()]
    text = head + f'#include "{include}"\n' + tail
    cl = CL_LINE.search(text)
    if not cl:
        return f"// cl: /I{incdir}\n" + text
    if f"/I{incdir}" in cl.group(1):
        return text
    return text[:cl.start()] + cl.group(1) + f" /I{incdir}" + text[cl.end():]


def verdict(rel):
    """(rel, why-it-failed or None). An unreadable answer is a defect, not a pass."""
    # through bash: on Windows a .sh is not executable (WinError 193)
    done = subprocess.run(["bash", str(ROOT / "build.sh"), rel], cwd=ROOT,
                          capture_output=True, text=True)
    out = done.stdout + done.stderr
    if done.returncode:
        # A compile error means the header lacks something the shim declared; a
        # Functions: FAIL means it compiled and the inlines moved the bytes.
        why = next((l.strip() for l in out.splitlines()
                    if ": error" in l or l.startswith("Functions: FAIL")),
                   f"build.sh exited {done.returncode}")
        return rel, why
    if "Functions: OK" not in out:
        raise RuntimeError(f"{rel}: build.sh exited 0 with no verdict:\n" + out[-2000:])
    return rel, None


def gate(paths, jobs):
    """(kept, [(path, why)]). Never an empty build -- that is the full gate."""
    if not paths:
        raise RuntimeError("refusing to build an empty set: that is the full gate")
    with cf.ThreadPoolExecutor(jobs) as pool:
        answers = list(pool.map(verdict, paths))
    bad = [(rel, why) for rel, why in answers if why]
    return [rel for rel, why in answers if not why], bad


def blocked_paths():
    if not BLOCKED.exists():
        return set()
    return {l.split("\t")[0] for l in
            BLOCKED.read_text(encoding="utf-8").splitlines() if l.strip()}


def staged_sources():
    out = subprocess.run(["git", "diff", "--cached", "--name-only", "--diff-filter=ACM"],
                         cwd=ROOT, capture_output=True, text=True).stdout.split()
    return [p for p in out if p.endswith((".cpp", ".c")) and (ROOT / p).exists()]


def offenders(paths):
    """(path, type) for each staged source that redeclares a type it could include.

    Only shims blocker() clears are reported: same layout, no namespace clash. A
    shim that declares its own operator== or a method the header lacks is a
    different claim and none of this gate's business.
    """
    exempt = blocked_paths()
    out = []
    for rel in paths:
        if rel in exempt:
            continue
        text = (ROOT / rel).read_text(encoding="utf-8", errors="replace")
        for kind in ENFORCED:
            spec = headers().get(kind)
            if spec and not blocker(text, kind, spec[2]):
                out.append((rel, kind))
    return out


def check():
    """Refuse a staged source that redeclares a type with a canonical header.

    WHY AT COMMIT TIME. The conversion fleet writes ~1,300 TU-local class bodies a
    day and ~300 of them are for a type a header already defines -- more per day
    than this lane adopts. Cleaning up afterwards loses about 2:1, so the only
    version of this that ever finishes is the one that stops it being written.

    The block is narrow by construction and never a dead end: the fix is one
    command, and a shim the compiler will not take gets recorded in
    targets/game/reverse/header_adopt_blocked.tsv and skipped from then on -- an exemption that
    is a recorded decision rather than a silent pass.
    """
    bad = offenders(staged_sources())
    if not bad:
        return 0
    for rel, kind in bad:
        print(f"{rel}: declares its own `class {kind}` where "
              f'#include "{headers()[kind][0]}" says the same thing')
    print("\n  python3 tools/adopt_header.py --fix-staged"
          "   (swaps, byte-gates, records whatever the compiler refuses)")
    return 1


def fix_staged(jobs):
    """Swap every staged source that can take the header, then restage it."""
    bad = offenders(staged_sources())
    if not bad:
        print("nothing staged needs a header")
        return 0
    kinds = dict(bad)
    for rel, kind in bad:
        include, incdir, _ = headers()[kind]
        text = (ROOT / rel).read_text(encoding="utf-8")
        (ROOT / rel).write_text(rewrite(text, kind, include, incdir),
                                encoding="utf-8", newline="")
    kept, rejected = gate([rel for rel, _ in bad], jobs)
    for rel, _ in rejected:
        subprocess.run(["git", "checkout", "--", rel], cwd=ROOT, check=False)
    record([(rel, kinds[rel], why) for rel, why in rejected])
    if kept:
        subprocess.run(["git", "add", *kept], cwd=ROOT, check=True)
    if rejected:
        subprocess.run(["git", "add", str(BLOCKED.relative_to(ROOT))], cwd=ROOT, check=True)
    print(f"adopted {len(kept)}, recorded {len(rejected)} the compiler refused")
    return 0


def record(entries):
    """Append (path, type, reason) so the next run does not re-pay for them."""
    if not entries:
        return
    with BLOCKED.open("a", encoding="utf-8") as fh:
        for path, kind, why in entries:
            fh.write(f"{path}\t{kind}\t{why}\n".replace("\r", " "))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--type", default="AsciiString")
    ap.add_argument("--count", type=int, default=40)
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--partial", action="store_true",
                    help="also take shims that declare fewer members than the header")
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--check", action="store_true",
                    help="refuse staged sources that redeclare a type with a header")
    ap.add_argument("--staged", action="store_true", help="with --check")
    ap.add_argument("--fix-staged", action="store_true",
                    help="swap what --check names, byte-gate it, and restage")
    args = ap.parse_args()
    if args.check:
        return check()
    if args.fix_staged:
        return fix_staged(args.jobs)
    if args.type not in headers():
        raise SystemExit(f"{args.type}: not a type with exactly one defining header")
    include, incdir, want = headers()[args.type]

    known = blocked_paths()
    listed = subprocess.run(
        ["git", "grep", "-l", "-E", rf"^\s*class\s+{args.type}\b", "--", "game/***.cpp"],
        cwd=ROOT, capture_output=True, text=True).stdout.split()

    changed = []
    for rel in listed:
        if len(changed) >= args.count:
            break
        if rel in known:
            continue
        text = (ROOT / rel).read_text(encoding="utf-8")
        if blocker(text, args.type, want, args.partial):
            continue
        # --type picks the FILE; once picked, every covered type in it is
        # swapped. Doing one at a time leaves the file still redeclaring another
        # covered type, and this tool's own commit gate then refuses the commit
        # it just produced -- the hook cannot tell "half adopted" from "not
        # adopted", and it should not have to.
        for kind, (inc_k, dir_k, want_k) in headers().items():
            if blocker(text, kind, want_k, args.partial) is None:
                text = rewrite(text, kind, inc_k, dir_k)
        (ROOT / rel).write_text(text, encoding="utf-8", newline="")
        changed.append(rel)
    if not changed:
        print("nothing swappable left in this pass")
        return 9
    print(f"swapped {len(changed)} TU-local {args.type} shim(s) for {include}")

    changed, rejected = gate(changed, args.jobs)
    for rel, _ in rejected:
        subprocess.run(["git", "checkout", "--", rel], cwd=ROOT, check=False)
    record([(rel, args.type, why) for rel, why in rejected])
    print(f"  byte gate: OK over {len(changed)}, {len(rejected)} rejected")
    if not changed:
        return 1

    if not args.commit:
        print("  --commit to land")
        return 0

    return land(changed, rejected, args.type, include)


def land(changed, rejected, kind, include):
    """Commit, shedding whatever the hook names. Retries are bounded, not hopeful.

    Some files cannot be committed at ALL: they define a function no ledger row
    declares, which predates this lane and needs a row, not a header. build.sh
    says nothing about it -- only the hook does -- so the hook is where they get
    found, and they are recorded so the next run skips them.
    """
    for _ in range(4):
        # `git add` aborts the WHOLE command on one missing pathspec, so a file
        # another seat moved between listing and staging takes the batch with it.
        changed = [rel for rel in changed if (ROOT / rel).exists()]
        if not changed:
            print("  nothing left to land")
            return 1
        paths = changed + ([str(BLOCKED.relative_to(ROOT))] if rejected else [])
        subprocess.run(["git", "add", *paths], cwd=ROOT, check=True)
        body = (f"Adopt {include} in {len(changed)} TUs that declared their own {kind}\n\n"
                f"The header already exists and is included by 45 TUs; 1,342 more declared a\n"
                f"local copy instead, which is why the type has no one definition to jump to.\n"
                f"Only shims whose layout IS the header's are swapped -- an opaque pad or the\n"
                f"four-field Counted heap block is a different claim and stays.\n\n"
                f"Byte-verified: a swap that compiles to the same bytes is the same program.\n")
        done = subprocess.run(["git", "commit", "-q", "-F", "-"], cwd=ROOT,
                              input=body, text=True, capture_output=True)
        if not done.returncode:
            print(f"  committed {len(changed)}")
            return 0
        out = done.stdout + done.stderr
        why = next((l for l in out.splitlines() if l.startswith("PRE-COMMIT FAILED")),
                   "the hook refused the commit")
        named = [rel for rel in changed
                 if any(l.startswith(rel + ":") for l in out.splitlines())]
        if not named:
            print("COMMIT REFUSED:\n" + out[-3000:], file=sys.stderr)
            return 1
        print(f"  hook rejected {len(named)}: {why}")
        subprocess.run(["git", "reset", "-q", "--", *named], cwd=ROOT, check=False)
        subprocess.run(["git", "checkout", "--", *named], cwd=ROOT, check=False)
        record([(rel, kind, why) for rel in named])
        rejected += [(rel, why) for rel in named]
        changed = [rel for rel in changed if rel not in named]
        if not changed:
            print("  nothing left to land")
            return 1
    print("COMMIT REFUSED: still refused after shedding 4 rounds of files", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
