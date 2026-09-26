#!/usr/bin/env python3
"""Decompile retail functions with the host's Ghidra, on Windows, Linux or macOS.

The old `ghdec` script was hard-wired to one contributor's Linux paths. This
finds Ghidra and a JDK wherever the host keeps them and runs
tools/ghidra/decompile_function.java against the analyzed project. Output is
identity evidence and a DRAFT of the control flow; AGENTS.md still applies:
decompiled C is never byte-match proof, and Ghidra's invented names and types
are not evidence.

  python tools/ghidra_decompile.py 0x003E8E10 [0xRVA ...]        # print
  python tools/ghidra_decompile.py --out build/ghdec 0x003E8E10   # one file per RVA
  python tools/ghidra_decompile.py --analyze                      # one-time import + analysis (long)

Looked up in this order: $GHIDRA_INSTALL_DIR, inputs/toolchains/ghidra_*; and
$JAVA_HOME, inputs/toolchains/jdk-*, then `java` on PATH. The project lives in
inputs/toolchains/bfme_ghidra (untracked; every host that wants to decompile
analyzes once, hosts that do not still get any exported drafts through git).
"""
import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
PROJECT = ROOT / "inputs/toolchains" / "bfme_ghidra"
EXE = ROOT / "inputs/baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"


def find_ghidra():
    roots = [os.environ.get("GHIDRA_INSTALL_DIR")] + sorted(map(str, (ROOT / "inputs/toolchains").glob("ghidra_*")), reverse=True)
    for root in filter(None, roots):
        launcher = Path(root) / "support" / ("analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless")
        if launcher.exists():
            return launcher
    sys.exit("Ghidra not found: set GHIDRA_INSTALL_DIR or unpack a release under inputs/toolchains/ (tools/ghidra/README.md)")


def java_env():
    env = dict(os.environ)
    homes = [os.environ.get("JAVA_HOME")] + sorted(map(str, (ROOT / "inputs/toolchains").glob("jdk-*")), reverse=True)
    for home in filter(None, homes):
        binary = Path(home) / "bin" / ("java.exe" if os.name == "nt" else "java")
        if binary.exists():
            env["JAVA_HOME"] = str(home)
            env["PATH"] = str(binary.parent) + os.pathsep + env.get("PATH", "")
            return env
    if shutil.which("java"):
        return env
    sys.exit("no JDK found: set JAVA_HOME or unpack a JDK 21 under inputs/toolchains/")


def headless(*args, capture=True):
    command = [str(find_ghidra()), str(PROJECT), "bfme", *args]
    return subprocess.run(command, cwd=ROOT, env=java_env(), capture_output=capture, text=True, errors="replace")


def split_output(text):
    """{rva text: block} from the script's println stream (Ghidra prefixes and
    log noise removed)."""
    lines = [re.sub(r"^INFO  decompile_function\.java> ", "", line).replace(" (GhidraScript)", "")
             for line in text.splitlines()]
    blocks, current = {}, None
    for line in lines:
        start = re.match(r"^RVA (0x[0-9A-Fa-f]+) ", line)
        if start and "falls inside" not in line:
            current = start.group(1).lower()
            blocks[current] = []
        if current and not re.match(r"^(INFO|WARN|ERROR) ", line):
            blocks[current].append(line.rstrip())
    return {rva: "\n".join(body).strip() + "\n" for rva, body in blocks.items()}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("rvas", nargs="*")
    ap.add_argument("--out", type=Path, help="write one <rva>.c file per function into this directory")
    ap.add_argument("--analyze", action="store_true", help="import and analyze the retail image (one time, long)")
    a = ap.parse_args()
    if a.analyze:
        PROJECT.mkdir(parents=True, exist_ok=True)
        sys.exit(headless("-import", str(EXE), "-overwrite", "-analysisTimeoutPerFile", "7200", capture=False).returncode)
    if not a.rvas:
        ap.error("pass at least one RVA, or --analyze")
    if not (PROJECT / "bfme.rep").exists():
        sys.exit(f"no analyzed project at {PROJECT}: run `python tools/ghidra_decompile.py --analyze` once on this host")
    done = headless("-process", EXE.name, "-noanalysis", "-readOnly", "-scriptPath", str(ROOT / "tools" / "ghidra"),
                    "-postScript", "decompile_function.java", *a.rvas)
    blocks = split_output(done.stdout + done.stderr)
    if not blocks:
        sys.exit("Ghidra produced no decompile:\n" + (done.stdout + done.stderr)[-2000:])
    for rva, text in blocks.items():
        if a.out:
            a.out.mkdir(parents=True, exist_ok=True)
            (a.out / f"{int(rva, 16):#010x}.c").write_text(text, encoding="utf-8")
        else:
            print(text)
    if a.out:
        print(f"wrote {len(blocks)} file(s) to {a.out}")


if __name__ == "__main__":
    main()
