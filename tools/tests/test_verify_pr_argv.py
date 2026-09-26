"""verify_pr batches exact-row selectors below the Windows argv limit."""
import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest


SCRIPT = Path(__file__).resolve().parents[1] / "verify_pr.sh"


@pytest.fixture
def pr_runner(tmp_path):
    if os.name == "nt":
        git = Path(shutil.which("git") or "")
        candidates = [git.parent.parent / "bin/bash.exe",
                      Path("C:/Program Files/Git/bin/bash.exe")]
        bash = next((str(path) for path in candidates if path.is_file()), None)
    else:
        bash = shutil.which("bash")
    if not bash:
        pytest.skip("Bash is required to exercise verify_pr.sh")

    root = tmp_path / "verify PR fixture with spaces"
    (root / "tools").mkdir(parents=True)
    (root / "game/Caller With Space").mkdir(parents=True)
    (root / "tools/verify_pr.sh").write_bytes(SCRIPT.read_bytes())
    (root / "game/Caller With Space/claim.cpp").touch()
    bindir = root / "bin"
    bindir.mkdir()

    scripts = {
        "git": '''import os, sys
a = sys.argv[1:]
if a == ["rev-parse", "--show-toplevel"]:
    print(os.environ["FIXTURE_ROOT"])
elif a == ["rev-parse", "--abbrev-ref", "HEAD"]:
    print("previous-branch")
elif a == ["fetch", "origin", "master"]:
    pass
elif a == ["checkout", "-q", "previous-branch"]:
    open(os.path.join(os.environ["FIXTURE_ROOT"], "restored"), "w").close()
elif a == ["merge-base", "HEAD", "origin/master"]:
    print("base")
elif a and a[0] == "diff" and "--quiet" in a:
    # The PR changes function rows but does not change the pin ledger or source.
    pass
else:
    print("unexpected git invocation: " + repr(a), file=sys.stderr)
    sys.exit(92)
''',
        "gh": '''import sys
if sys.argv[1:] != ["pr", "checkout", "123"]:
    print("unexpected gh invocation: " + repr(sys.argv[1:]), file=sys.stderr)
    sys.exit(93)
''',
        "python3": '''import os, sys
a = sys.argv[1:]
if a[:1] in (["tools/check_csv.py"], ["tools/conversion_gate.py"], ["tools/target_hooks.py"]):
    pass
elif a[:1] == ["tools/delta_sources.py"]:
    print("source:game/Caller With Space/claim.cpp")
    for i in range(int(os.environ["SELECTOR_COUNT"])):
        print("row:0x%08X:16:?candidate_%04d_%s@@YAXXZ" %
              (0x1000 + i, i, "x" * int(os.environ["NAME_LENGTH"])))
else:
    print("unexpected Python invocation: " + repr(a), file=sys.stderr)
    sys.exit(94)
''',
    }
    for name, body in scripts.items():
        path = bindir / name
        path.write_text(f"#!{sys.executable}\n" + body, encoding="utf-8")
        path.chmod(0o755)

    build = root / "build.sh"
    build.write_text(r'''#!/usr/bin/env bash
set -euo pipefail
n=0
if [ -f build-count ]; then read -r n < build-count; fi
n=$((n + 1))
printf '%s\n' "$n" > build-count
printf '%s\0' "$@" > "build-args-$n"
printf '%s\n' "${BUILD_POOL-unset}" > "build-pool-$n"
if [ "$n" -eq "${FAIL_CHUNK:-0}" ]; then exit 23; fi
''', encoding="utf-8", newline="\n")
    build.chmod(0o755)

    def run(selector_count=240, name_length=140, fail_chunk=0):
        env = dict(os.environ, PATH=f"{bindir}:{os.environ['PATH']}",
                   FIXTURE_ROOT=str(root), SELECTOR_COUNT=str(selector_count),
                   NAME_LENGTH=str(name_length), FAIL_CHUNK=str(fail_chunk),
                   BUILD_POOL="6")
        result = subprocess.run([bash, str(root / "tools/verify_pr.sh"), "123"],
                                cwd=root, env=env, text=True, capture_output=True,
                                encoding="utf-8", timeout=60)
        records = sorted(root.glob("build-args-*"),
                         key=lambda path: int(path.name.rsplit("-", 1)[1]))
        chunks = [path.read_bytes().split(b"\0")[:-1] for path in records]
        return result, chunks, root

    return run


def test_many_exact_rows_are_verified_once_in_bounded_chunks(pr_runner):
    result, chunks, root = pr_runner()
    expected = [b"source:game/Caller With Space/claim.cpp"] + [
        ("row:0x%08X:16:?candidate_%04d_%s@@YAXXZ" %
         (0x1000 + i, i, "x" * 140)).encode("utf-8")
        for i in range(240)
    ]
    assert result.returncode == 0, result.stderr
    assert len(chunks) > 1
    flattened = [selector for chunk in chunks for selector in chunk]
    assert len(flattened) == len(expected)
    assert set(flattened) == set(expected)
    for chunk in chunks:
        assert chunk
        assert sum(2 * len(selector) + 3 for selector in chunk) <= 24000
        command = subprocess.list2cmdline(
            ["p" * 1000, "s" * 1000] + [selector.decode("utf-8") for selector in chunk])
        assert len(command.encode("utf-16-le")) // 2 < 32767
    assert all((root / f"build-pool-{index}").read_text().strip() == "6"
               for index in range(1, len(chunks) + 1))
    assert "240 exact row(s) and 1 source claim(s)" in result.stdout
    assert "PR #123 VERIFIED" in result.stdout


def test_failed_chunk_stops_and_restores_previous_branch(pr_runner):
    result, chunks, root = pr_runner(fail_chunk=2)
    assert result.returncode != 0
    assert len(chunks) == 2
    assert "PR #123 FAILED byte-verification" in result.stderr
    assert "PR #123 VERIFIED" not in result.stdout
    assert (root / "restored").exists()
