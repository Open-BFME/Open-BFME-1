"""alias_guard: an /alternatename alias must bind its call to the body at the alias's pinned address."""
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import alias_guard as G  # noqa: E402
import link_census as L  # noqa: E402
import link_check as C  # noqa: E402


def coff(path, records, directives=""):
    """An object with one .drectve section and an external symbol table."""
    strings = bytearray(b"\0" * 4)
    symbols = bytearray()
    for name, value, section, storage in records:
        raw = name.encode()
        if len(raw) > 8:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(raw + b"\0")
        else:
            field = raw.ljust(8, b"\0")
        symbols.extend(field + struct.pack("<IhHBB", value, section, 0, storage, 0))
    strings[:4] = struct.pack("<I", len(strings))
    body = directives.encode("latin-1")
    table = 20 + 40 + len(body)
    section = b".drectve" + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x00100A00)
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, 1, 0, table, len(records), 0, 0) + section + body
                     + symbols + strings)
    return path


def row(name, rva, source="game/A.cpp", notes=""):
    return {"name": name, "target_rva": f"0x{rva:08X}", "source": source, "notes": notes, "status": "matched"}


def judge(monkeypatch, pins, rows, image=None, routes=None, dir32=None, notes=None):
    """A Judge over `pins` {name: address, or [addresses] for several pins}."""
    def fake_pins(found=None, every=None, pin_notes=None):
        if found is not None:
            found.update(routes or {})
        if every is not None:
            every.update({name: set(at) if isinstance(at, list) else {at} for name, at in pins.items()})
        if pin_notes is not None:
            pin_notes.update(notes or {})
        return {name: at[0] if isinstance(at, list) else at for name, at in pins.items()}
    monkeypatch.setattr(L, "pins", fake_pins)
    monkeypatch.setattr(L, "naked_rows", lambda: set())
    image = image or {}
    return G.Judge(rows, data_rows=[], image=lambda address, size: image.get(address, b"")[:size],
                   dir32=dir32 or {}, layout=(0xC73000, 0x1016000))


def jmp(at, to):
    return b"\xe9" + struct.pack("<i", to - (at + 5))


def test_directives_are_read_from_source_and_object(tmp_path):
    text = ('#pragma comment(linker, "/alternatename:?a@@YAXXZ=?b@@YAXXZ")\n'
            '// #pragma comment(linker, "/alternatename:?gone@@YAXXZ=?b@@YAXXZ")\n'
            '#pragma comment( linker , "/alternatename:_x=_y" )\n')
    assert G.source_aliases(text) == [("?a@@YAXXZ", "?b@@YAXXZ"), ("_x", "_y")]
    obj = coff(tmp_path / "a.obj", [], '   /alternatename:?a@@YAXXZ=?b@@YAXXZ "/alternatename:_x=_y" /DEFAULTLIB:x ')
    assert G.object_aliases(obj) == [("?a@@YAXXZ", "?b@@YAXXZ"), ("_x", "_y")]
    assert G.object_aliases(tmp_path / "missing.obj") == []


def test_verdicts(monkeypatch):
    rows = [row("?body@@YAXXZ", 0x7F0190), row("?next@@YAXXZ", 0x7F0170),
            row("?j_00001000@@YAXXZ", 0x1000, notes="gen-thunk;target=FUN_00bf0190")]
    image = {0x2000: jmp(0x2000, 0x7F0190)}
    j = judge(monkeypatch, {"?call@@YAXXZ": 0x7F0190, "?viaStub@@YAXXZ": 0x1000, "?viaJmp@@YAXXZ": 0x2000,
                            "?unknownTarget@@YAXXZ": 0x7F0190}, rows, image)
    assert j.verdict("?call@@YAXXZ", "?body@@YAXXZ")[0] == "ok"
    # the BFME2 replay case: the neighbouring body is wrong
    verdict, why = j.verdict("?call@@YAXXZ", "?next@@YAXXZ")
    assert verdict == "wrong" and "0x007F0190" in why and "0x007F0170" in why
    assert j.verdict("?call@@YAXXZ", "?j_00001000@@YAXXZ")[0] == "ok"      # an ILT stub row of the body
    assert j.verdict("?viaStub@@YAXXZ", "?body@@YAXXZ")[0] == "ok"         # the pin is the stub
    assert j.verdict("?viaJmp@@YAXXZ", "?body@@YAXXZ")[0] == "ok"          # a JMP rel32 in the image
    assert j.verdict("?unpinned@@YAXXZ", "?body@@YAXXZ")[0] == "unknown"
    assert j.verdict("?unknownTarget@@YAXXZ", "?nowhere@@YAXXZ")[0] == "unknown"


