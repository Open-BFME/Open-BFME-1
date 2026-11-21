#!/usr/bin/env python3
"""Refuse changes that run the conversion direction backward: asm -> C++ only.

Usage:  conversion_gate.py OLD NEW
        OLD/NEW are git revisions; NEW may be ":" for the staged index.

Rule A: added lines under game/ (outside game/gen_small/) may not contain
        __declspec(naked) or _emit/__emit. game/gen_small/ is exempt only
        because it is the frozen output of the retired generators, never
        because a new dump is welcome there; a proven codegen blocker
        (x87, SEH) belongs in game/masm_dumps/*.asm. Eighteen fleet commits
        titled "convert ... to exact C++" deleted real C++ bodies and added
        __emit thunks — byte-verification passes on those, so this is the
        only gate that can see them.

Rule B: a matched RVA that had at least one clean-C++ source in OLD must
        still have one in NEW. Retracting a wrong claim (row deleted or
        status changed) is legal and must be its own commit; repointing a
        live clean claim at a dump is never legal.

Rule C: game/gen_asm/ is machine output and stays that way. C1 every added
        line there must match the grammar the retired generator emitted, so a
        lift of a NAMED function cannot be expressed in the directory at all,
        unless the whole new file is exactly what tools/dump_apply.py writes
        from the old one (symbolic relocations, re-derived here, not trusted); C2 every added
        ledger row pointing there is anonymous (?d_<rva>@@YAXXZ, notes
        gen-dump), so a dump can never squat an identity byte-verification
        cannot falsify; C3 a wave commit may not touch any other file under
        game/, so a deleted C++ body cannot ride inside a diff of 33,000
        unreadable `db` lines. Rule A needs no exemption here and gets none:
        a `db` dump matches neither NAKED_RE nor LIFT_RE, and source_kind
        scores a .asm file as assembly unconditionally, so the offence Rule A
        polices -- inflating the C++ lane with re-encoded binary -- is not
        expressible in this directory.
"""

import collections
import csv
import io
import os
import posixpath
import re
import subprocess
import sys
from pathlib import Path

from list_naked_candidates import NAKED_RE
from progress import CPP_SUFFIXES, naked_cpp_rows, source_kind
import layout_history

LIFT_RE = re.compile(r"\b__?emit\b")
# A comment is prose, not a lift. The gate fired on a merge whose only `__emit`
# was in a line explaining why a dump was being LEFT ALONE, which reads as
# "you added a naked body" and sends the author hunting one that is not there.
# Only whole `//` tails and complete `/* */` pairs are removed: a line inside an
# unterminated block comment keeps its text and is still scanned, so the scan
# fails closed rather than being talked out of a real lift by an open comment.
COMMENT_RE = re.compile(r"/\*.*?\*/|//.*$")


def is_lift_line(line):
    """True when `line` ADDS a naked body or an __emit, ignoring its comments.

    The scanner must go through here rather than matching the raw line, or a
    comment mentioning __emit is reported as a lift.
    """
    scanned = COMMENT_RE.sub(" ", line)
    return bool(NAKED_RE.search(scanned) or LIFT_RE.search(scanned))
LEDGER = "targets/game/reverse/functions.csv"


