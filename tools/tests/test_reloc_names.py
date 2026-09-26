"""The naming harvester, what it publishes, and what the queue serves from it.

The mechanism these pin down is easy to get subtly wrong in a way that still
produces a plausible-looking file: resolving the callee through symbols.csv
instead of the retail bytes yields only names the project already had, and
stopping at the incremental-link thunk names the jump table rather than the
function. Both mistakes score zero new identity while looking like they worked.
"""
import csv
import importlib.util
import re
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
ROOT = TOOLS.parent
RELOC_NAMES = ROOT / "targets/game/reverse" / "reloc_names.csv"
REL32 = 0x0014
NOTES_RE = re.compile(r"reloc-derived;call-sites=[1-9]\d*;identity=(real|generated)")


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")
next_work = _load("next_work")


def call_row(caller_rva, callee_rva, opcode=0xE8, symbol="?callee@@YAXXZ",
             name="?caller@@YAXXZ"):
    """A byte-true row whose first instruction calls callee_rva.

    `name` is the caller's own ledger name: the harvester reads it to decide
    whether the row is entitled to name anything (a ?dup_<rva> row is not), so
    a fixture that omitted it would exercise the wrong branch.
    """
    displacement = struct.pack("<i", callee_rva - caller_rva - 5)
    return {"name": name, "target_rva": caller_rva, "source": "game/test.cpp",
            "target": bytes([opcode]) + displacement + b"\xc3",
            "relocs": [(1, REL32, symbol)]}


def a_thunked_function():
    """Return (body rva, one of its incremental-link thunk rvas)."""
    body, thunks = next(iter(build.build_call_thunks().items()))
    return body, thunks[0]


def a_publishable_function():
    """A thunked body that survives select_reloc_names' anonymous+unclaimed
    filters, so a test can exercise what the file actually publishes."""
    inventory = {int(row["rva"], 16): row["name"] for row in csv.DictReader(
        (ROOT / "targets/game/reverse" / "ghidra_functions.csv").open(
            newline="", encoding="utf-8"))}
    claimed = {int(row["target_rva"], 16)
               for row in build.load_all_function_rows()}
    for body in build.build_call_thunks():
        if inventory.get(body, "").startswith("FUN_") and body not in claimed:
            return body
    raise AssertionError("no anonymous unclaimed thunked body in the image")


def test_callee_comes_from_the_retail_bytes():
    body, _ = a_thunked_function()
    caller = 0x1000
    named = build.harvest_reloc_names([call_row(caller, body)])
    assert named == {body: {"names": {"?callee@@YAXXZ"},
                            "sources": {"game/test.cpp"}, "sites": 1}}, named
    print("PASS callee decoded from the displacement in the retail bytes")


def test_a_relocation_not_behind_a_call_is_ignored():
    """A REL32 fixup also sits behind `jmp` and inside data. Only the byte in
    front of the displacement says which, and reading the wrong ones would
    attach callee names to addresses nothing calls."""
    body, _ = a_thunked_function()
    assert build.harvest_reloc_names([call_row(0x1000, body, opcode=0xE9)]) == {}
    print("PASS relocation not preceded by 0xE8 is ignored")


def test_the_incremental_link_thunk_is_followed_to_the_body():
    """Call sites encode the thunk, not the function, for most of the image."""
    body, thunk = a_thunked_function()
    assert thunk != body
    named = build.harvest_reloc_names([call_row(0x1000, thunk)])
    assert list(named) == [body], (thunk, body, list(named))
    print(f"PASS thunk 0x{thunk:X} followed to body 0x{body:X}")


def test_two_names_for_one_address_are_dropped():
    """Identical-code folding gives one address several legitimate names. A row
    that kept one of them would be a coin flip the arity gate cannot see."""
    body, _ = a_thunked_function()
    rows = [call_row(0x1000, body, symbol="?one@@YAXXZ"),
            call_row(0x2000, body, symbol="?two@@YAXXZ")]
    named = build.harvest_reloc_names(rows)
    assert named[body]["names"] == {"?one@@YAXXZ", "?two@@YAXXZ"}
    assert build.select_reloc_names(named) == []
    print("PASS an address named two ways is dropped, not guessed at")


