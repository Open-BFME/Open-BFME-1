"""Shared plumbing for the nightly audit (tools/audit/): repo profile, git, ledgers, state.

The same tools/audit/ tree ships in Open-BFME-1 and Open-BFME-2; the only
difference between the repos is detected here from the layout (BFME1 keeps its
ledgers under targets/game/reverse/, BFME2 under reverse/).

Everything the audit writes goes under the state directory (AUDIT_STATE, default
build/audit/), never into tracked files: the audit is advisory and must not
change what the gate or the fleets see.
"""
import csv
import hashlib
import io
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(os.environ.get("AUDIT_ROOT") or Path(__file__).resolve().parents[2])
BFME1 = (ROOT / "targets" / "game" / "reverse").is_dir()
REPO = "bfme1" if BFME1 else "bfme2"
REV = "targets/game/reverse" if BFME1 else "reverse"
LEDGER = f"{REV}/functions.csv"
SYMBOLS = f"{REV}/symbols.csv"
LINK_STATUS = f"{REV}/link_status.csv"
CANONICAL = f"{REV}/canonical_classes.csv"
SOURCE_PREFIX = "game/" if BFME1 else "Code/"
SOURCE_EXT = (".cpp", ".c", ".h", ".hpp", ".inl")
STATE = Path(os.environ.get("AUDIT_STATE") or ROOT / "build" / "audit")
REF = os.environ.get("AUDIT_REF", "origin/master")
PY = [sys.executable]

# A name that is an address, not an identity: Rva00285708Host, rva0025E406,
# sub_00401000, FUN_00401000, g_rva00A1B2C3.
ADDRESS_NAME = re.compile(r"(?i)(?:rva|sub_|fun_|dat_|loc_|_0x)[0-9a-f]{6,8}")


def git(*args, check=True, cwd=None):
    proc = subprocess.run(["git", *args], cwd=cwd or ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")
    if check and proc.returncode:
        raise RuntimeError(f"git {' '.join(args)}: {proc.stderr.strip()}")
    return proc.stdout


def show(rev, path):
    """File text at a revision, or None when the path does not exist there."""
    proc = subprocess.run(["git", "show", f"{rev}:{path}"], cwd=ROOT, capture_output=True)
    if proc.returncode:
        return None
    return proc.stdout.decode("utf-8", errors="replace")


def read_rows(text):
    if not text:
        return []
    return list(csv.DictReader(io.StringIO(text)))


def ledger_at(rev=None):
    if rev is None:
        path = ROOT / LEDGER
        return read_rows(path.read_text(encoding="utf-8", errors="replace")) if path.exists() else []
    return read_rows(show(rev, LEDGER))


def parse_rva(text):
    try:
        return int(str(text).strip(), 16)
    except (TypeError, ValueError):
        return None


def is_source(path):
    return path.startswith(SOURCE_PREFIX) and path.lower().endswith(SOURCE_EXT)


def short_name(mangled):
    """Best-effort readable name of a ledger row: ?f@C@@... -> C::f, ??0C@@ -> C::C."""
    name = mangled or ""
    if name.startswith("??0") or name.startswith("??1"):
        cls = name[3:].split("@", 1)[0]
        return f"{cls}::{'~' if name[2] == '1' else ''}{cls}"
    if name.startswith("?") and not name.startswith("??"):
        parts = name[1:].split("@@", 1)[0].split("@")
        return "::".join(reversed(parts)) if parts and parts[0] else name
    return name.lstrip("_")


def leaf_name(mangled):
    return short_name(mangled).split("::")[-1].lstrip("~")


def digest(*parts, n=12):
    return hashlib.sha256("\x1f".join(str(p) for p in parts).encode()).hexdigest()[:n]


def load_json(path, default):
    try:
        return json.loads(Path(path).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return default


def save_json(path, data):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(path.suffix + ".tmp")
    tmp.write_text(json.dumps(data, indent=1, sort_keys=True), encoding="utf-8")
    os.replace(tmp, path)


def append_jsonl(path, record):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a", encoding="utf-8") as fh:
        fh.write(json.dumps(record, sort_keys=True) + "\n")


def read_jsonl(path):
    try:
        lines = Path(path).read_text(encoding="utf-8").splitlines()
    except OSError:
        return []
    return [json.loads(line) for line in lines if line.strip()]
