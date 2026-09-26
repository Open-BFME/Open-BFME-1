"""Header adoption must remove only the requested class declaration."""
import sys
from subprocess import CompletedProcess
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import adopt_header


FOLLOWING = "\nclass KeepMe\n{\npublic:\n    void untouched();\n};\n"


@pytest.mark.parametrize("declaration", [
    "class AsciiString { private: void *m_data; };\n",
    "class AsciiString\n{\nprivate:\n    void *m_data;\n};\n",
    "class AsciiString {\n    void method() { if (true) { action(); } }\n"
    "    struct Nested { int value; };\n    void *m_data;\n};\n",
    "class AsciiString {\n    // } and { are prose\n"
    "    /* };\nclass Fake {\n */\n"
    '    const char *method() { return "}\\\"{"; }\n'
    "    char brace() { return '}'; }\n    void *m_data;\n};\n",
])
def test_rewrite_preserves_the_following_class(declaration):
    source = declaration + FOLLOWING
    rewritten = adopt_header.rewrite(source, "AsciiString", "ascii_string.h", "headers")

    assert rewritten == '// cl: /Iheaders\n#include "ascii_string.h"\n' + FOLLOWING


def test_template_declaration_is_removed_with_its_class():
    source = "template <typename T>\nclass StringBase\n{\n    T *m_data;\n};\n" + FOLLOWING

    rewritten = adopt_header.rewrite(source, "StringBase", "string_base.h", "headers")

    assert rewritten == '// cl: /Iheaders\n#include "string_base.h"\n' + FOLLOWING


@pytest.mark.parametrize("source", [
    "class AsciiString { void *m_data;\n" + FOLLOWING,
    "class AsciiString { /* unterminated\n" + FOLLOWING,
    'class AsciiString { const char *text = "unterminated\n' + FOLLOWING,
    "class AsciiString { void *m_data; } missing_semicolon;\n" + FOLLOWING,
])
def test_incomplete_declarations_fail_without_rewriting(source):
    with pytest.raises(ValueError, match="supported local AsciiString class"):
        adopt_header.rewrite(source, "AsciiString", "ascii_string.h", "headers")


def test_unsupported_raw_strings_fail_explicitly():
    source = 'class AsciiString { const char *text = R"(}\")"; };\n' + FOLLOWING

    with pytest.raises(ValueError, match="raw string literals"):
        adopt_header.rewrite(source, "AsciiString", "ascii_string.h", "headers")


def test_class_text_in_a_comment_is_preserved():
    comment = "/*\nclass AsciiString { void *m_data; };\n*/\n"
    source = comment + "class AsciiString { void *m_data; };\n" + FOLLOWING

    rewritten = adopt_header.rewrite(source, "AsciiString", "ascii_string.h", "headers")

    assert comment in rewritten
    assert rewritten.endswith('#include "ascii_string.h"\n' + FOLLOWING)


@pytest.mark.parametrize("suffix", [
    " /* retained\ntext\n*/\n" + FOLLOWING,
    " class KeepMe { void untouched(); };\n",
])
def test_same_line_content_after_the_class_is_preserved(suffix):
    source = "class AsciiString { void *m_data; };" + suffix

    rewritten = adopt_header.rewrite(source, "AsciiString", "ascii_string.h", "headers")

    assert rewritten == '// cl: /Iheaders\n#include "ascii_string.h"\n' + suffix


def test_a_leading_block_comments_closing_delimiter_is_preserved():
    comment = "/* retained\n */ "
    source = comment + "class AsciiString { void *m_data; };\n" + FOLLOWING

    rewritten = adopt_header.rewrite(source, "AsciiString", "ascii_string.h", "headers")

    assert rewritten == '// cl: /Iheaders\n' + comment + '#include "ascii_string.h"\n' + FOLLOWING


def test_comments_between_a_template_and_class_do_not_leave_a_hanging_template():
    source = "template <typename T>\n/* comment\n */ class StringBase { T *m_data; };\n" + FOLLOWING

    rewritten = adopt_header.rewrite(source, "StringBase", "string_base.h", "headers")

    assert rewritten == '// cl: /Iheaders\n#include "string_base.h"\n' + FOLLOWING


def test_preprocessor_class_boundaries_are_rejected():
    source = "class AsciiString {\n    void *m_data;\n#if 0\n};\n#endif\n};\n" + FOLLOWING

    with pytest.raises(ValueError, match="supported local AsciiString class"):
        adopt_header.rewrite(source, "AsciiString", "ascii_string.h", "headers")


def test_an_unsupported_multiline_template_is_rejected():
    source = "template <\n typename T\n>\nclass StringBase { T *m_data; };\n" + FOLLOWING

    with pytest.raises(ValueError, match="supported local StringBase class"):
        adopt_header.rewrite(source, "StringBase", "string_base.h", "headers")


def test_automatic_commit_does_not_add_fabricated_attribution(tmp_path, monkeypatch):
    (tmp_path / "adopted.cpp").touch()
    monkeypatch.setattr(adopt_header, "ROOT", tmp_path)
    messages = []

    def run(args, **kwargs):
        if args[:2] == ["git", "commit"]:
            messages.append(kwargs["input"])
        return CompletedProcess(args, 0)

    monkeypatch.setattr(adopt_header.subprocess, "run", run)

    assert adopt_header.land(["adopted.cpp"], [], "AsciiString", "ascii_string.h") == 0
    assert len(messages) == 1
    assert "Co-Authored-By:" not in messages[0]
    assert "Claude-Session:" not in messages[0]
