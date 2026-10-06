"""boot_image: retail's .reloc table and ILT, the linked-image equivalence check, overlay admission.

The check tests need a linked image (`python3 tools/boot_image.py link`, about
10 s with the VS2003 toolchain); the overlay tests need the objects of
OVERLAY_SET built (tools/build.py). Each skips without them.
"""
import collections
import json
import shutil
import struct
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_image  # noqa: E402

BOOT = ROOT / "build" / "boot"


def block(page, offsets):
    entries = [0x3000 | o for o in offsets]
    if len(entries) % 2:
        entries.append(0)
    return struct.pack("<II", page, 8 + 2 * len(entries)) + struct.pack(f"<{len(entries)}H", *entries)


def test_parse_blocks_stops_at_a_non_block():
    good = block(0x1000, [0x10, 0x20]) + block(0x2000, [0x30])
    sites, pages, stop = boot_image.parse_blocks(good + b"\0" * 16)
    assert (sites, pages, stop) == ([0x1010, 0x1020, 0x2030], [0x1000, 0x2000], len(good))


def test_parse_blocks_rejects_pages_out_of_order():
    sites, _, _ = boot_image.parse_blocks(block(0x2000, [1]) + block(0x1000, [2]))
    assert sites == [0x2001]


@pytest.fixture(scope="module")
def retail():
    return boot_image.Retail()


def test_table_is_whole_and_stale_sites_are_dropped(retail):
    live, info = boot_image.all_sites(retail)
    assert info["table_sites"] == 284870
    assert info["dropped"] == {"stale-int3-padding": 67, "stale-not-an-address": 64, "stale-null": 2}
    assert retail.u32(0x61F10) == 0x01B80046            # a protection stub's field straddling two instructions
    assert 0x61F10 not in live and len(live) == 284737
    assert boot_image.site_target(retail, retail.u32(live[0])) in ("iat", "piece", "base")


def test_ilt_is_all_thunks(retail):
    slots = boot_image.ilt_slots(retail)
    assert len(slots) == 60965
    assert slots[0] == (0x1005, 0x874E0)
    assert all(boot_image.ILT[1] <= t for _, t in slots)


def linked():
    return (BOOT / "boot.exe").exists() and (BOOT / "boot.json").exists()


@pytest.fixture(scope="module")
def image(retail, tmp_path_factory):
    if not linked():
        pytest.skip("no linked boot image (python3 tools/boot_image.py link)")
    rep = json.loads((BOOT / "boot.json").read_text())
    pieces = boot_image.layout(retail, rep.get("overlay", {}).get("specs", ()))[0]
    base = int(rep["base"], 16)
    publics = boot_image.read_publics(BOOT / "boot.map", base)
    return pieces, base, publics, tmp_path_factory.mktemp("boot")


def mutated(image, exe, rva, piece, value):
    """A copy of exe with the dword at retail RVA `rva` (in piece) set to value."""
    import pefile
    pieces, base, publics, tmp = image
    out = tmp / f"m_{rva:x}_{value:x}.exe"
    shutil.copyfile(exe, out)
    pe = pefile.PE(str(out))
    off = pe.get_offset_from_rva(publics[piece.public] + rva - piece.start)
    pe.close()
    data = bytearray(out.read_bytes())
    data[off:off + 4] = struct.pack("<I", value)
    out.write_bytes(bytes(data))
    return out


def check(retail, image, exe):
    pieces, base, publics, _ = image
    return boot_image.check_image(retail, pieces, exe, base, publics)


def text_piece(pieces):
    return max((p for p in pieces if p.name.startswith(".text") and p.unit is None), key=lambda p: p.size)


def test_clean_image_is_equivalent(retail, image):
    counts, bad = check(retail, image, BOOT / "boot.exe")
    assert (counts.get("reloc-bad", 0), counts.get("ilt-bad", 0), counts["bytes-differ"], bad) == (0, 0, 0, [])
    assert counts["ilt-ok"] == 60965 and counts["exports"] == 1818 and counts["imports"] == 681


