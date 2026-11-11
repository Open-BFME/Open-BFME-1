"""The naming lane's landing rule."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane  # noqa: E402


def test_two_vendors_land_an_uncontested_name():
    assert name_lane.wins({"claude-fable", "grok"}, [])


def test_one_vendor_never_lands_a_name():
    assert not name_lane.wins({"claude-opus", "claude-fable"}, [])


def test_a_contested_name_needs_a_two_vote_lead():
    # DoXfer: Fable and Grok agreed while Opus had named the method differently
    assert not name_lane.wins({"claude-fable", "grok"}, [{"claude-opus"}])
    assert name_lane.wins({"claude-fable", "grok", "gpt-5.6-sol"}, [{"claude-opus"}])


def test_plain_spelling_strips_cpp_decoration():
    assert name_lane.plain_spelling("??0StructureCollapseFXVector@@QAE@XZ") == {"StructureCollapseFXVector"}
    assert name_lane.plain_spelling("?Rva008B5760Get@@YAPAVAptValue@@XZ") == {"Rva008B5760Get"}
    assert name_lane.plain_spelling("??_7Drawable@@6B@") == {"Drawable"}
    assert name_lane.plain_spelling("??_C@_0BB@foo@") == set()
    assert name_lane.plain_spelling("??_R0?AVFoo@@@8") == set()


def test_plain_spelling_strips_c_decoration():
    assert name_lane.plain_spelling("_piChatDisconnectedA") == {"piChatDisconnectedA"}
    assert name_lane.plain_spelling("_Rva0086B2D0Disconnected") == {"Rva0086B2D0Disconnected"}
    assert name_lane.plain_spelling("_piUserChangedNickCallback@0") == {"piUserChangedNickCallback"}


def test_plain_spelling_derives_only_from_its_input():
    assert name_lane.plain_spelling("??0BFMERetailAsciiString@@QAE@PBD@Z") == {"BFMERetailAsciiString"}
    assert name_lane.plain_spelling("??0MadeUpName@@QAE@XZ") == {"MadeUpName"}
    assert name_lane.plain_spelling("") == set()


def test_plain_spelling_reads_a_vftable_base_qualifier():
    assert name_lane.plain_spelling("??_7Rva007E9B40Object@@6BQ3MakeBaseA@@@") == {"Rva007E9B40Object", "Q3MakeBaseA"}
    assert name_lane.plain_spelling("??_7Object@@6BThing@@@") == {"Object", "Thing"}
    assert name_lane.plain_spelling("??_7Drawable@@6B@") == {"Drawable"}
