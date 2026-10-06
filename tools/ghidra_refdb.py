#!/usr/bin/env python3
"""Read-only Ghidra reference snapshots: one SQLite file per retail binary.

The shared analysed project (BFME1, BFME2 and RotWK in one Ghidra project) is the
best boundary/xref/type evidence the fleets have, but a Ghidra project cannot be
shared: it locks on open and every agent writing into it would make it drift.
So the project is exported once into immutable SQLite snapshots that any number
of agents read concurrently, and names flow back INTO the project only through
`sync-plan`, which admits evidence-tier names and nothing else.

  export   copy the project to a scratch dir (the owner's copy is never opened),
           run tools/ghidra/export_refdb.java headless, load the TSVs
  load     TSV directory -> SQLite (deterministic: sorted rows, content digest)
  verbs    fn, callers, callees, xrefs-to, xrefs-from, strings, switch, type
           -- the typed read interface agents call (JSON on stdout)
  sync-plan   evidence-tier ledger names that differ from the snapshot's names
  sync-apply  apply a sync plan to a CANONICAL project with tools/ghidra/apply_names.java

Snapshots are not committed. They live at build/refdb/<program>.sqlite and are
published as release artifacts `refdb-<program>-<sha12>.sqlite` (docs/agent_tools.md).
A snapshot's `meta.content_sha256` covers every row, so two exports of the same
project state carry the same digest whatever SQLite version wrote the file.

Usage:
  python3 tools/ghidra_refdb.py export --project PATH.gpr --program NAME [--out DB]
  python3 tools/ghidra_refdb.py load TSV_DIR DB
  python3 tools/ghidra_refdb.py fn DB 0x0068AAB0
  python3 tools/ghidra_refdb.py callers DB 0x0068AAB0
  python3 tools/ghidra_refdb.py sync-plan DB [--out plan.tsv]
"""
import argparse
import csv
import glob
import hashlib
import json
import os
import re
import shutil
import sqlite3
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REVERSE = (ROOT / "targets" / "game" / "reverse"
           if (ROOT / "targets" / "game" / "reverse").is_dir() else ROOT / "reverse")
DEFAULT_OUT = ROOT / "build" / "refdb"
SCHEMA_VERSION = 1

# (table, tsv, columns, primary order). Column order is the TSV field order.
TABLES = [
    ("functions", "functions.tsv",
     ["rva", "size", "max_rva", "ranges", "name", "source", "thunk", "convention", "signature"],
     "rva"),
    ("xrefs", "xrefs.tsv", ["from_rva", "to_rva", "kind", "operand", "from_func"],
     "from_rva, to_rva, kind, operand"),
    ("strings", "strings.tsv", ["rva", "length", "type", "value"], "rva"),
    ("data", "data.tsv", ["rva", "length", "type", "label"], "rva"),
    ("switches", "switches.tsv", ["func_rva", "jump_rva", "case_index", "target_rva"],
     "jump_rva, case_index"),
    ("types", "types.tsv", ["path", "ord", "kind", "length", "member", "member_type", "detail"],
     "path, ord, kind, member"),
]
INTEGER = {"size", "ranges", "thunk", "operand", "length", "case_index"}
RVA = {"rva", "max_rva", "from_rva", "to_rva", "from_func", "func_rva", "jump_rva", "target_rva"}


# ----------------------------------------------------------------- load

def _unescape(text):
    return re.sub(r"\\(.)", lambda m: {"t": "\t", "n": "\n", "r": "\r"}.get(m[1], m[1]), text)


def _value(column, text):
    if column in RVA:
        if not text:
            return None
        value = int(text, 16)
        # A reference below the image base (absolute low addresses) is exported as a
        # negative 64-bit offset; keep it negative so it never aliases a real RVA.
        return value - (1 << 64) if value >= 1 << 63 else value
    if column in INTEGER:
        return int(text) if text else None
    return _unescape(text)


