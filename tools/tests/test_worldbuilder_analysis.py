"""Owned-address counts must not turn gaps or tails into contiguous claims."""
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import worldbuilder_analysis as analysis


def test_exact_range_and_missing_start_are_distinct():
    assert analysis.boundary_verdict(0x1000, 10, [(0x1000, 0x1009)], 10) == "exact_contiguous"
    assert analysis.boundary_verdict(0x1000, 10, None, None) == "missing_function_start"


def test_equal_owned_count_with_gap_is_not_a_contiguous_extent():
    ranges = [(0x1000, 0x1004), (0x1008, 0x100C)]
    assert analysis.boundary_verdict(0x1000, 10, ranges, 10) == "different_owned_ranges"
    assert analysis.boundary_verdict(0x1000, 13, ranges, 10) == "different_owned_ranges"


def test_shared_tail_before_entry_is_not_promoted_to_a_range():
    ranges = [(0x900, 0x903), (0x1000, 0x1005)]
    assert analysis.boundary_verdict(0x1000, 10, ranges, 10) == "different_owned_ranges"


def test_inconsistent_and_overlapping_exported_ranges_fail():
    with pytest.raises(ValueError, match="owned-address count"):
        analysis.boundary_verdict(0x1000, 10, [(0x1000, 0x1009)], 9)
    with pytest.raises(ValueError, match="Overlapping"):
        analysis.parse_ranges("0x1000:0x1009;0x1008:0x1010")


def test_literal_quotes_in_ghidra_strings_do_not_merge_reference_rows(tmp_path):
    path = tmp_path / "strings.tsv"
    path.write_text('string_rva\tvalue\n0x1000\t"unfinished quote\n0x2000\tsecond\n')
    assert list(analysis.table(path)) == [
        {"string_rva": "0x1000", "value": '"unfinished quote'},
        {"string_rva": "0x2000", "value": "second"}]
