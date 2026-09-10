#!/usr/bin/env python3
"""Land a CSV wave of ledger rows as one proved, all-or-nothing transaction.

`gen_small.py land` proves one generated batch that it just emitted itself.
This is the same transaction with the batch supplied from outside, so any
deterministic mechanism (`tools/wave_accounting.py wave --mech A`, a funclet
sweep, a library attach) can hand it rows without growing a fourth copy of the
append/retract/revert code. Every ledger primitive below is imported from
gen_small — `validate_rows`, `retract_dump_rows`, `load_pins`, `format_row`,
`line_terminator` — because a second implementation of a retraction is how a
dump row comes back from the dead on somebody else's rebase.

Input CSV columns
  name,rva,size,source,notes            required
  alt1_source,alt1_notes, alt2_...      optional: owners to retry a row on

`--pins` takes a companion `name,address,notes` CSV appended to
reverse/symbols.csv in the same transaction.

Per attempt the transaction is exactly gen_small.land_batch's:

  reverse/.add_match.lock  (held across the WHOLE wave, not per attempt, so a
                            concurrent single-row append cannot slip between a
                            failed gate and its revert)
  byte snapshot of functions.csv, symbols.csv, deleted_rows.csv
  validate_rows            refuses a double claim; only a lone gen-dump row of
                           the exact range may be superseded, and dumpness is
                           that NOTE, never a directory
  retract_dump_rows        drops each superseded dump and tombstones it
  binary append            CRLF rows, symbols.csv's own terminator for pins
  git add                  a row's source must be in git or check_csv rejects it
  ./build.sh <sources> && tools/check_csv.py
  on ANY failure from retract_dump_rows onward — a gate verdict, a lost
  .git/index.lock under `git add`, a KeyboardInterrupt — all three ledgers are
  restored byte for byte before the error leaves this module. The guard has to
  open at the first WRITE, not at the gate: a tombstone that outlives an aborted
  run deletes that dump off every other clone on the next union merge.

Recovery. A wave is wide, and one TU in it can be unprovable for reasons that
have nothing to do with the other nineteen rows — a deterministic C1001 in that
source, or a row somebody else landed there that no longer verifies. When the
gate fails, the failing source or row is read out of the gate's own output —
off a line that is ITSELF a failure, because the gate prints the name of a row
it just proved too — and those rows leave the wave (to their next `altN_source`
if the CSV named one, otherwise to build/land_wave_dropped.csv with the gate
text that condemned them), and the remainder is attempted again from a clean
ledger. A drop is
always printed and always reported; the exit status is nonzero whenever
anything was dropped, so no caller can read a partial wave as a full one.

If the gate fails while naming NONE of this wave's rows or sources, that is not
a routable failure: the run stops with the ledger untouched rather than
guessing which rows to sacrifice.
"""
import argparse
import collections
import csv
import datetime
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import gen_small as G
from add_match import parse_ledger
from portable_lock import lock, unlock

ROOT = B.ROOT
DROPPED_REPORT = ROOT / "build" / "land_wave_dropped.csv"
DROPPED_COLUMNS = ["dropped_at", "wave", "name", "rva", "size", "source", "notes", "reason"]
REQUIRED_COLUMNS = ("name", "rva", "size", "source", "notes")
ALT_SOURCE_RE = re.compile(r"^alt(\d+)_source$")

# The three shapes the gate uses to name what it could not prove.
COMPILE_FAILED_RE = re.compile(r"^compile failed: (\S+)$", re.M)
ROW_FAILED_RE = re.compile(r"^\s+FAIL (\S+) \((\S+)\)\s*$", re.M)
SOURCE_CLAIM_RE = re.compile(r"^ {4}(Code/\S+?): ", re.M)
OBJECT_SYMBOL_RE = re.compile(r"(?:^|;)object-symbol=([^;]+)")
# A line may only condemn a row if the line is itself a failure. build.py prints
# "  <name> ({source})" for a row it just PROVED (build.py:1213, the one-row OK
# case), so a bare mention is not evidence. These are the shapes that are:
# check_csv renders every problem as "  - <text>", build.py prints FAIL/ERROR,
# and an uncaught exception's last line is "SomeError: <text>".
GATE_FAILURE_LINE_RE = re.compile(
    r"^\s+- |\bFAIL\b|\bERROR\b|^\w*(?:Error|Exception): |\bnot found\b")