def test_respell_names_the_row_at_the_pinned_address(monkeypatch):
    rows = [row("?real@@YAXXZ", 0x500), row("?dump@@YAXXZ", 0x600, source="game/gen_asm/x.asm"),
            row("?j_00000700@@YAXXZ", 0x700, notes="target=0x00000500")]
    j = judge(monkeypatch, {"?ph@@YAXXZ": 0x500, "?d@@YAXXZ": 0x600, "?viaStub@@YAXXZ": 0x700, "_cname": 0x500},
              rows)
    assert j.respell("?ph@@YAXXZ")[:2] == ("?real@@YAXXZ", "")
    assert j.respell("?viaStub@@YAXXZ")[:2] == ("?real@@YAXXZ", "")
    assert j.respell("?d@@YAXXZ")[0] is None        # a dump is not a C++ definition to call
    assert j.respell("?nopin@@YAXXZ") == (None, "not pinned", "")
    assert j.respell("?real@@YAXXZ")[0] is None     # already the row name
    assert "C name" in j.respell("_cname")[1]     # a C call to a C++ placeholder row is flagged


def test_census_charges_the_declarer_and_callers_through_a_wrong_alias(tmp_path, monkeypatch):
    j = judge(monkeypatch, {"?A@@YAXXZ": 0x500, "?OK@@YAXXZ": 0x700},
              [row("?B@@YAXXZ", 0x600), row("?Good@@YAXXZ", 0x700)])
    declarer = coff(tmp_path / "d.obj", [], "/alternatename:?A@@YAXXZ=?B@@YAXXZ /alternatename:?OK@@YAXXZ=?Good@@YAXXZ")
    caller, other = tmp_path / "c.obj", tmp_path / "o.obj"
    facts = [([], [], ["?A@@YAXXZ"], []), ([], [], ["?A@@YAXXZ", "?OK@@YAXXZ"], []), ([], ["?B@@YAXXZ"], [], [])]
    aliases, charged, unjudged, stats = L.alias_blockers([declarer, caller, other], facts, [], judge=j)
    assert aliases == {"?A@@YAXXZ": [(0, "?B@@YAXXZ")], "?OK@@YAXXZ": [(0, "?Good@@YAXXZ")]}
    assert charged == {"d.obj": ["?A@@YAXXZ=?B@@YAXXZ"], "c.obj": ["?A@@YAXXZ=?B@@YAXXZ"]}
    assert unjudged == {}
    assert stats["wrong"] == 1 and stats["ok"] == 1 and stats["charged"] == 2
    # A defined by some object: the alias is inert for callers, still wrong where declared
    facts[2] = ([], ["?A@@YAXXZ", "?B@@YAXXZ"], [], [])
    _, charged, _, _ = L.alias_blockers([declarer, caller, other], facts, [], judge=j)
    assert charged == {"d.obj": ["?A@@YAXXZ=?B@@YAXXZ"]}


