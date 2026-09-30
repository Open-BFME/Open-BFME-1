"""Static data stays separate from code and uses the data ledger's validation."""
import csv
import io
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_rows
import progress


def ledger(*rows):
    text = io.StringIO()
    writer = csv.writer(text)
    writer.writerow(data_rows.FIELDS)
    for name, address, kind, size, section in rows:
        writer.writerow([name, address, kind, size, section, "game/data.cpp",
                         "matched", "independently byte-gated", "test"])
    return text.getvalue().encode()


class StaticDataTests(unittest.TestCase):
    sections = [(".data", 0x401000, 0x402000), (".rdata", 0x402000, 0x403000)]

    def stats(self, raw):
        return progress.static_data_stats(raw, {"game/data.cpp"}, self.sections)

    def test_valid_mixed_address_kinds_sum_extents(self):
        stats = self.stats(ledger(("_a", "0x401000", "va", 4, ".data"),
                                  ("_b", "0x1004", "rva", 12, ".data")))
        self.assertEqual(stats["bytes"], 16)
        self.assertEqual(stats["rows"], 2)
        line = progress.static_data_line(stats, 4096)
        self.assertIn("16 bytes in 2 matched rows", line)
        self.assertIn("0.39% of .rdata/.data", line)
        self.assertIn("initial image values", line)

    def test_empty_and_absent_ledgers_count_zero(self):
        self.assertEqual(self.stats(ledger())["bytes"], 0)
        self.assertEqual(progress.static_data_stats(None)["rows"], 0)
        with patch.object(progress, "_text_at", return_value=None) as read:
            self.assertEqual(progress.static_data_at("old-ref")["rows"], 0)
            read.assert_called_once_with("old-ref", "targets/game/reverse/data_rows.csv")

    def test_invalid_overlap_status_and_source_refused(self):
        bad = ledger(("_a", "0x401000", "va", 8, ".data"),
                     ("_b", "0x1004", "rva", 8, ".data"))
        with self.assertRaisesRegex(SystemExit, "overlaps"):
            self.stats(bad)
        good = ledger(("_a", "0x401000", "va", 4, ".data"))
        with self.assertRaisesRegex(SystemExit, "status must be"):
            self.stats(good.replace(b"matched", b"pending"))
        with self.assertRaisesRegex(SystemExit, "not tracked"):
            progress.static_data_stats(good, set(), self.sections)

    def test_other_sections_or_unknown_denominator_have_no_percentage(self):
        stats = {"bytes": 16, "rows": 2, "sections": {".text"}}
        self.assertNotIn("%", progress.static_data_line(stats, 4096))
        stats["sections"] = {".data"}
        self.assertNotIn("%", progress.static_data_line(stats, 0))

    def test_selected_revision_uses_its_ledger_and_tracked_sources(self):
        raw = ledger(("_a", "0x401000", "va", 4, ".data"))
        with patch.object(progress, "_text_at", return_value=raw.decode()) as read, \
             patch.object(progress.subprocess, "run",
                          return_value=SimpleNamespace(stdout="game/data.cpp\n")) as run, \
             patch.object(data_rows, "retail_sections", return_value=self.sections):
            self.assertEqual(progress.static_data_at("selected-ref")["bytes"], 4)
            read.assert_called_once_with("selected-ref", "targets/game/reverse/data_rows.csv")
            self.assertEqual(run.call_args.args[0],
                             ["git", "ls-tree", "-r", "--name-only", "selected-ref", "--", "game"])


if __name__ == "__main__":
    unittest.main()
