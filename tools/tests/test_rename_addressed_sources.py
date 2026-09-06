"""The refusals, which are the whole safety story of this tool.

It renames a file only when the new name follows from rows the file already owns.
Every test here is a case where an earlier version produced a rename that was not
an improvement, so each one is a defect this tool shipped with for one iteration:

  * `Rva006D51B0Ctor.cpp -> Rva006D51B0_ctor.cpp` -- the row is
    `??0Rva006D51B0@@QAE@II@Z`, whose class IS address-derived, but the `??0`
    constructor prefix ends in a digit so readability_metric.PLACEHOLDER finds no
    word boundary before `Rva` and scores the row as a real name.
  * `Bfme5BasedListCtor.cpp -> Gen_000FDA80.cpp` -- strictly worse than the name
    it replaced, from the same blind spot.
  * `Gen_007164b0_Global.cpp -> get_007164b0.cpp` -- the address moved into the
    middle of the name, where a prefix test cannot see it.

Judging the PROPOSED name rather than the row is what closes all three, and it
stays closed however PLACEHOLDER changes.
"""
import importlib.util
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

spec = importlib.util.spec_from_file_location(
    "rename_addressed_sources", TOOLS / "rename_addressed_sources.py")
ras = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ras)


def test_a_proposed_name_that_still_hides_an_address_is_refused():
    assert ras.opaque("Rva006D51B0_ctor")
    assert ras.opaque("Gen_000FDA80")
    assert ras.opaque("get_007164b0")                  # address in the middle
    assert ras.opaque("Register_Rva009723C0_Prototype")
    assert ras.opaque("exp_00716520")
    assert ras.opaque("BfmeConv1152")


def test_a_real_name_is_not_mistaken_for_an_address():
    for stem in ("W3DTreeBuffer_cull", "Matrix3D_Rotate_Vector", "luaB_print",
                 "ServiceHubImpl_ctor", "DX8Wrapper_Set_Pixel_Shader_Constant",
                 "AudioEventRTS_isPositionalAudio", "Dictionary_insert"):
        assert not ras.opaque(stem), stem


def test_a_hex_looking_word_without_a_digit_is_a_word():
    """`Facade` and `Decade` are six hex characters each. Requiring a digit in the
    run is the only thing separating them from `007164b0`, and without it this
    tool would refuse perfectly good names and quietly do less work than it says."""
    for stem in ("Facade_build", "Decade", "Deface_Mesh", "Cull"):
        assert not ras.opaque(stem), stem
    assert ras.opaque("Deadbeef0")                      # a digit makes it an address


def test_the_owning_class_is_read_out_of_the_mangled_name():
    assert ras.identity("?updateSway@W3DShrubBuffer@@QAEXXZ") == ("W3DShrubBuffer", "updateSway")
    assert ras.identity("??0ServiceHubImpl@@QAE@XZ") == ("ServiceHubImpl", "ctor")
    assert ras.identity("??1W3DTreeBuffer@@UAE@XZ") == ("W3DTreeBuffer", "dtor")
    assert ras.identity("?updateMinMax@@YAXPAMM0@Z") == (None, "updateMinMax")


def test_a_name_this_tool_cannot_read_is_refused_not_guessed():
    """Operators, templates and the compiler's own glue have no spelling that makes
    a filename anyone wants. Returning None sends them to an agent with evidence;
    guessing would put an invented name on disk where nothing can catch it."""
    for name in ("??_GFoo@@UAEPAXI@Z", "??4Foo@@QAEAAV0@ABV0@@Z",
                 "?fn@?$Vector@H@@QAEXXZ", "??_7Foo@@6B@"):
        assert ras.identity(name) is None, name


def test_rows_from_two_classes_do_not_get_one_of_the_two_names():
    stem, why = ras.proposal(["?a@Alpha@@QAEXXZ", "?b@Beta@@QAEXXZ"])
    assert stem is None and "span" in why

    stem, why = ras.proposal(["?a@Alpha@@QAEXXZ", "?b@Alpha@@QAEXXZ"])
    assert stem == "Alpha" and why is None
