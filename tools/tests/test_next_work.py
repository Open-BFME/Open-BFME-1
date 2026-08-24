#!/usr/bin/env python3
"""Focused tests for the validated, decentralized work queue."""

import csv
import json
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))


def run(args=(), cwd=ROOT, env=None):
    return subprocess.run(
        [sys.executable, str(cwd / "tools" / "next_work.py"), *args],
        cwd=cwd, env=env, capture_output=True, text=True, timeout=60, check=False)


def get_ranked_json(extra=()):
    proc = run(["--ranked", "--json", *extra])
    assert proc.returncode == 0, f"ranked JSON failed (rc {proc.returncode}):\n{proc.stderr}"
    return json.loads(proc.stdout)


def get_selection_json(extra=(), env=None):
    proc = run(["--json", *extra], env=env)
    assert proc.returncode == 0, f"selection JSON failed (rc {proc.returncode}):\n{proc.stderr}"
    return json.loads(proc.stdout)


def sourced_rows():
    """Live ledger rows a work finder must respect: every one but the dumps.

    A gen-dump row pins retail's bytes under a synthetic name and holds no
    identity, so the ground under it is exactly what the queue should be serving.
    Asserting over the raw ledger here would demand that bug back — and it is the
    canonical predicate that decides, never the source path.
    """
    import build

    with (ROOT / "reverse" / "functions.csv").open(newline="") as fh:
        return [row for row in csv.DictReader(fh) if not build.is_scaffold_row(row)]


# Six tests below take `ranked`/`data`, but the fixtures were never defined, so
# pytest errored them out at setup and they have not run. Each ranked run is a
# subprocess that re-reads the whole ledger, so it is built once per module.
@pytest.fixture(scope="module")
def ranked():
    return get_ranked_json()


@pytest.fixture(scope="module")
def data(ranked):
    return ranked


def test_plain_run(ranked):
    proc = run()
    assert proc.returncode == 0, f"plain run failed (rc {proc.returncode}):\n{proc.stderr}"
    available = any(ranked[key] for key in
                    ("reloc_named", "drift_quick_wins", "structural",
                     "ghidra_absent"))
    if available:
        assert proc.stdout.count("== selected work:") == 1, proc.stdout
        assert proc.stdout.count("       start:") + proc.stdout.count(
            "then byte-verify:") == 1, proc.stdout
        assert "== 2. drift quick wins" not in proc.stdout, proc.stdout
    else:
        assert "No validated queue candidates remain." in proc.stdout
    print("PASS plain run: one work unit, no ranked queue dump")


def test_ranked_view():
    proc = run(["--ranked", "--limit", "2"])
    assert proc.returncode == 0, proc.stderr
    for needle in ("== 0. ledger health ==",
                   "== 1. reloc-named unclaimed functions",
                   "== 2. drift quick wins",
                   "== 3. structural reconciliation",
                   "== 4. Ghidra-anchored absent functions",
                   "== 5. rest of the ladder =="):
        assert needle in proc.stdout, f"ranked output missing {needle!r}"
    print("PASS --ranked: full human/debug queue remains available")


def test_selection_draws_from_the_whole_queue(ranked):
    first = get_selection_json(["--tier", "structural"])
    second = get_selection_json(["--tier", "structural"])
    candidates = ranked["structural"]
    if not candidates:
        assert first["selection"] is None and second["selection"] is None
        return

    functions = {candidate["function"] for candidate in candidates}
    for result in (first, second):
        assert result["selection"]["function"] in functions, result
        assert result["selection_meta"]["pool"] == len(candidates), result
    print(f"PASS default picker: draws from all {len(candidates)} queue candidate(s)")


