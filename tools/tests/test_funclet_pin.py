"""A $L funclet pin is a per-compilation ordinal, so the gate may not trust one.

MSVC numbers compiler-local labels per translation unit. Any edit that changes
how many labels precede a funclet group renumbers it, and the ledger's
`object-symbol=$L47551` then names a DIFFERENT body -- silently, because that
number still exists. Seven PlayerTemplate rows went red in a full gate exactly
that way: the group had shifted eight lower, so each pin landed on the 16-byte
`and eax,0xFFFFFEFF` funclet instead of its own 14-byte `and eax,-2` one, while
a per-file build of the same rows stayed green.

The bodies here are that family: near-identical guard rollbacks that differ only
in which bit they clear, which is what makes a wrong pick look plausible.
"""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


PARENT = "?findPlayerTemplate@Store@@QBEPBVPlayerTemplate@@W4NameKeyType@@@Z"
GUARD = 0x012ED794
# retail: mov eax,[guard] / and eax,-2 / mov [guard],eax / ret
TARGET = bytes.fromhex("a1") + struct.pack("<I", GUARD) + bytes.fromhex("83e0fe") \
    + bytes.fromhex("a3") + struct.pack("<I", GUARD) + bytes.fromhex("c3")


def funclet(clear):
    """One guard-rollback body, relocation sites holding their pre-link addend."""
    return bytes.fromhex("a1") + b"\0\0\0\0" + clear + bytes.fromhex("a3") + b"\0\0\0\0" \
        + bytes.fromhex("c3")


BIT0 = funclet(bytes.fromhex("83e0fe"))        # and eax,-2          -- retail's
BIT1 = funclet(bytes.fromhex("83e0fd"))        # and eax,-3
BIT16 = funclet(bytes.fromhex("25fffeffff"))   # and eax,0xFFFEFFFF  -- two longer


def write_object(path, bodies, sites=None):
    """A one-section object: `bodies` back to back as {label: bytes}, each with
    its two DIR32 sites, plus the __ehhandler$ symbol that marks the group."""
    names, blobs = list(bodies), b"".join(bodies.values())
    offsets, at = {}, 0
    for name in names:
        offsets[name] = at
        at += len(bodies[name])

    relocs, symbols, strings = [], [], bytearray(b"\0\0\0\0")

    def add_symbol(name, value, section):
        if len(name) <= 8:
            field = name.encode().ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(name.encode() + b"\0")
        symbols.append(struct.pack("<8sIhHBB", field, value, section, 0, 3, 0))

    add_symbol("?guard@@3HA", 0, 2)  # the static-local guard the bodies read
    for name in names:
        add_symbol(name, offsets[name], 1)
        where = (sites or {}).get(name, (1, len(bodies[name]) - 5))
        for site in where:
            relocs.append(struct.pack("<IIH", offsets[name] + site, 0, 0x0006))
    add_symbol(f"__ehhandler${PARENT}", len(blobs), 1)

    raw_at = 20 + 40
    reloc_at = raw_at + len(blobs)
    symbol_at = reloc_at + len(relocs) * 10
    header = struct.pack("<HHIIIHH", 0x014C, 1, 0, symbol_at, len(symbols), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text\0\0\0", 0, 0, len(blobs), raw_at,
                          reloc_at, 0, len(relocs), 0, 0)
    path.write_bytes(header + section + blobs + b"".join(relocs)
                     + b"".join(symbols) + bytes(strings))
    return path


def make_row(pin, size=len(TARGET)):
    return {"name": "uw_00bfa6c0", "target_rva": "0x00BFA6C0", "target_size": str(size),
            "source": "Code/GameEngine/Source/Common/RTS/PlayerTemplate.cpp",
            "status": "matched", "notes": f"gen-funclet;parent={PARENT};object-symbol={pin}"}


@pytest.fixture(autouse=True)
def retail(monkeypatch):
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: TARGET[:size])


def compile_row(obj, pin, **kwargs):
    return build.compile_function(make_row(pin, **kwargs), {}, obj)


def test_a_renumbered_pin_is_re_identified_from_the_parents_group(tmp_path):
    """The reported failure: the group shifted, so the pin names a longer body."""
    obj = write_object(tmp_path / "renumbered.obj",
                       {"$L47543": BIT0, "$L47544": BIT1, "$L47551": BIT16})

    patch = compile_row(obj, "$L47551")

    assert patch["bytes"] == patch["target"], "the row's own funclet still compiles exact"
    assert "$L47551" in patch["note"] and "$L47543" in patch["note"], \
        "the note names the stale pin and the label that holds the body now"


def test_a_pin_that_still_holds_its_funclet_is_used_untouched(tmp_path):
    """The common case must stay a plain lookup: no search, no note, no churn."""
    obj = write_object(tmp_path / "current.obj",
                       {"$L47551": BIT0, "$L47552": BIT1, "$L47559": BIT16})

    patch = compile_row(obj, "$L47551")

    assert patch["bytes"] == patch["target"]
    assert patch["note"] is None


def test_a_group_of_look_alikes_is_refused_not_picked_from(tmp_path):
    """Two bodies answer equally well: byte evidence cannot choose, so nothing does."""
    obj = write_object(tmp_path / "twins.obj",
                       {"$L47543": BIT0, "$L47547": BIT0, "$L47551": BIT16})

    with pytest.raises(SystemExit) as exc:
        compile_row(obj, "$L47551")

    message = str(exc.value)
    assert "$L47543" in message and "$L47547" in message, "both candidates are named"
    assert "uw_00bfa6c0" in message
    assert "will not pick one" in message