class WaveRow:
    """One row and the ordered list of owners it may be claimed on."""

    def __init__(self, name, rva, size, owners, line):
        self.name, self.rva, self.size, self.owners, self.line = name, rva, size, owners, line
        self.owner = 0

    @property
    def source(self):
        return self.owners[self.owner][0]

    @property
    def notes(self):
        return self.owners[self.owner][1]

    def next_owner(self):
        """Move to the next alternate owner; False when this row is out of them."""
        if self.owner + 1 >= len(self.owners):
            return False
        self.owner += 1
        return True

    def where(self):
        return f"{self.name} @0x{self.rva:08X}/{self.size}B ({self.source})"


# --------------------------------------------------------------------------
# input
# --------------------------------------------------------------------------

def read_wave(path):
    with Path(path).open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle)
        columns = reader.fieldnames or []
        missing = [c for c in REQUIRED_COLUMNS if c not in columns]
        if missing:
            raise SystemExit(f"land_wave: {path} is missing column(s) {', '.join(missing)}; "
                             f"it has {', '.join(columns) or '(no header)'}")
        alts = sorted((int(m.group(1)), m.group(0)) for m in
                      (ALT_SOURCE_RE.match(c) for c in columns) if m)
        for index, column in alts:
            if f"alt{index}_notes" not in columns:
                raise SystemExit(f"land_wave: {path} has {column} but no alt{index}_notes — "
                                 "an alternate owner without its notes cannot be landed")
        rows, by_name, by_rva = [], {}, {}
        for line, record in enumerate(reader, start=2):
            row = parse_record(record, alts, path, line)
            if row.name in by_name:
                raise SystemExit(f"land_wave: {path} line {line}: {row.name} is already "
                                 f"claimed on line {by_name[row.name]}")
            if row.rva in by_rva:
                raise SystemExit(f"land_wave: {path} line {line}: 0x{row.rva:08X} is already "
                                 f"claimed on line {by_rva[row.rva]}")
            by_name[row.name], by_rva[row.rva] = line, line
            rows.append(row)
    if not rows:
        raise SystemExit(f"land_wave: {path} holds no rows — nothing to land")
    # validate_rows overlaps a batch against the LEDGER, never against itself, so
    # two wave rows straddling the same bytes reach the gate and come back as a
    # check_csv problem nobody can attribute. Same start and same end cannot occur
    # here — a duplicate rva is already refused above — so any overlap is a defect.
    ordered = sorted(rows, key=lambda row: row.rva)
    for first, second in zip(ordered, ordered[1:]):
        if second.rva < first.rva + first.size:
            raise SystemExit(
                f"land_wave: {path} lines {first.line} and {second.line} claim overlapping "
                f"ranges: {first.name} [0x{first.rva:08X}, 0x{first.rva + first.size:08X}) and "
                f"{second.name} [0x{second.rva:08X}, 0x{second.rva + second.size:08X}). "
                "One of the two extents is wrong; nothing was changed.")
    return rows


def parse_record(record, alts, path, line):
    def field(column):
        value = (record.get(column) or "").strip()
        if not value:
            raise SystemExit(f"land_wave: {path} line {line}: column {column} is empty")
        return value

    name = field("name")
    try:
        rva = int(field("rva"), 16)
    except ValueError:
        raise SystemExit(f"land_wave: {path} line {line} ({name}): rva "
                         f"{record['rva']!r} is not hexadecimal")
    try:
        size = int(field("size"))
    except ValueError:
        raise SystemExit(f"land_wave: {path} line {line} ({name}): size "
                         f"{record['size']!r} is not an integer")
    if size <= 0:
        raise SystemExit(f"land_wave: {path} line {line} ({name}): size {size} is not positive")
    owners = [(field("source"), field("notes"))]
    for index, column in alts:
        source = (record.get(column) or "").strip()
        notes = (record.get(f"alt{index}_notes") or "").strip()
        if not source:
            continue
        if not notes:
            raise SystemExit(f"land_wave: {path} line {line} ({name}): {column} is set but "
                             f"alt{index}_notes is empty")
        owners.append((source, notes))
    return WaveRow(name, rva, size, owners, line)