def test_selection_beats_uniform_under_both_cost_models(ranked):
    """The selector must not discard the ranking, and must not bet the whole
    queue on an unmeasured cost model.

    Attempt duration is not recorded anywhere, so bytes-per-hour cannot be
    computed. The two plausible cost models pull in opposite directions, so the
    weighting is only defensible if it beats a uniform draw under BOTH:
      cost constant       -> value is P(land) * size
      cost scales w/ size -> value is P(land)
    """
    import yield_model

    candidates = ranked["structural"]
    if len(candidates) < 50:
        pytest.skip("queue too small to measure a distribution")

    def mean(sample, value):
        return sum(value(c) for c in sample) / len(sample)

    import next_work
    drawn = [next_work.weighted_choice(candidates) for _ in range(4000)]
    per_attempt = lambda c: yield_model.land_rate(c["size"]) * c["size"]
    per_hour = lambda c: yield_model.land_rate(c["size"])

    for label, value in (("bytes/attempt", per_attempt), ("bytes/hour", per_hour)):
        pool, got = mean(candidates, value), mean(drawn, value)
        assert got > pool, (
            f"weighted draw is no better than uniform on {label}: "
            f"{got:.2f} against a {pool:.2f} pool")
        print(f"PASS weighted picker: {label} {pool:.2f} -> {got:.2f} "
              f"({got / pool:.2f}x uniform)")

    # Assert suppression of the 14%-land-rate band RELATIVE to this pool's own
    # uniform baseline, not against a constant. An absolute ceiling rots as the
    # queue shifts: it silently becomes either unreachable or a coin flip
    # depending on how many small candidates happen to be queued that week.
    tiny = sum(1 for c in drawn if c["size"] < 64) / len(drawn)
    baseline = sum(1 for c in candidates if c["size"] < 64) / len(candidates)
    if baseline:
        assert tiny < baseline / 2, (
            f"{tiny:.2%} of draws in the <64B band against a {baseline:.2%} "
            f"uniform baseline — the band is not being suppressed "
            f"(measured suppression is normally ~3.9x)")
    assert len({id(c) for c in drawn}) > 20, "selection concentrated on too few candidates"


def test_land_rate_curve_is_not_monotonic_in_size(ranked):
    """Guards the measured shape against being 'simplified' back into a
    bigger-is-better weight. P(land) peaks at 128-255B (41%) and falls to 9%
    above 512B; a monotonic curve would re-serve the bands that do not pay."""
    import yield_model

    assert yield_model.land_rate(32) < yield_model.land_rate(200)
    assert yield_model.land_rate(1024) < yield_model.land_rate(200)
    assert yield_model.land_rate(200) == max(
        yield_model.land_rate(n) for n in (32, 100, 200, 400, 1024, 4096))
    print("PASS land-rate curve: peaks at the measured 128-255B band")


def test_anchored_candidates_are_real_and_unclaimed(data):
    """The string-anchor tier must never serve a body the ledger already covers.

    Its input is a cached CSV (tools/anchor_unclaimed.py), so it goes stale as
    the fleet lands rows — the tier has to re-check every candidate against the
    live ledger rather than trusting the cache."""
    ranges, claimed_rvas = [], set()
    for row in sourced_rows():
        if row["target_rva"]:
            start = int(row["target_rva"], 16)
            claimed_rvas.add(start)
            if row["target_size"]:
                ranges.append((start, start + int(row["target_size"])))
    for candidate in data["anchored"]:
        rva = int(candidate["target_rva"], 16)
        assert rva not in claimed_rvas, candidate
        assert not any(lo < rva < hi for lo, hi in ranges), candidate
        assert candidate["size"] > 0, candidate
        assert candidate["confidence"] in ("high", "medium"), candidate
        assert candidate["anchor"], candidate
        assert candidate["zh_source"], candidate
    print(f"PASS anchored queue: {len(data['anchored'])} candidates, none claimed")


