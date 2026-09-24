"""layout_witness --compile must attribute failures, not swallow them."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import layout_witness as lw


def test_first_cl_error_strips_file_line_so_tus_group():
    a = "Thing.cpp(12) : error C1083: Cannot open include file: 'bink.h': No such file or directory"
    b = "Other.cpp(8) : fatal error C1083: Cannot open include file: 'bink.h': No such file or directory"
    assert build.first_cl_error(a) == build.first_cl_error(b)
    assert build.first_cl_error(a).startswith("C1083:")
    assert "bink.h" in build.first_cl_error(a)


def test_first_cl_error_keeps_the_identifier():
    text = "TurretAI.cpp(41) : error C2065: 'theGameLogic' : undeclared identifier"
    assert build.first_cl_error(text) == "C2065: 'theGameLogic' : undeclared identifier"


def test_empty_transcript_is_a_named_bucket_not_silence():
    assert build.first_cl_error("") == "(empty compiler output)"
    assert build.first_cl_error("   \n") == "(empty compiler output)"


def test_wine_launch_failure_is_the_line_not_empty():
    text = "Application could not be started, The system cannot find the file specified.\n"
    assert "Application could not be started" in build.first_cl_error(text)


def test_groups_are_ranked_by_size_and_name_examples():
    fails = [
        ("GameEngine/Source/a.cpp", "a.cpp(1) : error C1083: Cannot open include file: 'x.h': No such file or directory"),
        ("GameEngine/Source/b.cpp", "b.cpp(2) : error C1083: Cannot open include file: 'x.h': No such file or directory"),
        ("GameEngine/Source/c.cpp", "c.cpp(3) : error C1083: Cannot open include file: 'x.h': No such file or directory"),
        ("GameEngine/Source/d.cpp", "d.cpp(4) : error C2065: 'theGameLogic' : undeclared identifier"),
    ]
    lines, ranked = lw.format_failure_groups(fails, examples=2)
    report = "\n".join(lines)
    assert "4 failing TUs in 2 groups" in report
    assert ranked[0][0].startswith("C1083:")
    assert ranked[0][1] == [
        "GameEngine/Source/a.cpp",
        "GameEngine/Source/b.cpp",
        "GameEngine/Source/c.cpp",
    ]
    assert "and 1 more" in report
    assert "theGameLogic" in report


def test_compile_reference_does_not_swallow_exceptions():
    src = Path(__file__).resolve().parents[1] / "layout_witness.py"
    text = src.read_text(encoding="utf-8")
    assert "except BaseException" not in text
    assert "try_compile_source" in text
    assert "format_failure_groups" in text


def _image():
    """Tiny PE-like image: .text at RVA 0x1000 (raw 0x100), .rdata at RVA 0x2000 (raw 0x200), base 0x400000.
    Exports: ?a@@ -> thunk 0x1010 -> thunk 0x1018 -> body 0x1090, ?b@@ -> body 0x10E0."""
    import struct
    data = bytearray(b'\xcc' * 0x300)
    struct.pack_into('<I', data, 0x3C, 0x40)
    struct.pack_into('<I', data, 0x40 + 0x34, 0x400000)
    def jmp(site, dst):
        o = 0x100 + site - 0x1000
        data[o] = 0xE9; struct.pack_into('<i', data, o + 1, dst - site - 5)
    jmp(0x1010, 0x1018)
    jmp(0x1018, 0x1090)
    data[0x200:0x300] = bytes(0x100)
    struct.pack_into('<I', data, 0x40 + 0x78, 0x2010)            # export directory
    struct.pack_into('<IIII', data, 0x210 + 0x18, 2, 0x2040, 0x2048, 0x2050)
    struct.pack_into('<II', data, 0x240, 0x1010, 0x10E0)         # address table
    struct.pack_into('<II', data, 0x248, 0x2060, 0x2068)         # name pointers
    struct.pack_into('<HH', data, 0x250, 0, 1)                   # name ordinals
    data[0x260:0x265] = b'?a@@\0'
    data[0x268:0x26D] = b'?b@@\0'
    secs = [dict(name='.text', rva=0x1000, size=0x100, raw_pointer=0x100),
            dict(name='.rdata', rva=0x2000, size=0x100, raw_pointer=0x200)]
    return bytes(data), secs


def test_exported_names_follow_thunk_chains_to_the_body():
    data, secs = _image()
    names = lw.exported_names(data, secs, {0x1010, 0x1018})
    assert names[0x1090] == {'?a@@'}   # through two chained thunks
    assert names[0x1010] == {'?a@@'}   # the exported thunk itself
    assert names[0x10E0] == {'?b@@'}   # exported directly
    assert 0x10A0 not in names