def read_pins(path):
    pins = []
    with Path(path).open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle)
        for column in ("name", "address", "notes"):
            if column not in (reader.fieldnames or []):
                raise SystemExit(f"land_wave: {path} is missing the {column} column; a pins CSV "
                                 "is name,address,notes like reverse/symbols.csv")
        for line, record in enumerate(reader, start=2):
            try:
                address = int(record["address"], 16)
            except ValueError:
                raise SystemExit(f"land_wave: {path} line {line}: address "
                                 f"{record['address']!r} is not hexadecimal")
            pins.append(G.format_pin(record["name"].strip(), address,
                                     (record.get("notes") or "").strip()))
    return pins


# --------------------------------------------------------------------------
# the transaction
# --------------------------------------------------------------------------

Attempt = collections.namedtuple("Attempt", "ok appended already_landed retracted pins output")


def snapshot():
    functions_raw = B.FUNCTIONS.read_bytes()
    if b"\r\n" not in functions_raw[:200]:
        raise SystemExit("land_wave: functions.csv has lost its CRLF line endings — "
                         "restore it from git before landing anything")
    if not functions_raw.endswith(b"\n"):
        raise SystemExit("land_wave: functions.csv does not end with a newline "
                         "(truncated last row?) — repair it before landing anything")
    return functions_raw, B.SYMBOLS.read_bytes(), G.DELETED.read_bytes()


def restore(snap):
    functions_raw, symbols_raw, deleted_raw = snap
    B.FUNCTIONS.write_bytes(functions_raw)
    B.SYMBOLS.write_bytes(symbols_raw)
    G.DELETED.write_bytes(deleted_raw)


def check_against_ledger(rows, ledger_rows):
    """A name already in the ledger must agree with the wave on rva, size AND source.

    validate_rows treats a name whose (rva, source) already match as idempotent
    and skips it without ever looking at the size — correct for a re-run of the
    batch that landed it, wrong for a wave CSV that disagrees about how long the
    body is. That disagreement is a defect in whatever produced the wave, so it
    stops the run instead of being routed around.
    """
    ledger = {}
    for row in ledger_rows:
        ledger.setdefault(row["name"], row)
    for row in rows:
        held = ledger.get(row.name)
        if held is None or (held["rva"], held["size"], held["source"]) == \
                (row.rva, row.size, row.source):
            continue
        raise SystemExit(
            f"land_wave: wave line {row.line}: {row.name} is already in functions.csv at "
            f"0x{held['rva']:08X}/{held['size']}B ({held['source']}, functions.csv line "
            f"{held['line']}), but this wave claims 0x{row.rva:08X}/{row.size}B "
            f"({row.source}). One of them is wrong; nothing was changed.")


