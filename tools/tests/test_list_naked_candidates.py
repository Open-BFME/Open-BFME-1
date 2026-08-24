#!/usr/bin/env python3
"""Fast unit tests for fleet partitioning and dead-end memory."""

import tempfile
import json
import subprocess
from pathlib import Path

import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import list_naked_candidates as queue


def candidate(index):
    return {
        "symbol": f"?candidate{index}@@YAXXZ",
        "path": f"Code/candidate{index}.cpp",
        "line": index,
        "signature": f"void candidate{index}()",
    }


def main():
    candidates = [candidate(index) for index in range(100)]
    shards = [queue.apply_shard(candidates, (index, 6)) for index in range(6)]
    identities = [{item["symbol"] for item in shard} for shard in shards]
    assert sum(len(shard) for shard in shards) == len(candidates)
    assert set().union(*identities) == {item["symbol"] for item in candidates}
    for left in range(6):
        for right in range(left + 1, 6):
            assert identities[left].isdisjoint(identities[right])

    with tempfile.TemporaryDirectory() as temporary:
        log = Path(temporary) / "dead.tsv"
        log.write_text("?candidate7@@YAXXZ\tno-match\tverified dead end\n"
                       "?candidate8@@YAXXZ\tother\tnot terminal\n",
                       encoding="utf-8")
        assert queue.logged_no_match([log]) == {"?candidate7@@YAXXZ"}
    proc = subprocess.run(
        [sys.executable, str(Path(__file__).resolve().parents[1] /
                             "list_naked_candidates.py"),
         "Code/GameEngine/Source/Common/FireWeaponUpdateDestructorThunk.cpp", "--json"],
        cwd=Path(__file__).resolve().parents[2], capture_output=True, text=True,
        timeout=60, check=True,
    )
    payload = json.loads(proc.stdout)
    assert isinstance(payload["candidates"], list)
    assert all("bytes" not in item and "bytes_hex" in item for item in payload["candidates"])
    print("PASS naked queue: stable shards and no-match filtering")


if __name__ == "__main__":
    main()


# --- collectable tests -----------------------------------------------------
# Everything above runs only under `python3 tools/tests/test_list_naked_candidates.py`:
# with no test_-prefixed function and no conftest.py, pytest collects NOTHING
# from this file, so a suite run would go green while the code below is broken.

import re  # noqa: E402
import pytest  # noqa: E402
import re_log  # noqa: E402


def test_partial_survives_the_legacy_three_field_filter(tmp_path, monkeypatch):
    """The silent blocking path: logged_no_match reads only the 3-field shape
    and has no latest-wins, so before the fix a stale `no-match` out-voted the
    `partial` that released the candidate and it was never served again."""
    log = tmp_path / "reverse" / "re_attempts.log"
    log.parent.mkdir(parents=True, exist_ok=True)
    log.write_text("?Sym@@QAEXXZ\tno-match\told 3-field row\n"
                   "?Sym@@QAEXXZ\t0x00401000\t16\tpartial\t92%, banked\r\n",
                   encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    re_log._reset()
    try:
        # The queue's own filter must release it...
        kept, dropped = queue.drop_logged(
            [{"symbol": "?Sym@@QAEXXZ", "rva": "0x00401000"}])
        assert dropped == 0 and len(kept) == 1, (kept, dropped)
        # ...and the legacy reader must no longer be fed re_attempts.log at all,
        # or it would retire the symbol on the 3-field row regardless.
        assert queue.logged_no_match([log]) == {"?Sym@@QAEXXZ"}, \
            "3-field reader still parses the file; it must not receive it"
    finally:
        re_log._reset()

    # Lock the wiring, not just the parts: the reader above still retires on a
    # 3-field row, so the fix is precisely that main() stops handing it the log.
    import inspect
    source = inspect.getsource(queue.main)
    call = re.search(r"logged_no_match\(([^)]*)\)", source)
    assert call and "RE_ATTEMPTS" not in call.group(1), (
        "main() feeds re_attempts.log to the 3-field reader again — a stale "
        f"no-match will silently out-vote a later partial: {call and call.group(0)}")


def test_stash_is_offered_with_a_served_candidate(tmp_path, monkeypatch):
    log = tmp_path / "reverse" / "re_attempts.log"
    log.parent.mkdir(parents=True, exist_ok=True)
    log.write_text("", encoding="utf-8")
    stash = tmp_path / "reverse" / "attempts" / "0x00401000.cpp"
    stash.parent.mkdir(parents=True, exist_ok=True)
    stash.write_text("// ?Sym@@QAEXXZ\n// partial score=0.5 date=2026-08-24\nvoid f(){}\n",
                     encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    monkeypatch.setattr(queue.build, "ROOT", tmp_path)
    re_log._reset()
    try:
        found = queue.stash_for_item({"symbol": "?Sym@@QAEXXZ", "rva": "0x00401000"})
        assert found == ("reverse/attempts/0x00401000.cpp", 0.5), found
        assert queue.stash_for_item({"symbol": "?X@@QAEXXZ", "rva": "0x00999000"}) is None
    finally:
        re_log._reset()


def test_add_match_clears_the_stash_only_on_success(tmp_path):
    """Landing removes the head start it consumed; a revert must not."""
    import add_match

    stash = tmp_path / "reverse" / "attempts" / "0x000c8220.cpp"
    stash.parent.mkdir(parents=True, exist_ok=True)
    stash.write_text("// sym\n// partial score=0.9 date=2026-08-24\nvoid f(){}\n",
                     encoding="utf-8")

    add_match.remove_stash(0x000C8220, tmp_path)
    assert not stash.exists(), "landing left its stash behind"

    add_match.remove_stash(0x000C8220, tmp_path)  # absent -> no-op, no raise

    other = tmp_path / "reverse" / "attempts" / "0x00401000.cpp"
    other.write_text("// other\n// partial score=0.1 date=2026-08-24\nvoid g(){}\n",
                     encoding="utf-8")
    add_match.remove_stash(0x000C8220, tmp_path)
    assert other.exists(), "removed a stash belonging to a different address"
