#!/usr/bin/env python3
"""Replay the boundary validator over recorded queues; stdlib + pytest.

Two numbers only mean anything together, and both are asserted here: how much of
the fleet's recorded waste this refuses, and how much proven-correct work it
refuses along with it. A filter that rejects everything scores perfectly on the
first and is worthless.

The two populations are committed under fixtures/ instead of being rebuilt from
the live queue, because the live queue changes every few minutes as the fleet
lands rows, and a measurement whose population moves under you is not a
measurement. The Ghidra inventory is read at a pinned commit for the same
reason -- the retail image never changes, but the fleet keeps extending the
inventory. Both fixtures were cut from the queue and the dead-end log as they
stood at that commit; regenerate them with tools/tests/fixtures/README.md.
"""
import csv
import functools
import io
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
FIXTURES = Path(__file__).parent / "fixtures"
INVENTORY_COMMIT = "2459fa69ba123a663651e181afe70ad9e5ded7c3"

sys.path.insert(0, str(ROOT / "tools"))
csv.field_size_limit(10_000_000)

import boundary_validator  # noqa: E402
import build  # noqa: E402
import next_work  # noqa: E402


@functools.lru_cache(maxsize=1)
def inventory():
    """{function start: body size} as the inventory stood at INVENTORY_COMMIT."""
    blob = subprocess.run(
        ["git", "show", f"{INVENTORY_COMMIT}:reverse/ghidra_functions.csv"],
        cwd=ROOT, capture_output=True, text=True, check=True).stdout
    return {int(row["rva"], 16): int(row["size"])
            for row in csv.DictReader(io.StringIO(blob))}


@functools.lru_cache(maxsize=1)
def validator():
    return boundary_validator.BoundaryValidator(build.read_target_bytes, inventory())


def fixture(name):
    with (FIXTURES / name).open(newline="") as handle:
        return list(csv.DictReader(handle))


def fake_image(bodies, base=0x1000, span=0x2000):
    """A stand-in retail image: the bodies given, int3 padding everywhere else."""
    data = bytearray(b"\xcc" * span)
    for rva, body in bodies.items():
        data[rva - base:rva - base + len(body)] = body

    def read(rva, count):
        if not base <= rva < base + span:
            raise AssertionError(f"fake image has no rva 0x{rva:08X}")
        return bytes(data[rva - base:rva - base + count])
    return read


def test_recorded_dead_ends_are_refused():
    """Every row here is a boundary the queue served, a contributor spent a slot
    on, and the log records as no-match. The bar is 70%: the checks that would
    push it higher are the ones that reject a good address for a drifted size,
    which is the very thing this tier exists to reconcile."""
    rows = fixture("dead_ends.csv")
    verdicts = [validator().validate([row["symbol"]], int(row["rva"], 16),
                                     int(row["size"]))
                for row in rows]
    refused = [v for v in verdicts if v["reject"]]
    rate = len(refused) / len(rows)
    by_check = Counter(v["reject"].split()[0] for v in refused)
    assert rate >= 0.70, (
        f"only {rate:.2%} of {len(rows)} recorded dead ends refused, by check "
        f"{dict(by_check)} — the tier no longer pays for itself")
    assert min(by_check.values()) > 50, (
        f"a check stopped contributing: {dict(by_check)}")
    print(f"PASS dead-end replay: {len(refused)}/{len(rows)} = {rate:.2%} refused "
          f"{dict(by_check)}")


def test_byte_verified_boundaries_are_not_refused():
    """The control the rejection rate is meaningless without. Every row here has
    a byte-verified body behind it, so any refusal is a contributor being told
    to skip work that was provably doable. Read live, not from a fixture: the
    ledger only grows, and this bound has to hold for the rows landing today."""
    boundaries = {}
    with (ROOT / "targets/game/reverse" / "functions.csv").open(newline="") as handle:
        for row in csv.DictReader(handle):
            if row["status"] != "matched" or not row["target_rva"]:
                continue
            if not (row["target_size"] or "").isdigit():
                continue
            # ICF aliases share one body; counting each would over-weight it.
            boundaries.setdefault(
                (int(row["target_rva"], 16), int(row["target_size"])), row["name"])
    live = boundary_validator.BoundaryValidator(
        build.read_target_bytes, next_work._ghidra_sizes())
    refused = [live.validate([name], rva, size)
               for (rva, size), name in boundaries.items()]
    refused = [v for v in refused if v["reject"]]
    rate = len(refused) / len(boundaries)
    assert rate <= 0.025, (
        f"{rate:.2%} of {len(boundaries)} byte-verified boundaries refused "
        f"{dict(Counter(v['reject'].split()[0] for v in refused))} — this filter "
        f"is now hiding real work")
    print(f"PASS false-reject control: {len(refused)}/{len(boundaries)} = "
          f"{rate:.3%} of byte-verified boundaries refused")