def attempt(rows, pins):
    """Append, prove, and either keep or byte-restore every ledger this touched."""
    snap = snapshot()
    functions_raw, symbols_raw, _ = snap

    ledger_rows = parse_ledger(functions_raw)
    check_against_ledger(rows, ledger_rows)
    selectors = sorted({row.source for row in rows})
    for rel in selectors:
        # Checked here, before a single byte is appended: build.py would abort with
        # "functions.csv references missing source file(s)" halfway through the
        # transaction, and a wave CSV naming a source that is not on disk is a
        # defect in whatever wrote it, not something to route around.
        if not (ROOT / rel).exists():
            raise SystemExit(f"land_wave: {rel} does not exist — a wave row cannot name a "
                             "source that is not in the tree. Nothing was changed.")
    by_text = {}
    for row in rows:
        text = G.format_row(row.name, row.rva, row.size, row.source, row.notes)
        if text in by_text:
            raise SystemExit(f"land_wave: wave lines {by_text[text].line} and {row.line} format "
                             f"to the same ledger row ({text}); nothing was changed")
        by_text[text] = row
    to_append, landed_count, to_retract = G.validate_rows(list(by_text), ledger_rows)
    appending = set(to_append)
    appended_rows = [by_text[text] for text in to_append]
    already_rows = [row for text, row in by_text.items() if text not in appending]
    if len(already_rows) != landed_count:
        raise SystemExit(f"land_wave: validate_rows reported {landed_count} already-landed "
                         f"row(s) but withheld {len(already_rows)} of this wave's {len(rows)}; "
                         "the two disagree, so nothing was changed")

    pinned = G.load_pins()
    new_pins = []
    for pin in pins:
        name, address = pin.split(",")[0], int(pin.split(",")[1], 16)
        if pinned.get(name) == address:
            continue
        if name in pinned:
            raise SystemExit(f"land_wave: {name} is pinned at 0x{pinned[name]:08X}, this wave "
                             f"wants 0x{address:08X} — nothing was changed")
        new_pins.append(pin)

    if not to_append and not new_pins:
        print(f"land_wave: nothing to append — all {len(rows)} row(s) are already in "
              "functions.csv exactly as this wave states them; NO gate was run")
        return Attempt(True, [], already_rows, 0, 0, "")

    staged = []

    def revert(reason):
        restore(snap)
        for rel in staged:
            result = G.git("rm", "--cached", "--quiet", "--", rel)
            if result.returncode != 0:
                print(f"land_wave: could NOT un-stage {rel} (git rm --cached exit "
                      f"{result.returncode}) — it is still in the index; run "
                      f"`git reset -- {rel}` before committing anything", file=sys.stderr)
        print(f"land_wave: {reason} — {len(to_append)} row(s), {len(new_pins)} pin(s), "
              f"{len(to_retract)} retraction(s)"
              + (f" and {len(staged)} staged source(s)" if staged else "")
              + " REVERTED (ledgers restored byte for byte)", file=sys.stderr)

    # The guard opens at the FIRST write, not at the gate: retract_dump_rows
    # rewrites functions.csv and appends a tombstone to deleted_rows.csv, and a
    # tombstone that survives an abort deletes that dump off every other clone on
    # the next union merge. Anything between here and the gate's verdict — a lost
    # .git/index.lock under stage_sources, ENOSPC on the 18 MB append — has to
    # land in revert(), or the ledgers stay mutated with nothing to restore them.
    try:
        if to_retract:
            G.retract_dump_rows(functions_raw, to_retract)
        with B.FUNCTIONS.open("ab") as handle:
            handle.write(b"".join(row.encode("utf-8") + b"\r\n" for row in to_append))
        if new_pins:
            # Asked for HERE, not at the top of the transaction: line_terminator
            # refuses a symbols.csv that mixes CRLF and LF, and the shared ledger
            # does mix them — agents append pins with whichever their tool wrote.
            # A wave carrying no pins never writes that file, so demanding the
            # file be uniform before it could matter blocked every pinless wave
            # on damage none of them would have touched. Repairing it is not the
            # alternative: symbols.csv is merge=union, so rewriting a line that
            # another clone still holds in the old spelling gives the next rebase
            # BOTH spellings of the same pin.
            symbols_eol = G.line_terminator(symbols_raw, "symbols.csv")
            with B.SYMBOLS.open("ab") as handle:
                handle.write(b"".join(pin.encode("utf-8") + symbols_eol for pin in new_pins))
        stage_sources(selectors, staged)
        print(f"land_wave: appended {len(to_append)} row(s) and {len(new_pins)} pin(s) over "
              f"{len(selectors)} source(s) ({landed_count} already landed, {len(to_retract)} "
              "dump row(s) superseded)")
        code, output = run_streamed([str(ROOT / "build.sh"), *selectors],
                                    "./build.sh " + " ".join(selectors))
        if code == 0:
            code, check_output = run_streamed(
                [sys.executable, str(ROOT / "tools" / "check_csv.py")],
                "python3 tools/check_csv.py")
            output += check_output
    except BaseException as exc:
        revert(f"aborted by {type(exc).__name__}" + (f": {exc}" if str(exc) else ""))
        raise
    if code != 0:
        revert(f"gate failed (exit {code})")
        return Attempt(False, [], [], 0, 0, output)
    print(f"land_wave: verified OK — {len(to_append)} row(s) and {len(new_pins)} pin(s) are live")
    return Attempt(True, appended_rows, already_rows, len(to_retract), len(new_pins), output)


