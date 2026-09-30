import os
import re
import struct
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import startup_tables as st  # noqa: E402
import throwinfo_graph as tg  # noqa: E402

EMITTER = r"""
#include <windows.h>
int g_copies, g_dtors;
class XferException {
public:
    XferException(int t) : text(0), tagValue(t) {}
    XferException(const XferException &that) : text(0), tagValue(that.tagValue) { ++g_copies; }
    ~XferException(void) { ++g_dtors; }
    char *text;
    int tagValue;
};
void emitGraph(int t) { throw XferException(t); }
void emitInt(int t) { throw t; }
void manualThrow(int t);
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // every try ends in catch (...): a wrong ThrowInfo must score, never
    // escape to an unhandled-exception dialog
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    int score = 0;
    try { manualThrow(7); } catch (XferException &e) { score += e.tagValue == 7; } catch (...) {}
    int copies = g_copies;
    try { manualThrow(9); } catch (XferException e) { score += e.tagValue == 9 && g_copies == copies + 1; }
    catch (...) {}
    try { emitGraph(5); } catch (const XferException &e) { score += e.tagValue == 5; } catch (...) {}
    try { manualThrow(3); } catch (int) { score = -100; } catch (...) { score += 1; }
    return score == 4 && g_dtors >= 5 ? 37 : 90 + score;
}
"""
# the game sources' spelling: C++-linkage declarations and an `int` ThrowInfo
MANUAL = r"""
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern int g_guardTargetTypeThrowInfo;
struct Error { char *text; int tag; };
void manualThrow(int t)
{
    Error e = { 0, t };
    _CxxThrowException(&e, &g_guardTargetTypeThrowInfo);
}
"""
THROW = "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8"


@pytest.fixture(scope="module")
def built(tmp_path_factory):
    try:
        root = build.vc71_root()
    except SystemExit:
        pytest.skip("VC 7.1 toolchain not present")
    env = build.compiler_environment(root, None)
    vc = root / "Vc7"
    out = tmp_path_factory.mktemp("eh")
    for name, text in (("emitter", EMITTER), ("manual", MANUAL)):
        (out / f"{name}.cpp").write_text(text, encoding="ascii")
        proc = subprocess.run([str(vc / "bin" / "cl.exe"), "/nologo", "/c", "/MD", "/O2", "/EHsc",
                               f"/I{vc / 'include'}", f"/I{vc / 'PlatformSDK' / 'Include'}",
                               f"/Fo{out / name}.obj", str(out / f"{name}.cpp")],
                              capture_output=True, text=True, env=env)
        assert proc.returncode == 0, proc.stdout

    def link(tag, throwinfo):
        proc = subprocess.run([str(vc / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO",
                               "/SUBSYSTEM:WINDOWS", "/SAFESEH:NO", "/BASE:0x600000", f"/MAP:{out / tag}.map",
                               f"/OUT:{out / tag}.exe", str(out / "emitter.obj"), str(out / "manual.obj"),
                               str(vc / "lib" / "msvcrt.lib"), str(vc / "lib" / "kernel32.lib"), THROW,
                               f"/alternatename:?g_guardTargetTypeThrowInfo@@3HA={throwinfo}"],
                              capture_output=True, text=True, env=env)
        assert proc.returncode == 0, proc.stdout
        return out / f"{tag}.exe", out / f"{tag}.map"

    return out, link


def run(exe):
    runtime = build.ROOT / "inputs" / "toolchains" / "vs2003"
    if not (runtime / "msvcr71.dll").exists():
        pytest.skip("msvcr71.dll not present")
    env = dict(os.environ, PATH=str(runtime) + os.pathsep + os.environ.get("PATH", ""))
    return subprocess.run([str(exe)], capture_output=True, env=env, timeout=60).returncode


def test_graph_walk_finds_the_four_items_and_six_edges(built):
    out, _ = built
    items, terminals = tg.walk((out / "emitter.obj").read_bytes(), "__TI1?AVXferException@@")
    assert sorted(len(i["bytes"]) for i in items.values()) == [8, 16, 28, 28]
    assert sum(len(i["relocs"]) for i in items.values()) == 6
    assert terminals == {"??1XferException@@QAE@XZ", "??0XferException@@QAE@ABV0@@Z", "??_7type_info@@6B@"}


def test_aliased_manual_throw_is_caught_at_a_moved_base(built):
    _, link = built
    exe, _ = link("alias", "__TI1?AVXferException@@")
    assert run(exe) == 37


def test_wrong_type_throwinfo_is_caught_as_that_type(built):
    """Negative control: the same manual throw bound to int's graph lands in
    catch (int), so the harness can tell a wrong ThrowInfo apart."""
    _, link = built
    exe, _ = link("wrong", "__TI1H")
    assert run(exe) & 0xFFFFFFFF == (90 - 100) & 0xFFFFFFFF  # catch (int) ran


def test_linked_graph_pointers_follow_their_targets(built):
    _, link = built
    exe, mapfile = link("alias_map", "__TI1?AVXferException@@")
    import pefile
    pe = pefile.PE(str(exe), fast_load=True)
    image, base = pe.get_memory_mapped_image(), pe.OPTIONAL_HEADER.ImageBase
    names = {}
    for line in mapfile.read_text(encoding="latin-1").splitlines():
        m = re.match(r"^\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s", line)
        if m:
            names[m.group(1)] = int(m.group(2), 16)
    assert names["?g_guardTargetTypeThrowInfo@@3HA"] == names["__TI1?AVXferException@@"]
    items, _ = tg.walk((built[0] / "emitter.obj").read_bytes(), "__TI1?AVXferException@@")
    checked = 0
    for name, item in items.items():
        for off, target in item["relocs"]:
            value = struct.unpack_from("<I", image, names[name] + off - base)[0]
            assert value == names[target], (name, off, target)
            checked += 1
    assert checked == 6


def test_emitted_graph_equals_retail_at_its_retail_address(built):
    if not build.EXE.exists():
        pytest.skip("retail image not present")
    items, _ = tg.walk((built[0] / "emitter.obj").read_bytes(), "__TI1?AVXferException@@")
    rows = st.matched_rows()
    rows_at = {}
    for r in rows:
        rows_at.setdefault(int(r["target_rva"], 16), []).append(r["name"])
    report = tg.verify(items, "__TI1?AVXferException@@", 0x011DFE5C, st.Retail(), st.Resolver(rows), rows_at)
    assert report["problems"] == [] and report["bytes"] == 80 and len(report["fields"]) == 6
