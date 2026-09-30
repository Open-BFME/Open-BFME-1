"""provider_repair: source surgery, serving rules, and one synthetic conflict end to end."""
import os
import hashlib
import shutil
import subprocess
import sys
import types
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import provider_repair as pr  # noqa: E402

LEGACY = """// cl: test
struct View { int init(); int reset(); int zoom(int); int zoom(int, int); };
View::View *TheView;

/*
** Reset
*/
// ?reset@View@@ present-unmatched
int View::reset()
{
\treturn View::init() + 1;
}

// keep this one
int View::init() { return 7; }

__declspec(noinline) int View::zoom(int a)
{
\treturn a;
}

View::Kind View::zoom(int a, int b)
{
\tint v = View::zoom(a
\t\t);
\treturn v + b;
}
"""


def lines(text):
    return text.split("\n")


def test_method_of_parses_members_ctors_and_dtors():
    assert pr.method_of("?clip@Pathfinder@@QAEXPAUCoord3D@@0@Z") == "Pathfinder::clip"
    assert pr.method_of("??0W3DTruckDraw@@QAE@PAVThing@@PBVModuleData@@@Z") == "W3DTruckDraw::W3DTruckDraw"
    assert pr.method_of("??1W3DTruckDrawModuleData@@UAE@XZ") == "W3DTruckDrawModuleData::~W3DTruckDrawModuleData"
    assert pr.method_of("??4VertexMaterialClass@@QAEAAV0@ABV0@@Z") is None      # operators are not served
    assert pr.method_of("?ClipLine2D@@YA_NPAUICoord2D@@000PAUIRegion2D@@@Z") is None


def test_find_definitions_takes_the_comment_block_and_skips_call_sites():
    spans = pr.find_definitions(LEGACY, "View::reset")
    assert len(spans) == 1
    first, last = spans[0]
    assert lines(LEGACY)[first] == "/*" and lines(LEGACY)[last] == "}"
    # `return View::init()` inside reset's body is a call, not a definition
    assert [lines(LEGACY)[a] for a, _ in pr.find_definitions(LEGACY, "View::init")] == ["// keep this one"]


def test_find_definitions_sees_overloads_declspec_and_qualified_return_types():
    spans = pr.find_definitions(LEGACY, "View::zoom")
    heads = [next(l for l in lines(LEGACY)[a:b + 1] if "View::zoom(" in l) for a, b in spans]
    assert heads == ["__declspec(noinline) int View::zoom(int a)", "View::Kind View::zoom(int a, int b)"]


def test_remove_definition_keeps_crlf_and_the_rest(tmp_path):
    path = tmp_path / "legacy.cpp"
    path.write_bytes(LEGACY.replace("\n", "\r\n").encode())
    span = pr.find_definitions(path.read_text(encoding="latin-1").replace("\r", ""), "View::reset")[0]
    pr.remove_definition(path, span, "Retail View::reset is implemented in view_reset.cpp.")
    text = path.read_bytes()
    assert b"\r\n// Retail View::reset is implemented in view_reset.cpp.\r\n" in text
    assert b"int View::reset()" not in text and b"int View::init()" in text
    assert text.count(b"\n") == text.count(b"\r\n")


def fake(strong, comdat, objects):
    return {"objects": objects, "strong": strong, "comdat": comdat}


def owner_row(name, source):
    return {"name": name, "target_rva": "0x00001000", "target_size": "16", "source": source,
            "status": "matched", "notes": ""}


def repo_scratch(path, label):
    """Put compiler inputs under ROOT; build.compiler_command needs repo paths."""
    path = Path(path).resolve()
    try:
        path.relative_to(build.ROOT.resolve())
        return path
    except ValueError:
        key = hashlib.sha1(str(path).encode()).hexdigest()[:12]
        result = build.ROOT / "build" / "provider_repair_tests" / label / key
        result.mkdir(parents=True, exist_ok=True)
        return result