def stage_sources(selectors, staged):
    """check_csv rejects a row whose source is not in git, so stage the new ones.

    Explicit paths only, and only the ones this wave's rows actually name. Each
    path is recorded in the caller's `staged` as it is added, so a failure part
    way through still leaves revert() the exact set to un-stage.
    """
    for rel in selectors:
        if G.git("ls-files", "--error-unmatch", "--", rel).returncode == 0:
            continue
        # Not G.git(check=True): that routes stderr to DEVNULL, so a lost index
        # lock would surface as a bare "exit status 128" with no reason attached.
        result = subprocess.run(["git", "-C", str(ROOT), "add", "--", rel],
                                capture_output=True, text=True)
        if result.returncode != 0:
            raise SystemExit(f"land_wave: git add {rel} failed (exit {result.returncode}): "
                             f"{result.stderr.strip() or '(git printed nothing)'}")
        staged.append(rel)


def run_streamed(command, label):
    """Run `command`, echoing its output live and returning (exit code, text)."""
    print(f"land_wave: {label}", flush=True)
    process = subprocess.Popen(command, cwd=ROOT, stdout=subprocess.PIPE,
                               stderr=subprocess.STDOUT, text=True, bufsize=1)
    lines = []
    for line in process.stdout:
        sys.stdout.write(line)
        sys.stdout.flush()
        lines.append(line)
    process.stdout.close()
    return process.wait(), "".join(lines)


# --------------------------------------------------------------------------
# failure attribution
# --------------------------------------------------------------------------

def attribute(output, rows):
    """{id(row): reason} for every pending row the gate's own output blames.

    Empty means the gate failed for something outside this wave — the caller
    must stop, not guess.
    """
    by_name = {row.name: row for row in rows}
    by_source = collections.defaultdict(list)
    for row in rows:
        by_source[row.source].append(row)
    blamed = {}

    def blame(row, reason):
        blamed.setdefault(id(row), (row, reason))

    for source in COMPILE_FAILED_RE.findall(output):
        for row in by_source.get(source, ()):
            blame(row, f"{source} failed to compile")
    for name, source in ROW_FAILED_RE.findall(output):
        if name in by_name:
            blame(by_name[name], f"byte comparison failed for {name} in {source}")
        else:
            for row in by_source.get(source, ()):
                blame(row, f"{source} already carries a row the gate cannot prove ({name}); "
                           "this wave cannot be verified there")
    if "Source claims: FAIL" in output:
        for source in SOURCE_CLAIM_RE.findall(output):
            for row in by_source.get(source, ()):
                blame(row, f"{source} fails the source-claims gate")
    if not blamed:
        # Nothing named a source, so fall back on the two mangled symbols only this
        # row can be blamed through: its own ledger name (how check_csv reports a
        # bad row) and the COFF symbol its notes aim the comparison at (how a
        # mistyped object-symbol= surfaces — `symbol not found in object: ...`,
        # raised before build.py can name the row it came from). Both are unique
        # decorated names — but only on a line that is itself a failure. build.py
        # prints "  <name> (<source>)" for a row it just PROVED, so matching on any
        # mention would let a green verify_functions condemn its own row when the
        # run failed somewhere else entirely.
        for line in output.splitlines():
            if not GATE_FAILURE_LINE_RE.search(line):
                continue
            for row in rows:
                if any(token in line for token in gate_identity(row)):
                    blame(row, f"named by the gate: {line.strip()}")
    return blamed


def gate_identity(row):
    """The decorated names the gate can refer to this row by."""
    match = OBJECT_SYMBOL_RE.search(row.notes)
    return (row.name, match.group(1)) if match else (row.name,)


# --------------------------------------------------------------------------
# driver
# --------------------------------------------------------------------------

def record_drops(dropped, wave_path):
    if not dropped:
        return
    DROPPED_REPORT.parent.mkdir(parents=True, exist_ok=True)
    new = not DROPPED_REPORT.exists()
    stamp = datetime.datetime.now().isoformat(timespec="seconds")
    with DROPPED_REPORT.open("a", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, DROPPED_COLUMNS, lineterminator="\n")
        if new:
            writer.writeheader()
        for row, reason in dropped:
            writer.writerow({"dropped_at": stamp, "wave": wave_path, "name": row.name,
                             "rva": f"0x{row.rva:08X}", "size": row.size,
                             "source": row.source, "notes": row.notes, "reason": reason})


