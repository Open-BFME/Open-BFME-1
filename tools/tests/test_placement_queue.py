"""Placement requires stronger evidence than a method emitted from a header."""
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import placement_queue as queue  # noqa: E402


POPUP = "Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGame.cpp"
MISPLACED = "Code/GameEngine/Source/Common/GameInfoReset.cpp"
NETWORK = "Code/GameEngine/Source/GameNetwork"


def _write(root, relative, text="// fixture\n"):
    path = root / relative
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)


def _world(tmp_path):
    root = tmp_path / "repo"
    _write(root, POPUP)
    _write(root, MISPLACED)
    _write(root, f"{NETWORK}/keep-directory.txt")

    zh_root = queue.ZH
    _write(root, f"{zh_root}/GameEngine/Source/GameNetwork/GameInfo.cpp")
    _write(root, f"{zh_root}/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGame.cpp")

    ledger = (
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        f"?setUseStats@GameInfo@@QAEXH@Z,,0x00100000,10,{POPUP},matched,\n"
        f"?reset@GameInfo@@QAEXXZ,,0x00100010,10,{MISPLACED},matched,\n"
    )
    _write(root, "reverse/functions.csv", ledger)
    return root


def test_exact_zh_source_path_outranks_an_inline_method_owner(tmp_path):
    root = _world(tmp_path)
    single, homes = queue.survey(root)
    zh = queue.zh_directories(root)

    assert single[POPUP] == "GameInfo"
    assert queue.destination(root, POPUP, "GameInfo", homes, zh, {}) == NETWORK

    queued, skipped = queue.build(root)
    assert all(source != POPUP for source, _target, _cls in queued)
    assert skipped["ZH keeps this source at its current path"] == 1


def test_a_source_without_exact_zh_path_still_moves_to_its_class(tmp_path):
    root = _world(tmp_path)
    queued, _skipped = queue.build(root)

    assert (MISPLACED, f"{NETWORK}/GameInfoReset.cpp", "GameInfo") in queued
