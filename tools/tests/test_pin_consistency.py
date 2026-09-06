"""The pin-consistency guard: one name, one function.

reverse/symbols.csv is an additive candidate list, so a wrong pin does not fail
anything by itself -- it waits for a call site whose displacement it happens to
reproduce and then lends its address to a body that is not the function. The
mistakes this file pins down are the ones that still look like they worked:

  * comparing two copies of one function WITHOUT rebasing their rel32 slots
    reports every template instantiation as a violation, which floods the
    backlog and gets the guard turned off;
  * forgiving any four bytes that differ by the RVA delta, without demanding a
    branch opcode in front of them, silently accepts two DIFFERENT functions;
  * stopping the thunk walk after one hop compares two jump stubs instead of
    two bodies -- 1,915 pinned addresses reach their body through two or more;
  * a baseline that admits new lines is a whitelist, and this repo has already
    been bitten by one.
"""
import importlib.util
import struct
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")
pin_consistency = _load("pin_consistency")

# Two retail copies of one 25-byte function. Both call 0x000247E9; the only
# difference between them is the E8 displacement at offset 17, which is what
# makes the pair the exact shape a legitimately-duplicated template takes.
TWIN_A, TWIN_B, TWIN_SIZE, TWIN_SITE = 0x000BB8F0, 0x000BC440, 25, 17
# 0x0001AAE1 -> 0x003D34D0 -> 0x00887940: two `?j_` stubs before the body.
CHAIN_PIN, CHAIN_MID, CHAIN_BODY = 0x0001AAE1, 0x003D34D0, 0x00887940


@pytest.fixture(scope="module")
def twins():
    return (build.read_target_bytes(TWIN_A, TWIN_SIZE),
            build.read_target_bytes(TWIN_B, TWIN_SIZE))


@pytest.fixture(scope="module")
def scanner():
    return pin_consistency.Scanner()


def test_relocated_copy_of_one_function_is_equal(twins):
    """The template-fold case: same function, two addresses, no exclusion list.

    If this ever fails, every duplicated instantiation in the image becomes a
    violation and the backlog stops meaning anything.
    """
    left, right = twins
    assert left != right, "fixture must exercise rebasing, not plain equality"
    verdict, sites, divergence = pin_consistency.rebased_equal(
        left, right, TWIN_A, TWIN_B)
    assert (verdict, sites, divergence) == (True, [TWIN_SITE], None)


def test_a_different_call_target_is_not_forgiven(twins):
    """The whole point: rebasing reconciles the ADDRESS, never the CALLEE."""
    left, right = twins
    tampered = bytearray(right)
    struct.pack_into("<i", tampered, TWIN_SITE,
                     struct.unpack_from("<i", tampered, TWIN_SITE)[0] + 0x40)
    verdict, _sites, divergence = pin_consistency.rebased_equal(
        left, bytes(tampered), TWIN_A, TWIN_B)
    assert verdict is False
    assert divergence == TWIN_SITE


def test_a_delta_sized_difference_without_a_branch_is_not_forgiven():
    """Four bytes that differ by the RVA delta are not a displacement.

    Without the opcode anchor this pair reads as "the same function relocated",
    which is how a guard like this ends up proving nothing: `mov eax, imm32`
    holds an absolute address and two different functions can differ there by
    any amount at all, including exactly the delta.
    """
    left_rva, right_rva = 0x00400000, 0x00400100
    delta = right_rva - left_rva
    left = b"\xb8" + struct.pack("<I", 0x00500000) + b"\xc3"
    right = b"\xb8" + struct.pack("<I", 0x00500000 - delta) + b"\xc3"
    verdict, _sites, divergence = pin_consistency.rebased_equal(
        left, right, left_rva, right_rva)
    assert verdict is False
    assert divergence == 2  # first byte of the immediate that actually differs


def test_jcc_displacements_are_anchored_too():
    """A 0F 8x conditional carries a rel32 exactly as E8/E9 does."""
    left_rva, right_rva = 0x00400000, 0x00400100
    left = b"\x0f\x84" + struct.pack("<i", 0x20) + b"\xc3"
    right = b"\x0f\x84" + struct.pack("<i", 0x20 - (right_rva - left_rva)) + b"\xc3"
    assert pin_consistency.rebased_equal(left, right, left_rva, right_rva)[:2] == (True, [2])


def test_thunk_walk_reaches_the_body_not_the_next_stub(scanner):
    """One hop lands on 0x003D34D0, which is another 5-byte `jmp`, not a body."""
    body, chain = scanner.image.resolve(CHAIN_PIN)
    assert body == CHAIN_BODY
    assert chain == [CHAIN_PIN, CHAIN_MID, CHAIN_BODY]