def test_explicit_stable_sharding(ranked):
    full = ranked["structural"]
    shards = [get_ranked_json(["--tier", "structural", "--shard", f"{i}/3"])
              for i in range(3)]
    names = [{candidate["function"] for candidate in data["structural"]}
             for data in shards]
    assert not (names[0] & names[1] or names[0] & names[2] or names[1] & names[2])
    assert set().union(*names) == {candidate["function"] for candidate in full}
    for index, data in enumerate(shards):
        assert data["shard"] == {"index": index, "count": 3}, data["shard"]

    selection = get_selection_json(["--tier", "structural", "--shard", "1/3"])
    assert selection["selection_meta"]["shard"] == {"index": 1, "count": 3}
    if selection["selection"]:
        assert selection["selection"]["function"] in names[1]

    invalid = run(["--shard", "3/3"])
    assert invalid.returncode != 0 and "0 <= INDEX < COUNT" in invalid.stderr
    obsolete = run(["--any"])
    assert obsolete.returncode != 0 and "unrecognized arguments: --any" in obsolete.stderr
    print("PASS explicit sharding: stable, disjoint, complete partitions")


def test_ranked_json_shape(data):
    for key in ("ledger", "drift_quick_wins", "structural",
                "ghidra_meta", "ghidra_absent", "pointers"):
        assert key in data, f"ranked JSON missing key {key!r}"
    for stale in ("slot", "pool", "filtered"):
        assert stale not in data, f"ranked JSON retained sharding field {stale!r}"
    assert data["shard"] is None
    print(f"PASS ranked JSON: {len(data['structural'])} structural and "
          f"{len(data['ghidra_absent'])} Ghidra candidates")


def test_ghidra_candidates_validated(data):
    claimed_names, claimed_rvas = set(), set()
    for row in sourced_rows():
        claimed_names.add(row["name"])
        if row["target_rva"]:
            claimed_rvas.add(int(row["target_rva"], 16))
    for candidate in data["ghidra_absent"]:
        assert candidate["function"] not in claimed_names, candidate
        assert int(candidate["target_rva"], 16) not in claimed_rvas, candidate
        assert (ROOT / candidate["source"]).exists(), candidate
        assert candidate["target_size"] > 0 and candidate["anchors"], candidate
        assert candidate["confidence"] in ("high", "medium"), candidate
        assert candidate["command"].startswith("python3 tools/explain_mismatch.py ")
    print(f"PASS Ghidra queue: {len(data['ghidra_absent'])} validated candidates")


def test_structural_candidates_do_not_start_inside_claimed_ranges(data):
    ranges = []
    for row in sourced_rows():
        if row["target_rva"] and row["target_size"]:
            start = int(row["target_rva"], 16)
            ranges.append((start, start + int(row["target_size"]), row["name"]))
    for candidate in data["structural"]:
        rva = int(candidate["candidate_rva"], 16)
        overlaps = [name for start, end, name in ranges if start < rva < end]
        assert not overlaps, (candidate, overlaps[:3])
    print(f"PASS structural queue: {len(data['structural'])} candidates outside claimed ranges")


QUEUES = ("reloc_named", "drift_quick_wins", "structural", "ghidra_absent")


def served_names(candidate):
    """Every name a queue item stands for: the structural tier collapses each
    address to one item carrying all of them."""
    return candidate.get("functions") or [candidate["function"]]


def item_rva(candidate):
    return int((candidate.get("candidate_rva") or candidate.get("target_rva") or "0"), 16)


def leaked_names(candidate):
    """Names on this item that a standing verdict should have retired.

    The item's hint belongs to the name it is served under, so that one is
    checked exactly. The names collapsed in alongside it kept no hint of their
    own, so they are read the most forgiving way -- `boundary_moved=True`
    retires a name only where the log gives no boundary to have moved, which is
    exactly the leak this filter exists to close.
    """
    import re_log

    rva, names = item_rva(candidate), served_names(candidate)
    moved = "drift-corrected" in candidate.get("hint", "")
    leaked = [names[0]] if re_log.is_dead_end(names[0], rva, boundary_moved=moved) else []
    return leaked + [name for name in names[1:]
                     if re_log.is_dead_end(name, rva, boundary_moved=True)]