def _rows(path, columns):
    if not path.exists():
        return
    with path.open(encoding="utf-8", newline="") as handle:
        for line in handle:
            fields = line.rstrip("\r\n").split("\t")
            if len(fields) != len(columns):
                raise SystemExit(f"{path.name}: expected {len(columns)} fields, got "
                                 f"{len(fields)}: {line[:120]!r}")
            yield tuple(_value(c, f) for c, f in zip(columns, fields))


def load(tsv_dir, db_path):
    """Build the snapshot from export_refdb.java's TSVs. Returns the meta dict."""
    tsv_dir, db_path = Path(tsv_dir), Path(db_path)
    meta = {}
    with (tsv_dir / "meta.tsv").open(encoding="utf-8") as handle:
        for line in handle:
            key, _, value = line.rstrip("\r\n").partition("\t")
            meta[key] = _unescape(value)
    db_path.parent.mkdir(parents=True, exist_ok=True)
    partial = db_path.with_suffix(".partial")
    partial.unlink(missing_ok=True)
    digest = hashlib.sha256()
    db = sqlite3.connect(partial)
    try:
        for table, tsv, columns, order in TABLES:
            db.execute(f"CREATE TABLE {table} ({', '.join(columns)})")
            rows = sorted(_rows(tsv_dir / tsv, columns),
                          key=lambda r: tuple((v is None, v if v is not None else 0) for v in r))
            db.executemany(f"INSERT INTO {table} VALUES ({', '.join('?' * len(columns))})", rows)
            digest.update(table.encode())
            for row in rows:
                digest.update(json.dumps(row).encode())
            meta[f"rows.{table}"] = str(len(rows))
        meta["schema_version"] = str(SCHEMA_VERSION)
        meta["content_sha256"] = digest.hexdigest()
        db.execute("CREATE TABLE meta (key, value)")
        db.executemany("INSERT INTO meta VALUES (?, ?)", sorted(meta.items()))
        for statement in ("CREATE INDEX functions_name ON functions(name)",
                          "CREATE INDEX xrefs_to ON xrefs(to_rva)",
                          "CREATE INDEX xrefs_from ON xrefs(from_rva)",
                          "CREATE INDEX xrefs_func ON xrefs(from_func)",
                          "CREATE INDEX switches_func ON switches(func_rva)",
                          "CREATE INDEX types_path ON types(path)"):
            db.execute(statement)
        db.commit()
        db.execute("VACUUM")
    finally:
        db.close()
    os.replace(partial, db_path)
    return meta


# ----------------------------------------------------------------- export

def _find(env, patterns, what):
    if os.environ.get(env):
        return Path(os.environ[env])
    for pattern in patterns:
        found = sorted(glob.glob(str(pattern)))
        if found:
            return Path(found[-1])
    raise SystemExit(f"{what} not found: set {env} or unpack it under build/toolchains")


def ghidra_home(explicit=None):
    if explicit:
        return Path(explicit)
    return _find("GHIDRA_INSTALL_DIR", [ROOT / "build/toolchains/ghidra_*",
                                        ROOT / "inputs/toolchains/ghidra_*"], "Ghidra")


def java_home(explicit=None):
    if explicit:
        return Path(explicit)
    return _find("JAVA_HOME", [ROOT / "build/toolchains/jdk-*",
                               ROOT / "inputs/toolchains/jdk-*"], "JDK 21")


def headless(ghidra, java, project_dir, project_name, program, script, args, *, read_only):
    launcher = ghidra / "support" / ("analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless")
    command = [str(launcher), str(Path(project_dir).resolve()), project_name, "-process", program,
               "-noanalysis",
               "-scriptPath", str(ROOT / "tools" / "ghidra"), "-postScript", script, *map(str, args)]
    if read_only:
        command.insert(command.index("-noanalysis") + 1, "-readOnly")
    env = dict(os.environ, JAVA_HOME=str(java))
    proc = subprocess.run(command, env=env, capture_output=True, text=True, errors="replace")
    if proc.returncode != 0 or "SCRIPT ERROR" in proc.stdout or "ERROR REPORT" in proc.stdout:
        sys.stderr.write(proc.stdout[-4000:] + proc.stderr[-2000:])
        raise SystemExit(f"analyzeHeadless failed for {program} ({script})")
    return proc