@pytest.fixture
def rows(monkeypatch):
    monkeypatch.setattr(pr, "is_lift", lambda source: "Lift" in source)
    objs = [build.obj_path(pr.ROOT / "game/A/Owner.cpp").name, build.obj_path(pr.ROOT / "game/A/Legacy.cpp").name,
            build.obj_path(pr.ROOT / "game/A/User.cpp").name, "inputs_reference_x.obj"]
    src = {objs[0]: "game/A/Owner.cpp", objs[1]: "game/A/Legacy.cpp", objs[2]: "game/A/User.cpp",
           objs[3]: "inputs/reference/x.cpp"}
    return objs, src


def classify(rows, strong, comdat, owner_source="game/A/Owner.cpp"):
    objs, src = rows
    name = "?f@C@@QAEXXZ"
    return pr.classify(name, fake(strong, comdat, objs), src, {name: [owner_row(name, owner_source)]})[0]


def test_serves_a_strong_disproved_copy_in_a_game_tu(rows):
    n = "?f@C@@QAEXXZ"
    assert classify(rows, {n: [0, 1]}, {n: [(0, "a", "retail"), (1, "b", "wrong")]}) == "serve"


def test_inline_copy_needs_the_header_window(rows):
    n = "?f@C@@QAEXXZ"
    assert classify(rows, {n: [0]}, {n: [(0, "a", "retail"), (2, "b", "wrong")]}) == "needs-header-window"


def test_refuses_unproven_owner_undecided_copy_lift_and_reference_objects(rows):
    n = "?f@C@@QAEXXZ"
    assert classify(rows, {n: [0, 1]}, {n: [(0, "a", "unknown"), (1, "b", "wrong")]}) == "owner-unproven"
    assert classify(rows, {n: [0, 1]}, {n: [(0, "a", "retail"), (1, "b", None)]}) == "competitor-undecided"
    assert classify(rows, {n: [0, 3]}, {n: [(0, "a", "retail"), (3, "b", "wrong")]}) == "reference-object"
    objs, src = rows
    lift = build.obj_path(pr.ROOT / "game/A/OwnerLift.cpp").name
    objs2, src2 = objs + [lift], dict(src, **{lift: "game/A/OwnerLift.cpp"})
    verdict = pr.classify(n, fake({n: [4, 1]}, {n: [(4, "a", "retail"), (1, "b", "wrong")]}, objs2), src2,
                          {n: [owner_row(n, "game/A/OwnerLift.cpp")]})[0]
    assert verdict == "owner-lift"


def test_orphans_flags_removed_sole_definitions_others_reference():
    index = fake({"?v@C@@": [1], "?shared@C@@": [1, 2]}, {"??_7C@@6B@": [(1, "x", None)]}, ["o.obj", "legacy.obj", "u.obj"])
    refs = {"??_7C@@6B@": ["o.obj"], "?v@C@@": ["legacy.obj"], "?shared@C@@": ["o.obj"]}
    lost = pr.orphans(["??_7C@@6B@", "?v@C@@", "?shared@C@@"], "legacy.obj", index, refs)
    assert [o["name"] for o in lost] == ["??_7C@@6B@"]      # ?v only used by itself; ?shared has another definer


# ---------------------------------------------------------------- synthetic conflict, real toolchain
CL = Path(os.environ.get("VC71_ROOT", build.DEFAULT_VC71_ROOT)) / "Vc7" / "bin" / "cl.exe"
toolchain = pytest.mark.skipif(not CL.exists() or (sys.platform != "win32" and shutil.which("wine") is None),
                               reason="MSVC 7.1 toolchain not present")

OWNER_CPP = "struct C { int a, b; int get(); };\nint C::get() { return b * 3; }\n"
LEGACY_CPP = ("struct C { int b, a; int get(); int other(); };\n"
              "int C::get() { return b * 3; }\n"             # same text, other layout: a wrong copy
              "int C::other() { return a; }\n")


def compile_to(tmp_path, name, text):
    work = repo_scratch(tmp_path, "synthetic")
    src = work / f"{name}.cpp"
    src.write_text("// cl: /Gy /Zl\n" + text)
    obj = work / f"{name}.obj"
    compiled, output, _ = build.try_compile_source(src, obj)
    assert compiled, output
    return obj


