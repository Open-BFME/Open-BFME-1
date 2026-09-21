#!/usr/bin/env python3
"""Write a worker brief from the LIVE ledger, so no worker is ever sent stale work.

Every brief hand-written on 2026-09-02 that listed RVAs from an older report sent
workers to bodies other lanes had already landed. This regenerates the target
list at the moment of writing and drops anything that no longer points at a
dump row, then attaches what the ledger knows per body: size, pins, the latest
attempt's evidence and stash, and the ZH twin when the sweep found one.

  python3 tools/brief.py --dump Code/gen_asm/d_0023c310.asm            > brief.txt
  python3 tools/brief.py --rvas 0x002FDDB0 0x002FC4C0 --note "..."      > brief.txt
  python3 tools/brief.py --csv reverse/zh_sweep/big_identified_worklist.csv --limit 12 > brief.txt

Then launch it with the engine of your choice, e.g.
  grok -p "$(cat brief.txt)" --always-approve --output-format plain
  codex exec -m gpt-5.6-sol --sandbox danger-full-access "$(cat brief.txt)"

Read-only. Writes nothing but stdout.
"""
import argparse
import csv
import json
import re
import sys
import re_log
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

METHOD = """
METHOD. Read AGENTS.md and docs/matching.md first. docs/shape_levers.md is a 97 KB
reference, not reading: open the sections a target's LEVER SECTIONS line names, and
`grep -n "^## " docs/shape_levers.md` for the first divergence you meet. The HISTORY
block under a target is every earlier verdict on it: do not repeat a lever it lists. For each
target: confirm the row still points at a .asm dump or carved boundary (`grep ,0xRVA, reverse/functions.csv reverse/carved.csv`);
grep reverse/symbols.csv and reverse/re_attempts.log for the RVA; use
`python3 tools/vtable_lookup.py <vtable VA>` for owning-class questions; port from the
Zero Hour twin under reference/CnC_Generals_Zero_Hour when one is named. Iterate with
`python3 tools/probe.py SOURCE.cpp "MANGLED" 0xRVA` -- it compiles, diffs against retail
with relocations masked, and prints a CANDIDATE cause with evidence; treat the label as
a hint and check the evidence lines. Land with
`python3 tools/add_match.py NAME 0xRVA SIZE SOURCE --notes "no commas"` (add
`--replace-rva 0xRVA` only when replacing a generated scaffold; carved rows are
ordinary new claims). The command byte-verifies, auto-reverts, and may wait on the
ledger lock -- that is normal. If a body
resists after ~40 minutes bank it:
`python3 tools/re_log.py record SYM 0xRVA SIZE partial "evidence t=Xmin model=MODEL" --stash FILE.cpp --score 0.NN`
and move on.
For a narrow codegen hypothesis, tools/shape_search.py tests explicit C++ alternatives
with a trial/plateau budget; see docs/throughput-tools.md. If the EVIDENCE block says
EH FRAME, run `python3 tools/eh_levers.py SRC.cpp > choices.json` and feed that to
shape_search BEFORE hand-iterating: it tries throw() per callee, /EHsc, _STLP_NO_EXCEPTIONS
and nothrow delete[] mechanically. Read probe's experiment
history before repeating a spelling. Record blocker=NAME for a shared missing
callee/layout and explain what changed before retrying a banked attempt.
For non-EH SIB, register-allocation, call-result-boolean, commutative TEST,
pointer-copy-lifetime, adjacent-store-order, loop-inversion/header,
branch-length/polarity, constant-materialisation, or frame-array residues, run
`python3 tools/shape_family_levers.py SRC.cpp --families sib,register,bool,test,copy,store,loop,branch,constant,frame > choices.json`
and feed the finite choices to shape_search. It is a hypothesis generator only:
the byte gate decides, and the SIB family may remain compiler-internal after all
choices are exhausted.
NAMING. Ask before you invent: `python3 tools/name_oracle.py --class <C> --offset 0x2c`
answers from the ZH<->retail layout witness and the binary's own FieldParse tables, and
`--todo` lists placeholders the evidence can already name. The commit hook REFUSES a
member name that contradicts the witness, and refuses a placeholder you ADD at an offset
the evidence already names -- its message carries the name to use, so there is nothing to
guess. An address-derived name is honest and greps out in a second; a plausible WRONG one
is invisible and no byte gate can see it. So: identity you can PROVE (matched caller,
vtable slot, string literal, ZH twin) -> the real name, cite the evidence. Identity you
cannot prove -> a name describing what the body itself proves, KEEPING the address token
(`FiveDwordElem063700`, not `Rva063700Elem` and not a guessed class name). The address has
to stay UNIQUE, because ICF means one spelling reaches several retail copies; it never has
to be the whole name. Never put a real class's name on a shim whose layout you have not
checked. docs/naming_evidence.md has the detail.
HARD RULES: never run git commands (the orchestrator owns VCS); never run a full ./build.sh;
never edit files under Code/gen_asm/; only touch your assigned bodies; new sources go in
the class's home directory under Code/ with descriptive names.
REPORT at the end: bodies landed (name rva size), partials banked, total bytes.
"""