def test_logged_dead_ends_suppressed(ranked):
    """A standing dead-end verdict is a finished investigation, so the queues
    must not serve that boundary again; --include-logged restores it."""
    for key in QUEUES:
        # A verdict retires a candidate only while its boundary is unchanged;
        # a snap-corrected boundary is new evidence and comes back.
        stale = [name for c in ranked[key] for name in leaked_names(c)]
        assert not stale, f"{key} served {len(stale)} finished candidate(s): {stale[:3]}"

    # Compare (name, boundary) pairs, not bare names. A verdict describes the
    # address its author examined, so one name can be retired at that boundary
    # and legitimately live at another a drift snap moved it to; comparing names
    # alone reads that as a leak. ??4GameSpyStagingRoom is suppressed at its
    # no-match boundary 0x004F15B0 and served, correctly, as a collapsed sibling
    # of the drift-corrected 0x009D2970, and ?updateState@Team likewise at
    # 0x000F71C0 against 0x009C0A30. Dropping one dead name off a shared address
    # still removes a name from the collapsed item, not the address. More pairs
    # come back than the log retires, because an address with no Ghidra extent is
    # validated over the range it would serve, and restoring the candidates
    # ahead of it in the ranking changes which range that is.
    full = get_ranked_json(["--include-logged"])
    shown = {(name, item_rva(c)) for key in QUEUES for c in ranked[key]
             for name in served_names(c)}
    restored = {(name, item_rva(c)) for key in QUEUES for c in full[key]
                for name in served_names(c)} - shown
    retired = {(name, item_rva(c)) for key in QUEUES for c in full[key]
               for name in leaked_names(c)}
    assert retired, "no queued candidate carries a standing verdict at all"
    assert retired <= restored, sorted(
        f"{name} at 0x{rva:08X}" for name, rva in retired - restored)[:3]
    assert len(restored) <= ranked["suppressed_logged"], (
        len(restored), ranked["suppressed_logged"])
    print(f"PASS re_attempts filter: {ranked['suppressed_logged']} finished "
          f"candidate(s) suppressed, --include-logged restores {len(restored)} "
          f"name(s) including all {len(retired)} with a standing verdict")


def test_a_verdict_with_no_boundary_is_not_released_by_a_snap(ranked):
    """Every drift candidate is snap-corrected by construction, so reading
    "the boundary moved" as "the verdict no longer applies" released every
    3-field verdict in the log -- 374 already-investigated candidates went
    straight back into the queue, and the fleet worked several of them twice.
    A row that records no boundary is a finding about the symbol."""
    import re_log

    repeat_offender = "?PreStaticInit@Debug@@CAXXZ"   # three no-match rows, no rva
    assert re_log.is_dead_end(repeat_offender, 0x00C6E37E, boundary_moved=True)
    assert re_log.is_dead_end(repeat_offender, 0x00C6E37E, boundary_moved=False)
    served = {name for key in QUEUES for c in ranked[key] for name in served_names(c)}
    assert repeat_offender not in served

    # A verdict that DOES record its boundary still only retires that boundary.
    at_boundary = "??0FastAllocatorGeneral@@QAE@XZ"
    assert re_log.is_dead_end(at_boundary, 0x00B027B0)
    assert not re_log.is_dead_end(at_boundary, 0x00B027B0 + 0x40, boundary_moved=True)
    print("PASS dead-end verdicts recorded without an rva survive a boundary snap")


