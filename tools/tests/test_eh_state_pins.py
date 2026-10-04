import re
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import eh_state_pins as ep  # noqa: E402

# two temporaries in exclusive scopes share a frame slot, so their unwind
# funclets are byte-identical labels bound to different states
SOURCE = r"""
#include <windows.h>
struct S { S(); ~S(); int x; };
__declspec(noinline) S::S() : x(0) {}
__declspec(noinline) S::~S() { x = 1; }
__declspec(noinline) void use(S &s) { if (s.x == 7) throw 1; }
__declspec(noinline) void parent(int a)
{
    if (a) { S t; use(t); } else { S t; use(t); }
    if (a > 1) { S u; use(u); } else { S u; use(u); }
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) { parent(0); return 0; }
"""


def fixture_commands(vc, out, *, windows):
    # Linux must launch the Windows tools through Wine and translate every
    # path argument; direct .exe execution only works on a Windows host.
    runner = []
    path = str
    if not windows:
        wine = shutil.which("wine")
        assert wine is not None, "wine not found: the integration fixture requires Wine"
        runner = [wine]
        path = build.wine_path
    return (
        [*runner, str(vc / "bin" / "cl.exe"), "/nologo", "/c", "/MD", "/O2", "/EHsc", "/Gy",
         f"/I{path(vc / 'include')}", f"/I{path(vc / 'PlatformSDK' / 'Include')}",
         f"/Fo{path(out / 't.obj')}", path(out / "t.cpp")],
        [*runner, str(vc / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO",
         "/SUBSYSTEM:WINDOWS", "/SAFESEH:NO", f"/MAP:{path(out / 't.map')}",
         f"/OUT:{path(out / 't.exe')}", path(out / "t.obj"),
         path(vc / "lib" / "msvcrt.lib"), path(vc / "lib" / "kernel32.lib")]
    )


@pytest.fixture(scope="module")
def linked(tmp_path_factory):
    try:
        root = build.vc71_root()
    except SystemExit:
        pytest.skip("VC 7.1 toolchain not present")
    env = build.compiler_environment(root, None)
    vc = root / "Vc7"
    out = tmp_path_factory.mktemp("ehpins")
    (out / "t.cpp").write_text(SOURCE, encoding="ascii")
    for command in fixture_commands(vc, out, windows=sys.platform == "win32"):
        proc = subprocess.run(command, capture_output=True, text=True, env=env)
        assert proc.returncode == 0, proc.stdout + proc.stderr
    text = (out / "t.map").read_text(encoding="latin-1")
    rva = int(re.search(r"\?parent@@YAXH@Z\s+([0-9a-f]{8})", text).group(1), 16) - 0x400000
    obj = ep.Obj((out / "t.obj").read_bytes())
    retail = ep.Retail(out / "t.exe")
    return obj, ep.tables(obj, {"?parent@@YAXH@Z": rva}, retail)


def row(address):
    return {"target_rva": f"0x{address:08X}"}


def test_tables_agree_on_every_to_state(linked):
    obj, tables = linked
    assert len(tables) == 1
    t = tables[0]
    assert t["theirs"] and [x for x, _ in t["ours"]] == [x for x, _ in t["theirs"]]


def test_the_state_label_is_proven_and_its_twin_is_wrong(linked):
    obj, tables = linked
    ours, theirs = tables[0]["ours"], tables[0]["theirs"]
    twins_seen = 0
    for state, ((_, label), (_, address)) in enumerate(zip(ours, theirs)):
        if label is None:
            continue
        good = ep.judge(obj, tables, row(address), label)
        assert good["verdict"] == "proven", good
        for twin in good["twins"]:
            if any(lab == twin and a == address for (_, lab), (_, a) in zip(ours, theirs)):
                continue  # the twin is also bound to this address
            bad = ep.judge(obj, tables, row(address), twin)
            assert bad["verdict"] == "wrong" and bad["correct"] == label and bad["ambiguous"]
            twins_seen += 1
    assert twins_seen > 0, "the fixture no longer produces byte-identical funclets"


def test_an_address_no_parent_reaches_is_unprovable(linked):
    obj, tables = linked
    label = next(lab for _, lab in tables[0]["ours"] if lab)
    assert ep.judge(obj, tables, row(0x10), label)["verdict"] == "unprovable"
    assert ep.judge(obj, tables, row(0x10), "$L999999")["verdict"] == "unprovable"


def test_a_pin_the_object_no_longer_defines_is_stale_with_the_state_label(linked):
    obj, tables = linked
    ours, theirs = tables[0]["ours"], tables[0]["theirs"]
    state = next(i for i, (_, lab) in enumerate(ours) if lab)
    got = ep.judge(obj, tables, row(theirs[state][1]), "$L999999")
    assert got["verdict"] == "stale" and got["correct"] == ours[state][1] and not got["pin_defined"]


def test_label_of_reads_object_symbol_or_name():
    assert ep.label_of({"name": "?a_1@@YAXXZ", "notes": "x;object-symbol=$L4571;y"}) == "$L4571"
    assert ep.label_of({"name": "$L314", "notes": ""}) == "$L314"
    assert ep.label_of({"name": "?f@@YAXXZ", "notes": "object-symbol=_$E1"}) is None


@pytest.mark.parametrize("windows", [False, True])
def test_fixture_commands_use_host_runner_and_translate_all_paths(monkeypatch, tmp_path, windows):
    vc, out = tmp_path / "VC with spaces", tmp_path / "output with spaces"
    monkeypatch.setattr(shutil, "which", lambda name: "/usr/bin/wine" if name == "wine" else None)
    translated = []
    def wine_path(path):
        translated.append(path)
        return "Z:" + str(path)
    monkeypatch.setattr(build, "wine_path", wine_path)
    compile_cmd, link_cmd = fixture_commands(vc, out, windows=windows)
    prefix = [] if windows else ["/usr/bin/wine"]
    assert compile_cmd[:len(prefix) + 1] == prefix + [str(vc / "bin" / "cl.exe")]
    assert link_cmd[:len(prefix) + 1] == prefix + [str(vc / "bin" / "link.exe")]
    paths = [vc / "include", vc / "PlatformSDK" / "Include", out / "t.obj", out / "t.cpp",
             out / "t.map", out / "t.exe", out / "t.obj", vc / "lib" / "msvcrt.lib",
             vc / "lib" / "kernel32.lib"]
    assert translated == ([] if windows else paths)
    mapped = lambda path: str(path) if windows else "Z:" + str(path)
    assert compile_cmd[-4:] == ["/I" + mapped(paths[0]), "/I" + mapped(paths[1]),
                               "/Fo" + mapped(paths[2]), mapped(paths[3])]
    assert link_cmd[-5:] == ["/MAP:" + mapped(paths[4]), "/OUT:" + mapped(paths[5]),
                            *(mapped(path) for path in paths[6:])]


def test_fixture_requires_wine_on_non_windows(monkeypatch, tmp_path):
    monkeypatch.setattr(shutil, "which", lambda name: None)
    with pytest.raises(AssertionError, match="wine not found"):
        fixture_commands(tmp_path, tmp_path, windows=False)
