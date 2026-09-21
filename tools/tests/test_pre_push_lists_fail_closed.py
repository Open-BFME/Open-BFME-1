"""The pre-push hook must see the exit status of every script that lists what to verify.

`mapfile -t x < <(python3 ...)` discards the script's status, so a crash reads
as an empty list and the sources it would have named go out unverified. The
hook documents this trap for its delta_sources calls; the inline script that
lists edited claimed sources sat in the same trap.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
UNCHECKED = re.compile(r"mapfile[^\n]*<\s*<\(\s*python3")


def test_no_python_list_is_read_through_a_process_substitution():
    text = (ROOT / ".githooks" / "pre-push").read_text(encoding="utf-8")
    found = [line.strip() for line in text.splitlines() if UNCHECKED.search(line)]
    assert not found, found


def test_the_edited_sources_list_is_status_checked():
    text = (ROOT / ".githooks" / "pre-push").read_text(encoding="utf-8")
    assert re.search(r"python3 - \"\$base\" \"\$local_sha\" > \"\$edited_out\" <<'PY' \\\r?\n\s+\|\| \{", text)
    assert 'mapfile -t edited < "$edited_out"' in text


def test_the_pattern_is_recognised():
    assert UNCHECKED.search('    mapfile -t edited < <(python3 - "$base" "$local_sha" <<\'PY\'')
