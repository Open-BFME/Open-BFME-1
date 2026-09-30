import re
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
    proc = subprocess.run([str(vc / "bin" / "cl.exe"), "/nologo", "/c", "/MD", "/O2", "/EHsc", "/Gy",
                           f"/I{vc / 'include'}", f"/I{vc / 'PlatformSDK' / 'Include'}", f"/Fo{out / 't.obj'}",
                           str(out / "t.cpp")], capture_output=True, text=True, env=env)
    assert proc.returncode == 0, proc.stdout
    proc = subprocess.run([str(vc / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO",
                           "/SUBSYSTEM:WINDOWS", "/SAFESEH:NO", f"/MAP:{out / 't.map'}", f"/OUT:{out / 't.exe'}",
                           str(out / "t.obj"), str(vc / "lib" / "msvcrt.lib"), str(vc / "lib" / "kernel32.lib")],
                          capture_output=True, text=True, env=env)
    assert proc.returncode == 0, proc.stdout
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