def test_census_charges_callers_through_an_unknown_alias_not_its_declarer(tmp_path, monkeypatch):
    j = judge(monkeypatch, {"?OK@@YAXXZ": 0x700}, [row("?B@@YAXXZ", 0x600), row("?Good@@YAXXZ", 0x700)])
    declarer = coff(tmp_path / "d.obj", [], "/alternatename:?U@@YAXXZ=?B@@YAXXZ /alternatename:?OK@@YAXXZ=?Good@@YAXXZ")
    caller, other = tmp_path / "c.obj", tmp_path / "o.obj"
    facts = [([], [], [], []), ([], [], ["?U@@YAXXZ", "?OK@@YAXXZ"], []), ([], ["?B@@YAXXZ"], [], [])]
    _, charged, unjudged, stats = L.alias_blockers([declarer, caller, other], facts, [], judge=j)
    assert charged == {} and unjudged == {"c.obj": ["?U@@YAXXZ=?B@@YAXXZ"]}
    assert stats["unknown"] == 1 and stats["charged_unknown"] == 1
    facts[2] = ([], ["?U@@YAXXZ", "?B@@YAXXZ"], [], [])   # defined: nobody calls through it
    assert L.alias_blockers([declarer, caller, other], facts, [], judge=j)[2] == {}


class NoTruth:
    def verdict(self, *args):
        return None


def test_link_check_resolves_through_an_alias_and_judges_it(tmp_path, monkeypatch):
    j = judge(monkeypatch, {"?A@@YAXXZ": 0x500}, [row("?B@@YAXXZ", 0x600), row("?Real@@YAXXZ", 0x500)])
    target = coff(tmp_path / "t.obj", [("?B@@YAXXZ", 0, 1, 2), ("?Real@@YAXXZ", 0, 1, 2)])
    user = coff(tmp_path / "u.obj", [("?A@@YAXXZ", 0, 0, 2)], "/alternatename:?A@@YAXXZ=?B@@YAXXZ")
    plain = coff(tmp_path / "p.obj", [("?A@@YAXXZ", 0, 0, 2)])
    objects = [target, user, plain]
    facts = [L.object_facts(o, NoTruth()) for o in objects]
    index = C.index_tables(objects, facts, {"exceptions": {}, "owners": {}})
    index["excuses"] = {"runtime": set(), "imported": {}, "stubs": {}}
    assert index["aliases"] == {"?A@@YAXXZ": [(1, "?B@@YAXXZ")]}
    for obj in (user, plain):  # the declarer and a caller through the other object's directive
        result = C.check_object(obj, index, NoTruth(), judge=j)
        assert result["unresolved"] == [] and result["alias_target"] == ["?A@@YAXXZ=?B@@YAXXZ"]
    # respelled to the row at the pin: a clean alias resolves and is not charged
    user = coff(tmp_path / "u.obj", [("?A@@YAXXZ", 0, 0, 2)], "/alternatename:?A@@YAXXZ=?Real@@YAXXZ")
    C.refresh(index, [user], NoTruth())
    assert index["aliases"] == {"?A@@YAXXZ": [(1, "?Real@@YAXXZ")]}
    assert not any(C.check_object(plain, index, NoTruth(), judge=j).values())
    # without any alias the name is simply unresolved
    index["aliases"] = {}
    assert C.check_object(plain, index, NoTruth(), judge=j)["unresolved"] == ["?A@@YAXXZ"]


def test_near_serves_files_whose_every_blocker_a_respelling_fixes(monkeypatch):
    j = judge(monkeypatch, {"?d_00000500@@YAXXZ": 0x500, "?d_00000600@@YAXXZ": 0x600, "?d_00000900@@YAXXZ": 0x900},
              [row("?one@@YAXXZ", 0x500, "game/T/a.cpp"), row("?two@@YAXXZ", 0x600, "game/T/a.cpp")])
    blank = {"duplicates": [], "losers": [], "wrong_selected": [], "alias_target": [], "addresses": 0,
             "linked": False}
    blockers = {"game/T/N/both.cpp": {**blank, "unresolved": ["?d_00000500@@YAXXZ", "?d_00000600@@YAXXZ"]},
                "game/T/N/gap.cpp": {**blank, "unresolved": ["?d_00000500@@YAXXZ", "?d_00000900@@YAXXZ"]},
                "game/T/N/dup.cpp": {**blank, "unresolved": ["?d_00000500@@YAXXZ"], "duplicates": ["?x@@YAXXZ"]},
                "game/T/M/one.cpp": {**blank, "unresolved": ["?d_00000500@@YAXXZ"]}}
    index = {"blockers": blockers, "bytes": {"game/T/N/both.cpp": 300, "game/T/M/one.cpp": 500}}
    rows = C.near_rows(index, j)
    assert [r["source"] for r in rows] == ["game/T/M/one.cpp", "game/T/N/both.cpp"]
    assert rows[1]["fixes"] == [("?d_00000500@@YAXXZ", "?one@@YAXXZ", ""), ("?d_00000600@@YAXXZ", "?two@@YAXXZ", "")]
    assert [r["source"] for r in C.near_rows(index, j, most=1)] == ["game/T/M/one.cpp"]
    assert [r["source"] for r in C.near_rows(index, j, under="game/T/N/")] == ["game/T/N/both.cpp"]
    # a file calling through an alias nothing can judge is not near
    blockers["game/T/M/one.cpp"]["alias_unknown"] = ["?U@@YAXXZ=?B@@YAXXZ"]
    assert [r["source"] for r in C.near_rows(index, j)] == ["game/T/N/both.cpp"]


