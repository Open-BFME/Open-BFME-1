"""Tests for the bounded non-EH codegen choice generator."""
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import shape_family_levers  # noqa: E402
import shape_search  # noqa: E402


SOURCE = """class Sample {
public:
    bool test(int a, int b);
};
bool Sample::test(int a, int b)
{
    int first = a;
    int second = b;
    int sum = first + second;
    return !isReady(sum);
}
"""

BIT_SOURCE = """void check(unsigned int *words, unsigned int index, unsigned int bit)
{
    if ( words[index >> 5] & bit )
        return;
    if( ( words[index >> 5] & bit ) != 0 )
        return;
}
"""

COPY_SOURCE = """struct Node { Node *next; };
Node *walk(Node *start)
{
    Node *cursor;
    cursor = start;
    if (cursor != 0)
        return cursor;
    cursor = start;
    cursor = cursor->next;
    return cursor;
}
"""

CHAIN_SOURCE = """void chain(int a, int b, int c)
{
    int first = a;
    int second = b;
    int third = c;
    use(first, second, third);
}
"""

SHADOW_COPY_SOURCE = """struct Node { Node *next; };
void shadow(Node *source, const Node *other)
{
    Node *value;
    value = source;
    if (value != 0)
        return;
    {
        const Node *value;
        value = other;
        if (value != 0)
            return;
    }
}
"""

STORE_SOURCE = """struct Pair { int first; int second; };
void stores(Pair *pair, int a, int b)
{
    pair->first = a;
    pair->second = b;
}
"""

BRANCH_SOURCE = """bool branch(int ready)
{
    if (ready != 0) return true;
    return false;
}
"""

CONSTANT_SOURCE = """bool constant()
{
    return false;
}
"""

FRAME_SOURCE = """int frame(int input)
{
    int value = input;
    return value + 1;
}
"""

LOOP_SOURCE = """int loop(int limit)
{
    int value = 0;
    while (value < limit)
    {
        ++value;
    }
    return value;
}
"""


def test_sib_choice_reverses_only_a_unique_integer_addition():
    choices = shape_family_levers.choices_for(SOURCE, ("sib",))
    assert len(choices) == 1
    assert choices[0]["lever"] == "sib-order"
    assert choices[0]["after"] == ["    int sum = second + first;"]


def test_register_choice_swaps_independent_local_definitions():
    choices = shape_family_levers.choices_for(SOURCE, ("register",))
    assert len(choices) == 1
    assert "int second = b;\n    int first = a;" in choices[0]["after"][0]


def test_bool_choice_materialises_the_call_result():
    choices = shape_family_levers.choices_for(SOURCE, ("bool",))
    assert len(choices) == 1
    assert "unsigned char shape_result" in choices[0]["after"][0]
    assert "return !shape_result;" in choices[0]["after"][0]


def test_test_choice_reverses_simple_bit_test_operands():
    choices = shape_family_levers.choices_for(BIT_SOURCE, ("test",))
    assert len(choices) == 2
    assert all(choice["lever"] == "test-operand-order" for choice in choices)
    assert "if ( bit & words[index >> 5] )" in choices[0]["after"][0]
    assert "if ( ( bit & words[index >> 5] ) != 0 )" in choices[1]["after"][0]


def test_copy_choice_keeps_pointer_alias_for_guard_or_member_load():
    choices = shape_family_levers.choices_for(COPY_SOURCE, ("copy",))
    assert len(choices) == 2
    assert all(choice["lever"] == "copy-lifetime" for choice in choices)
    assert "Node *shape_copy_cursor_4 = cursor;" in choices[0]["after"][0]
    assert "shape_copy_cursor_7->next" in choices[1]["after"][0]


def test_overlapping_adjacent_choices_are_suppressed():
    choices = shape_family_levers.choices_for(CHAIN_SOURCE, ("register",))
    assert len(choices) == 1
    assert list(shape_search.variants(CHAIN_SOURCE, choices))


def test_copy_choice_skips_shadowed_pointer_names():
    assert shape_family_levers.choices_for(SHADOW_COPY_SOURCE, ("copy",)) == []


def test_store_choice_swaps_independent_field_stores():
    choices = shape_family_levers.choices_for(STORE_SOURCE, ("store",))
    assert len(choices) == 1
    assert choices[0]["lever"] == "store-order"
    assert "pair->second = b;\n    pair->first = a;" in choices[0]["after"][0]


def test_store_choice_accepts_side_effect_free_conditional_rhs():
    source = STORE_SOURCE.replace("pair->second = b;", "pair->second = (a != 0) ? -1 : 0;")
    choices = shape_family_levers.choices_for(source, ("store",))
    assert len(choices) == 1
    assert "pair->second = (a != 0) ? -1 : 0;\n    pair->first = a;" in choices[0]["after"][0]


def test_default_choices_include_store_order():
    choices = shape_family_levers.choices_for(STORE_SOURCE)
    assert any(choice["lever"] == "store-order" for choice in choices)


def test_loop_choice_toggles_empty_for_header():
    choices = shape_family_levers.choices_for(LOOP_SOURCE, ("loop",))
    assert len(choices) == 1
    assert choices[0]["lever"] == "loop-header"
    assert "for (; value < limit; )" in choices[0]["after"][0]


def test_branch_choice_folds_boolean_return_pair():
    choices = shape_family_levers.choices_for(BRANCH_SOURCE, ("branch",))
    assert len(choices) == 1
    assert choices[0]["lever"] == "branch-return"
    assert "return ready != 0;" in choices[0]["after"][0]


def test_constant_choice_materialises_false():
    choices = shape_family_levers.choices_for(CONSTANT_SOURCE, ("constant",))
    assert len(choices) == 1
    assert choices[0]["lever"] == "constant-materialization"
    assert "unsigned char shape_constant_false_2 = 0;" in choices[0]["after"][0]


def test_frame_choice_promotes_scalar_local():
    choices = shape_family_levers.choices_for(FRAME_SOURCE, ("frame",))
    assert len(choices) == 1
    assert choices[0]["lever"] == "frame-array"
    assert "int shape_frame_value_2[2];" in choices[0]["after"][0]
    assert "return shape_frame_value_2[1] + 1;" in choices[0]["after"][0]


def test_choices_are_accepted_by_shape_search_variants():
    choices = shape_family_levers.choices_for(SOURCE)
    variants = list(shape_search.variants(SOURCE, choices))
    assert len(variants) == 8
    assert variants[0][1] == SOURCE