def test_a_generated_placeholder_name_is_marked_not_passed_off_as_identity():
    """Two thirds of the harvest names a class tools/gen_dump.py invented rather
    than one recovered from retail. The evidence is equally good; the name is
    worth nothing to a worker, so the row has to say which it is."""
    body = a_publishable_function()
    minted = build.select_reloc_names(build.harvest_reloc_names(
        [call_row(0x1000, body, symbol="??1Gen_dtor_0093e860@@UAE@XZ")]))
    recovered = build.select_reloc_names(build.harvest_reloc_names(
        [call_row(0x1000, body, symbol="?realName@SomeClass@@QAEXXZ")]))
    assert [row["notes"].endswith("identity=generated") for row in minted] == [True]
    assert [row["notes"].endswith("identity=real") for row in recovered] == [True]
    print("PASS a gen_dump-minted name is published marked, not as identity")


def test_every_generator_prefix_is_marked_generated():
    """One prefix per generator-minted class, and the marker has to know all of
    them.

    The pattern was written for gen_dump's three prefixes and never widened when
    tools/gen_uw.py added six more, so a full gate published 15 Gen_uws pins as
    `identity=real` -- the exact confusion the marker exists to prevent. A name
    this project invented is not identity whichever tool invented it.
    """
    body = a_publishable_function()
    minted = ["??1Gen_dtor_0093e860@@UAE@XZ", "??1Gen_dtorv_0093e860@@UAE@XZ",
              "??1Gen_t_00093990_mc4@@QAE@XZ",
              "??1Gen_uw_008bd020@@QAE@XZ", "??1Gen_uwm_008bd020@@QAE@XZ",
              "??0Gen_uwh4_008bd020@@QAE@XZ", "??3Gen_uws100_00891650@@SAXPAXI@Z",
              "??3@YAXPAXPAUGen_uwt_0002aaa9@@@Z", "??1Gen_uw_new@@QAE@XZ"]
    for name in minted:
        rows = build.select_reloc_names(build.harvest_reloc_names(
            [call_row(0x1000, body, symbol=name)]))
        assert [row["notes"].endswith("identity=generated") for row in rows] == [True], (
            f"{name} is a generator-minted placeholder and must not be published "
            f"as recovered identity")
    # A retail class whose name merely starts the same way is still identity.
    rows = build.select_reloc_names(build.harvest_reloc_names(
        [call_row(0x1000, body, symbol="?update@GeneratorObject@@QAEXXZ")]))
    assert [row["notes"].endswith("identity=real") for row in rows] == [True]
    print("PASS all %d generator prefixes publish as identity=generated" % len(minted))


def published_rows():
    with RELOC_NAMES.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle)
        assert "status" not in reader.fieldnames, (
            "a derived name file must not carry a status column: what is "
            "byte-verified here is the evidence, not the named body")
        return list(reader)