def test_queue_serves_a_wrong_alias_as_its_own_kind():
    blockers = {"a.cpp": {"object": "a.obj", "linked": False, "unresolved": [], "duplicates": [], "losers": [],
                          "addresses": 0, "wrong_selected": [], "alias_target": ["?A@@YAXXZ=?B@@YAXXZ"]}}
    rows = C.queue_rows({"meta": {"commit": "c"}, "blockers": blockers, "bytes": {"a.cpp": 50}})
    assert rows[0]["kind"] == "alias_target" and rows[0]["name"] == "?A@@YAXXZ=?B@@YAXXZ"


def test_staged_fails_on_a_new_wrong_alias_but_not_a_baselined_one(monkeypatch, capsys):
    j = judge(monkeypatch, {"?A@@YAXXZ": 0x500}, [row("?B@@YAXXZ", 0x600), row("?Real@@YAXXZ", 0x500)])
    files = {"game/x.cpp": '#pragma comment(linker, "/alternatename:?A@@YAXXZ=?B@@YAXXZ")\n',
             "game/ok.cpp": '#pragma comment(linker, "/alternatename:?A@@YAXXZ=?Real@@YAXXZ")\n'}
    upstream = {}
    baseline = {"text": ""}
    fake_git(monkeypatch, files, upstream, baseline)
    assert G.staged(lambda: j) == 1
    assert "game/x.cpp: ?A@@YAXXZ=?B@@YAXXZ" in capsys.readouterr().err
    baseline["text"] = G.BASELINE_HEADER + "game/x.cpp: ?A@@YAXXZ=?B@@YAXXZ\n"
    assert G.staged(lambda: j) == 0
    del files["game/x.cpp"]
    assert G.staged(lambda: j) == 0


def fake_git(monkeypatch, files, upstream, baseline, renamed=None):
    """git as the hook sees it: `files` staged, `upstream` origin/master's copies."""
    renamed = renamed or {}

    def run(*args):
        if args[0] == "diff":
            return SimpleNamespace(stdout="".join(f"R100\t{renamed[path]}\t{path}\n" if path in renamed
                                                  else f"M\t{path}\n" for path in files), returncode=0)
        ref, path = args[1].split(":", 1)
        if path.endswith("baseline.txt"):
            return SimpleNamespace(stdout=baseline["text"], returncode=0)
        table = upstream if ref == G.UPSTREAM else files
        return SimpleNamespace(stdout=table.get(path, ""), returncode=0 if path in table else 128)
    monkeypatch.setattr(G, "git", run)
    monkeypatch.setattr(G, "BASELINE", SimpleNamespace(exists=lambda: True,
                                                       relative_to=lambda root: Path("targets/baseline.txt")))