def snapshot_project(gpr):
    """Copy <name>.gpr + <name>.rep into a fresh temp dir and return (dir, name).

    Ghidra takes a lock on the project it opens; the owner's project may be open
    in a GUI or an MCP server, so exports always read a private copy."""
    gpr = Path(gpr)
    work = Path(tempfile.mkdtemp(prefix="refdb-"))
    shutil.copy2(gpr, work / gpr.name)
    shutil.copytree(gpr.with_suffix(".rep"), work / (gpr.stem + ".rep"),
                    ignore=shutil.ignore_patterns("*.lock", "*.lock~"))
    return work, gpr.stem


def export(gpr, program, out=None, *, ghidra=None, java=None, copy=True, keep_tsv=None):
    ghidra, java = ghidra_home(ghidra), java_home(java)
    if copy:
        project_dir, name = snapshot_project(gpr)
    else:
        project_dir, name = Path(gpr).parent, Path(gpr).stem
    tsv = Path(keep_tsv) if keep_tsv else Path(tempfile.mkdtemp(prefix="refdb-tsv-"))
    try:
        headless(ghidra, java, project_dir, name, program, "export_refdb.java", [tsv],
                 read_only=True)
        meta = load(tsv, out or DEFAULT_OUT / f"{program}.sqlite")
    finally:
        if copy:
            shutil.rmtree(project_dir, ignore_errors=True)
        if not keep_tsv:
            shutil.rmtree(tsv, ignore_errors=True)
    return meta


# ----------------------------------------------------------------- verbs

def connect(db_path):
    path = Path(db_path)
    if not path.exists():
        raise SystemExit(f"{path}: no snapshot (python3 tools/ghidra_refdb.py export ...)")
    return sqlite3.connect(f"file:{path.as_posix()}?mode=ro", uri=True)


def _dicts(cursor):
    names = [d[0] for d in cursor.description]
    return [{k: (f"{'-' if v < 0 else ''}0x{abs(v):08X}" if k in RVA and v is not None else v)
             for k, v in zip(names, row)} for row in cursor.fetchall()]


def parse_rva(text):
    return int(text, 16)


def fn(db, key):
    """The function at (or containing) an RVA, or every function with this name."""
    if re.fullmatch(r"(0x)?[0-9A-Fa-f]+", key):
        rva = parse_rva(key)
        rows = _dicts(db.execute(
            "SELECT * FROM functions WHERE rva <= ? AND max_rva >= ? ORDER BY rva DESC LIMIT 1",
            (rva, rva)))
    else:
        rows = _dicts(db.execute("SELECT * FROM functions WHERE name = ? ORDER BY rva", (key,)))
    return rows


def callers(db, rva):
    return _dicts(db.execute(
        "SELECT DISTINCT x.from_func, f.name FROM xrefs x LEFT JOIN functions f ON f.rva = x.from_func "
        "WHERE x.to_rva = ? AND x.kind LIKE '%CALL%' ORDER BY x.from_func", (parse_rva(rva),)))


def callees(db, rva):
    return _dicts(db.execute(
        "SELECT DISTINCT x.to_rva, f.name FROM xrefs x LEFT JOIN functions f ON f.rva = x.to_rva "
        "WHERE x.from_func = ? AND x.kind LIKE '%CALL%' ORDER BY x.to_rva", (parse_rva(rva),)))


def xrefs_to(db, rva):
    return _dicts(db.execute("SELECT * FROM xrefs WHERE to_rva = ? ORDER BY from_rva",
                             (parse_rva(rva),)))