def test_collision_collapse_serves_each_address_once():
    """The queue dedupes by symbol name and never by address, so one body is
    served once per name that drifted onto it."""
    rows = fixture("structural_queue.csv")
    queue = [{"function": row["function"], "candidate_rva": row["rva"],
              "size": int(row["size"]), "source": "game/fixture.cpp"}
             for row in rows]
    addresses = {row["rva"] for row in rows}
    assert (len(queue), len(addresses)) == (3923, 1200), (len(queue), len(addresses))

    items, meta = next_work.collapse_and_validate(queue, validator())
    served = [item["candidate_rva"] for item in items]
    assert len(set(served)) == len(served), "an address was served twice"
    assert meta["addresses"] == len(addresses)
    # Frozen population, frozen inventory, frozen image: these are exact. If a
    # pinned input is deliberately moved, re-measure and re-pin them.
    assert meta["served"] == len(items) == 849, meta
    assert meta["names"] == sum(len(i["functions"]) for i in items) == 2209, meta
    assert meta["refuted"] == 1278, meta
    assert meta["rejected"] == 351, meta
    for item in items:
        assert item["function"] == item["functions"][0], item
        assert item["source"] and item["size"] > 0, item
    print(f"PASS collision-collapse: {len(queue)} candidates over {len(addresses)} "
          f"addresses -> {meta['served']} served carrying {meta['names']} name(s), "
          f"{meta['refuted']} refuted, {meta['rejected']} addresses refused")


def test_absence_of_evidence_never_refuses():
    """61% of the bodies already landed are absent from the inventory, so an
    address the inventory does not cover is unknown, not wrong."""
    read = fake_image({0x1400: bytes([0x55, 0x8B, 0xEC, 0xC3])})
    unknown = boundary_validator.BoundaryValidator(read, {})
    assert unknown.check_start(0x1400) == (None, "unmapped-gap")
    verdict = unknown.validate(["?h@C@@QAEXXZ"], 0x1400, 4)
    assert verdict["reject"] is None, verdict
    assert verdict["extent"] is None, verdict
    print("PASS unmapped addresses are unknown, not refused")


def test_positive_evidence_refuses():
    """int3 at the address, another start inside the range, an address inside a
    known body: each is the image or the inventory saying no."""
    body = bytes([0x55, 0x8B, 0xEC]) + bytes([0xC3])
    read = fake_image({0x1400: body, 0x1500: body})
    known = boundary_validator.BoundaryValidator(read, {0x1400: 4, 0x1500: 4})

    assert known.validate(["?h@C@@QAEXXZ"], 0x1420, 4)["reject"] == "C1 in-int3-padding"
    assert known.validate(["?h@C@@QAEXXZ"], 0x1402, 2)["reject"] == "C1 interior-of-function"
    # a range starting at a real body but running over the next start
    spanning = boundary_validator.BoundaryValidator(read, {0x1400: 0x120, 0x1500: 4})
    assert spanning.validate(["?h@C@@QAEXXZ"], 0x1400, 0x120)["reject"] == (
        "C2 spans-1-function-start(s)")
    # int3 run with code after it, inside one claimed range
    padded = fake_image({0x1400: bytes([0x90, 0xC3, 0xCC, 0xCC, 0xCC, 0x55, 0xC3])})
    crossing = boundary_validator.BoundaryValidator(padded, {})
    assert crossing.validate(["?h@C@@QAEXXZ"], 0x1400, 7)["reject"] == "C2 crosses-int3-run"
    print("PASS int3 padding, interior addresses and spanned starts are refused")