def test_staged_fails_on_an_unknown_alias_new_since_origin_master(monkeypatch, capsys):
    j = judge(monkeypatch, {}, [row("?B@@YAXXZ", 0x600)])
    old = '#pragma comment(linker, "/alternatename:?Old@@YAXXZ=?B@@YAXXZ")\n'
    new = '#pragma comment(linker, "/alternatename:?New@@YAXXZ=?B@@YAXXZ")\n'
    files, upstream, baseline = {"game/x.cpp": old}, {"game/x.cpp": old}, {"text": ""}
    fake_git(monkeypatch, files, upstream, baseline)
    assert G.staged(lambda: j) == 0                       # already on origin/master: reported, not blocking
    assert "already on origin/master" in capsys.readouterr().err
    files["game/x.cpp"] = old + new
    assert G.staged(lambda: j) == 1
    err = capsys.readouterr().err
    assert "game/x.cpp: ?New@@YAXXZ=?B@@YAXXZ" in err and "?Old@@" not in err.split("cannot be judged, so")[1]
    files.clear()
    files["game/y.cpp"] = old                             # a file new since origin/master
    assert G.staged(lambda: j) == 1
    fake_git(monkeypatch, files, upstream, baseline, renamed={"game/y.cpp": "game/x.cpp"})
    assert G.staged(lambda: j) == 0                       # a rename keeps its upstream copy

def test_dir32_entries_make_vftable_data_aliases_judgeable(monkeypatch):
    dir32 = {"_bfmeVftThing": 0x1100000, "??_7Thing@@6B@": 0x1100000, "??_7Other@@6B@": 0x1100010}
    # an E9 byte at a data address is a pointer's low byte, never a jump to follow
    j = judge(monkeypatch, {"??_7Pinned@@6B@": 0x1100000}, [], image={0xD00000: jmp(0xD00000, 0xD00010)},
              dir32=dir32)
    assert j.verdict("_bfmeVftThing", "??_7Thing@@6B@")[0] == "ok"
    assert j.verdict("_bfmeVftThing", "??_7Pinned@@6B@")[0] == "ok"     # a symbols.csv datum pin is a VA
    assert j.verdict("_bfmeVftThing", "??_7Other@@6B@")[0] == "wrong"
    assert j.verdict("_bfmeVftNone", "??_7Thing@@6B@")[0] == "unknown"


def test_a_name_pinned_at_several_bodies_is_unknown(monkeypatch):
    rows = [row("?body@@YAXXZ", 0x500), row("?other@@YAXXZ", 0x600)]
    image = {0x1000: jmp(0x1000, 0x500)}
    j = judge(monkeypatch, {"?split@@YAXXZ": [0x500, 0x600], "?stubbed@@YAXXZ": [0x500, 0x1000],
                            "?target@@YAXXZ": [0x500, 0x600]}, rows, image)
    verdict, why = j.verdict("?split@@YAXXZ", "?body@@YAXXZ")
    assert verdict == "unknown" and "2 pins at different bodies" in why
    assert j.verdict("?stubbed@@YAXXZ", "?body@@YAXXZ")[0] == "ok"      # the second pin is the body's ILT stub
    assert j.verdict("?stubbed@@YAXXZ", "?other@@YAXXZ")[0] == "wrong"
    assert j.verdict("?stubbed@@YAXXZ", "?target@@YAXXZ")[0] == "unknown"   # a target pinned at two bodies
    assert j.respell("?split@@YAXXZ")[0] is None


def test_address_derived_names():
    for name in ("?hasError@Rva007E8810Message@@QAE_NXZ", "??1BfmeLegendStringVec@@QAE@XZ", "??3Gen007F0190@@YAXPAX@Z",
                 "?d_00123456@@YAXXZ", "tg_00061640", "??_GBfmeFoo@@UAEPAXI@Z"):
        assert G.address_derived(name), name
    for name in ("?valid@W3DVideoBuffer@@UAE_NXZ", "?getX@GlobalData@@QAEHXZ", "??1SubsystemLegendEntry@@QAE@XZ"):
        assert not G.address_derived(name), name