def test_wrong_pointer_is_caught(retail, image):
    p = text_piece(image[0])
    site, _, _ = next(x for x in p.relocs if x[1] == boot_image.DIR32 and x[2][0] == "piece")
    counts, _ = check(retail, image, mutated(image, BOOT / "boot.exe", site, p, image[1] + 0x1234))
    assert counts.get("reloc-bad") == 1


def test_unrelocated_retail_address_is_caught(retail, image):
    p = text_piece(image[0])
    site, _, _ = next(x for x in p.relocs if x[1] == boot_image.DIR32 and x[2][0] == "piece")
    counts, _ = check(retail, image, mutated(image, BOOT / "boot.exe", site, p, retail.u32(site)))
    assert counts.get("reloc-bad") == 1


def test_wrong_ilt_thunk_is_caught(retail, image):
    p = text_piece(image[0])
    site, _, _ = next(x for x in p.relocs if x[1] == boot_image.REL32)
    rel = retail.u32(site)
    counts, _ = check(retail, image, mutated(image, BOOT / "boot.exe", site, p, (rel + 0x10) & 0xFFFFFFFF))
    assert (counts.get("ilt-bad"), counts.get("reloc-bad")) == (1, 1)


def test_changed_byte_is_caught(retail, image):
    p = text_piece(image[0])
    sites = {s for s, _, _ in p.relocs}
    a = next(x for x in range(0x60000, 0x61000, 4) if not any(x - 3 <= s <= x + 3 for s in sites))
    counts, _ = check(retail, image, mutated(image, BOOT / "boot.exe", a, p, retail.u32(a) ^ 0xFF))
    assert counts["bytes-differ"] == 1


# ---------------------------------------------------------------- overlay
OVERLAY_SET = "game/Libraries/Source/WWVegas/WWLib/"


def overlay_ready():
    try:
        rows = boot_image.overlay_rows([OVERLAY_SET])
        boot_image.build.vc71_root()
    except (SystemExit, Exception):
        return False
    built = sum(1 for r in rows if boot_image.build.row_object(r).exists())
    return bool(rows) and built >= 0.95 * len(rows)       # a missing object is a `no-object` refusal


class MutatedObjects:
    """link_cycle.Objects, but one object comes back changed by `edit(secs, syms, data)`."""
    def __init__(self, path, edit):
        import link_cycle
        self.inner, self.path, self.edit = link_cycle.Objects([]), Path(path), edit

    def get(self, p):
        o = self.inner.get(p)
        if o is not None and Path(p) == self.path and self.edit:
            secs, syms, data = o
            o = self.inner.cache[Path(p)] = self.edit(secs, syms, bytearray(data))
            self.edit = None
        return o


needs_overlay = pytest.mark.skipif(not overlay_ready(), reason=f"objects of {OVERLAY_SET} not built")


@pytest.fixture(scope="module")
def overlay(retail):
    sites, _ = boot_image.all_sites(retail)
    rows = boot_image.overlay_rows([OVERLAY_SET])

    def plan(objs=None):            # admission logic only: every built object counts as current
        units, refused, names = boot_image.overlay_plan(retail, sites, rows, objs, lambda source, obj: True)
        return {u.rva: u for u in units}, {int(x["target_rva"], 16): why for x, why in refused}, names
    return plan


def named_callee(retail, units):
    """(unit, reloc index, other symbol index): an admitted unit calling a named
    function through retail's ILT thunk, and another named function of its
    object it could call instead."""
    ident = boot_image.identities(retail)
    for u in units.values():
        if not u.bind.get("name-via-ilt-thunk"):
            continue
        secs, syms, _ = u.obj
        s = secs[u.sec - 1]
        named = [(k, si) for k, (off, si, kind) in enumerate(s.relocs)
                 if kind == boot_image.REL32 and u.off <= off < u.off + u.size and syms[si].sec == 0
                 and syms[si].name in ident]
        others = [i for i, y in syms.items() if y.sec == 0 and y.name in ident and y.name.startswith("?")]
        for k, si in named:
            alt = next((i for i in others if ident[syms[i].name].isdisjoint(ident[syms[si].name])), None)
            if alt is not None:
                return u, k, alt
    return None