def test_published_rows_are_unambiguous_anonymous_and_sized_by_the_inventory():
    """What a generated file can be held to is how it was generated.

    Not that it is still unclaimed: the fleet claims these addresses -- that is
    the file doing its job -- and asserting otherwise would fail every
    contributor for someone else's landing. Anonymity does not decay the same
    way, because ghidra_functions.csv is a Ghidra export that only ever gains
    appended FUN_ rows; nothing renames one, so a published row that has stopped
    being anonymous means the file no longer matches the inventory it was cut
    from. Sizes come from that same inventory, and the names are the whole point
    of the file, so all three are pinned here.
    """
    rows = published_rows()
    inventory = {int(row["rva"], 16): (int(row["size"]), row["name"])
                 for row in csv.DictReader((ROOT / "targets/game/reverse" /
                 "ghidra_functions.csv").open(newline="", encoding="utf-8"))}

    seen = {}
    for row in rows:
        rva = int(row["target_rva"], 16)
        assert row["target_rva"] == f"0x{rva:08X}", (
            f"non-canonical target_rva {row['target_rva']!r}")
        assert rva not in seen, (
            f"0x{rva:X} published twice, as {seen[rva]!r} and {row['name']!r}: "
            f"an address named two ways is a coin flip, not identity")
        assert rva in inventory, f"0x{rva:X} is in no inventory row"
        assert inventory[rva][1].startswith("FUN_"), (
            f"0x{rva:X} is named {inventory[rva][1]} in the inventory, so "
            f"publishing a derived name for it is not new identity")
        assert int(row["target_size"]) == inventory[rva][0], (
            f"0x{rva:X}: published size {row['target_size']} but the inventory "
            f"says {inventory[rva][0]}")
        assert row["name"] and row["source"]
        assert NOTES_RE.fullmatch(row["notes"]), (
            f"0x{rva:X}: unreadable notes {row['notes']!r}")
        seen[rva] = row["name"]
    print(f"PASS {len(rows)} published name(s) unambiguous, anonymous, "
          f"sized by the inventory")


def test_the_queue_drops_published_rows_the_ledger_has_claimed():
    """Staleness is the consumer's job, which is why the file may carry it.

    reloc_names.csv is a snapshot of who was unclaimed when the gate last ran,
    and the ledger moves under it every few minutes. Serving a claimed address
    as available work is the real defect, and it lives here, not in the file --
    so it is tested here, against claim sets this test states outright rather
    than whatever the ledger happens to hold this minute.

    The universe is the RECOVERED half of the file, not all of it: 74ac64e06
    stopped serving `identity=generated` rows, because a name this project
    minted for a machine funclet tells a worker nothing and the weighted draw
    landed on them half the time. Their bytes go out through the convert lane.
    """
    recovered = [row for row in published_rows()
                 if not row["notes"].endswith("identity=generated")]
    rva = int(recovered[0]["target_rva"], 16)

    served, note = next_work.reloc_named_candidates(set(), [])
    assert len(served) == len(recovered), note
    assert not [c for c in served if c["notes"].endswith("identity=generated")], (
        "a minted name is evidence about nothing; the convert lane owns those bytes")
    assert "already landed" not in note, note

    claimed, note = next_work.reloc_named_candidates({rva}, [])
    assert rva not in {int(c["target_rva"], 16) for c in claimed}
    assert len(claimed) == len(served) - 1
    assert "1 already landed" in note, note

    # A worker that lands a bigger function swallows the address without ever
    # claiming it by name; the queue has to notice that too.
    inside, note = next_work.reloc_named_candidates(set(), [(rva - 4, rva + 4)])
    assert rva not in {int(c["target_rva"], 16) for c in inside}
    assert "1 already landed" in note, note
    print(f"PASS the queue drops 0x{rva:X} once claimed, by name or by range")


def test_refuted_drawable_route_is_not_served_as_recovered_identity():
    """The matched wrapper at 0x527200 once gave a false Drawable name to
    the multiplayer setup body reached through ILT 0x1C8D2. The corrected
    thunk may lend an address-derived name, but no real identity is proven at
    this body, so the published snapshot and work queue must not claim one.
    """
    target = 0x00526660
    derived = [row for row in published_rows()
               if int(row["target_rva"], 16) == target]
    assert all(row["notes"].endswith("identity=generated") for row in derived), derived
    served, _ = next_work.reloc_named_candidates(set(), [])
    assert not [row for row in served if int(row["target_rva"], 16) == target]
    print("PASS refuted Drawable route is absent from recovered-name work")


def test_corrected_opaque_drawable_route_does_not_recover_an_identity():
    """A future green full gate may rederive this call, but its new symbol
    keeps the ILT address and must remain a generated, unservable candidate.
    """
    thunk = 0x0001C8D2
    body = 0x00526660
    caller = call_row(0x00527200, thunk,
                      symbol="?forward@Rva0001C8D2Thunk@@QAEXHH@Z")
    rows = build.select_reloc_names(build.harvest_reloc_names([caller]))
    assert len(rows) == 1 and int(rows[0]["target_rva"], 16) == body, rows
    assert rows[0]["notes"].endswith("identity=generated"), rows


