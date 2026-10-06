#!/usr/bin/env python3
"""Build a publisher fixture set (fixtures.json + one patch per case) on a revision.

`publisher.py promote` refuses a checker without exploit fixtures (cases that
must be rejected) and benign controls (cases that must pass). Patches made
once go stale as master moves, so the set is generated from case files right
before a promotion: every case is a list of edits applied to the revision, and
a `replace` whose text is gone fails here, loudly, instead of silently
testing nothing.

cases.json: [{"name", "expect": "reject"|"pass", "why", "message",
             "edits": [{"path", "write": TEXT} | {"path", "append": TEXT} |
                       {"path", "old": TEXT, "new": TEXT}]}]

  python3 tools/publisher_fixtures/make_fixtures.py tools/publisher_fixtures/bfme1/cases.json OUT [--rev origin/master]
  python3 tools/publisher.py promote --state S <sha> --fixtures OUT
"""
import argparse
import json
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def git(*args, cwd, env=None):
    got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, env=env)
    if got.returncode:
        raise RuntimeError(f"git {' '.join(args)}: {got.stderr.decode(errors='replace').strip()}")
    return got.stdout


def build(cases_path, out, rev="HEAD", repo="."):
    cases = json.loads(Path(cases_path).read_text(encoding="utf-8"))
    out = Path(out)
    out.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, GIT_AUTHOR_NAME="fixture", GIT_AUTHOR_EMAIL="",
               GIT_COMMITTER_NAME="fixture", GIT_COMMITTER_EMAIL="",
               GIT_AUTHOR_DATE="2026-10-06T00:00:00Z", GIT_COMMITTER_DATE="2026-10-06T00:00:00Z")
    sha = git("rev-parse", rev, cwd=repo).decode().strip()
    tmp = Path(tempfile.mkdtemp(prefix="pubfix-"))
    try:
        work = tmp / "wt"
        git("clone", "-q", "--shared", "--no-checkout", str(Path(repo).resolve()), str(work), cwd=tmp)
        git("-c", "core.autocrlf=false", "checkout", "-q", "--detach", sha, cwd=work)
        manifest = []
        for case in cases:
            git("reset", "-q", "--hard", sha, cwd=work)
            for edit in case["edits"]:
                path = work / edit["path"]
                if "write" in edit:
                    path.parent.mkdir(parents=True, exist_ok=True)
                    path.write_bytes(edit["write"].encode())
                elif "append" in edit:
                    with path.open("ab") as handle:
                        handle.write(edit["append"].encode())
                else:
                    text = path.read_bytes().decode()
                    if edit["old"] not in text:
                        raise RuntimeError(f"case {case['name']}: {edit['path']} no longer "
                                           f"contains {edit['old'][:60]!r}; update the case")
                    path.write_bytes(text.replace(edit["old"], edit["new"], 1).encode())
                git("add", "--", edit["path"], cwd=work)
            # a fresh scratch clone: the repository's hooks are not installed in it
            git("commit", "-q", "-m", case["message"], cwd=work, env=env)
            (out / f"{case['name']}.patch").write_bytes(
                git("format-patch", "-1", "--stdout", cwd=work, env=env))
            manifest.append(dict(patch=f"{case['name']}.patch", expect=case["expect"],
                                 why=case.get("why", "")))
        (out / "fixtures.json").write_text(json.dumps(manifest, indent=1),
                                           encoding="utf-8")
        (out / "rev.txt").write_text(sha + "\n", encoding="utf-8")
        return manifest
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("cases")
    ap.add_argument("out")
    ap.add_argument("--rev", default="HEAD")
    ap.add_argument("--repo", default=".")
    args = ap.parse_args(argv)
    for case in build(args.cases, args.out, args.rev, args.repo):
        print(f"{case['expect']:7} {case['patch']}  {case['why']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
