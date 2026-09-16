"""ctor_vtable reads the operand the byte comparison masks away.

The tests that matter are the four over-flags that made the first run of this
useless: a placeholder destructor is not a class name, a template instantiation
sharing a folded vtable is not a defect, a one-slot vtable must not be read into
the next class's table, and a destructor two classes claim settles nothing. Plus
the shape it exists for -- 0x0024FC20, where fourteen constructor names sat on
one body and the vtable named exactly one of them.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import ctor_vtable as V  # noqa: E402

VTABLE = 0x01000000
OTHER = 0x01000100


class FakeImage:
    """Only the two questions classify() asks of the retail bytes."""

    def __init__(self, tables):
        self.tables = tables            # {vtable VA: [slot target rva]}

    def is_vtable(self, va):
        return va in self.tables

    def slots(self, va, cap=V.MAX_SLOTS):
        return self.tables.get(va, [])[:cap]


def _row(name, rva="0x00024FC20", size="46"):
    return {"name": name, "export_rva": "", "target_rva": rva, "target_size": size,
            "source": "a.cpp", "status": "matched", "notes": ""}


def _store(va, disp=0):
    """`mov dword ptr [esi+disp], va` -- the only form the decoder reads."""
    if disp == 0:
        return b"\xc7\x06" + va.to_bytes(4, "little")
    return b"\xc7\x46" + disp.to_bytes(1, "little") + va.to_bytes(4, "little")


def _verdicts(rows, tables, bodies, pinned=None, names_at=None):
    image = FakeImage(tables)
    got = V.classify(rows, image, names_at or {}, pinned or {},
                     read=lambda row, rva, size: bodies[row["name"]])
    return {f.name: f.verdict for f in got}


def test_the_shape_it_exists_for():
    """One body, two constructor names, and the vtable names one of them.

    This is 0x0024FC20 reduced: the two bodies are the SAME bytes -- there is
    only one body -- so no comparison of ours can separate them. The vtable's
    destructor slot can.
    """
    rows = [_row("??0LockWeaponCreate@@QAE@PAVThing@@@Z"),
            _row("??0DamDie@@QAE@PAVThing@@@Z")]
    body = _store(VTABLE)
    verdicts = _verdicts(
        rows,
        tables={VTABLE: [0x1000]},
        bodies={r["name"]: body for r in rows},
        names_at={0x1000: {"??_GLockWeaponCreate@@MAEPAXI@Z"}})
    assert verdicts["??0LockWeaponCreate@@QAE@PAVThing@@@Z"] == V.CONFIRMED
    assert verdicts["??0DamDie@@QAE@PAVThing@@@Z"] == V.CONTRADICTED


def test_a_placeholder_destructor_names_no_class():
    """`??_GGen_dtor_00076e90@@` makes no claim, so it cannot contradict one.

    Reading placeholders as classes indicted 1,239 rows on the live ledger --
    twenty times the real finding -- which is the whole reason this is a
    separate test rather than a line in the one above.
    """
    rows = [_row("??0DamageFXStore@@QAE@XZ")]
    verdicts = _verdicts(
        rows,
        tables={VTABLE: [0x1000]},
        bodies={rows[0]["name"]: _store(VTABLE)},
        names_at={0x1000: {"??_GGen_dtor_00076e90@@UAEPAXI@Z"}})
    assert verdicts[rows[0]["name"]] == V.UNNAMED


def test_template_instantiations_never_reach_a_verdict():
    """VectorClass<int> and VectorClass<char*> DO share one constructor.

    Their vtables were identical COMDATs the linker folded, so the surviving
    table names several instantiations and every naive comparison flags all of
    them. Excluded by construction: the class must be a plain identifier.
    """
    rows = [_row("??0?$VectorClass@H@@QAE@HPBH@Z"),
            _row("??0?$VectorClass@PAD@@QAE@HPBQAD@Z")]
    verdicts = _verdicts(
        rows,
        tables={VTABLE: [0x1000]},
        bodies={r["name"]: _store(VTABLE) for r in rows},
        names_at={0x1000: {"??_G?$VectorClass@H@@UAEPAXI@Z"}})
    assert verdicts == {}


def test_a_one_slot_vtable_does_not_borrow_the_next_ones_destructor():
    """INIEntry's table is one slot; INISection's begins in the next word.

    A walk that stops only at a non-code word reads them as one table and hands
    INIEntry's constructor INISection's destructor. The boundary is what the
    Image's start scan is for, so here the fake image supplies the same bound.
    """
    rows = [_row("??0INIEntry@@QAE@PAD0@Z")]
    verdicts = _verdicts(
        rows,
        tables={VTABLE: [0x2000]},                       # bounded: one slot
        bodies={rows[0]["name"]: _store(VTABLE)},
        names_at={0x2000: {"??_GGen_dtor_009e35b0@@UAEPAXI@Z"},
                  0x2004: {"??_GINISection@@UAEPAXI@Z"}})
    assert verdicts[rows[0]["name"]] == V.UNNAMED


def test_a_destructor_two_classes_claim_settles_nothing():
    """The attester is then this same defect one level down."""
    rows = [_row("??0MetaMap@@QAE@XZ")]
    verdicts = _verdicts(
        rows,
        tables={VTABLE: [0x1000]},
        bodies={rows[0]["name"]: _store(VTABLE)},
        names_at={0x1000: {"??_GAnimationSteeringUpdateModuleData@@UAEPAXI@Z",
                           "??_GPowerPlantUpdateModuleData@@UAEPAXI@Z"}})
    assert verdicts[rows[0]["name"]] == V.UNNAMED


def test_a_base_class_named_by_its_own_methods_is_cleared():
    """`??0SceneClass@@` installs a table full of `?...@SceneClass@@`.

    That is a base constructor doing exactly the right thing, even when the
    table's destructor slot carries a derived class's name -- so any mention of
    the class clears the row, not only an owner-grade symbol.
    """
    rows = [_row("??0SceneClass@@QAE@XZ")]
    verdicts = _verdicts(
        rows,
        tables={VTABLE: [0x1000, 0x1010]},
        bodies={rows[0]["name"]: _store(VTABLE)},
        names_at={0x1000: {"??_GSimpleSceneClass@@UAEPAXI@Z"},
                  0x1010: {"?Add_Render_Object@SceneClass@@UAEXPAVRenderObjClass@@@Z"}})
    assert verdicts[rows[0]["name"]] == V.CONFIRMED


def test_the_derived_store_wins_over_the_inlined_base_store():
    """AimWeaponBehavior's body installs the base vtable, then its own.

    Taking the union would answer "BehaviorModuleInterface" and indict the row;
    the last store to each object offset is the only one that survives the
    constructor.
    """
    body = _store(OTHER) + _store(OTHER, 0x0C) + _store(VTABLE) + _store(VTABLE, 0x0C)
    assert V.most_derived(body, {VTABLE, OTHER}.__contains__) == {VTABLE}


def test_a_polymorphic_member_does_not_name_its_enclosing_class():
    """PlayerTemplate is not polymorphic but copies a Money member at +0x1c.

    The member's vtable store is real and survives the constructor.  It says
    nothing about the identity of the enclosing copy constructor, however.
    """
    body = _store(VTABLE, 0x1C)
    assert V.most_derived(body, {VTABLE}.__contains__) == set()


def test_an_undecoded_vtable_constant_blocks_every_verdict():
    """A vtable that reached the body by a form the decoder does not read means
    which store lands last is unknown, so no verdict may rest on it."""
    body = _store(VTABLE) + b"\x68" + OTHER.to_bytes(4, "little")   # push imm32
    assert V.most_derived(body, {VTABLE, OTHER}.__contains__) is None
    rows = [_row("??0GameSpyConfig@@QAE@XZ")]
    verdicts = _verdicts(
        rows,
        tables={VTABLE: [0x1000], OTHER: [0x1000]},
        bodies={rows[0]["name"]: body},
        names_at={0x1000: {"??_GLadderList@@UAEPAXI@Z"}})
    assert verdicts[rows[0]["name"]] == V.UNDECODED


def test_a_pin_two_classes_claim_attests_nothing():
    """0x01073744 carries three ??_7 pins; taking the first indicted Snapshot."""
    pins = [["??_7BfmeBaseVUQ@@6B@", "0x01073744"],
            ["??_7DockUpdateModuleData@@6B@", "0x01073744"],
            ["??_7HordeContainModuleDataBase@@6B@", "0x01073744"],
            ["??_7LockWeaponCreate@@6B@", "0x010B18E4"]]
    pinned = V.pinned_vtables(pins)
    assert 0x01073744 not in pinned
    assert pinned[0x010B18E4] == "LockWeaponCreate"


def test_an_unreadable_body_is_reported_not_dropped():
    """A body this cannot read is one it would otherwise call clean."""
    rows = [_row("??0Weapon@@QAE@XZ")]
    verdicts = _verdicts(rows, tables={}, bodies={rows[0]["name"]: None})
    assert verdicts[rows[0]["name"]] == V.UNREADABLE


def test_the_next_vtable_start_bounds_the_slot_walk():
    """The bound itself, since the fake image above supplies one ready-made.

    Four one-slot tables laid back to back is INIEntry/INISection: unbounded,
    the first table reads all four destructors.
    """
    starts = [0x01145494, 0x01145498, 0x0114549C, 0x011454A0]
    assert V.slot_cap(starts, 0x01145494) == 1
    assert V.slot_cap(starts, 0x011454A0) == V.MAX_SLOTS      # nothing follows
    assert V.slot_cap(starts, 0x01145494, cap=0) == 0