def run(*argv):
    proc = subprocess.run(argv, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")
    if proc.returncode != 0:
        raise SystemExit("conversion_gate: %s failed: %s" % (" ".join(argv), proc.stderr.strip()))
    return proc.stdout


def added_lift_lines(old, new, lines=None):
    if lines is None:
        lines = diff_lines(old, new, "Code/", "game/", SHIMS, ":(exclude)game/gen_small/")
    # Authored code only. A ledger row may name a file in the vendored
    # inputs/reference/ tree, and those rows sit outside this scan on purpose: nobody
    # authors that tree, nine of its files already contain __emit upstream, and
    # scanning it would fire on the next re-vendor rather than on a regression.
    # Rule B below reads whatever path a row names, so it covers them.
    # inputs/reference/shims/ is authored (and followed for macros), so its
    # diff is judged like a game/ header's (approved 2026-10-14).
    # A naked declarator the same diff removes from the same file is a retyped
    # existing lift, not a new one: re_attempts 59794 added a tick parameter to
    # the unchanged naked CommUdpProcess so its C caller could pass it, and was
    # charged with adding a naked body. Only a line naming the same function
    # cancels by name. An __emit line names none: it is forgiven only when no
    # function in that file gains emitted bytes (emit_growth, OLD vs NEW file
    # text, per function), so a hunk that merely re-shows a function's existing
    # __emit lines passes (re_attempts 0x006D88A0, removing ~W3DBridge from
    # W3DBridgeBuffer.cpp) while bytes removed from one function never pay
    # for bytes added to another. Bytes on preprocessor lines count under the
    # macro's own key, and a function invoking an emit macro defined in the
    # same file owns that macro's bytes, so `#define RAW __emit 0xC3` plus
    # `__asm { RAW }` in a clean function is growth (orchestrator probe of
    # 0204cb9c94). Every touched file whose NEW text mentions emit is checked
    # for growth even when no added line names __emit. Macros defined in a
    # header are not followed (a gap that predates 47cf6cb).
    _PRELUDE.clear()  # per run: ":" and revs mean a different tree per call
    _OUTSIDE.clear()
    _LISTING.clear()
    _CHANGED.clear()
    removed, added, path, touched = collections.Counter(), [], None, []
    for line in lines:
        if line.startswith("+++ b/"):
            path = line[6:]
        elif line.startswith("---") or line.startswith("+++"):
            continue
        elif line[:1] and line[:1] in "+-":
            if path is None or not path.startswith(("game/", SHIMS)) \
                    or path.startswith("game/gen_small/"):
                continue
            if line[0] == "+" and path not in touched:
                touched.append(path)
            if is_lift_line(line):
                name = declared_name(COMMENT_RE.sub(" ", line[1:]))
                if line[0] == "-":
                    if name:
                        removed[(path, name)] += 1
                else:
                    added.append((path, name, line))
    # First, so the prelude already holds the headers of re-defined names.
    users = users_of_changed_names(old, new, lines)
    bad, grown = {}, {}
    for path, name, line in added:
        if name and removed[(path, name)]:
            removed[(path, name)] -= 1
            continue
        if not name and LIFT_RE.search(COMMENT_RE.sub(" ", line[1:])) \
                and not NAKED_RE.search(COMMENT_RE.sub(" ", line[1:])):
            if path not in grown:
                grown[path] = emit_growth(file_text(old, path), file_text(new, path),
                                          header_prelude(old)[0], header_prelude(new)[0])
            if not grown[path]:
                continue
        first, count = bad.get(path, (line[1:].strip()[:80], 0))
        bad[path] = (first, count + 1)
    for path in users:
        if path not in touched:
            touched.append(path)
    for path in touched:
        if path in bad or not (path.endswith(tuple(CPP_SUFFIXES) + (".h", ".hpp", ".inl"))
                               or path.startswith(SHIMS)):
            continue
        if path not in grown:
            new_text = file_text(new, path)
            names = header_prelude(new)[1]
            mentions = names and re.search(
                r"\b(?:%s)\b" % "|".join(map(re.escape, sorted(names))), new_text)
            grown[path] = emit_growth(file_text(old, path), new_text,
                                      header_prelude(old)[0], header_prelude(new)[0]) \
                if LIFT_RE.search(new_text) or "##" in new_text or mentions \
                or path in users else []
        if grown[path]:
            bad[path] = ("emitted bytes grow in " + ", ".join(grown[path])[:80], 1)
    return [(p, "%s  (%d such lines)" % (first, count)) for p, (first, count) in bad.items()]


# Every __emit counts, whatever its operand (owner verdict 2026-10-13;
# adversarial review round 2): a literal is its byte value; a #define, enum or
# `const` integral constant with a literal initializer resolves to its value
# (same file, or a tracked game/ header); anything else is counted as its own
# symbol (operand text plus its definition, so a changed definition is
# growth). Emit macros are expanded to a fixpoint: a macro is an emit macro if
# its body names __emit/_emit or another emit macro, and a function-like one
# has its arguments substituted, so `EB(0x90)` -> `EB(0xC3)` is a new byte.
# Emit macros and constants are also collected from every tracked game/ header
# (outside game/gen_small/) and every tracked file under inputs/reference/shims/
# (authored, edited often; any extension) that defines one, at the revision
# being compared; the rest of inputs/reference/ (the vendored EA tree, nine
# files with __emit upstream) is not followed. A name defined more than once
# is an emit macro if ANY definition emits (fail closed: the gate cannot tell
# which header or #ifdef branch a TU sees), and identical duplicate constant
# definitions count once.
# A renamed function's emits count as new (conservative: the gate cannot tell
# a rename from a move, G2 note 8).
EMIT_OPERAND = r"\b__?emit\b\s*(\(?\s*[\w$]+\s*\)?|[^\s;{}]+)?"
EMIT_BYTE_RE = re.compile(EMIT_OPERAND)
_LITERAL_RE = re.compile(r"\(?\s*(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*\)?$")
_DEFINE_RE = re.compile(
    r"(?m)^[ \t]*#\s*define\s+(\w+)(\([^)\n]*\))?[ \t]*((?:[^\n]*\\\n)*[^\n]*)")
_CONST_RE = re.compile(
    r"\bconst\b[^;=(){}#\n]*?\b(\w+)\s*=\s*([^;,{}\n]+)\s*[;,]")
SHIMS = "inputs/reference/shims/"
_HEADER_GLOBS = ("game/*.h", "game/*.hpp", "game/*.inl", ":(exclude)game/gen_small/", SHIMS)
_SOURCE_GLOBS = ("game/", ":(exclude)game/gen_small/", ":(exclude)game/gen_asm/")


def file_text(rev, path):
    """Text of path at rev (":" = the index), "" when absent."""
    data = blob(rev, path)
    return "" if data is None else data.decode("utf-8", errors="replace")


def _definitions(text):
    """{name: definitions} of every constant and macro a text defines."""
    text = _strip_comments(text)
    defs = {k: tuple(v) for k, v in _constants(text).items()}
    for name, values in _macro_defs(text).items():
        defs[name] = defs.get(name, ()) + tuple(values)
    return defs


def _grep(rev, args, paths):
    """`git grep -l` at rev (":" = index); paths without the rev prefix."""
    cmd = ["git", "grep", "-l", "-I"] + (["--cached"] if rev == ":" else []) + args
    cmd += ([] if rev == ":" else [rev]) + ["--"] + list(paths)
    out = subprocess.run(cmd, capture_output=True, text=True).stdout
    return [p.split(":", 1)[1] if rev != ":" else p for p in out.splitlines()]


def _words(names):
    return ["-w"] + sum((["-e", n] for n in sorted(names)), [])


def users_of_changed_names(old, new, lines):
    """game/ files whose emits use a #define/enum/const/macro this diff
    re-defines: a header-only edit of `#define OP 0x90` must re-judge every
    unchanged .cpp emitting `__emit OP`, function by function. Only files that
    emit at all (literal __emit, or a game/ header emit macro) are candidates:
    one batched `git grep` per revision, and none when no definition changed
    (a4c07311a8 grepped every user of every changed name and took 60+ s)."""
    paths = {line[6:] for line in lines if line.startswith(("+++ b/", "--- a/"))}
    changed = set()
    for path in paths:
        if not path.startswith(("game/", SHIMS)) or path.startswith("game/gen_small/"):
            continue
        before, after = _definitions(file_text(old, path)), _definitions(file_text(new, path))
        changed |= {n for n in set(before) | set(after) if before.get(n) != after.get(n)}
    if not changed:
        return []
    found, used = set(), set()
    alt = "|".join(map(re.escape, sorted(changed)))
    word = re.compile(r"\b(?:%s)\b" % alt)
    for rev in (old, new):
        # Files emitting a changed name directly: one grep.
        found |= set(_grep(rev, ["-E", r"\b__?emit\b[[:space:](]*(%s)\b" % alt], _SOURCE_GLOBS))
        # Files using a header emit macro whose body names a changed name.
        text, names = header_prelude(rev)
        table = _macro_table(text)
        via = {n for n in names if n in table and word.search(table[n][1])}
        if via:
            found |= set(_grep(rev, _words(via), _SOURCE_GLOBS))
    used = changed if found else set()
    if used - _CHANGED:
        _CHANGED.update(used)
        _PRELUDE.clear()
    return sorted(found)


def _strip_comments(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", " ", text)


_PRELUDE, _CHANGED, _PARSED = {}, set(), {}


def header_prelude(rev):
    """(definitions text, emit/paste macro names) of the tracked game/ headers
    that define an emit macro, a pasting macro, or a macro naming one
    (fixpoint over `git grep`), plus the headers naming a constant this diff
    re-defines that an emitting file uses (_CHANGED), at rev. Cheap: a few
    batched greps; only headers that matter are read."""
    if rev in _PRELUDE:
        return _PRELUDE[rev]
    seen, texts, names = set(), [], set()
    new = _grep(rev, ["-E", r"\b__?emit\b|##"], _HEADER_GLOBS)
    if _CHANGED:
        new += _grep(rev, _words(_CHANGED), _HEADER_GLOBS)
    for _ in range(8):
        new = [p for p in new if p not in seen]
        if not new:
            break
        for path in new:
            seen.add(path)
            texts.append(_strip_comments(file_text(rev, path)))
        table = _macro_table("\n".join(texts))
        more = (_emit_macros(table) | _paste_macros(table)) - names
        if not more:
            break
        names |= more
        new = _grep(rev, _words(more), _HEADER_GLOBS)
    out_text, out_names = outside_emit_defs(rev)
    if out_text:
        texts.append(out_text)
        names |= out_names
    _PRELUDE[rev] = ("\n".join(texts), names)
    return _PRELUDE[rev]


# Outside headers (approved 2026-10-14, CR2B H1): emit macros and raw emit
# bodies outside game/ and inputs/reference/shims/ (inputs/vendor/, the
# vendored EA tree, the rest of inputs/) are never judged where they are
# written. An "emit file" is an outside file that defines an emit macro or
# holds a literal __emit/_emit outside comments, strings and char literals.
# - Rule A3 refuses an include a game/ or shims file adds (an #include line,
#   or a `// cl:` /FI) that resolves to an emit file or to an outside file
#   that includes one. An added, changed or removed `// cl:` or `// stlport`
#   line re-judges that file's includes; one that reached the same emit
#   files before is not blamed again.
# - Rule A6 refuses a symlink (mode 120000) under game/ or shims: the gate
#   reads a link as its target text and cannot resolve through it.
# - Rule A5 refuses a diff after which the emit files reached from the
#   existing includes of game/ and shims files (R) hold one they did not:
#   the macro or raw-body flip of an included file, reach growing behind an
#   existing include, an emit file moved into reach. A vendor import that
#   nothing in game/ reaches passes.
# - The #define lines of every outside emit macro (and of outside macros
#   naming one) join header_prelude, so a NEW use in game/ is emit growth
#   like any header macro's, while a re-shown or moved use is not.
# Includes resolve the way build.py runs cl.exe: a quoted include first looks
# next to the including file, then every include tries the `// cl:` /I dirs
# in order, then INCLUDE (the STLport overlay, stlport and stlport/src for a
# `// stlport` file, nbench for Benchmark/, then Vc7/include). A header with
# no `// cl:` line, and every outside file, falls back to a path-suffix match
# against the outside tree after the quoted-sibling check. The suffix match
# is a guess, not a proof: it can send an include to the wrong outside file
# (the EA debug/_pch.h's "internal.h" once matched profile/internal.h), so it
# can refuse wrongly as well as miss; a wrong refusal goes on the shrink-only
# allowlist below. Names are normalised (posixpath.normpath, `\` -> `/`) and
# compared without case, as on Windows. A3 and A5 run only when the diff
# touches an outside inputs/ path, deletes or renames a game/ or shims file,
# or changes an #include, `// cl:` or `// stlport` line. The outside scan is
# cached under build/, keyed on this file's hash and the outside subtree OIDs.
_OUTSIDE_GLOBS = ("inputs/", ":(exclude)inputs/reference/shims/")
# Shrink-only: (including file, include name) pairs on master that resolve
# to an outside emit file. Empty since /I resolution (2026-10-14).
OUTSIDE_INCLUDE_ALLOW = set()
_OUTSIDE, _LISTING = {}, {}
_INCLUDE_RE = re.compile(r'^\s*#\s*include\s*([<"])([^">]+)[">]')
_OUTSIDE_CACHE_DIR = Path("build") / "conversion_gate_outside"
_VC7_INCLUDE = "inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/include"
_STLPORT, _STLPORT_OVERLAY = "inputs/vendor/stlport", "inputs/reference/shims/stlport_bfme"
_STLPORT_OPT_OUT = "// stlport-range-errors: vendored"
_NBENCH = "inputs/vendor/nbench"
try:
    import hashlib
    _GATE_HASH = hashlib.sha1(Path(__file__).read_bytes()).hexdigest()
except OSError:
    _GATE_HASH = None


def _outside_key(rev):
    """Cache key: this file's hash plus the OIDs of every inputs/ subtree the
    outside scan reads (all but shims) at rev; ":" uses `git write-tree`.
    None when unknown (no caching)."""
    if _GATE_HASH is None:
        return None
    tree = rev
    if rev == ":":
        proc = subprocess.run(["git", "write-tree"], capture_output=True, text=True)
        if proc.returncode != 0:
            return None
        tree = proc.stdout.strip()
    proc = subprocess.run(["git", "ls-tree", tree, "inputs/", "inputs/reference/"],
                          capture_output=True, text=True)
    if proc.returncode != 0:
        return None
    rows = sorted(r for r in proc.stdout.splitlines()
                  if not r.endswith(("\tinputs/reference", "\tinputs/reference/shims")))
    return hashlib.sha1("\n".join([_GATE_HASH] + rows).encode()).hexdigest()


def _listing(rev):
    """(lower path -> path for every tracked file, lower basename -> outside
    paths) at rev; one ls-tree, kept for the last rev only."""
    if rev not in _LISTING:
        cmd = (["git", "ls-files", "--cached"] if rev == ":"
               else ["git", "ls-tree", "-r", "--name-only", rev])
        files = [p for p in subprocess.run(cmd, capture_output=True,
                                           text=True).stdout.split("\n") if p]
        by_base = {}
        for p in files:
            if _outside(p):
                by_base.setdefault(p.rsplit("/", 1)[-1].lower(), []).append(p)
        _LISTING.clear()
        _LISTING[rev] = ({p.lower(): p for p in files}, by_base)
    return _LISTING[rev]


def _outside(path):
    return path.startswith("inputs/") and not path.startswith(SHIMS)


def _norm(name):
    name = posixpath.normpath(name.replace("\\", "/"))
    return "" if name in (".", "") else name


def _cl_args(text):
    args, found = [], False
    for line in text.lstrip("﻿").splitlines():
        if line.startswith("// cl:"):
            found = True
            args += line[len("// cl:"):].split()
    return args if found else None


def _flag_values(args, flag):
    out = []
    for i, arg in enumerate(args):
        if arg.upper() in ("/" + flag, "-" + flag) and i + 1 < len(args):
            out.append(_norm(args[i + 1]))
        elif arg[:1] in "/-" and arg[1:1 + len(flag)].upper() == flag and len(arg) > len(flag) + 1:
            out.append(_norm(arg[1 + len(flag):]))
    return out


def cl_include_dirs(text):
    """/I dirs of a file's `// cl:` lines, in order; None without one."""
    args = _cl_args(text)
    return None if args is None else _flag_values(args, "I")


def include_dirs(path, text):
    """Search dirs after the quoted sibling, as build.py runs cl.exe: the
    `// cl:` /I dirs, then INCLUDE. None (suffix fallback) for a header or
    outside file without a `// cl:` line."""
    cl = cl_include_dirs(text)
    if cl is None and (_outside(path) or not path.lower().endswith(tuple(CPP_SUFFIXES))):
        return None
    extra = []
    if "// stlport" in text[:8192]:
        extra += ([] if _STLPORT_OPT_OUT in text[:8192] else [_STLPORT_OVERLAY])
        extra += [_STLPORT, _STLPORT + "/src"]
    if path.startswith("game/Libraries/Source/Benchmark/"):
        extra.append(_NBENCH)
    return (cl or []) + extra + [_VC7_INCLUDE]


def include_entries(text):
    """[(quoted, name)] for each #include line and `// cl:` /FI ("fi": cl.exe
    runs from the checkout root, so a /FI path is root-relative first)."""
    out = [(m.group(1) == '"', m.group(2)) for m in map(_INCLUDE_RE.match, text.splitlines()) if m]
    args = _cl_args(text)
    return out + [("fi", n) for n in _flag_values(args or [], "FI")]


def resolve_include(rev, includer, name, quoted, dirs):
    """Tracked files an include names, as cl.exe searches: a quoted one
    next to its includer first, then each dir in order (dirs; None for a
    file that falls back to an outside suffix match)."""
    exact, by_base = _listing(rev)
    name = _norm(name)
    if not name:
        return []
    tries = [posixpath.dirname(includer)] if quoted else []
    tries += dirs or []
    for base in tries:
        hit = exact.get(_norm(posixpath.join(base, name)).lower())
        if hit:
            return [hit]
    if dirs is not None:
        return []
    tail = name.lower()
    while tail.startswith("../"):
        tail = tail[3:]
    return [p for p in by_base.get(tail.rsplit("/", 1)[-1], ())
            if p.lower() == tail or p.lower().endswith("/" + tail)]


def _outside_scan(rev):
    """{"defs", "names", "seeds", "reach"} for the outside tree at rev: the
    #define lines of the outside emit macros (and outside macros naming one,
    fixpoint over `git grep`), their names, the emit files, and {outside
    path: [emit files it reaches]} through outside includes (sibling first,
    then suffix)."""
    seen, lines, names, owners = set(), [], set(), []
    first = _grep(rev, ["-E", r"\b__?emit\b"], _OUTSIDE_GLOBS)
    new, raw = list(first), set()
    for _ in range(8):
        new = [p for p in new if p not in seen]
        if not new:
            break
        for path in new:
            seen.add(path)
            text = _strip_comments(file_text(rev, path))
            if path in first and _emits(re.sub(r"(?m)^[ \t]*#\s*define(?:[^\n]*\\\n)*[^\n]*",
                                               " ", text)):
                raw.add(path)
            found = [m.group(0) for m in _DEFINE_RE.finditer(text)]
            lines += found
            owners += [(path, m) for m in found]
        more = _emit_macros(_macro_table("\n".join(lines))) - names
        if not more:
            break
        names |= more
        new = _grep(rev, _words(more), _OUTSIDE_GLOBS)
    names = _emit_macros(_macro_table("\n".join(lines)))
    keep = [l for l in lines if _DEFINE_RE.match(l).group(1) in names]
    seeds = raw | {p for p, l in owners if _DEFINE_RE.match(l).group(1) in names}
    edges = collections.defaultdict(set)
    for path, quoted, name in _grep_includes(rev, _OUTSIDE_GLOBS):
        for target in resolve_include(rev, path, name, quoted, None):
            if target != path:
                edges[path].add(target)
    reach = {p: {p} for p in seeds}
    for _ in range(64):
        grew = False
        for path, targets in edges.items():
            got = set().union(*(reach.get(t, ()) for t in targets))
            if got - reach.get(path, set()):
                reach.setdefault(path, set()).update(got)
                grew = True
        if not grew:
            break
    return {"defs": "\n".join(keep), "names": sorted(names), "seeds": sorted(seeds),
            "reach": {p: sorted(v) for p, v in sorted(reach.items())}}


def _grep_includes(rev, globs):
    """[(path, quoted, name)] for every #include line under globs at rev."""
    cmd = ["git", "grep", "-n", "-I"] + (["--cached"] if rev == ":" else [])
    cmd += ["-E", r'^\s*#\s*include\s*[<"][^">]+[">]'] + ([] if rev == ":" else [rev])
    out = subprocess.run(cmd + ["--"] + list(globs), capture_output=True, text=True).stdout
    rows = []
    for row in out.splitlines():
        parts = row.split(":", 3 if rev != ":" else 2)
        if len(parts) < (4 if rev != ":" else 3):
            continue  # not a match row (a grep diagnostic)
        path, line = parts[-3], parts[-1]
        m = _INCLUDE_RE.match(line)
        if m:
            rows.append((path, m.group(1) == '"', m.group(2)))
    return rows


def _valid_state(state):
    """A loaded cache entry is used only with the right shape and a
    non-empty emit-file set (an empty one would silently disable A3/A5)."""
    try:
        return (isinstance(state, dict) and isinstance(state["defs"], str)
                and isinstance(state["names"], list) and isinstance(state["seeds"], list)
                and isinstance(state["reach"], dict) and bool(state["seeds"])
                and all(isinstance(n, str) for n in state["names"] + state["seeds"])
                and all(isinstance(k, str) and isinstance(v, list)
                        and all(isinstance(x, str) for x in v)
                        for k, v in state["reach"].items())
                and set(state["seeds"]) <= set(state["reach"]))
    except (KeyError, TypeError):
        return False


def outside_state(rev):
    """_outside_scan(rev), cached in memory and on disk by _outside_key."""
    if rev in _OUTSIDE:
        return _OUTSIDE[rev]
    import json
    key = _outside_key(rev)
    path = _OUTSIDE_CACHE_DIR / (key + ".json") if key else None
    state = None
    if path is not None:
        try:
            state = json.loads(path.read_text())
        except (OSError, ValueError):
            state = None
    if not _valid_state(state):
        state = _outside_scan(rev)
        if path is not None and state["seeds"]:
            try:
                path.parent.mkdir(parents=True, exist_ok=True)
                tmp = path.with_suffix(".tmp%d" % os.getpid())
                tmp.write_text(json.dumps(state))
                os.replace(tmp, path)
            except OSError:
                pass
    _OUTSIDE[rev] = state
    return state


def outside_emit_defs(rev):
    """(#define lines, names) of the outside emit macros at rev."""
    state = outside_state(rev)
    return state["defs"], set(state["names"])


def _reached(rev, path, text, entries=None):
    """{emit file: include name} the includes (or entries) of a game/ or
    shims file reach at rev."""
    dirs, reach, out = include_dirs(path, text), outside_state(rev)["reach"], {}
    for quoted, name in (include_entries(text) if entries is None else entries):
        if quoted == "fi":
            quoted, search = True, [""] + (dirs or [])
        else:
            search = dirs
        for target in resolve_include(rev, path, name, quoted, search):
            for hit in reach.get(target, ()):
                out.setdefault(hit, name)
    return out


def outside_work(old, new, lines):
    """(run A3, run A5) for a diff: A3 when an #include, `// cl:` or
    `// stlport` line in a game/ or shims file changes; A5 when the diff
    touches an outside inputs/ path or deletes or renames a game/ or shims
    file (a deleted sibling can send an existing include elsewhere)."""
    path, a3 = None, False
    for line in lines:
        if line.startswith(("+++ b/", "--- a/")):
            path = line[6:]
        elif line.startswith(("---", "+++")):
            continue
        elif line[:1] in "+-" and path and path.startswith(("game/", SHIMS)):
            body = line[1:].lstrip("﻿")
            if _INCLUDE_RE.match(body) or body.startswith("// cl:") or "// stlport" in body:
                a3 = True
                break
    cmd = ["git", "diff", "--name-status", "--find-renames=50%"]
    cmd += ["--cached", old] if new == ":" else [old, new]
    rows = subprocess.run(cmd + ["--", "inputs/", "game/"], capture_output=True,
                          text=True).stdout.splitlines()
    a5 = False  # an added include, /I or // stlport change is A3's to judge
    for row in rows:
        status, *paths = row.split("\t")
        if any(_outside(p) for p in paths) or (status[:1] in "DR" and any(
                p.startswith(("game/", SHIMS)) for p in paths)):
            a5 = True
            break
    return a3, a5


def reach_set(rev):
    """R(rev): the emit files the existing includes of game/ and shims files
    reach. One grep of their #include, `// cl:` and `// stlport` lines."""
    cmd = ["git", "grep", "-n", "-I"] + (["--cached"] if rev == ":" else [])
    cmd += ["-E", r'^\s*#\s*include\s*[<"]|// cl:|// stlport'] + ([] if rev == ":" else [rev])
    out = subprocess.run(cmd + ["--", "game/", SHIMS, ":(exclude)game/gen_small/"],
                         capture_output=True, text=True).stdout
    texts = collections.defaultdict(list)
    for row in out.splitlines():
        parts = row.split(":", 3 if rev != ":" else 2)
        if len(parts) < (4 if rev != ":" else 3):
            continue  # not a match row (a grep diagnostic)
        path, line = parts[-3], parts[-1]
        texts[path].append(line)
    # `// stlport` (and its opt-out) count only in a file's first 8 KiB, as
    # in A3 and build.py: read those files' heads, not the joined grep rows.
    marked = sorted(p for p, t in texts.items() if any("// stlport" in l for l in t))
    heads = _heads(rev, marked)
    hits = set()
    for path, text in texts.items():
        lines = [l for l in text if "// stlport" not in l]
        head = heads.get(path, "")
        lines += [m for m in ("// stlport", _STLPORT_OPT_OUT) if m in head]
        hits |= set(_reached(rev, path, "\n".join(lines)))
    return hits


def _heads(rev, paths):
    """{path: first 8192 characters} at rev, one `git cat-file --batch`."""
    if not paths:
        return {}
    spec = "".join(("%s:%s\n" % ("" if rev == ":" else rev, p)) for p in paths)
    out = subprocess.run(["git", "cat-file", "--batch"], input=spec.encode(),
                         capture_output=True).stdout
    heads, pos = {}, 0
    for path in paths:
        end = out.index(b"\n", pos)
        header = out[pos:end].split()
        pos = end + 1
        if len(header) == 3 and header[1] == b"blob":
            size = int(header[2])
            heads[path] = out[pos:pos + size].decode("utf-8", "replace")[:8192]
            pos += size + 1
    return heads


def reach_growth(old, new):
    """Rule A5: emit files R(new) holds that R(old) did not (R(old) is
    skipped when R(new) is empty)."""
    grown = reach_set(new)
    return sorted(grown - reach_set(old)) if grown else []


def added_symlinks(old, new):
    """Rule A6: paths under game/ or shims that the diff makes a symlink
    (mode 120000). The gate reads a link as its target text, so an include
    through one is never resolved; the repo tracks none."""
    cmd = ["git", "diff", "--raw", "--no-renames"]
    cmd += ["--cached", old] if new == ":" else [old, new]
    out = subprocess.run(cmd + ["--", "game/", SHIMS], capture_output=True, text=True).stdout
    bad = []
    for row in out.splitlines():
        meta, _, path = row.partition("\t")
        fields = meta.split()
        if len(fields) >= 2 and fields[1] == "120000":
            bad.append(path)
    return bad


def added_outside_includes(old, new, lines=None):
    """Rule A3: [(path, include, outside emit file)] for each include a
    game/ or shims file adds that reaches an outside emit file. An include
    the same diff removes from the same file is a move; an added, changed or
    removed `// cl:` or `// stlport` line re-judges every include of that file, and
    one that reached the same emit file before is not blamed again."""
    if lines is None:
        lines = collect_diff_lines(old, new)
    added, removed, recl, path = [], collections.Counter(), set(), None
    for line in lines:
        if line.startswith("+++ b/"):
            path = line[6:]
        elif line.startswith(("---", "+++")):
            continue
        elif line[:1] in "+-" and path and path.startswith(("game/", SHIMS)) \
                and not path.startswith("game/gen_small/"):
            body = line[1:].lstrip("﻿")
            if body.startswith("// cl:") or "// stlport" in body:  # added or removed
                recl.add(path)
            m = _INCLUDE_RE.match(line[1:])
            if m:
                key = (path, m.group(1) == '"', m.group(2))
                if line[0] == "-":
                    removed[key] += 1
                else:
                    added.append(key)
    for p in recl:
        for quoted, name in include_entries(file_text(new, p)):
            if (p, quoted, name) not in added:
                added.append((p, quoted, name))
    bad, before = [], {}
    for path, quoted, name in added:
        if removed[(path, quoted, name)] and path not in recl:
            removed[(path, quoted, name)] -= 1
            continue
        if (path, name) in OUTSIDE_INCLUDE_ALLOW:
            continue
        hits = _reached(new, path, file_text(new, path), [(quoted, name)])
        if path in recl and hits:
            if path not in before:
                before[path] = _reached(old, path, file_text(old, path))
            hits = {h: n for h, n in hits.items() if h not in before[path]}
        if hits:
            bad.append((path, name, sorted(hits)[0]))
    return bad


def _constants(text):
    """{name: [definition text]} for #define, enum and `const` constants."""
    consts = {}
    for m in _DEFINE_RE.finditer(text):
        if m.group(2):
            continue
        consts.setdefault(m.group(1), []).append(
            " ".join(m.group(3).replace("\\\n", " ").split()))
    for m in _CONST_RE.finditer(text):
        val = " ".join(m.group(2).split())
        lit = _LITERAL_RE.match(val)
        consts.setdefault(m.group(1), []).append(
            str(_emit_value(lit.group(1))) if lit else "const=" + val)
    for m in re.finditer(r"\benum\b[^{;]*\{([^}]*)\}", text):
        nxt = 0
        for item in m.group(1).split(","):
            item = " ".join(item.split())
            if not item:
                continue
            name, _, val = item.partition("=")
            name, val = name.strip(), val.strip()
            if not re.fullmatch(r"\w+", name):
                continue
            if val:
                lit = _LITERAL_RE.match(val)
                if lit:
                    nxt = _emit_value(lit.group(1))
                    consts.setdefault(name, []).append(str(nxt))
                else:
                    nxt = None
                    consts.setdefault(name, []).append("enum=" + val)
            elif nxt is not None:
                consts.setdefault(name, []).append(str(nxt))
            else:
                consts.setdefault(name, []).append("enum-after-symbolic")
            if nxt is not None:
                nxt += 1
    return consts


def _operand_key(op, consts, seen=()):
    """Byte value (int) or a symbol string for one __emit operand."""
    op = (op or "").strip()
    if not op:
        return "sym:<none>"
    lit = _LITERAL_RE.match(op)
    if lit:
        return _emit_value(lit.group(1))
    name = op.strip("() \t")
    defs = list(dict.fromkeys(consts.get(name) or ()))  # identical copies count once
    if defs and len(defs) == 1 and name not in seen:
        d = defs[0]
        lit = _LITERAL_RE.match(d)
        if lit:
            return _emit_value(lit.group(1))
        if re.fullmatch(r"\(?\s*\w+\s*\)?", d):
            return _operand_key(d, consts, seen + (name,))
    return "sym:%s=%s" % (op, "|".join(defs) if defs else "?")


def _macro_defs(text):
    """{name: [(params or None, body)]}: every definition, in text order."""
    defs = {}
    for m in _DEFINE_RE.finditer(text):
        params = None
        if m.group(2):
            params = [p.strip() for p in m.group(2)[1:-1].split(",") if p.strip()]
        defs.setdefault(m.group(1), []).append(
            (params, " ".join(m.group(3).replace("\\\n", " ").split())))
    return defs


# Char literals are skipped in the same pass so '"' cannot open a fake string.
_STRING_RE = re.compile(r"'(?:\\.|[^'\\\n])*'" r'|"(?:\\.|[^"\\\n])*"')


def _emits(body):
    """True when a macro body names __emit/_emit outside a string literal."""
    return bool(LIFT_RE.search(_STRING_RE.sub('""', body)))


def _choose(defs):
    """{name: (params, body)} from _macro_defs: the last definition, except
    that a name with any emitting definition (directly or through another
    such name, fixpoint) keeps its last emitting one. The gate cannot tell
    which header, #undef or #ifdef branch a TU sees, so it fails closed."""
    emit = {n for n, ds in defs.items() if any(_emits(b) for _, b in ds)}
    while emit:
        names = re.compile(r"\b(?:%s)\b" % "|".join(map(re.escape, sorted(emit))))
        more = {n for n, ds in defs.items()
                if n not in emit and any(names.search(b) for _, b in ds)}
        if not more:
            break
        emit |= more
    table = {}
    names = emit and re.compile(r"\b(?:%s)\b" % "|".join(map(re.escape, sorted(emit))))
    for n, ds in defs.items():
        if n in emit:
            ds = [d for d in ds if _emits(d[1]) or names.search(d[1])] or ds
        table[n] = ds[-1]
    return table


def _macro_table(text):
    """{name: (params or None, body)}; see _choose for which definition wins."""
    return _choose(_macro_defs(text))


def _emit_macros(table):
    """Names of macros whose expansion reaches __emit (fixpoint). A pasting
    macro (`##`) is not one by itself: each use of it is expanded with its
    arguments pasted and rescanned (emit_bytes_by_function), so
    `CAT(__em,it)` counts and `BFME_VIRTUAL_SLOT(n)` (491e03cf7c) does not."""
    emit = {n for n, (_, body) in table.items() if _emits(body)}
    while emit:
        names = re.compile(r"\b(?:%s)\b" % "|".join(map(re.escape, sorted(emit))))
        more = {n for n, (_, body) in table.items() if n not in emit and names.search(body)}
        if not more:
            break
        emit |= more
    return emit


def _paste_macros(table):
    """Function-like macros whose body pastes tokens."""
    return {n for n, (params, body) in table.items() if params is not None and "##" in body}


_OPEN_PAREN_RE = re.compile(r"\s*\(")
UNEXPANDABLE = " __emit <unexpandable> "


def _call_args(text, pos):
    """(args, end) for a `(a, b)` starting at text[pos:] (after spaces), or
    (None, pos) when none."""
    m = _OPEN_PAREN_RE.match(text, pos)
    if not m:
        return None, pos
    i, depth, args, cur = m.end(), 1, [], ""
    while i < len(text) and depth:
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if not depth:
                break
        if c == "," and depth == 1:
            args.append(cur.strip())
            cur = ""
        else:
            cur += c
        i += 1
    if depth:
        return False, len(text)  # unbalanced: cannot be expanded
    args.append(cur.strip())
    return args, i + 1


_NAME_RE_CACHE = {}


def _expand(text, table, emit, limit=16):
    """Expand emit and pasting macros in text to a fixpoint. A use that
    cannot be expanded (unbalanced arguments, recursion limit) becomes an
    unknown emit: the gate fails closed."""
    if not emit:
        return text
    key = tuple(sorted(emit))
    if key not in _NAME_RE_CACHE:
        _NAME_RE_CACHE.clear()
        _NAME_RE_CACHE[key] = re.compile(r"\b(%s)\b" % "|".join(map(re.escape, key)))
    name_re = _NAME_RE_CACHE[key]
    for _ in range(limit):
        out, pos, changed = [], 0, False
        for m in name_re.finditer(text):
            if m.start() < pos:
                continue
            params, body = table[m.group(1)]
            end = m.end()
            if params is not None:
                args, end = _call_args(text, m.end())
                if args is None:
                    continue
                if args is False:
                    out.append(text[pos:m.start()] + UNEXPANDABLE)
                    pos, changed = end, True
                    continue
                for p, a in zip(params, args + [""] * len(params)):
                    body = re.sub(r"\b%s\b" % re.escape(p), lambda _m, a=a: a, body)
            # `##` pastes tokens (CAT(__em,it) -> __emit); the result is
            # rescanned on the next round like any other expansion.
            body = re.sub(r"\s*##\s*", "", body)
            out.append(text[pos:m.start()] + " " + body + " ")
            pos, changed = end, True
        if not changed:
            return text
        text = "".join(out) + text[pos:]
    return text + UNEXPANDABLE if name_re.search(text) else text


def emit_bytes_by_function(text, prelude=""):
    """{scoped function signature: Counter of emitted operands} for a C++ text.

    A brace block whose header declares a function (a `name(` declarator) is a
    function; any other block (namespace, class, extern "C") is a container
    and is scanned inside. A header ending in `namespace [N]`, `extern "C"`
    or `class|struct|union Name [: bases]` opens a container whatever
    precedes it (a macro invocation without `;`). A function's key is its
    enclosing container path plus its signature, so same-named functions in
    different scopes differ. Emits outside every function are keyed None.
    `prelude` supplies definitions only (game/ headers); its own emits are
    owned by the header's own check."""
    text = _strip_comments(text)
    if prelude not in _PARSED:
        if len(_PARSED) >= 4:
            _PARSED.clear()
        _PARSED[prelude] = (_constants(prelude), _macro_defs(prelude))
    pre_consts, pre_defs = _PARSED[prelude]
    consts = {k: list(v) for k, v in pre_consts.items()}
    for k, v in _constants(text).items():
        consts.setdefault(k, []).extend(v)
    defs = {k: list(v) for k, v in pre_defs.items()}
    for k, v in _macro_defs(text).items():
        defs.setdefault(k, []).extend(v)
    table = _choose(defs)
    emit = _emit_macros(table)
    expandable = emit | _paste_macros(table)
    owners = {}

    def count(snippet):
        return collections.Counter(_operand_key(m.group(1), consts)
                                   for m in EMIT_BYTE_RE.finditer(_expand(snippet, table, expandable)))

    def directive(match):
        line = " ".join(match.group(0).replace("\\\n", " ").split())
        name = re.match(r"#\s*define\s+(\w+)", line)
        if name and name.group(1) in emit:
            body = re.sub(r"#\s*define\s+\w+(\([^)]*\))?", " ", line, count=1)
            found = count(body)
            if not found:
                found = collections.Counter({"macro:" + body.strip(): 1})
        else:
            found = collections.Counter(_operand_key(m.group(1), consts)
                                        for m in EMIT_BYTE_RE.finditer(line))
        if found:
            key = "#define " + name.group(1) if name else "#preprocessor"
            owners.setdefault(key, collections.Counter()).update(found)
        return " "
    text = re.sub(r"(?m)^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", directive, text)
    text = _STRING_RE.sub('""', text)
    depth, func, func_depth, header = 0, None, None, []
    scopes = []  # (depth at open, normalized container header)
    pos, skip = 0, 0
    token = r"[{};]|" + EMIT_OPERAND
    if expandable:
        token += r"|\b(?:%s)\b" % "|".join(map(re.escape, sorted(expandable)))
    for match in re.finditer(token, text):
        if match.start() < skip:
            continue
        tok = match.group(0)
        if func is None:
            header.append(text[pos:match.start()])
        pos = match.end()
        if tok == "{":
            if func is None:
                head = " ".join("".join(header).split())
                header = []
                scope = _SCOPE_HEAD_RE.search(head)
                if scope:
                    scopes.append((depth, " ".join(scope.group(0).split())))
                elif declared_name(head):
                    func = " :: ".join([s for _, s in scopes] + [head])
                    func_depth = depth
                else:
                    scopes.append((depth, head))
            depth += 1
        elif tok == "}":
            depth -= 1
            if func is not None and depth == func_depth:
                func = None
            elif func is None and scopes and scopes[-1][0] == depth:
                scopes.pop()
            header = []
        elif tok == ";":
            if func is None:
                header = []
        elif tok in expandable:
            end = match.end()
            if table[tok][0] is not None:
                args, end = _call_args(text, match.end())
                if args is None:
                    continue
                if args is False:
                    owners.setdefault(func, collections.Counter())["sym:<unexpandable>"] += 1
                    continue
            owners.setdefault(func, collections.Counter()).update(
                count(text[match.start():end]))
            pos = skip = end
        else:
            owners.setdefault(func, collections.Counter())[
                _operand_key(match.group(1), consts)] += 1
    return owners


_SCOPE_HEAD_RE = re.compile(
    r'(?:\bnamespace(?:\s+[\w:]+)?|\bextern\s*""'
    r"|\b(?:class|struct|union)\s+[\w:]+(?:\s*final)?(?:\s*:[^(){};]*)?)\s*$")


def _emit_value(value):
    return int(value, 16 if value[:2] in ("0x", "0X") else 10) & 0xFF


def emit_growth(old_text, new_text, old_prelude="", new_prelude=""):
    """Functions whose emitted bytes grow from OLD to NEW (a new function with
    any __emit counts). Bytes a deleted or shrunk function loses free nothing
    for any other function."""
    before = emit_bytes_by_function(old_text, old_prelude)
    after = emit_bytes_by_function(new_text, new_prelude)
    return sorted((str(k) for k, v in after.items()
                   if v - before.get(k, collections.Counter())), key=str)


_DECLSPEC_RE = re.compile(r"__declspec\s*\([^)]*\)")
_DECLARATOR_RE = re.compile(r"([~\w:]+)\s*\(")


def declared_name(text):
    """The function a declarator line or signature names, or None."""
    match = _DECLARATOR_RE.search(_DECLSPEC_RE.sub(" ", text))
    return match.group(1) if match else None


def added_asm_only_bodies(old, new, lines=None):
    """Rule A2: a function whose whole body is mnemonic __asm is a lift too.

    It needs no __emit, so Rule A cannot see it, and progress.py scored it as
    C++ until it learned asm_only_bodies. Compare per file, by signature, so an
    edit elsewhere in a file that already holds one is not charged for it."""
    from progress import asm_only_bodies
    if lines is None:
        lines = collect_diff_lines(old, new)
    # Reuse the one game/ diff Rules A and C read: only files with added lines.
    paths = sorted({line[6:] for line in lines if line.startswith("+++ b/")
                    and line[6:].startswith("game/") and line[6:].endswith(tuple(CPP_SUFFIXES))
                    and not line[6:].startswith("game/gen_small/")})
    bad = []
    for path in paths:
        def body_signatures(rev):
            proc = subprocess.run(["git", "show", f"{rev}:{path}"], capture_output=True)
            if proc.returncode != 0:
                return set()
            text = proc.stdout.decode("utf-8", errors="replace")
            return {b["signature"] for b in asm_only_bodies(text)} if "_asm" in text else set()
        before, after = body_signatures(old), body_signatures("" if new == ":" else new)
        # A retyped existing body (same function, new parameter list; 59794)
        # replaces a signature the diff removes; it is not an added lift.
        retyped = collections.Counter(declared_name(sig) for sig in before - after)
        for signature in sorted(after - before):
            name = declared_name(signature)
            if name and retyped[name]:
                retyped[name] -= 1
                continue
            bad.append((path, signature))
    return bad


GEN_ASM = "game/gen_asm/"
# The generator's whole vocabulary. Anything else in a dump file is a hand edit.
GEN_ASM_LINE_RE = re.compile(
    r"^(?:\.386|\.model flat|_TEXT SEGMENT|_TEXT ENDS|END|;.*|"
    r"public \?d_[0-9a-f]{8}@@YAXXZ|"
    r"\?d_[0-9a-f]{8}@@YAXXZ (?:PROC|ENDP)|"
    r"    db (?:0?[0-9A-F]{2}h)(?:, 0?[0-9A-F]{2}h)*|)$")


def diff_lines(old, new, *paths):
    cmd = ["git", "diff", "--unified=0", "--find-renames=1%"]
    cmd += ["--cached", old] if new == ":" else [old, new]
    return run(*cmd, "--", *paths).splitlines()


def collect_diff_lines(old, new):
    """Collect the shared game/ledger diff used by Rules A and C."""
    return diff_lines(old, new, "Code/", "game/", SHIMS, layout_history.OLD_LEDGER, LEDGER)


def gen_asm_offences(old, new, lines=None):
    """Rule C. Returns a list of human-readable offences, empty when clean."""
    offences = []
    path = None
    dump_rows, other_code_edits, c1 = [], set(), {}
    old_ledger = layout_history.path_at(old, LEDGER, layout_history.OLD_LEDGER,
                                         root=Path.cwd())
    existing = {(r["name"], r["target_rva"], r["target_size"],
                 layout_history.canonical_source(r["source"]), r["status"])
                for r in csv.DictReader(io.StringIO(show(old, old_ledger)))}
    if lines is None:
        lines = diff_lines(old, new, "Code/", "game/", layout_history.OLD_LEDGER, LEDGER)
    for line in lines:
        if line.startswith("+++ b/"):
            path = line[6:]
            continue
        if path is None or line.startswith("---") or line.startswith("+++"):
            continue
        added = line.startswith("+")
        if not added and not line.startswith("-"):
            continue
        body = line[1:]
        if path.startswith(GEN_ASM):
            if added and not GEN_ASM_LINE_RE.match(body):
                c1.setdefault(path, []).append("C1 %s: not generator output: %s"
                                               % (path, body.strip()[:80]))
        elif path == LEDGER:
            if not added:
                continue
            fields = next(csv.reader([body]), [])
            if len(fields) >= 5 and fields[4].startswith(GEN_ASM):
                if len(fields) >= 6 and (fields[0], fields[2], fields[3],
                                          fields[4], fields[5]) in existing:
                    continue
                dump_rows.append(fields)
        elif path.startswith("game/"):
            other_code_edits.add(path)

    for path, found in c1.items():
        if not tool_reproduced(old, new, path):
            offences.extend(found)
    for fields in dump_rows:
        name, rva, notes = fields[0], fields[2], fields[6] if len(fields) > 6 else ""
        expected = "?d_%08x@@YAXXZ" % int(rva, 16)
        if name != expected:
            offences.append("C2 %s claims identity %s; a dump proves bytes and "
                            "an extent, never what the function is (expected %s)"
                            % (rva, name, expected))
        if not notes.lstrip().startswith("gen-dump"):
            offences.append("C2 %s: a game/gen_asm/ row must carry gen-dump "
                            "notes, or is_scaffold_row cannot see it" % rva)
    if dump_rows and other_code_edits:
        offences.append("C3 wave commit also edits %s — dumps-and-ledger only, "
                        "so a deleted C++ body cannot ride inside an unreadable "
                        "diff" % ", ".join(sorted(other_code_edits)))
    return offences


_DUMP_APPLY = []


def tool_reproduced(old, new, path):
    """C1's one exception: the new blob is byte-for-byte what tools/dump_apply.py
    writes when re-run on the OLD blob of the same path (reproduce(), which
    reads only that text, the ledger and the retail tables). Anything else --
    a hand edit, tool output from another base, one changed byte -- is refused."""
    base, staged = blob(old, path), blob(new, path)
    if base is None or staged is None:
        return False
    try:
        import dump_apply
        if not _DUMP_APPLY:
            _DUMP_APPLY.append(dump_apply.Context())
        text, _ = dump_apply.reproduce(path, base.decode("utf-8"), _DUMP_APPLY[0])
    except Exception as exc:  # any failure to reproduce is a refusal
        print("conversion gate: %s: dump_apply could not reproduce it (%s)" % (path, exc), file=sys.stderr)
        return False
    if text is None:
        return False
    if b"\r\n" in base:
        text = text.replace("\n", "\r\n")
    return text.encode("utf-8") == staged


def blob(rev, path):
    """Raw bytes of path at rev (":" = the index), or None."""
    spec = (":%s" if rev == ":" else rev + ":%s") % path
    proc = subprocess.run(["git", "show", spec], capture_output=True)
    return proc.stdout if proc.returncode == 0 else None


class _MissingSource(Exception):
    """A ledger row's source is unreadable at the revision being judged.

    Raised instead of exiting: HEAD itself can carry such rows (a commit that
    added rows without adding the file), and crashing on them blocks the very
    repair commit that retracts them. Callers treat a missing source as
    proving nothing -- neither clean nor naked -- and check_csv (which runs
    beside this gate in the hook) still rejects any NEW row in that state.
    """


def show(rev, path, allow_missing=False):
    spec = (":%s" if rev == ":" else rev + ":%s") % path
    proc = subprocess.run(["git", "show", spec], capture_output=True, text=True)
    if proc.returncode != 0:
        if allow_missing:
            raise _MissingSource(spec)
        raise SystemExit("conversion_gate: cannot read %s — a matched row's source "
                         "must exist at its revision (ledger corruption?)" % spec)
    return proc.stdout


def ledger_text(rev):
    path = layout_history.path_at("" if rev == ":" else rev, LEDGER,
                                  layout_history.OLD_LEDGER, root=Path.cwd())
    return show(rev, path)


def matched_by_rva(text):
    rows = {}
    for row in csv.DictReader(io.StringIO(text)):
        if row.get("status") == "matched":
            row["source"] = layout_history.canonical_source(row["source"])
            rows.setdefault(row["target_rva"], []).append(row)
    return rows


def _rva_field(line):
    if '"' in line:
        fields = next(csv.reader([line]), [])
    else:
        fields = line.split(",", 3)
    return fields[2] if len(fields) > 2 else None


def scoped_rows(old_text, new_text):
    """matched_by_rva for both revisions, restricted to what can matter.

    An address's source set can only differ between revisions if one of its
    ledger lines differs, so only those addresses are parsed in full, plus
    (lazily, via the returned callable) every row of the sources they involve
    for the naked-body proof. Parsing both whole 170k-row ledgers was ~9 s of
    every push. Line-scoping is exact while each record is one line; a line
    with an odd number of quotes (a record that may span lines) keeps the full
    parse. Returns (old_rows, new_rows, rows_for_sources) or None to fall back.
    """
    lines = []
    for text in (old_text, new_text):
        split = re.findall(r"[^\n]*\n|[^\n]+$", text)
        if any(line.count('"') % 2 for line in split):
            return None
        lines.append(split)
    old_lines, new_lines = lines
    if not old_lines or not new_lines or old_lines[0] != new_lines[0]:
        return None
    header = old_lines[0]
    changed_lines = set(old_lines[1:]) ^ set(new_lines[1:])
    candidates = {_rva_field(line) for line in changed_lines}

    def parse(selected):
        return matched_by_rva(header + "".join(selected))

    old_rows = parse([l for l in old_lines[1:] if _rva_field(l) in candidates])
    new_rows = parse([l for l in new_lines[1:] if _rva_field(l) in candidates])

    def rows_for_sources(which, sources):
        names = {Path(s).name for s in sources}
        body = old_lines if which == "old" else new_lines
        return parse([l for l in body[1:] if any(n in l for n in names)])

    return old_rows, new_rows, rows_for_sources


def ledger_blob(rev):
    path = layout_history.path_at("" if rev == ":" else rev, LEDGER,
                                  layout_history.OLD_LEDGER, root=Path.cwd())
    spec = (":%s" if rev == ":" else rev + ":%s") % path
    return run("git", "rev-parse", spec).strip()


def naked_keys(rev, all_rows, sources):
    """(Row keys naked at `rev`, sources unreadable at `rev`).

    Judged by progress.py's per-row machinery. Feeds naked_cpp_rows every
    matched row of each affected source, not just the changed rows: its
    sole-row-sole-body proof is only valid on whole files. A source missing
    at `rev` proves nothing either way, so its rows are withheld from the
    proof and reported beside it for clean_sources to exclude as well.
    """
    matched = {(r["name"], r["target_rva"]): (int(r["target_size"]), r["source"])
               for rows in all_rows.values() for r in rows if r["source"] in sources}
    texts, missing = {}, set()
    for s in sources:
        if Path(s).suffix.lower() not in CPP_SUFFIXES:
            continue
        try:
            texts[s] = show(rev, s, allow_missing=True)
        except _MissingSource:
            missing.add(s)
    matched = {k: v for k, v in matched.items() if v[1] not in missing}
    return naked_cpp_rows(matched, texts), missing


def clean_coverage_lost(old, new):
    if ledger_blob(old) == ledger_blob(new):
        return []
    old_text, new_text = ledger_text(old), ledger_text(new)
    scoped = scoped_rows(old_text, new_text)
    if scoped is None:
        old_rows, new_rows = matched_by_rva(old_text), matched_by_rva(new_text)
        rows_for_sources = lambda which, _sources: old_rows if which == "old" else new_rows
    else:
        old_rows, new_rows, rows_for_sources = scoped
    changed = [rva for rva, rows in new_rows.items()
               if rva in old_rows and
               {r["source"] for r in old_rows[rva]} != {r["source"] for r in rows}]
    if not changed:
        return []

    def clean_sources(rva, rows_by_rva, naked, missing):
        # Use the same code-axis classification as progress.py: prebuilt
        # archives and assembly own no clean C++ coverage. In either
        # direction, moving a row to .lib cannot retain C++ coverage.
        return sorted({r["source"] for r in rows_by_rva[rva]
                       if source_kind(r["source"]) == "cpp"
                       and r["source"] not in missing
                       and (r["name"], r["target_rva"]) not in naked})

    old_sources = {r["source"] for rva in changed for r in old_rows[rva]}
    new_sources = {r["source"] for rva in changed for r in new_rows[rva]}
    old_naked, old_missing = naked_keys(old, rows_for_sources("old", old_sources), old_sources)
    new_naked, new_missing = naked_keys(new, rows_for_sources("new", new_sources), new_sources)
    lost = []
    for rva in changed:
        before = clean_sources(rva, old_rows, old_naked, old_missing)
        if before and not clean_sources(rva, new_rows, new_naked, new_missing):
            lost.append((rva, old_rows[rva][0]["name"], ", ".join(before),
                         ", ".join(sorted({r["source"] for r in new_rows[rva]}))))
    return lost


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__.strip().splitlines()[2].strip())
    old, new = sys.argv[1], sys.argv[2]
    # Rule A and Rule C consume the same game/ledger diff. Keep the complete
    # diff in memory once, then let each rule apply its own path filter. Rule B
    # independently uses ledger_blob so its authoritative ledger-state check
    # remains valid for binary, rename, or otherwise unusual Git diffs.
    collected = collect_diff_lines(old, new)
    failed = False
    for path, line in added_lift_lines(old, new, collected):
        failed = True
        print("conversion gate: %s adds a naked/__emit body outside game/gen_small/:\n"
              "    %s" % (path, line), file=sys.stderr)
    if failed:
        print("A lift is not a conversion: it deletes the C++ this project exists to\n"
              "produce and moves progress.py C++ exact by +0. Convert to real C++, or\n"
              "leave the .asm dump alone (codegen blockers: game/masm_dumps/*.asm).",
              file=sys.stderr)
    run_a3, run_a5 = outside_work(old, new, collected)
    for path, name, hit in added_outside_includes(old, new, collected) if run_a3 else ():
        failed = True
        print("conversion gate: %s adds an include of \"%s\", which reaches %s: an\n"
              "emit outside game/ and inputs/reference/shims/ is never judged where it is\n"
              "written. Copy what you need into game/ as C++." % (path, name, hit),
              file=sys.stderr)
    for path in added_symlinks(old, new):
        failed = True
        print("conversion gate: %s is a symlink. game/ and inputs/reference/shims/ hold\n"
              "real files only: the gate cannot judge what a link points at." % path,
              file=sys.stderr)
    for hit in reach_growth(old, new) if run_a5 else ():
        failed = True
        print("conversion gate: %s now holds an emit and is reached from the includes of\n"
              "game/ or inputs/reference/shims/ files, which it was not before. An emit\n"
              "outside those trees is never judged where it is written; write the code in\n"
              "game/ as C++." % hit, file=sys.stderr)
    for path, signature in added_asm_only_bodies(old, new, collected):
        failed = True
        print("conversion gate: %s adds a function whose whole body is __asm:\n"
              "    %s\nMnemonic inline asm is a lift like __emit; convert it to C++, or put a "
              "proven codegen blocker in game/masm_dumps/*.asm." % (path, signature),
              file=sys.stderr)
    for offence in gen_asm_offences(old, new, collected):
        failed = True
        print("conversion gate: " + offence, file=sys.stderr)
    for rva, name, old_src, new_src in clean_coverage_lost(old, new):
        failed = True
        print("conversion gate: %s (%s) was clean C++ at %s, repointed to %s.\n"
              "C++ exact never goes backward: retract the row in its own commit if the\n"
              "claim is wrong; never swap a dump under a live claim."
              % (rva, name, old_src, new_src), file=sys.stderr)
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
