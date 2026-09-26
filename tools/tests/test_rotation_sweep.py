"""Toggle generation for tools/rotation_sweep.py (text only; no compiler)."""
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rotation_sweep as R  # noqa: E402

SOURCE = """// Owner::run( is mentioned in a comment first
struct Owner { void run(void *arg); void *m_objects; };
void notify(void *, void *);
void Owner::run(void *arg)
{
\tvoid *contain = m_objects;
\tnotify(*(void **)((char *)this - 0x18), arg);
\tnotify(contain, 0);
}
"""
SYMBOL = "?run@Owner@@QAEXPAX@Z"


def test_the_definition_not_the_comment_or_declaration_is_found():
    line0, brace, end = R.locate(SOURCE, SYMBOL)
    assert SOURCE[line0:brace].startswith("void Owner::run(void *arg)")
    assert SOURCE[end] == "}"


def test_every_pushed_argument_and_initialiser_gets_a_copy_toggle():
    found = {what for what, _ in R.variants(SOURCE, SYMBOL).values()}
    assert "copy: argument `*(void **)((char *)this - 0x18)` of notify(...)" in found
    assert "copy: argument `arg` of notify(...)" in found
    assert "copy: argument `contain` of notify(...)" in found
    assert "copy: initialiser of local `contain`" in found
    assert not any("`0`" in w for w in found)          # literals take no rotation step


def test_a_single_use_local_can_be_inlined():
    found = R.variants(SOURCE, SYMBOL)
    inline = [text for what, text in found.values() if what.startswith("inline: single-use local `contain`")]
    assert inline and "notify((m_objects), 0);" in inline[0] and "void *contain" not in inline[0]


def test_every_variant_carries_the_identity_inline_once():
    for _, text in R.variants(SOURCE, SYMBOL).values():
        assert text.count(R.PRELUDE) == 1


def test_pairs_combine_two_distinct_toggles_once():
    first = R.variants(SOURCE, SYMBOL)
    second = R.pairs(SOURCE, SYMBOL, first)
    assert second
    for what, text in second.values():
        assert " AND " in what and text.count(R.PRELUDE) == 1
    assert len({t for _, t in second.values()}) == len(second)


def test_a_nested_scope_names_the_innermost_class():
    text = "struct ios_base { void f(int); };\nvoid ios_base::f(int x)\n{\n\tg(x);\n}\n"
    line0, brace, _ = R.locate(text, "?f@ios_base@_STL@@QAEXH@Z")
    assert text[line0:brace].startswith("void ios_base::f(int x)")