def load():
    rows = {}
    ledger_rows = list(csv.DictReader(open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace")))
    for r in ledger_rows:
        try:
            rows[int(r["target_rva"], 16)] = r
        except ValueError:
            pass
    import eligibility
    for r in eligibility.carved_rows(rows=ledger_rows):
        rows.setdefault(int(r["target_rva"], 16), r)
    pins = {}
    for r in csv.reader(open(ROOT / "reverse/symbols.csv", newline="", encoding="utf-8", errors="replace")):
        if len(r) > 1 and r[1].startswith("0x"):
            try:
                pins.setdefault(int(r[1], 16), []).append((r[0], r[2] if len(r) > 2 else ""))
            except ValueError:
                pass
    latest = re_log.latest_records(ROOT / "reverse/re_attempts.log")
    near = {}
    mj = ROOT / "build/zh_sweep/match.json"
    if mj.exists():
        try:
            for e in json.load(open(mj)):
                if e.get("bucket") == "near":
                    near.setdefault(e["rva"], e["sym"] + " from " + e["source"])
        except Exception:
            pass
    return rows, pins, latest, near


LEVER_WORDS = {   # blocker family -> words that mark a relevant docs/shape_levers.md heading
    "regalloc": ("register", "lea ", "reload", "caching", "read the member", "operand order", "local"),
    "stack-slot": ("frame", "locals", "slot", "own block", "temporar", "lifetime"),
    "eh": ("cleanup", "lifetime", "destructor", "constructor", "unwind", "exception"),
    "layout": ("member", "accessor", "layout", "aggregate", "base"),
    "codegen-order": ("order", "conjunction", "conditional", "branch", "early return", "switch", "loop"),
    "inline": ("inline", "helper", "accessor"),
    "callee": ("helper", "abi", "thunk", "secondary-base"),
    "identity": ("abi", "deleting-destructor", "visibility"),
    "float": ("float", "matrix", "coordinate"),
    "stl": ("container", "stl", "filter construction"),
}
_history = None
_headings = None


def history(rva):
    """Every live verdict row for one body, oldest first: [(status, evidence)]."""
    global _history
    if _history is None:
        _history = {}
        log = ROOT / "reverse/re_attempts.log"
        if log.exists():
            for line in log.read_text(encoding="utf-8", errors="replace").splitlines():
                fields = line.split("\t")
                if len(fields) < 5 or fields[3] not in re_log.VERDICT_STATUSES:
                    continue
                try:
                    _history.setdefault(int(fields[1], 16), []).append((fields[3], fields[4]))
                except ValueError:
                    pass
    return _history.get(rva, [])


def lever_sections(families, limit=6):
    global _headings
    if _headings is None:
        doc = ROOT / "docs/shape_levers.md"
        _headings = [l[3:].strip() for l in doc.read_text(encoding="utf-8", errors="replace").splitlines()
                     if l.startswith("## ")] if doc.exists() else []
    words = [w for f in families for w in LEVER_WORDS.get(f, ())]
    return [h for h in _headings if any(w in h.lower() for w in words)][:limit]


def digest(rva, depth):
    """What earlier sessions already established, so this one does not pay to
    rediscover it. The brief used to carry the latest verdict cut to 220
    characters and an instruction to go and read the log."""
    import blockers
    rows = history(rva)
    if not rows:
        return []
    counts = {}
    for status, _ in rows:
        counts[status] = counts.get(status, 0) + 1
    scores = [float(m) for _, ev in rows for m in re.findall(r"score=([01](?:\.\d+)?)", ev)]
    families = list(dict.fromkeys(f for _, ev in rows for f in blockers.families(ev)))
    head = f"    HISTORY: {len(rows)} verdict(s) (" + ", ".join(f"{n} {s}" for s, n in counts.items()) + ")"
    if scores:
        head += f"; best author score {max(scores):.2f}"
    if families:
        head += "; blockers named: " + ", ".join(families)
    out = [head]
    shown, seen = rows[-depth:], set()
    for index, (status, ev) in enumerate(shown, len(rows) - len(shown) + 1):
        text = re.sub(r"\s+", " ", ev).strip()
        if text[:120] in seen:       # a re-bank that says the same thing
            continue
        seen.add(text[:120])
        out.append(f"      #{index} {status}: {text[:420]}")
    sections = lever_sections(families)
    if sections:
        out.append("    LEVER SECTIONS (docs/shape_levers.md): " + " | ".join(sections))
    return out


def describe(rva, rows, pins, latest, near, depth=5):
    r = rows[rva]
    parts = [f"- 0x{rva:08X} {r['target_size']}B {r['name']} (dump {Path(r['source']).name})"]
    real = [n for n, _ in pins.get(rva, []) if not re.match(r"^\?(d_|b_|j_|dup_)", n)]
    if real:
        parts.append(f"    pins: {'; '.join(real[:3])}")
    p = latest.get(rva)
    if p and p[3] in ("partial", "blocked"):
        ev = p[4]
        st = re.search(r"stash=(\S+)", ev)
        sc = re.search(r"score=([0-9.]+)", ev)
        parts += digest(rva, depth) or [f"    last attempt ({p[3]}{', score ' + sc.group(1) if sc else ''}): {ev[:220]}"]
        if st and (ROOT / st.group(1)).exists():
            parts.append(f"    START FROM STASH: {st.group(1)}")
    if rva in near:
        parts.append(f"    ZH twin: {near[rva]}")
    from source_donors import lookup
    for donor in lookup(rva, int(r["target_size"])):
        parts.append(f"    Similar operand-shape donor (hypothesis only): {donor['name']} @ {donor['source']}; verify constants/callees independently")
    stash = re_log.stash_for(rva)
    if stash:
        parts.append(f"    PREFERRED STASH: {stash[0].relative_to(ROOT).as_posix()} (author estimate {stash[1]}; verify it)")
        history = ROOT / "reverse/attempt_history" / f"0x{rva:08x}"
        if history.exists():
            parts.append(f"    Saved alternatives: {history.relative_to(ROOT).as_posix()} (immutable source JSON)")
    # mechanical evidence (callees, callers, vtable slot, strings, fields,
    # landed neighbours) so the session does not spend its first half hour
    # re-deriving it from the bytes; never let it break a brief
    try:
        sys.path.insert(0, str(ROOT / "tools/fleet"))
        import context_pack
        parts += ["    " + l for l in context_pack.pack(rva)[1:]]
    except Exception as e:  # noqa: BLE001
        parts.append(f"    (context pack unavailable: {e})")
    return "\n".join(parts)


def picker_note(text):
    lines = text.splitlines()
    for index, line in enumerate(lines):
        if line.startswith("NOTE: "):
            return "\n".join([line[6:]] + lines[index + 1:])
    raise ValueError("class picker produced no NOTE; refusing an incomplete class brief")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dump", help="assign every remaining dump row in this gen_asm file")
    ap.add_argument("--rvas", nargs="*", help="explicit RVAs")
    ap.add_argument("--csv", help="worklist CSV with an 'rva' column")
    ap.add_argument("--limit", type=int, default=30)
    ap.add_argument("--max-size", type=int, default=0,
                    help="--dump only: skip bodies above this many bytes (0 = no cap). "
                         "Bodies over 2,500 B landed 0 of 69 attempts on 2026-09-16.")
    ap.add_argument("--note", default="", help="extra context placed at the top")
    ap.add_argument("--note-file", type=Path, help="picker output: include NOTE and its complete slot table")
    ap.add_argument("--model", default="MODEL", help="model tag for re_log evidence")
    a = ap.parse_args()
    if a.note_file:
        a.note = picker_note(a.note_file.read_text(encoding="utf-8")) + "\n" + a.note

    rows, pins, latest, near = load()
    targets = []
    if a.dump:
        want = a.dump.replace("\\", "/")
        targets = [rva for rva, r in rows.items() if r["source"].replace("\\", "/") == want
                   and (not a.max_size or int(rows[rva]["target_size"] or 0) <= a.max_size)]
        targets.sort(key=lambda v: int(rows[v]["target_size"]))
    if a.rvas:
        targets += [int(x, 16) for x in a.rvas]
    if a.csv:
        for r in csv.DictReader(open(a.csv, newline="")):
            targets.append(int(r["rva"], 16))

    import eligibility
    live, dropped, retired = [], [], []
    for rva in targets:
        r = rows.get(rva)
        if r and (eligibility.is_dump_row(r) or eligibility.is_carved_row(r)):
            p = latest.get(rva)
            # SecuROM post-link bodies (55 89 E5 frames, opaque predicates) can never
            # byte-match clean C++; 32 sessions re-proved that at ~35 min each.
            if a.dump and p and p[3] in ("blocked", "no-match") and "SecuROM" in p[4]:
                continue
            # a dead-end verdict is a finding about the boundary; serving it again
            # is rework in every lane, not just the file lane
            if p and p[3] in re_log.DEAD_END_STATUSES:
                retired.append(rva)
                continue
            if rva not in live:
                live.append(rva)
        else:
            dropped.append(rva)
    live = live[:a.limit]
    if not live:
        sys.exit("brief: no live dump targets (all landed or unknown)")

    out = ["You are a conversion worker in the Open-BFME reverse-engineering repo (run everything from the repo root). "
           "Convert the bodies below into byte-matching C++ (MSVC 7.1), smallest first unless told otherwise."]
    if a.note:
        out.append("CONTEXT: " + a.note)
    if dropped:
        out.append(f"(Already landed by other lanes and removed from this brief: {len(dropped)} body/bodies.)")
    out.append("TARGETS:")
    for rva in live:
        # a one-to-four body brief can afford the last five verdicts per body;
        # a 12-to-40 body brief gets the last two so it stays readable
        out.append(describe(rva, rows, pins, latest, near, depth=5 if len(live) <= 4 else 2))
    out.append(METHOD.replace("model=MODEL", f"model={a.model}"))
    print("\n".join(out))
    print(f"[brief: {len(live)} live target(s), {sum(int(rows[v]['target_size']) for v in live)} bytes; {len(dropped)} dropped as stale; {len(retired)} retired by a dead-end verdict]", file=sys.stderr)


if __name__ == "__main__":
    main()