@toolchain
def test_synthetic_conflict_positive_negative_and_duplicate(tmp_path):
    name = "?get@C@@QAEHXZ"
    owner = compile_to(tmp_path, "owner", OWNER_CPP).read_bytes()
    legacy = compile_to(tmp_path, "legacy", LEGACY_CPP).read_bytes()
    expected = next(b for s, b, _, _, _ in pr.link_census._comdat_sections(owner) if s["name"] == name)
    result = pr.harness(name, owner, legacy, expected, tmp_path / "h")
    assert result["positive"] == "equal"
    assert result["negative"].startswith("differs")
    assert result["duplicate_LNK2005"] and result["pass"]
    # a wrong provider can never pass: the negative control flips the verdict
    assert not pr.harness(name, legacy, owner, expected, tmp_path / "h2")["pass"]


@pytest.mark.skipif(sys.platform == "win32", reason="path defect is specific to Wine")
@toolchain
def test_wine_strict_link_uses_inputs_and_validates_pe(tmp_path, monkeypatch):
    """LINK can exit zero after treating /home/...obj as an option."""
    work = repo_scratch(tmp_path, "wine_strict_link") / "folder with spaces"
    work.mkdir()
    src = work / "entry.cpp"
    src.write_text('extern "C" int __cdecl entry(void) { return 7; }\n', encoding="ascii")
    obj = work / "entry.obj"
    compiled, output, _ = build.try_compile_source(src, obj)
    assert compiled, output

    root = build.vc71_root()
    raw_out = work / "raw.dll"
    raw = subprocess.run(["wine", str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/NODEFAULTLIB",
                          "/INCREMENTAL:NO", "/MACHINE:X86", "/DLL", "/NOENTRY",
                          f"/OUT:{raw_out}", str(obj)], capture_output=True, text=True,
                         errors="replace", env=build.compiler_environment(root), cwd=build.ROOT)
    assert raw.returncode == 0
    assert "LNK4001: no object files specified" in raw.stdout + raw.stderr

    fixed_out = work / "fixed.dll"
    response_dir = tmp_path / "response path with spaces"
    response_dir.mkdir()
    response = response_dir / "objects with spaces.rsp"
    response.write_text(f'"{build.wine_path(obj)}"\n', encoding="utf-8")
    fixed = pr._link(["/DLL", "/NOENTRY", f"/OUT:{fixed_out}", f"@{response}"])
    assert fixed.returncode == 0, fixed.stdout + fixed.stderr
    assert pr._valid_link_image(fixed_out) == (True, "")
    assert pr._link_input_path(build.wine_path(obj)) == obj.resolve()

    empty = work / "empty.obj"
    empty.write_bytes(b"")
    rejected = pr._link(["/DLL", "/NOENTRY", f"/OUT:{work / 'empty.dll'}", empty])
    assert rejected.returncode != 0
    assert "input missing or empty" in rejected.stderr

    stale = work / "stale.dll"
    stale.write_bytes(fixed_out.read_bytes())
    fake_result = subprocess.CompletedProcess([], 0, "", "")
    monkeypatch.setattr(pr, "subprocess", types.SimpleNamespace(
        run=lambda *args, **kwargs: fake_result, CompletedProcess=subprocess.CompletedProcess))
    no_new_image = pr._link(["/DLL", "/NOENTRY", f"/OUT:{stale}", obj])
    assert no_new_image.returncode != 0
    assert "no valid PE image" in no_new_image.stderr


@toolchain
def test_synthetic_removal_objdiff_shows_only_the_definition(tmp_path):
    before = compile_to(tmp_path, "legacy", LEGACY_CPP)
    keep = tmp_path / "before.obj"
    shutil.copy2(before, keep)
    text = LEGACY_CPP.replace("int C::get() { return b * 3; }\n", "")
    after = compile_to(tmp_path, "legacy", text)
    diff = pr.objdiff(keep, after)
    assert diff["removed"] == ["?get@C@@QAEHXZ"] and not diff["changed"] and diff["unchanged"] == 1
    assert not pr.defines(after, "?get@C@@QAEHXZ") and pr.defines(keep, "?get@C@@QAEHXZ")
