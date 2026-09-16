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


def test_choices_are_accepted_by_shape_search_variants():
    choices = shape_family_levers.choices_for(SOURCE)
    variants = list(shape_search.variants(SOURCE, choices))
    assert len(variants) == 8
    assert variants[0][1] == SOURCE