def xrefs_from(db, rva):
    """Every reference made from inside the function at this entry RVA."""
    return _dicts(db.execute("SELECT * FROM xrefs WHERE from_func = ? ORDER BY from_rva",
                             (parse_rva(rva),)))


def strings(db, rva):
    """Strings the function at this entry RVA references."""
    return _dicts(db.execute(
        "SELECT DISTINCT s.rva, s.value FROM xrefs x JOIN strings s ON s.rva = x.to_rva "
        "WHERE x.from_func = ? ORDER BY s.rva", (parse_rva(rva),)))


def switch(db, rva):
    return _dicts(db.execute(
        "SELECT jump_rva, case_index, target_rva FROM switches WHERE func_rva = ? "
        "ORDER BY jump_rva, case_index", (parse_rva(rva),)))


def type_(db, name):
    return _dicts(db.execute(
        "SELECT * FROM types WHERE path = ? OR path LIKE ? ORDER BY path, ord, kind, member",
        (name, f"%/{name}")))


VERBS = {"fn": fn, "callers": callers, "callees": callees, "xrefs-to": xrefs_to,
         "xrefs-from": xrefs_from, "strings": strings, "switch": switch, "type": type_}


# ----------------------------------------------------------------- name sync

PLACEHOLDER = re.compile(
    r"(?i)(?:^|[^A-Za-z])(?:fun|sub|thunk_fun|lab|dat|d|dup|uw|eh|tg|nullsub|loc|j)_[0-9a-f]{4,8}"
    r"|rva[0-9a-f]{4,8}|gen_?[0-9a-f]{3,8}|(?:^|[^a-z])bfme|[0-9A-F]{6,8}")


def placeholder(name):
    return bool(PLACEHOLDER.search(name))


def _csv(path):
    if not path.exists():
        return []
    with path.open(encoding="utf-8", newline="") as handle:
        return list(csv.DictReader(handle))


def evidence_names(reverse=None):
    """{rva: (name, tier)} for names the repo holds on evidence, not on assertion.

    Tiers, strongest first: `export` (the PE export table names it), `ilt` (the
    incremental-link-thunk oracle confirmed it; tools write `ilt-verified=` notes),
    `reloc` (a byte-true call site in matched code proved the mangled name,
    reverse/reloc_names.csv identity=real). A matched ledger row alone is NOT
    evidence: agents choose those names. Placeholders never sync.
    """
    reverse = Path(reverse or REVERSE)
    found = {}

    def offer(rva_text, name, tier):
        if not rva_text or not name or placeholder(name):
            return
        rva = int(rva_text, 16)
        if rva not in found:
            found[rva] = (name, tier)

    for row in _csv(reverse / "exports.csv"):
        if row.get("kind") in ("code", "function", "func") and row.get("section", ".text") == ".text":
            offer(row.get("rva"), row.get("name"), "export")
    for row in _csv(reverse / "functions.csv"):
        if row.get("status") == "matched" and "ilt-verified=" in (row.get("notes") or ""):
            offer(row.get("target_rva"), row.get("name"), "ilt")
    for row in _csv(reverse / "reloc_names.csv"):
        if "identity=real" in (row.get("notes") or ""):
            offer(row.get("target_rva"), row.get("name"), "reloc")
    return found


MANGLED = re.compile(r"^\?(\?[0-9]|\?_[A-Z0-9])?([^@?]*)@((?:[^@?]+@)*)@")


def qualified(name):
    """'A::B::f' for a mangled '?f@B@A@@...' (ctors/dtors included), else the name.

    Ghidra stores demangled, qualified names; an evidence name that demangles to
    the name Ghidra already holds is not a rename."""
    m = MANGLED.match(name)
    if not m:
        return name
    special, base, scopes = m.groups()
    scopes = [s for s in scopes.split("@") if s][::-1]
    if special == "?0":
        base = (base or (scopes[-1] if scopes else "")) if not base else base
        scopes, base = scopes + [base], base
    elif special == "?1":
        scopes, base = scopes + [base], "~" + base
    elif special:
        return name
    return "::".join(scopes + [base])


