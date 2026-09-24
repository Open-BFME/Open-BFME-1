"""verify_pr.sh must not read delta_sources through a process substitution.

`mapfile -t x < <(cmd)` discards cmd's exit status, and `set -e` does not see
it either. A delta_sources crash then yields an empty list, the script prints
"adds no ledger claims" and reports the PR VERIFIED with nothing compared.
.githooks/pre-push documents the same trap and runs the tool to a file first.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
UNCHECKED = re.compile(r"mapfile[^\n]*<\s*<\([^\n]*delta_sources\.py")


def test_verify_pr_checks_the_status_of_delta_sources():
    text = (ROOT / "tools" / "verify_pr.sh").read_text(encoding="utf-8")
    assert not UNCHECKED.search(text), (
        "verify_pr.sh reads delta_sources.py through a process substitution; "
        "its failure would look like an empty delta and the PR would pass")
    # Both invocations, the claim delta and the pin delta, must be guarded.
    guarded = re.findall(r"if ! python3 tools/delta_sources\.py [^\n]*> \"\$\w+\"; then", text)
    assert len(guarded) == 2, guarded
    assert all("--selectors" in command for command in guarded)


def test_the_pattern_is_recognised():
    bad = 'mapfile -t delta < <(python3 tools/delta_sources.py --range "$base" HEAD)'
    assert UNCHECKED.search(bad)