def test_void_retracts_the_row_it_names_and_nothing_else():
    """An append-only log still has to be able to take back a typed address.

    `_LoadInt` was logged `blocked` at 0x0099D2E0 — an address typed from memory,
    16 bytes inside `_chunk`'s matched body, nothing to do with lundump.c. The
    row appended after it says "read the 0x0099D2E0 entry as void", which is a
    sentence for a human; every queue kept reading the phantom boundary as a
    finished investigation. `void` is the machine-readable form.

    Written to FAIL on the code before the fix: with void rows treated as
    unknown-status annotations — exactly what the old reader did with them —
    the first assertion below is True, not False.
    """
    import re_log

    false_locator, measured = 0x0099D2E0, 0x0099D670

    def fresh(void_enabled):
        re_log._reset()
        re_log.VOID_STATUS = "void" if void_enabled else "__void_disabled__"
        re_log._load()

    try:
        fresh(True)
        assert re_log.standing_status("_LoadInt", false_locator,
                                      boundary_moved=True) is None, (
            "the retracted boundary still governs candidates")
        assert re_log.standing_status("_LoadInt", measured,
                                      boundary_moved=True) == "blocked", (
            "voiding the typo also released the boundary that WAS measured")

        fresh(False)
        assert re_log.standing_status("_LoadInt", false_locator,
                                      boundary_moved=True) == "blocked", (
            "this test cannot fail on the broken code, so it proves nothing")
    finally:
        fresh(True)

    # A void names a row; one that names no row is a typo about a typo.
    proc = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "re_log.py"), "record",
         "?NeverLoggedAnywhere@@QAEXXZ", "0x00400000", "16", "void", "nothing to take back"],
        cwd=ROOT, capture_output=True, text=True, timeout=60, check=False)
    assert proc.returncode != 0, "a void matching no row was accepted"
    assert "nothing to void" in proc.stdout + proc.stderr
    print("PASS void retracts only its own (symbol, rva); unmatched voids refused")