def test_respell_guard_two_real_names_or_another_tree(monkeypatch):
    rows = [row("?valid@W3DVideoBuffer@@UAE_NXZ", 0x7E88A0,
                source="game/GameEngineDevice/Source/W3DDevice/GameClient/W3DVideoBuffer.cpp", notes="seen twice"),
            row("?real@Thing@@QAEXXZ", 0x500, source="game/GameEngine/Source/A.cpp")]
    hasError = "?hasError@Rva007E8810Message@@QAE_NXZ"
    j = judge(monkeypatch, {hasError: 0x7E88A0, "?named@Other@@QAEXXZ": 0x500, "?Rva00000500Call@@YAXXZ": 0x500},
              rows, notes={hasError: ["V2 lane: ICF-folded with ?valid@W3DVideoBuffer@@UAE_NXZ"]})
    caller = "game/GameEngine/Source/GameNetwork/V2FeslMessage.cpp"
    target, note, guard = j.respell(hasError, caller)
    assert target == "?valid@W3DVideoBuffer@@UAE_NXZ"
    assert "two real names, one body: run tools/one_identity.py first" in guard and "game/GameEngineDevice" in guard
    assert "row notes: seen twice" in note and "ICF-folded with" in note
    assert "both are real names" in j.respell("?named@Other@@QAEXXZ", "game/GameEngine/Source/B.cpp")[2]
    assert j.respell("?Rva00000500Call@@YAXXZ", "game/GameEngine/Source/B.cpp")[2] == ""
    blank = {"duplicates": [], "losers": [], "wrong_selected": [], "alias_target": [], "addresses": 0,
             "linked": False}
    index = {"blockers": {caller: {**blank, "unresolved": [hasError]},
                          "game/GameEngine/Source/B.cpp": {**blank, "unresolved": ["?Rva00000500Call@@YAXXZ"]}},
             "bytes": {caller: 100, "game/GameEngine/Source/B.cpp": 50}}
    skipped = __import__("collections").Counter()
    assert [r["source"] for r in C.near_rows(index, j, skipped=skipped)] == ["game/GameEngine/Source/B.cpp"]
    assert skipped == {"two real names, one body": 1}
    rows = C.near_rows(index, j, every=True)
    assert rows[0]["source"] == caller and "run tools/one_identity.py first" in rows[0]["fixes"][0][2]


def test_link_check_does_not_count_a_call_through_an_unknown_alias(tmp_path, monkeypatch):
    j = judge(monkeypatch, {}, [row("?B@@YAXXZ", 0x600)])
    target = coff(tmp_path / "t.obj", [("?B@@YAXXZ", 0, 1, 2)])
    user = coff(tmp_path / "u.obj", [("?U@@YAXXZ", 0, 0, 2)], "/alternatename:?U@@YAXXZ=?B@@YAXXZ")
    declarer = coff(tmp_path / "d.obj", [], "/alternatename:?U@@YAXXZ=?B@@YAXXZ")
    objects = [target, user, declarer]
    facts = [L.object_facts(o, NoTruth()) for o in objects]
    index = C.index_tables(objects, facts, {"exceptions": {}, "owners": {}})
    index["excuses"] = {"runtime": set(), "imported": {}, "stubs": {}}
    result = C.check_object(user, index, NoTruth(), judge=j)
    assert result["unresolved"] == [] and result["alias_target"] == []
    assert result["alias_unknown"] == ["?U@@YAXXZ=?B@@YAXXZ"] and "no pin or row" in result["alias_why"]["?U@@YAXXZ=?B@@YAXXZ"]
    assert not any(C.check_object(declarer, index, NoTruth(), judge=j).values())   # declared, not relied on


def test_queue_serves_an_unknown_alias_as_its_own_kind():
    blockers = {"a.cpp": {"object": "a.obj", "linked": False, "unresolved": [], "duplicates": [], "losers": [],
                          "addresses": 0, "wrong_selected": [], "alias_target": [],
                          "alias_unknown": ["?U@@YAXXZ=?B@@YAXXZ"]}}
    rows = C.queue_rows({"meta": {"commit": "c"}, "blockers": blockers, "bytes": {"a.cpp": 50}})
    assert rows[0]["kind"] == "alias_unknown" and "pin" in rows[0]["hint"]