@needs_overlay
def test_overlay_admits_units(overlay):
    units, refused, names = overlay()
    assert units, refused
    assert all(u.why is None for u in units.values())
    bound = collections.Counter()
    for u in units.values():
        bound.update(u.bind)
    assert bound["name-via-ilt-thunk"] and bound["internal-via-ilt-thunk"]   # calls keep retail's thunks
    assert refused[0x8837] == "in-ilt"      # an authored "thunk" body: the ILT stays the linker's


@needs_overlay
def test_wrong_callee_is_refused(retail, overlay):
    units, _, _ = overlay()
    found = named_callee(retail, units)
    assert found, "no admitted unit with a named callee"
    u, k, alt = found

    def edit(secs, syms, data):
        s = secs[u.sec - 1]
        s.relocs = [(o, alt if j == k else i, t) for j, (o, i, t) in enumerate(s.relocs)]
        return secs, syms, bytes(data)
    _, refused, _ = overlay(MutatedObjects(u.path, edit))
    assert refused.get(u.rva) == f"identity-differs:{u.obj[1][alt].name}"


@needs_overlay
def test_wrong_byte_is_refused(overlay):
    units, _, _ = overlay()
    u = next(x for x in units.values() if x.size > 16)
    masked = {o + k for o, _, _ in u.relocs for k in range(4)}
    at = next(o for o in range(4, u.size) if o not in masked)

    def edit(secs, syms, data):
        data[secs[u.sec - 1].ptr + u.off + at] ^= 0x01
        return secs, syms, bytes(data)
    _, refused, _ = overlay(MutatedObjects(u.path, edit))
    assert refused.get(u.rva) == "bytes-differ"


@needs_overlay
def test_stale_object_is_refused(retail):
    sites, _ = boot_image.all_sites(retail)
    rows = boot_image.overlay_rows([OVERLAY_SET])
    units, refused, _ = boot_image.overlay_plan(retail, sites, rows, None, lambda source, obj: False)
    assert not units
    assert {why for _, why in refused} <= {"stale-object", "in-ilt", "no-object"}


@pytest.fixture(scope="module")
def overlay_image(retail, tmp_path_factory):
    if not overlay_ready():
        pytest.skip(f"objects of {OVERLAY_SET} not built")
    tmp = tmp_path_factory.mktemp("ov")
    rep = boot_image.build_image(0x10000000, tmp, "ov", [OVERLAY_SET])
    pieces = boot_image.layout(retail, [OVERLAY_SET])[0]
    return rep, (pieces, 0x10000000, boot_image.read_publics(tmp / "ov.map", 0x10000000), tmp)


def test_overlay_links_and_is_equivalent(overlay_image):
    rep, _ = overlay_image
    ov, chk = rep["overlay"], rep["check"]
    assert boot_image.image_ok(rep), rep.get("check_bad")
    assert ov["units"] and chk["authored-bytes-equal"] == ov["bytes"]
    assert (chk.get("authored-bytes-differ"), chk.get("authored-reloc-bad", 0)) == (0, 0)


def test_authored_wrong_relocation_target_is_caught(retail, overlay_image):
    rep, image = overlay_image
    pieces, base, publics, tmp = image
    p = next(x for x in pieces if x.unit is not None and any(r[2][0] == "piece" for r in x.relocs))
    site, kind, tgt = next(x for x in p.relocs if x[2][0] == "piece")
    good = publics[tgt[1].public] + tgt[2] - tgt[1].start + (base if kind == boot_image.DIR32 else 0)
    counts, _ = check(retail, image, mutated(image, tmp / "ov.exe", site, p, good + 0x10))
    assert counts.get("authored-reloc-bad") == 1