def test_a_funclet_that_stopped_matching_goes_red_with_what_it_compiled(tmp_path):
    """No recovery available: the row must fail on its bytes and say why, never
    raise -- a red row's job is to print the dump the next reader debugs from."""
    obj = write_object(tmp_path / "regressed.obj", {"$L47551": BIT16})

    patch = compile_row(obj, "$L47551")

    assert patch["bytes"] != patch["target"], "a body that is not retail's stays red"
    assert len(patch["bytes"]) == len(patch["target"])
    assert "$L47551" in patch["note"] and "nothing in the parent's group" in patch["note"]


def test_a_vanished_pin_is_still_recovered(tmp_path):
    """The renumbering can also run the label off the end of the group."""
    obj = write_object(tmp_path / "gone.obj", {"$L47543": BIT0, "$L47544": BIT1})

    patch = compile_row(obj, "$L47551")

    assert patch["bytes"] == patch["target"]
    assert "$L47543" in patch["note"]


def test_a_vanished_pin_with_nothing_to_recover_reports_and_still_fails(tmp_path):
    """The refusal has to show its work AND still fail.

    This used to raise a bare ValueError("symbol not found in object: $L47551"),
    which killed the gate before it printed a single result line and named
    nothing but a compiler-local label. It now raises SystemExit carrying the
    row, the source, the missing pin and every candidate examined -- and
    SystemExit is what run() records as a failure, so the report cannot turn
    into a pass. That second half is the point: a refusal that prints nicely and
    succeeds would be worse than the crash it replaced.
    """
    obj = write_object(tmp_path / "empty.obj", {"$L47544": BIT1})

    with pytest.raises(SystemExit) as exc:
        compile_row(obj, "$L47551")

    message = str(exc.value)
    assert "$L47551" in message, "the vanished pin is still named"
    assert "uw_00bfa6c0" in message, "and so is the row that wanted it"
    assert "deserves one" in message, "and it asks whether the row should heal at all"
    assert "$L47544" in message, "the candidate examined is shown"
    assert "surviving=" in message, "with what the comparison actually saw"


def write_split_object(path, bodies):
    """The same group, laid out the way MSVC 7.1 actually emits it.

    The compiler gives `__ehhandler$<parent>` a COMDAT of its own, so it does
    NOT share a section with the $L funclet bodies -- those stay in the parent
    function's. Every one of the eighteen ehhandlers in StagingRoomGameInfo.obj
    is split this way. Searching only the handler's section therefore finds no
    candidate at all and a renumbered pin dies instead of healing.
    """
    names, blobs = list(bodies), b"".join(bodies.values())
    offsets, at = {}, 0
    for name in names:
        offsets[name] = at
        at += len(bodies[name])

    relocs, symbols, strings = [], [], bytearray(b"\0\0\0\0")

    def add_symbol(name, value, section):
        if len(name) <= 8:
            field = name.encode().ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(name.encode() + b"\0")
        symbols.append(struct.pack("<8sIhHBB", field, value, section, 0, 3, 0))

    add_symbol("?guard@@3HA", 0, 3)
    add_symbol(PARENT, 0, 1)                    # the parent body, with the labels
    for name in names:
        add_symbol(name, offsets[name], 1)
        for site in (1, len(bodies[name]) - 5):
            relocs.append(struct.pack("<IIH", offsets[name] + site, 0, 0x0006))
    add_symbol(f"__ehhandler${PARENT}", 0, 2)   # its own COMDAT, section 2

    raw_at = 20 + 80
    reloc_at = raw_at + len(blobs)
    symbol_at = reloc_at + len(relocs) * 10
    header = struct.pack("<HHIIIHH", 0x014C, 2, 0, symbol_at, len(symbols), 0, 0)
    text = struct.pack("<8sIIIIIIHHI", b".text\0\0\0", 0, 0, len(blobs), raw_at,
                       reloc_at, 0, len(relocs), 0, 0)
    handler = struct.pack("<8sIIIIIIHHI", b".text\0\0\0", 0, 0, 0, 0, 0, 0, 0, 0, 0)
    path.write_bytes(header + text + handler + blobs + b"".join(relocs)
                     + b"".join(symbols) + bytes(strings))
    return path


def test_a_renumbered_pin_heals_when_the_ehhandler_is_its_own_comdat(tmp_path):
    """The parent's section carries the bodies even when the handler's does not."""
    obj = write_split_object(tmp_path / "split.obj",
                             {"$L70459": BIT1, "$L70461": BIT0, "$L70463": BIT16})

    patch = compile_row(obj, "$L70459")

    assert patch["bytes"] == patch["target"], "the row's own funclet still compiles exact"
    assert "$L70459" in patch["note"] and "$L70461" in patch["note"], \
        "the note names the stale pin and the label holding the body now"


def test_a_fully_relocated_body_is_not_a_candidate(tmp_path):
    """A body with no unmasked byte left compares equal to ANY target its size.

    That is an absence of evidence, not a match, and counting it is how a DATA
    table ties with a real funclet. AIPlayer.cpp's $L86009 is four label
    pointers covering all eight of its bytes; it tied with $L85915, which
    decodes to retail's own `lea ecx,[ebp-0x1c]; jmp <dtor>`, and the gate
    refused the pair rather than pick between them. Requiring one surviving
    byte separates them without choosing.
    """
    decoy = b"\0" * len(TARGET)                      # every byte a relocation site
    obj = write_object(tmp_path / "table.obj",
                       {"$L47543": BIT0, "$L47547": decoy, "$L47551": BIT16},
                       sites={"$L47547": (0, 4, 8, 10)})   # covers all 14 bytes

    patch = compile_row(obj, "$L47551")

    assert patch["bytes"] == patch["target"], "the real funclet still compiles exact"
    assert "$L47543" in patch["note"], "the note names the body that actually holds it"
    assert "$L47547" not in patch["note"], "the all-masked table is not a candidate"
