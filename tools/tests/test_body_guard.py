"""Red-team fixtures for what the byte gate's masking could not see (BFME1, 2026-10-05).

Each exploit compiles a WRONG body whose in-extent bytes still equal retail
once DIR32 operands are copied, so verify_functions passes it; the checks here
must fail it, and the correct body (negative control) must still pass. Retail
is a fake image the correct object is linked into by a ten-line linker.
"""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import body_guard  # noqa: E402
import build  # noqa: E402

R = 0x1000          # where the fake image places the function under test
DATA = 0x8000       # where it places everything the function references
WORK = build.ROOT / "build" / "body_guard_test"


def _toolchain():
    if not (build.vc71_root() / "Vc7" / "bin" / "cl.exe").exists():
        pytest.skip("MSVC 7.1 toolchain not present")


def compiled(name, text):
    _toolchain()
    WORK.mkdir(parents=True, exist_ok=True)
    source = WORK / f"{name}.cpp"
    source.write_text(text)
    output = WORK / f"{name}.obj"
    build.compile_source(source, output)
    return output


def link(obj, symbol, image):
    """Place `symbol`'s section at R and every symbol it references at DATA+."""
    body, relocs, info = build.read_object_symbol_bytes(obj, symbol, detail=True)
    data, sections = info["data"], info["sections"]
    image[R:R + len(body)] = body
    placed, cursor = {}, DATA
    for (off, rtype, name), target in zip(relocs, info["reloc_symbols"]):
        addend = struct.unpack_from("<I", body, off)[0]
        if target["section"] == info["section"]:
            va = 0x400000 + R + target["value"] - info["value"]
        else:
            if name not in placed:
                placed[name] = cursor
                if target["section"] > 0:
                    sec = sections[target["section"] - 1]
                    if sec["raw_pointer"]:
                        blob = data[sec["raw_pointer"] + target["value"]:
                                    sec["raw_pointer"] + sec["raw_size"]]
                        image[cursor:cursor + len(blob)] = blob
                cursor += 0x100
            va = 0x400000 + placed[name]
        if rtype == 0x0006:
            struct.pack_into("<I", image, R + off, (va + addend) & 0xFFFFFFFF)
        elif rtype == 0x0014:
            struct.pack_into("<i", image, R + off, va - 0x400000 + addend - (R + off + 4))
    return len(body.rstrip(b"\xcc"))


def findings(monkeypatch, wrong_obj, symbol, image, size):
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, n: bytes(image[rva:rva + n]))
    monkeypatch.setattr(build, "row_object", lambda row: wrong_obj)
    ctx = object.__new__(body_guard.Context)
    ctx.symbol_map, ctx._follow = {}, (lambda rva: rva)
    row = {"name": symbol, "target_rva": f"0x{R:08X}", "target_size": str(size),
           "source": "game/x.cpp", "notes": ""}
    return [check for check, _ in body_guard.row_findings(row, ctx)]


SWITCH = """
int g(int);
int f(int x)
{
    switch (x) {
    case %s: return g(11);
    case %s: return g(22);
    case 2: return g(33);
    case 3: return g(44);
    case 4: return g(55);
    }
    return 0;
}
"""


def test_a_swapped_case_label_is_refused_and_the_retail_mapping_passes(monkeypatch):
    good = compiled("switch_good", "// cl: /O2\n" + SWITCH % (0, 1))
    bad = compiled("switch_bad", "// cl: /O2\n" + SWITCH % (1, 0))
    image = bytearray(0x10000)
    size = link(good, "?f@@YAHH@Z", image)
    assert findings(monkeypatch, good, "?f@@YAHH@Z", image, size) == []
    assert "ltable" in findings(monkeypatch, bad, "?f@@YAHH@Z", image, size)


def test_a_wrong_local_string_is_refused(monkeypatch):
    text = 'const char *name()\n{\n    return "%s";\n}\n'
    # /GF- keeps the literal a TU-local $SG symbol instead of a pooled ??_C@
    good = compiled("sg_good", "// cl: /O2 /GF-\n" + text % "SnapshotName")
    bad = compiled("sg_bad", "// cl: /O2 /GF-\n" + text % "SnapshotNamf")
    image = bytearray(0x10000)
    size = link(good, "?name@@YAPBDXZ", image)
    assert findings(monkeypatch, good, "?name@@YAPBDXZ", image, size) == []
    assert findings(monkeypatch, bad, "?name@@YAPBDXZ", image, size) == ["static"]


def test_a_wrong_tu_local_const_table_is_refused(monkeypatch):
    text = "static const int table[4] = { %s };\nint pick(int i)\n{\n    return table[i];\n}\n"
    good = compiled("tab_good", "// cl: /O2\n" + text % "3, 1, 4, 1")
    bad = compiled("tab_bad", "// cl: /O2\n" + text % "3, 1, 4, 2")
    image = bytearray(0x10000)
    size = link(good, "?pick@@YAHH@Z", image)
    assert findings(monkeypatch, good, "?pick@@YAHH@Z", image, size) == []
    assert findings(monkeypatch, bad, "?pick@@YAHH@Z", image, size) == ["static"]


def test_bytes_past_the_extent_must_equal_retail(monkeypatch):
    text = "int h(int a)\n{\n    return a * 3 + %d;\n}\n"
    good = compiled("tail_good", "// cl: /O2\n" + text % 1)
    bad = compiled("tail_bad", "// cl: /O2\n" + text % 2)
    image = bytearray(0x10000)
    size = link(good, "?h@@YAHH@Z", image)
    body, _ = build.read_object_symbol_bytes(bad, "?h@@YAHH@Z")
    first_diff = next(i for i in range(size) if body[i] != image[R + i])
    # the ledger claims only the bytes before the difference: in-extent equal
    assert findings(monkeypatch, good, "?h@@YAHH@Z", image, first_diff) == []
    assert findings(monkeypatch, bad, "?h@@YAHH@Z", image, first_diff) == ["tail"]


