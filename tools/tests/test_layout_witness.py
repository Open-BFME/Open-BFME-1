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