def a_dup_claimed_function():
    """A body whose ONLY ledger claim is a ?dup_<rva> row, and which Ghidra
    still calls FUN_. The ledger covers its bytes and names nothing."""
    inventory = {int(row["rva"], 16): row["name"] for row in csv.DictReader(
        (ROOT / "targets/game/reverse" / "ghidra_functions.csv").open(
            newline="", encoding="utf-8"))}
    names_by_rva = {}
    for row in build.load_all_function_rows():
        names_by_rva.setdefault(int(row["target_rva"], 16), []).append(row["name"])
    for body in build.build_call_thunks():
        names = names_by_rva.get(body)
        if (names and all(build.DUP_ALIAS_RE.match(n) for n in names)
                and inventory.get(body, "").startswith("FUN_")):
            return body
    raise AssertionError("no dup-claimed anonymous thunked body in the ledger")


def test_a_dup_row_does_not_lend_its_callee_names_to_the_harvest():
    """?dup_<rva> rows carry Zero Hour's names for Zero Hour's callees.

    The row's bytes are retail's, but the relocation symbols come from whichever
    member of an ICF fold the reference TU happened to compile, and BFME does
    not fold the same set. Two landed twins of ZH's
    GadgetSliderSetDisabled*ThumbColor named 0x00479040 winSetDisabledColor;
    six BFME call sites had recovered winSetEnabledBorderColor for that address,
    the two names collided, and select_reloc_names dropped the address. The
    identity was deleted from a derived file with no other record.
    """
    body, _ = a_thunked_function()
    real = call_row(0x1000, body, symbol="?winSetEnabledBorderColor@GameWindow@@QAEHHH@Z")
    twin = call_row(0x2000, body, symbol="?winSetDisabledColor@GameWindow@@QAEHHH@Z",
                    name="?dup_0047b680@@YAXXZ")

    named = build.harvest_reloc_names([real, twin])
    assert named[body]["names"] == {"?winSetEnabledBorderColor@GameWindow@@QAEHHH@Z"}, named
    assert named[body]["sites"] == 1, named

    # The control: without the filter both names land and the address is lost.
    both = build.harvest_reloc_names([real, dict(twin, name="?other@@YAXXZ")])
    assert len(both[body]["names"]) == 2 and build.select_reloc_names(both) == []
    print("PASS a dup_ row's ZH callee names stay out of the identity harvest")


def test_a_dup_claimed_address_is_still_anonymous_to_the_harvest():
    """Covering an address is not naming it.

    A ?dup_<rva> row says in its own name that the identity is unproven, so the
    one recovered name for that address has to survive. It did not: the dup row
    counted as `claimed` and the harvested
    ?findCommandSet@ControlBar@@... at 0x4A0340 was dropped on the same gate run
    that landed the twin over it.
    """
    body = a_dup_claimed_function()
    rows = build.select_reloc_names(build.harvest_reloc_names(
        [call_row(0x1000, body, symbol="?realName@SomeClass@@QAEXXZ")]))
    assert [int(r["target_rva"], 16) for r in rows] == [body], (hex(body), rows)

    # ...while an address a real name already claims stays out.
    claimed_body = next(
        int(row["target_rva"], 16) for row in build.load_all_function_rows()
        if not build.is_scaffold_row(row)
        and not build.DUP_ALIAS_RE.match(row["name"])
        and int(row["target_rva"], 16) in build.build_call_thunks())
    assert build.select_reloc_names(build.harvest_reloc_names(
        [call_row(0x1000, claimed_body, symbol="?realName@SomeClass@@QAEXXZ")])) == []
    print(f"PASS 0x{body:X} is still nameable behind its dup_ row")