def test_the_walk_stops_at_a_body_the_ledger_has_proven(scanner):
    """A proven body is where resolution ends, however it happens to start.

    Without this bound a genuine one-instruction tail call would be followed
    into its callee, and the guard would compare -- and name -- the wrong
    function while looking like it did more work.
    """
    assert scanner.ledger_sizes[CHAIN_BODY]
    assert max(scanner.ledger_sizes[CHAIN_BODY]) > pin_consistency.THUNK_SIZE
    assert scanner.image.resolve(CHAIN_BODY) == (CHAIN_BODY, [CHAIN_BODY])


def test_the_gamewindow_colour_setters_are_reported(scanner):
    """The historical ba1dbf6f8 wrong/right pair stays stable as a fixture.

    The live pin list is intentionally drained over time, so this regression
    must carry the two addresses that exposed the defect instead of depending
    on whichever backlog rows remain today.  The identity was claimed at
    0x00478FE0 while the real colour setter body was 0x00479010; both extents
    and their divergent bytes are still present in the matched ledger.
    """
    name = "?winSetEnabledColor@GameWindow@@QAEHHH@Z"
    pins = [0x00478FE0, 0x00479010]
    violation = scanner.inspect(name, pins)
    assert violation is not None
    assert violation["kind"] in ("divergent-bodies", "size-disagreement")
    assert len(violation["bodies"]) > 1


def test_a_pin_inside_a_proven_body_is_named_as_such(scanner):
    """0x0012C877 is 0x597 bytes into ModuleFactory::init, pinned as freeBytes.

    An address inside a byte-verified extent cannot be a function entry, so it
    cannot be any callee. Left unlabelled it reads as merely "unclaimed" -- the
    same as a body nobody has got to yet -- and sits in the backlog forever.
    """
    inside = scanner.interior_of(0x0012C877)
    assert inside == ("?init@ModuleFactory@@UAEXXZ", 0x0012C2E0, 18040)
    assert scanner.interior_of(0x0012C2E0) is None, "an entry is not its own interior"


def test_one_pin_per_name_is_never_a_violation(scanner):
    """A single address cannot disagree with itself -- the guard costs nothing
    for the 70,144 symbols that pin one."""
    assert scanner.inspect("?whatever@@YAXXZ", [0x00014867]) is None


def _violation(symbol, bodies, kind="divergent-bodies", evidence="e"):
    return {"symbol": symbol, "bodies": list(bodies), "pins": {},
            "kind": kind, "evidence": evidence}


def test_a_new_violation_fails_the_gate(tmp_path):
    baseline = tmp_path / "baseline.csv"
    known = _violation("?known@@YAXXZ", [0x1000, 0x2000])
    pin_consistency.write_baseline([known], baseline, seed=True)
    fresh = _violation("?fresh@@YAXXZ", [0x3000, 0x4000])
    new, stale = pin_consistency.check([known, fresh], baseline)
    assert [v["symbol"] for v in new] == ["?fresh@@YAXXZ"]
    assert stale == []


def test_a_new_address_on_a_baselined_symbol_fails(tmp_path):
    """The key is the symbol AND its bodies.

    Keyed on the name alone, a baselined symbol becomes a permanent licence to
    pin anything else at it -- the additive-candidate bug with a rubber stamp.
    """
    baseline = tmp_path / "baseline.csv"
    pin_consistency.write_baseline(
        [_violation("?known@@YAXXZ", [0x1000, 0x2000])], baseline, seed=True)
    grown = _violation("?known@@YAXXZ", [0x1000, 0x2000, 0x5000])
    new, _stale = pin_consistency.check([grown], baseline)
    assert [v["symbol"] for v in new] == ["?known@@YAXXZ"]


def test_a_fixed_symbol_leaves_a_stale_line_that_fails(tmp_path):
    """Shrinking is the only direction: the fix and the deletion are one commit."""
    baseline = tmp_path / "baseline.csv"
    pin_consistency.write_baseline(
        [_violation("?known@@YAXXZ", [0x1000, 0x2000])], baseline, seed=True)
    new, stale = pin_consistency.check([], baseline)
    assert new == []
    assert [row["symbol"] for row in stale] == ["?known@@YAXXZ"]


def test_a_missing_baseline_is_a_failure_not_a_free_pass(tmp_path):
    """verify_dir32_consistency seeds itself on first run and that is how 18
    unreviewed entries landed. This one refuses."""
    with pytest.raises(SystemExit) as excinfo:
        pin_consistency.read_baseline(tmp_path / "absent.csv")
    assert "--write-baseline" in str(excinfo.value)