def test_a_refuted_address_is_corrected_to_the_body_the_inventory_names():
    """A refused address is still evidence: the needle aligned on a real body,
    it just named the wrong point in it. The two refusals point opposite ways --
    interior back to the start enclosing it, padding forward to the start it
    runs up to -- which is why no single-direction rule recovers both."""
    code = bytes([0x55, 0x8B, 0xEC, 0xC3])
    read = fake_image({0x1400: code, 0x1480: code, 0x1500: code})
    known = boundary_validator.BoundaryValidator(read, {0x1400: 4, 0x1500: 4})

    assert known.check_start(0x1402) == (False, "interior-of-function")
    assert known.corrected_start(0x1402) == 0x1400
    assert known.check_start(0x1420) == (False, "in-int3-padding")
    assert known.corrected_start(0x1420) == 0x1500
    # 0x1480 is code the inventory never covered: unknown, not wrong. The
    # tempting wrong rule -- correct whenever `containing()` is None -- snaps it
    # forward to 0x1500, past its own end, and does that to all 32 such live
    # addresses. Absence of evidence decides nothing here either.
    assert known.check_start(0x1480) == (None, "unmapped-gap")
    assert known.corrected_start(0x1480) is None
    # padding past the last known start: a body ends here, but nothing says where
    assert known.check_start(0x1600) == (False, "in-int3-padding")
    assert known.corrected_start(0x1600) is None
    assert known.corrected_start(0x1400) is None, "a confirmed start needs no correction"
    print("PASS refuted addresses correct to their body, unmapped ones are left alone")


def test_arity_is_per_name_and_read_from_the_retail_body():
    """What makes collapse pay: one address, many claimant names, and the body's
    own stack cleanup rules out the ones it cannot be. Read at the retail extent
    -- a `ret` at the end of a drifted claim is not this body's `ret`."""
    read = fake_image({0x1400: bytes([0x55, 0x8B, 0xEC, 0xC2, 0x08, 0x00])})
    known = boundary_validator.BoundaryValidator(read, {0x1400: 6})

    verdict = known.validate(["?g@C@@QAEXHH@Z", "?f@C@@QAEXH@Z", "?anon@@YAXXZ"],
                             0x1400, 6)
    assert verdict["reject"] is None, verdict
    # Boundary validation leaves caller-cleaned names opinion-free; the naked
    # queue's dedicated arity filter handles parsed cdecl cleanup.
    assert verdict["names"] == ["?g@C@@QAEXHH@Z", "?anon@@YAXXZ"], verdict
    assert "?f@C@@QAEXH@Z" in verdict["refuted"], verdict

    assert known.validate(["?f@C@@QAEXH@Z"], 0x1400, 6)["reject"].startswith("C3 ")
    # the claimed size ends one byte early, where the body reads as `ret 0`
    assert known.validate(["?h@C@@QAEXXZ"], 0x1400, 4)["refuted"], "extent ignored"
    print("PASS arity is per name, read at the retail extent")


def test_a_drifted_size_warns_and_is_still_served():
    """Reconciling size drift is the tier's job, so a size that disagrees with
    retail is what the candidate says, not grounds to refuse it."""
    read = fake_image({0x1400: bytes([0x55, 0x8B, 0xEC, 0xC3])})
    known = boundary_validator.BoundaryValidator(read, {0x1400: 4})
    verdict = known.validate(["?h@C@@QAEXXZ"], 0x1400, 64)
    assert verdict["reject"] is None, verdict
    assert verdict["extent"] == 4 and verdict["size"] == 64, verdict
    assert verdict["warnings"] == ["source claims 64B, retail body is 4B"], verdict
    print("PASS size drift warns, and the retail extent is what gets served")


def main():
    test_recorded_dead_ends_are_refused()
    test_byte_verified_boundaries_are_not_refused()
    test_collision_collapse_serves_each_address_once()
    test_absence_of_evidence_never_refuses()
    test_positive_evidence_refuses()
    test_a_refuted_address_is_corrected_to_the_body_the_inventory_names()
    test_arity_is_per_name_and_read_from_the_retail_body()
    test_a_drifted_size_warns_and_is_still_served()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