def sync_plan(db, reverse=None):
    """Rows (rva, current, proposed, tier) where an evidence-tier name differs.

    Only entries of functions Ghidra already has are proposed, and only over a
    placeholder name unless the tier is `ilt`."""
    current = {rva: (name, source) for rva, name, source in
               db.execute("SELECT rva, name, source FROM functions")}
    plan = []
    for rva, (name, tier) in sorted(evidence_names(reverse).items()):
        if rva not in current:
            continue
        have, source = current[rva]
        if have == name or have == qualified(name):
            continue
        # New information only: a name Ghidra already holds from the export table or
        # its demangler is left alone (Ghidra stores it demangled, so the strings
        # differ). Only the ILT oracle may correct a name that is not a placeholder.
        if tier != "ilt" and not (source == "DEFAULT" or placeholder(have)):
            continue
        plan.append((f"0x{rva:08X}", have, name, tier))
    return plan


def write_plan(plan, out):
    with open(out, "w", encoding="utf-8", newline="") as handle:
        for row in plan:
            handle.write("\t".join(row) + "\n")


# ----------------------------------------------------------------- cli

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    e = sub.add_parser("export")
    e.add_argument("--project", required=True, help="path to the analysed <name>.gpr")
    e.add_argument("--program", required=True, action="append",
                   help="program name inside the project (repeatable)")
    e.add_argument("--out-dir", default=str(DEFAULT_OUT))
    e.add_argument("--ghidra"), e.add_argument("--java")
    e.add_argument("--keep-tsv", help="keep the raw TSVs under this directory")
    lo = sub.add_parser("load")
    lo.add_argument("tsv_dir"), lo.add_argument("db")
    for verb in VERBS:
        v = sub.add_parser(verb)
        v.add_argument("db"), v.add_argument("key")
    sp = sub.add_parser("sync-plan")
    sp.add_argument("db"), sp.add_argument("--out"), sp.add_argument("--reverse")
    sa = sub.add_parser("sync-apply")
    sa.add_argument("--project", required=True, help="the CANONICAL project, never a working copy")
    sa.add_argument("--program", required=True), sa.add_argument("--plan", required=True)
    sa.add_argument("--ghidra"), sa.add_argument("--java")
    args = ap.parse_args(argv)

    if args.cmd == "export":
        for program in args.program:
            keep = Path(args.keep_tsv) / program if args.keep_tsv else None
            meta = export(args.project, program, Path(args.out_dir) / f"{program}.sqlite",
                          ghidra=args.ghidra, java=args.java, keep_tsv=keep)
            print(f"{program}: {meta['rows.functions']} functions, {meta['rows.xrefs']} xrefs, "
                  f"content {meta['content_sha256'][:12]}")
    elif args.cmd == "load":
        meta = load(args.tsv_dir, args.db)
        print(json.dumps(meta, indent=2))
    elif args.cmd in VERBS:
        print(json.dumps(VERBS[args.cmd](connect(args.db), args.key), indent=2))
    elif args.cmd == "sync-plan":
        plan = sync_plan(connect(args.db), args.reverse)
        if args.out:
            write_plan(plan, args.out)
        tiers = {}
        for row in plan:
            tiers[row[3]] = tiers.get(row[3], 0) + 1
        print(json.dumps({"renames": len(plan), "by_tier": tiers}, indent=2))
    elif args.cmd == "sync-apply":
        gpr = Path(args.project)
        headless(ghidra_home(args.ghidra), java_home(args.java), gpr.parent, gpr.stem,
                 args.program, "apply_names.java", [Path(args.plan).resolve()], read_only=False)
        print(f"applied {args.plan} to {args.program}")


if __name__ == "__main__":
    main()