def test_the_baseline_round_trips_its_evidence(tmp_path):
    baseline = tmp_path / "baseline.csv"
    written = _violation("?known@@YAXXZ", [0x2000, 0x1000],
                         evidence="size=46; first divergence at +0x16")
    pin_consistency.write_baseline([written], baseline, seed=True)
    entries = pin_consistency.read_baseline(baseline)
    key = pin_consistency.key_of("?known@@YAXXZ", [0x1000, 0x2000])
    assert entries[key]["evidence"] == "size=46; first divergence at +0x16"
    assert entries[key]["bodies"] == "0x00001000 0x00002000"


def test_the_committed_baseline_matches_the_ledger():
    """The gate's own assertion, run as a test so a bad rebase says why."""
    violations, _stats = pin_consistency.Scanner().scan()
    new, stale = pin_consistency.check(violations)
    assert (new, stale) == ([], [])


def test_write_baseline_refuses_to_grow(tmp_path):
    """The prose said "only allowed to shrink" and nothing enforced it, which
    left --write-baseline as a one-command way to turn any red green -- the same
    move verify_dir32_consistency's self-bootstrap made, and the reason 18
    unreviewed whitelist entries exist. Regeneration may only DROP lines."""
    baseline = tmp_path / "baseline.csv"
    known = _violation("?known@@YAXXZ", [0x1000, 0x2000])
    pin_consistency.write_baseline([known], baseline, seed=True)

    fresh = _violation("?fresh@@YAXXZ", [0x3000, 0x4000])
    with pytest.raises(SystemExit) as excinfo:
        pin_consistency.write_baseline([known, fresh], baseline)
    assert "SHRINK-ONLY" in str(excinfo.value)
    assert "?fresh@@YAXXZ" in str(excinfo.value)

    # ...and dropping one is still allowed, or adjudication could never land.
    pin_consistency.write_baseline([], baseline)
    assert pin_consistency.read_baseline(baseline) == {}


def test_seeding_cannot_overwrite_and_writing_cannot_seed(tmp_path):
    """Delete-then-regenerate must not be a way to launder a red into a green.
    Growth therefore costs two loud, separately-named acts on a tracked file."""
    baseline = tmp_path / "baseline.csv"
    pin_consistency.write_baseline([_violation("?a@@YAXXZ", [0x1000, 0x2000])],
                                   baseline, seed=True)
    with pytest.raises(SystemExit) as seeding:
        pin_consistency.write_baseline([], baseline, seed=True)
    assert "refuses to overwrite" in str(seeding.value)

    baseline.unlink()
    with pytest.raises(SystemExit) as writing:
        pin_consistency.write_baseline([_violation("?b@@YAXXZ", [0x7000, 0x8000])],
                                       baseline)
    assert "does NOT seed itself" in str(writing.value)


def test_shrink_only_is_keyed_not_counted(tmp_path, monkeypatch):
    """A hand-typed line is the same anti-pattern the tool refuses, so the
    committed file is judged against git history too. Keys, not line counts:
    trading one adjudicated line for one new violation keeps the count flat and
    must still fail."""
    baseline = tmp_path / "baseline.csv"
    monkeypatch.setattr(pin_consistency, "ROOT", tmp_path)

    def fake_blob(ref, path):
        assert ref == "HEAD"
        return ("symbol,bodies,kind,evidence\n"
                "?old@@YAXXZ,0x00001000 0x00002000,divergent-bodies,e\n")

    monkeypatch.setattr(pin_consistency, "_blob_at", fake_blob)

    baseline.write_text("symbol,bodies,kind,evidence\n"
                        "?new@@YAXXZ,0x00003000 0x00004000,divergent-bodies,e\n",
                        encoding="utf-8")
    with pytest.raises(SystemExit):
        pin_consistency.assert_shrink_only("HEAD", path=baseline)

    baseline.write_text("symbol,bodies,kind,evidence\n", encoding="utf-8")
    pin_consistency.assert_shrink_only("HEAD", path=baseline)


def test_the_guard_reads_only_half_the_resolvers_candidate_list():
    """load_symbol_map seeds a name from its functions.csv rows and THEN appends
    its symbols.csv pins, so the additive list the REL32 resolver walks is the
    union. scan() reads the pins alone, which means `len(pins) < 2` skips a name
    whose single pin disagrees with its own ledger row -- the same hazard, one
    source over. Documented and reported by --candidates, not gated."""
    lists = pin_consistency.candidate_lists()
    pins = pin_consistency.load_pins()
    wider = [name for name, addresses in lists.items()
             if len(addresses) > 1 and len(pins.get(name, ())) < 2]
    assert wider, "expected names the pin-only view cannot compare"
