"""Retail truth fingerprints must ignore mapping insertion order."""
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as census


def _truth(sections, *, image=b"retail", inputs="stable inputs"):
    truth = object.__new__(census.RetailTruth)
    truth._weak_rows_current = True
    truth.image = image
    truth.ledger = {"symbol": {0x1234}}
    truth.pinned = {"pin": {0x2345}}
    truth.slots = {"import": {0x3456}}
    truth.import_routes = {"route": {0x4567}}
    truth.shared = {0x5678}
    truth.sections = sections
    truth._weak_inputs = inputs
    return truth


def test_nested_section_mapping_order_does_not_change_fingerprint():
    section = {"name": ".text", "rva": 0x1000, "size": 0x200,
               "raw_pointer": 0x400}
    reordered = dict(reversed(tuple(section.items())))
    first = _truth([section, {"name": ".data", "rva": 0x3000,
                              "size": 0x100, "raw_pointer": 0x600}])
    second = _truth([reordered, {"raw_pointer": 0x600, "size": 0x100,
                                 "rva": 0x3000, "name": ".data"}])

    assert first.sections == second.sections
    assert census.truth_fingerprint(first) == census.truth_fingerprint(second)


def test_fingerprint_still_changes_when_truth_inputs_change():
    sections = [{"name": ".text", "rva": 0x1000, "size": 0x200,
                 "raw_pointer": 0x400}]
    baseline = census.truth_fingerprint(_truth(sections))
    assert census.truth_fingerprint(_truth(sections, image=b"changed image")) != baseline
    assert census.truth_fingerprint(_truth(sections, inputs="changed ledger")) != baseline


def test_section_sequence_order_remains_significant():
    sections = [{"name": ".text", "rva": 0x1000, "size": 0x200,
                 "raw_pointer": 0x400},
                {"name": ".data", "rva": 0x3000, "size": 0x100,
                 "raw_pointer": 0x600}]
    assert census.truth_fingerprint(_truth(sections)) != census.truth_fingerprint(
        _truth(list(reversed(sections))))
