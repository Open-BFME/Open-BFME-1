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


def judge(monkeypatch, pins, rows, image=None, routes=None):
    def fake_pins(found=None):
        if found is not None:
            found.update(routes or {})
        return dict(pins)
    monkeypatch.setattr(L, "pins", fake_pins)
    image = image or {}
    return G.Judge(rows, data_rows=[], image=lambda address, size: image.get(address, b"")[:size])


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


def test_census_charges_the_declarer_and_callers_through_a_wrong_alias(tmp_path, monkeypatch):
    j = judge(monkeypatch, {"?A@@YAXXZ": 0x500, "?OK@@YAXXZ": 0x700},
              [row("?B@@YAXXZ", 0x600), row("?Good@@YAXXZ", 0x700)])
    declarer = coff(tmp_path / "d.obj", [], "/alternatename:?A@@YAXXZ=?B@@YAXXZ /alternatename:?OK@@YAXXZ=?Good@@YAXXZ")
    caller, other = tmp_path / "c.obj", tmp_path / "o.obj"
    facts = [([], [], ["?A@@YAXXZ"], []), ([], [], ["?A@@YAXXZ", "?OK@@YAXXZ"], []), ([], ["?B@@YAXXZ"], [], [])]
    aliases, charged, stats = L.alias_blockers([declarer, caller, other], facts, [], judge=j)
    assert aliases == {"?A@@YAXXZ": [(0, "?B@@YAXXZ")], "?OK@@YAXXZ": [(0, "?Good@@YAXXZ")]}
    assert charged == {"d.obj": ["?A@@YAXXZ=?B@@YAXXZ"], "c.obj": ["?A@@YAXXZ=?B@@YAXXZ"]}
    assert stats["wrong"] == 1 and stats["ok"] == 1 and stats["charged"] == 2
    # A defined by some object: the alias is inert for callers, still wrong where declared
    facts[2] = ([], ["?A@@YAXXZ", "?B@@YAXXZ"], [], [])
    _, charged, _ = L.alias_blockers([declarer, caller, other], facts, [], judge=j)
    assert charged == {"d.obj": ["?A@@YAXXZ=?B@@YAXXZ"]}


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


def test_queue_serves_a_wrong_alias_as_its_own_kind():
    blockers = {"a.cpp": {"object": "a.obj", "linked": False, "unresolved": [], "duplicates": [], "losers": [],
                          "addresses": 0, "wrong_selected": [], "alias_target": ["?A@@YAXXZ=?B@@YAXXZ"]}}
    rows = C.queue_rows({"meta": {"commit": "c"}, "blockers": blockers, "bytes": {"a.cpp": 50}})
    assert rows[0]["kind"] == "alias_target" and rows[0]["name"] == "?A@@YAXXZ=?B@@YAXXZ"


def test_staged_fails_on_a_new_wrong_alias_but_not_a_baselined_one(monkeypatch, capsys):
    j = judge(monkeypatch, {"?A@@YAXXZ": 0x500}, [row("?B@@YAXXZ", 0x600), row("?Real@@YAXXZ", 0x500)])
    files = {"game/x.cpp": '#pragma comment(linker, "/alternatename:?A@@YAXXZ=?B@@YAXXZ")\n',
             "game/ok.cpp": '#pragma comment(linker, "/alternatename:?A@@YAXXZ=?Real@@YAXXZ")\n'}
    baseline = {"text": ""}

    def fake_git(*args):
        if args[0] == "diff":
            return SimpleNamespace(stdout="\n".join(files) + "\n")
        path = args[1][1:]
        return SimpleNamespace(stdout=baseline["text"] if path.endswith("baseline.txt") else files.get(path, ""))
    monkeypatch.setattr(G, "git", fake_git)
    monkeypatch.setattr(G, "BASELINE", SimpleNamespace(exists=lambda: True,
                                                       relative_to=lambda root: Path("targets/baseline.txt")))
    assert G.staged(lambda: j) == 1
    assert "game/x.cpp: ?A@@YAXXZ=?B@@YAXXZ" in capsys.readouterr().err
    baseline["text"] = G.BASELINE_HEADER + "game/x.cpp: ?A@@YAXXZ=?B@@YAXXZ\n"
    assert G.staged(lambda: j) == 0
    del files["game/x.cpp"]
    assert G.staged(lambda: j) == 0
