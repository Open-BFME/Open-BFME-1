"""A REL32 site cannot straddle a row's end, and the gate must say so by name.

`resolved` in compile_function is a bytearray sized to the row, and the REL32
branch assigns a fixed four-byte displacement into it. A site starting at
`target_size-1..-3` therefore GROWS the body past the row instead of failing:
verify_functions then prints two hex dumps of different lengths with nothing
naming the extent, the offset or the symbol, and the straddling write has also
clobbered the row's own last bytes, so the visible diff is not where the fault
is.

Raising is the point. A straddling call displacement means the ROW'S EXTENT is
wrong -- a function's last instruction cannot end after the function does -- so
clipping the write would make the body compare equal on a boundary the ledger
got wrong, which is the silent pass this gate exists to prevent.
"""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


CALLEE = "?theCallee@Store@@QBEXXZ"
CALLEE_RVA = 0x00401000
TARGET_RVA = 0x00BFA6C0
SITE = 6  # the REL32 displacement occupies bytes 6..9 of the body

# push ebp / mov ebp,esp / pop ebp / nop / call theCallee / ret, then padding.
BODY = bytes.fromhex("558bec5d90") + bytes.fromhex("e8") + b"\0\0\0\0" \
    + bytes.fromhex("c3cc")
# retail, linked: the same body with the call displacement the linker wrote.
TARGET = BODY[:SITE] + struct.pack("<i", CALLEE_RVA - (TARGET_RVA + SITE + 4)) \
    + BODY[SITE + 4:]

STRADDLES = SITE + 2   # 8: the site's last two bytes fall past the row's end
FITS = SITE + 4        # 10: the site ends exactly on the row's end


def write_object(path):
    """A one-section object: BODY at offset 0 with its one REL32 site.

    Copied from test_funclet_pin.write_object, narrowed to a single body and a
    relocation whose type and target symbol this test chooses.
    """
    symbols, strings = [], bytearray(b"\0\0\0\0")

    def add_symbol(name, value, section, storage):
        if len(name) <= 8:
            field = name.encode().ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(name.encode() + b"\0")
        symbols.append(struct.pack("<8sIhHBB", field, value, section, 0, storage, 0))

    add_symbol(CALLEE, 0, 0, 2)   # undefined external: the call's target
    add_symbol("_straddle", 0, 1, 2)
    relocs = [struct.pack("<IIH", SITE, 0, 0x0014)]  # IMAGE_REL_I386_REL32

    raw_at = 20 + 40
    reloc_at = raw_at + len(BODY)
    symbol_at = reloc_at + len(relocs) * 10
    header = struct.pack("<HHIIIHH", 0x014C, 1, 0, symbol_at, len(symbols), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text\0\0\0", 0, 0, len(BODY), raw_at,
                          reloc_at, 0, len(relocs), 0, 0)
    path.write_bytes(header + section + BODY + b"".join(relocs)
                     + b"".join(symbols) + bytes(strings))
    return path


def make_row(size):
    return {"name": "uw_00bfa6c0", "target_rva": f"0x{TARGET_RVA:08X}",
            "target_size": str(size),
            "source": "Code/GameEngine/Source/Common/RTS/PlayerTemplate.cpp",
            "status": "matched", "notes": "object-symbol=_straddle"}


@pytest.fixture(autouse=True)
def retail(monkeypatch):
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: TARGET[:size])


def compile_row(obj, size):
    # A real symbol_map: with the default empty one the site takes the
    # `unresolved` path and nothing is ever written, so neither case is tested.
    return build.compile_function(make_row(size), {CALLEE: [CALLEE_RVA]}, obj)


def test_a_rel32_running_past_the_rows_end_is_refused_by_name(tmp_path):
    """The row is two bytes short of holding its own call: that is a ledger fault."""
    obj = write_object(tmp_path / "straddle.obj")

    with pytest.raises(SystemExit) as exc:
        compile_row(obj, STRADDLES)

    message = str(exc.value)
    assert "uw_00bfa6c0" in message, "the row is named"
    assert CALLEE in message, "the callee whose displacement does not fit is named"
    assert f"{SITE}" in message, "the offset of the site is named"
    assert str(STRADDLES) in message and str(SITE + 4) in message, \
        "both the row's size and the size the site demands are named"


def test_a_rel32_ending_exactly_on_the_rows_end_still_resolves(tmp_path):
    """Negative control: an unconditional raise would pass the test above too."""
    obj = write_object(tmp_path / "fits.obj")

    patch = compile_row(obj, FITS)

    assert len(patch["bytes"]) == FITS, "the body is exactly the row's extent"
    assert patch["bytes"] == patch["target"], "the displacement resolved to retail's"
    assert patch["unresolved"] == []


def test_a_differing_rel32_site_says_what_retail_called(tmp_path, capsys, monkeypatch):
    """The other half of "naming neither the extent nor this site".

    A site that fits but resolves to the wrong copy of the callee -- the ICF
    case the candidate list exists for -- used to print only the two hex dumps,
    so reading it meant decoding the displacement, following the thunk and
    grepping the ledger by hand, once per red row.
    """
    obj = write_object(tmp_path / "differs.obj")
    twin = CALLEE_RVA + 0x40  # a second fold of the same name: not what retail encodes

    patch = build.compile_function(make_row(FITS), {CALLEE: [twin]}, obj)
    assert patch["bytes"] != patch["target"], "the wrong fold is a byte mismatch"

    monkeypatch.setattr(build, "ledger_names_by_address",
                        lambda: {CALLEE_RVA: [("?theCallee@Store@@QBEXXZ", "matched")]})
    build.explain_rel32(patch)
    line = capsys.readouterr().out

    assert f"+0x{SITE:x}" in line, "the offset of the differing site"
    assert CALLEE in line, "the relocation's symbol"
    assert f"0x{CALLEE_RVA:08X}" in line, "the address retail actually calls"
    assert "matched" in line, "what the ledger calls that address"
    assert f"0x{twin:08X}" in line, "the candidate emitted instead"