def _ctor_findings(monkeypatch, name, source, image, size):
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, n: bytes(image[rva:rva + n]))
    monkeypatch.setattr(build, "row_object", lambda row: source["obj"])
    ctx = object.__new__(body_guard.Context)
    ctx.symbol_map, ctx._follow = {}, (lambda rva: rva)
    row = {"name": name, "target_rva": f"0x{R:08X}", "target_size": str(size),
           "source": source["row_src"], "notes": ""}
    return [check for check, _ in body_guard.row_findings(row, ctx)]


def test_a_naked_ctor_dumps_return_this_trailer_is_machinery(monkeypatch):
    # MSVC 7.1 appends mov eax,[ebp-4] (the ctor return-this load) after a
    # naked ctor's __emit block: unreachable after its ret, absent from retail.
    good = compiled("naked_ctor", "class Thing;\nclass A { public: A(Thing *); };\n"
                    "__declspec(naked) A::A(Thing *t) { __asm { _emit 0xC3 } }\n")
    body, _ = build.read_object_symbol_bytes(good, "??0A@@QAE@PAVThing@@@Z")
    assert body.rstrip(b"\xcc") == b"\xc3\x8b\x45\xfc"
    image = bytearray(0x10000)
    image[R:R + 1] = b"\xc3"                # retail's body ends at the ret
    image[R + 1:R + 4] = b"\xcc\xcc\xcc"    # int3 padding where the object trails
    row_src = (WORK / "naked_ctor.cpp").relative_to(build.ROOT).as_posix()
    sym = "??0A@@QAE@PAVThing@@@Z"
    # the ledger extent stops at the __emit ret: the trailer is machinery
    assert _ctor_findings(monkeypatch, sym, {"obj": good, "row_src": row_src}, image, 1) == []
    # a source that is not a naked dump keeps the finding: the strip is earned
    assert _ctor_findings(monkeypatch, sym, {"obj": good, "row_src": "game/x.cpp"},
                          image, 1) == ["tail"]


def test_a_ctor_tail_is_still_checked_outside_the_naked_dump_trailer(monkeypatch):
    # A compiled (non-naked) ctor whose ledger stops before a real difference
    # keeps its tail finding: only the exact three-byte trailer on a naked
    # ctor dump row is machinery.
    text = "class Thing;\nclass B { public: int m; B(Thing *); };\nB::B(Thing *t) : m(%d) {}\n"
    good = compiled("plain_ctor_good", "// cl: /O2\n" + text % 3)
    bad = compiled("plain_ctor_bad", "// cl: /O2\n" + text % 4)
    image = bytearray(0x10000)
    size = link(good, "??0B@@QAE@PAVThing@@@Z", image)
    body, _ = build.read_object_symbol_bytes(bad, "??0B@@QAE@PAVThing@@@Z")
    first_diff = next(i for i in range(size) if body[i] != image[R + i])
    sym = "??0B@@QAE@PAVThing@@@Z"
    assert "tail" in _ctor_findings(monkeypatch, sym, {"obj": bad, "row_src": "game/x.cpp"},
                                    image, first_diff)


def test_shrink_only_baseline_refuses_growth(tmp_path, monkeypatch):
    path = tmp_path / "b.csv"
    path.write_text("check,target_rva,name,detail\nltable,0x00001000,?f@@YAHH@Z,x\n")
    assert body_guard.read_baseline(path) == {("ltable", "0x00001000", "?f@@YAHH@Z")}


# --- gen-alias: a masked call is admitted only to a retail twin of the named callee

def _image(monkeypatch, bodies, sizes):
    image = bytearray(0x1000)
    for at, code in bodies.items():
        image[at:at + len(code)] = code
    monkeypatch.setattr(body_guard, "_retail", lambda rva, n: bytes(image[rva:rva + n]))
    monkeypatch.setattr(body_guard, "_text_follow", lambda rva: rva)
    monkeypatch.setattr(body_guard, "_ROW_SIZE", dict(sizes))


def _calls(at, dest):
    return b"\x55\x8b\xec\xe8" + struct.pack("<i", dest - (at + 8)) + b"\x5d\xc3"


def test_gen_alias_fallback_needs_a_twin_by_bytes_and_resolved_calls(monkeypatch):
    _image(monkeypatch, {0x100: _calls(0x100, 0x500), 0x200: _calls(0x200, 0x500),
                         0x300: _calls(0x300, 0x600), 0x400: b"\x33\xc0\xc3" + b"\x90" * 7},
           {0x100: 10, 0x200: 10, 0x300: 10, 0x400: 10})
    assert body_guard.callee_twin(0x100, [0x100])          # the callee itself
    assert body_guard.callee_twin(0x200, [0x100])          # identical copy, same callee
    assert not body_guard.callee_twin(0x300, [0x100])      # same bytes shape, other callee
    assert not body_guard.callee_twin(0x400, [0x100])      # different body
    assert not body_guard.callee_twin(0x200, [])           # unresolved name: no proof


def test_gen_alias_is_a_whole_token():
    token = build.gen_alias_marked
    assert token("gen-alias") and token("x; gen-alias") and token("a, gen-alias ;b")
    assert not token("replaces borrowed gen-alias pattern") and not token("gen-aliased")
