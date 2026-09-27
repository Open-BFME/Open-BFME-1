"""dedup_csv --tombstoned-only: drop resurrected rows without reordering anything."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import dedup_csv  # noqa: E402


def test_only_tombstoned_lines_go_and_order_and_eol_survive(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
                       b"?z@@YAXXZ,,0x00000200,4,b.cpp,matched,\r\n"
                       b"?d_00000100@@YAXXZ,,0x00000100,8,d.asm,matched,\r\n"
                       b"?a@@YAXXZ,,0x00000100,8,a.cpp,matched,\n")
    dropped = dedup_csv.drop_tombstoned_in_place(ledger, {("?d_00000100@@YAXXZ", 0x100)})
    assert dropped == [("?d_00000100@@YAXXZ", 0x100)]
    assert ledger.read_bytes() == (b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
                                   b"?z@@YAXXZ,,0x00000200,4,b.cpp,matched,\r\n"
                                   b"?a@@YAXXZ,,0x00000100,8,a.cpp,matched,\n")


def test_nothing_tombstoned_leaves_the_file_untouched(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(b"name,export_rva,target_rva\r\n?a@@YAXXZ,,0x00000100\r\n")
    before = ledger.stat().st_mtime_ns
    assert dedup_csv.drop_tombstoned_in_place(ledger, {("?b@@YAXXZ", 0x100)}) == []
    assert ledger.stat().st_mtime_ns == before


def test_merge_repair_drops_tombstones_and_exact_duplicates_only(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
                       b"?a@@YAXXZ,,0x00000100,8,a.cpp,matched,\r\r\n"
                       b"?d_00000200@@YAXXZ,,0x00000200,8,d.asm,matched,\r\n"
                       b"?b@@YAXXZ,,0x00000300,8,b.cpp,matched,\r\n"
                       b"?a@@YAXXZ,,0x00000100,8,a.cpp,matched,\r\n")
    dropped = dedup_csv.merge_repair(ledger, {("?d_00000200@@YAXXZ", 0x200)})
    assert dropped == ["tombstoned ?d_00000200@@YAXXZ", "duplicate ?a@@YAXXZ"]
    assert ledger.read_bytes() == (b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
                                   b"?a@@YAXXZ,,0x00000100,8,a.cpp,matched,\r\r\n"
                                   b"?b@@YAXXZ,,0x00000300,8,b.cpp,matched,\r\n")