def land(rows, pins, wave_path, max_attempts):
    """-> (appended rows, already-held rows, [(row, reason)] dropped).

    Appended and already-held are reported apart because only the first is a
    delta this run moved. Holds the ledger lock throughout.
    """
    handle = G.LOCK_FILE.open("a")
    lock(handle, exclusive=True,
         wait_notice="land_wave: waiting for ledger lock (another append is running)...")
    dropped, pending = [], list(rows)
    try:
        for attempt_no in range(1, max_attempts + 1):
            print(f"\nland_wave: attempt {attempt_no} — {len(pending)} row(s), "
                  f"{sum(row.size for row in pending):,d} byte(s)")
            result = attempt(pending, pins)
            if result.ok:
                return result.appended, result.already_landed, dropped
            blamed = attribute(result.output, pending)
            if not blamed:
                raise SystemExit(
                    f"land_wave: the gate failed but named none of this wave's {len(pending)} "
                    f"row(s) or {len({r.source for r in pending})} source(s). The ledgers are "
                    "byte-identical to before the run and nothing was dropped — read the gate "
                    "output above; this is not a failure the lander can route around.")
            keep = []
            for row in pending:
                entry = blamed.get(id(row))
                if entry is None:
                    keep.append(row)
                elif row.next_owner():
                    print(f"land_wave: RETRY {row.name} @0x{row.rva:08X} on alternate owner "
                          f"{row.source} — {entry[1]}")
                    keep.append(row)
                else:
                    print(f"land_wave: DROP {row.where()} — {entry[1]}", file=sys.stderr)
                    dropped.append((row, entry[1]))
            pending = keep
            if not pending:
                return [], [], dropped
        raise SystemExit(f"land_wave: gave up after {max_attempts} attempts with "
                         f"{len(pending)} row(s) still unproved; the ledgers are byte-identical "
                         "to before the run. Raise --max-attempts only if the drops above show "
                         "real progress each round.")
    finally:
        # In the finally, not on the way out: a wave that exhausts --max-attempts
        # leaves through SystemExit, and rows already dropped by then are exactly
        # the ones somebody has to go read.
        record_drops(dropped, wave_path)
        unlock(handle)
        handle.close()


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("wave", help="wave CSV: name,rva,size,source,notes[,altN_source,...]")
    parser.add_argument("--pins", help="companion name,address,notes CSV for reverse/symbols.csv")
    parser.add_argument("--max-attempts", type=int, default=8,
                        help="give up after this many gate rounds (default 8)")
    args = parser.parse_args(argv)

    rows = read_wave(args.wave)
    pins = read_pins(args.pins) if args.pins else []
    print(f"land_wave: {args.wave} — {len(rows)} row(s), {sum(r.size for r in rows):,d} byte(s) "
          f"over {len({r.source for r in rows})} source(s), {len(pins)} pin(s)")

    try:
        appended, already, dropped = land(rows, pins, args.wave, args.max_attempts)
    except G.FormatError as exc:
        # A malformed field or a double claim is a defect in whatever wrote the
        # wave, caught before a single byte was appended. Routing around it would
        # bury the defect; the whole wave stops.
        raise SystemExit(f"land_wave: this wave conflicts with the ledger — {exc}. "
                         "Nothing was changed.")

    print(f"\nland_wave: appended and proved {len(appended)} row(s), "
          f"{sum(r.size for r in appended):,d} byte(s) over "
          f"{len({r.source for r in appended})} source(s)")
    if already:
        # Never folded into the figure above: those rows were in functions.csv
        # before this run, so counting them as landed reports a progress delta this
        # run did not move — and when every row is already held no gate ran at all.
        print(f"land_wave: {len(already)} row(s), {sum(r.size for r in already):,d} byte(s) "
              "were already in functions.csv before this run — NOT part of that figure")
    if dropped:
        print(f"land_wave: dropped {len(dropped)} row(s), "
              f"{sum(r.size for r, _ in dropped):,d} byte(s) — reported in "
              f"{DROPPED_REPORT.relative_to(ROOT)}:", file=sys.stderr)
        for row, reason in dropped:
            print(f"  {row.where()}: {reason}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
