"""multi_name decides whether the claimants of one address COULD be one body.

The tests that matter are the two the obvious implementations get wrong: a
group differing ONLY at relocation sites is a real fold and must NOT be flagged
(that is the vftable case, and comparing target names flags 367 addresses on the
live ledger because of it), and an unreadable object must be REPORTED rather
than dropped into the benign bucket.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import multi_name  # noqa: E402


def _row(name, rva="0x00001000", size="8", source="a.cpp"):
    return {"name": name, "export_rva": "", "target_rva": rva, "target_size": size,
            "source": source, "status": "matched", "notes": ""}


def _reader(table):
    """table: name -> (body, relocs) or None."""
    return lambda row, size: table[row["name"]]


def test_bodies_differing_only_at_reloc_sites_are_a_real_fold():
    """The case that breaks the obvious implementation. Two constructors store
    DIFFERENT vftables, so their relocation targets differ -- but a vftable store
    is a masked DIR32, the bytes between the relocations are identical, and the
    linker really can fold them. Comparing target names calls this a defect."""
    rows = [_row("??0A@@QAE@XZ"), _row("??0B@@QAE@XZ")]
    table = {
        "??0A@@QAE@XZ": (b"\xc7\x06AAAA\x33\xc0", [(2, 0x0006, "??_7A@@6B@")]),
        "??0B@@QAE@XZ": (b"\xc7\x06BBBB\x33\xc0", [(2, 0x0006, "??_7B@@6B@")]),
    }
    out = list(multi_name.classify(rows, _reader(table)))
    assert [v for *_, v, _ in out] == [multi_name.FOLD]


def test_bodies_differing_between_the_relocs_cannot_share_an_address():
    rows = [_row("?winSetPrev@GameWindow@@QAEXPAV1@@Z"),
            _row("?winSetTooltipFunc@GameWindow@@QAEHXZ")]
    table = {
        "?winSetPrev@GameWindow@@QAEXPAV1@@Z": (b"\x89\x81\xf8\x01\x00\x00\xc3\x90", []),
        "?winSetTooltipFunc@GameWindow@@QAEHXZ": (b"\x89\x81\x00\x02\x00\x00\xc3\x90", []),
    }
    (rva, size, names, verdict, family), = multi_name.classify(rows, _reader(table))
    assert verdict == multi_name.DIFFER
    assert family, "one class, two method names -- the GameWindow shape"


def test_reloc_sites_at_different_offsets_are_different_bodies():
    """Same masked bytes are not enough: a call at a different offset is
    different code, even when everything around it happens to zero out."""
    rows = [_row("?a@C@@QAEXXZ"), _row("?b@C@@QAEXXZ")]
    table = {
        "?a@C@@QAEXXZ": (b"\x00\x00\x00\x00\xc3\x90\x90\x90", [(0, 0x0014, "?x@@YAXXZ")]),
        "?b@C@@QAEXXZ": (b"\x00\x00\x00\x00\xc3\x90\x90\x90", [(1, 0x0014, "?x@@YAXXZ")]),
    }
    (_, _, _, verdict, _), = multi_name.classify(rows, _reader(table))
    assert verdict == multi_name.DIFFER


def test_an_unreadable_object_is_reported_not_treated_as_benign():
    """A sweep that silently drops rows it could not load reports 'consistent'
    for a symbol whose contradiction it failed to read -- the swallowed-exception
    trap that put 18 unreviewed entries in a whitelist."""
    rows = [_row("?a@C@@QAEXXZ"), _row("?b@C@@QAEXXZ")]
    table = {"?a@C@@QAEXXZ": (b"\x90" * 8, []), "?b@C@@QAEXXZ": None}
    (_, _, _, verdict, _), = multi_name.classify(rows, _reader(table))
    assert verdict == multi_name.UNREADABLE


def test_placeholder_only_groups_are_set_aside():
    """1,048 gen_small ?j_ rows claim ILT slots by address on purpose, and
    ?dup_ names a real body of unknown identity. Neither asserts an identity, so
    neither can be wrong about one."""
    rows = [_row("?j_00001000@@YAXXZ"), _row("?dup_00001000@@YAXXZ")]
    (_, _, _, verdict, _), = multi_name.classify(rows, _reader({}))
    assert verdict == multi_name.PLACEHOLDERS


def test_a_lone_name_is_not_a_group():
    rows = [_row("?a@C@@QAEXXZ"), _row("?b@C@@QAEXXZ", rva="0x00002000")]
    assert list(multi_name.classify(rows, _reader({}))) == []


def test_same_class_label_does_not_fire_across_classes():
    assert multi_name.same_class_different_methods(
        ["?winSetPrev@GameWindow@@QAEXXZ", "?winSetNext@GameWindow@@QAEXXZ"])
    assert not multi_name.same_class_different_methods(
        ["?getFrame@GameLogic@@QAEIXZ", "?winGetStyle@GameWindow@@QAEIXZ"])
    assert not multi_name.same_class_different_methods(
        ["?same@C@@QAEXXZ", "?same@C@@QAEXXZ"]), "one method name is not a family"


def test_a_large_group_is_reported_apart_from_a_real_candidate():
    """Forty names on one nine-byte constructor is an ICF group the linker
    really built. One member compiling differently HERE points at our compile of
    that member long before it points at thirty-nine wrong rows, so it must not
    land in the same bucket as a two-name collision."""
    def group(n):
        return [_row("?m%d@C@@QAEXXZ" % i) for i in range(n)]
    table = {"?m0@C@@QAEXXZ": (b"\x90" * 8, [])}
    for i in range(1, 40):
        table["?m%d@C@@QAEXXZ" % i] = (b"\x91" * 8, [])
    (_, _, _, verdict, _), = multi_name.classify(group(40), _reader(table))
    assert verdict == multi_name.ODD_MEMBER

    two = [_row("?a@C@@QAEXXZ"), _row("?b@C@@QAEXXZ")]
    table2 = {"?a@C@@QAEXXZ": (b"\x90" * 8, []), "?b@C@@QAEXXZ": (b"\x91" * 8, [])}
    (_, _, _, verdict, _), = multi_name.classify(two, _reader(table2))
    assert verdict == multi_name.DIFFER, "a two-name collision is still a candidate"


def test_a_family_conflict_is_flagged_even_when_the_bodies_match_here():
    """The GameWindow case, and the only one structure cannot see. Our header is
    short by a field, so winSetEnabledColor compiles to exactly what retail's
    winSetEnabledImage does -- identical bytes, both green, and one of the two
    names is on the wrong body."""
    rows = [_row("?winSetEnabledColor@GameWindow@@QAEHHH@Z"),
            _row("?winSetEnabledImage@GameWindow@@QAEHHPBVImage@@@Z")]
    same = (b"\x89\x81\x48\x00\x00\x00\xc3\x90", [])
    table = {r["name"]: same for r in rows}
    (_, _, _, verdict, _), = multi_name.classify(rows, _reader(table))
    assert verdict == multi_name.FAMILY


def test_names_differing_everywhere_are_left_alone():
    """getClassMemoryPool and getModuleNameKey share a body legitimately -- they
    are two functions, not one operation on two fields. This is why the test is
    ONE token apart rather than any name difference; a looser rule flags all
    seven pool-glue groups."""
    rows = [_row("?getClassMemoryPool@W3DTruckDraw@@CAPAVMemoryPool@@XZ"),
            _row("?getModuleNameKey@W3DTruckDraw@@UBE?AW4NameKeyType@@XZ")]
    same = (b"\x90" * 8, [])
    table = {r["name"]: same for r in rows}
    (_, _, _, verdict, _), = multi_name.classify(rows, _reader(table))
    assert verdict == multi_name.FOLD


def test_a_large_icf_group_is_not_a_family_conflict():
    """Any forty-name group of trivial accessors contains SOME one-token pair.
    Applying the name test to it would flag the largest honest folds in the
    tree, so it is bounded by the same size threshold."""
    names = ["?get%s@C@@QBEHXZ" % w for w in
             ("Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot")]
    rows = [_row(n) for n in names]
    same = (b"\x90" * 8, [])
    (_, _, _, verdict, _), = multi_name.classify(rows, _reader({n: same for n in names}))
    assert verdict == multi_name.FOLD