def test_void_is_positional_so_a_later_verdict_still_stands(tmp_path, monkeypatch):
    """Voids retract upwards only. Re-recording a boundary after voiding it is
    new evidence and must count, or a single typo would poison an address for
    the life of the repository."""
    import re_log

    log = tmp_path / "re_attempts.log"
    log.write_text(
        "?Sym@@QAEXXZ\t0x00401000\t16\tblocked\tfirst, wrong\r\n"
        "?Sym@@QAEXXZ\t0x00401000\t16\tvoid\tretracts the above\r\n"
        "?Sym@@QAEXXZ\t0x00401000\t16\tblocked\tmeasured this time\r\n",
        encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    re_log._reset()
    try:
        assert re_log.standing_status("?Sym@@QAEXXZ", 0x00401000,
                                      boundary_moved=True) == "blocked"
    finally:
        re_log._reset()
    print("PASS void retracts earlier rows only; a later verdict survives it")


def test_structural_queue_is_collapsed_and_validated(ranked):
    """One item per address, each carrying every name that still fits its body,
    and the retail extent -- not the drifted source size -- in the command."""
    queue = ranked["structural"]
    meta = ranked["structural_meta"]
    if not queue:
        pytest.skip("structural tier is empty")

    addresses = [c["candidate_rva"] for c in queue]
    assert len(set(addresses)) == len(addresses), "an address was served twice"
    assert meta["served"] == len(queue), meta
    assert meta["names"] == sum(len(c["functions"]) for c in queue) >= len(queue)
    assert meta["rejected"] and meta["addresses"] == meta["served"] + meta["rejected"]

    for candidate in queue:
        assert candidate["function"] == candidate["functions"][0], candidate
        served = candidate["extent"] or candidate["size"]
        assert f"--rva {candidate['candidate_rva']} --size {served} " in \
            candidate["command"], candidate
    # `size` stays the compiled size: candidate_weight reads it, and overwriting
    # it with the extent would retune the selection weights as a side effect.
    drifted = [c for c in queue if c["extent"] and c["extent"] != c["size"]]
    assert drifted, "no candidate disagrees with retail on size — suspicious"
    assert all(c["warnings"] for c in drifted)
    print(f"PASS structural queue: {meta['served']} address(es) carrying "
          f"{meta['names']} name(s), {meta['refuted']} refuted by arity, "
          f"{meta['rejected']} address(es) refused")


def test_padding_snap_refuses_an_all_padding_window():
    """padding_snap returned (rva, None) when the whole window was padding, and
    a None note reads as "nothing wrong here" -- which is how all 76 int3-headed
    addresses reached the queue."""
    import build
    import next_work

    original = build.read_target_bytes
    build.read_target_bytes = lambda rva, count: b"\xcc" * count
    try:
        rva, note = next_work.padding_snap(0x00C6E37E)
    finally:
        build.read_target_bytes = original
    assert rva == 0x00C6E37E, rva
    assert "no trustworthy boundary" in note, note
    print("PASS padding_snap: an all-padding window is refused, not passed through")


def test_dead_end_index_reads_both_log_shapes():
    """re_attempts.log carries a 3-field and a 5-field shape; the old reader
    tested field 1 for "no-match", which in a 5-field row is the RVA, so 441
    rows were invisible. Annotations must not overturn a standing verdict."""
    import re_log

    dead, total = re_log.stats()
    assert total > 0 and dead > 0, (dead, total)
    # ends `converted` after earlier dead ends -> released for work
    assert not re_log.is_dead_end("?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ")
    # ends `refuted` after three `solved` rows -> stays retired
    assert re_log.is_dead_end("??0FastAllocatorGeneral@@QAE@XZ")
    # no-match then six annotation rows -> the annotations must not release it
    assert re_log.is_dead_end("?validateAudio@ThingTemplate@@IAEXXZ")
    assert not re_log.is_dead_end("?NeverLoggedAnywhere@@QAEXXZ")
    print(f"PASS dead-end index: {dead} standing dead ends of {total} symbols with verdicts")


def test_corrupt_ledger():
    (ROOT / "build").mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as temp:
        temp = Path(temp)
        (temp / "tools").mkdir()
        (temp / "reverse" / "zh_sweep").mkdir(parents=True)
        (temp / "src" / "zh").mkdir(parents=True)
        for name in ("next_work.py", "check_csv.py", "re_log.py", "yield_model.py",
                     "boundary_validator.py", "audit_ret_arity.py"):
            (temp / "tools" / name).write_bytes((ROOT / "tools" / name).read_bytes())
        (temp / "src" / "zh" / "stub.cpp").write_text("// stub\n")
        row = "?Foo@@QAEXXZ,,0x00400000,16,src/zh/stub.cpp,matched,\r\n"
        (temp / "reverse" / "functions.csv").write_bytes(
            b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
            + (row + row).encode())
        (temp / "reverse" / "symbols.csv").write_text("name,address,notes\n")
        (temp / "reverse" / "zh_sweep" / "drift_report.csv").write_text(
            "function,source,size,candidate_rva,aligned_pct,class,first_diff,hint,votes\n")
        proc = run(cwd=temp)
        output = proc.stdout + proc.stderr
        assert proc.returncode == 2, output
        assert "dedup_csv" in output and "LEDGER CORRUPT" in output, output
        assert "selected work" not in output, output
    print("PASS corrupt ledger: exit 2 before selection")


def main():
    ranked = get_ranked_json()
    test_plain_run(ranked)
    test_ranked_view()
    test_selection_draws_from_the_whole_queue(ranked)
    test_selection_beats_uniform_under_both_cost_models(ranked)
    test_land_rate_curve_is_not_monotonic_in_size(ranked)
    test_anchored_candidates_are_real_and_unclaimed(ranked)
    test_explicit_stable_sharding(ranked)
    test_ranked_json_shape(ranked)
    test_ghidra_candidates_validated(ranked)
    test_structural_candidates_do_not_start_inside_claimed_ranges(ranked)
    test_logged_dead_ends_suppressed(ranked)
    test_a_verdict_with_no_boundary_is_not_released_by_a_snap(ranked)
    test_structural_queue_is_collapsed_and_validated(ranked)
    test_padding_snap_refuses_an_all_padding_window()
    test_dead_end_index_reads_both_log_shapes()
    test_corrupt_ledger()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
