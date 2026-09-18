"""Placement requires stronger evidence than a method emitted from a header."""
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import placement_queue as queue  # noqa: E402


POPUP = "Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGame.cpp"
MISPLACED = "Code/GameEngine/Source/Common/GameInfoReset.cpp"
NETWORK = "Code/GameEngine/Source/GameNetwork"
COMMAND_SET = "Code/GameEngine/Source/Common/BfmeConv1641.cpp"
CLIENT = "Code/GameEngine/Source/GameClient"
CONTROL_BAR = f"{CLIENT}/GUI/ControlBar"
SPLIT = "Code/GameEngine/Source/Common/SplitOwner.cpp"


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


def _command_set_world(tmp_path):
    root = tmp_path / "repo"
    _write(root, COMMAND_SET)
    _write(root, f"{CONTROL_BAR}/CommandSetLifetime.cpp")
    _write(root, f"{CONTROL_BAR}/CommandSetParser.cpp")

    zh_root = queue.ZH
    _write(root, f"{zh_root}/GameEngine/Include/GameClient/ControlBar.h",
           "class CommandSet { public: void reset(); };\n")
    _write(root, f"{zh_root}/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp")

    ledger = (
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        f"??1CommandSet@@MAE@XZ,,0x00100000,10,{COMMAND_SET},matched,\n"
        f"??0CommandSet@@QAE@XZ,,0x00100010,10,{CONTROL_BAR}/CommandSetLifetime.cpp,matched,\n"
        f"?parse@CommandSet@@QAEXXZ,,0x00100020,10,{CONTROL_BAR}/CommandSetParser.cpp,matched,\n"
    )
    _write(root, "reverse/functions.csv", ledger)
    return root


def _split_home_world(tmp_path):
    root = tmp_path / "repo"
    first = f"{CLIENT}/GUI/First"
    second = f"{CLIENT}/GUI/Second"
    sources = [
        ("??1SplitOwner@@MAE@XZ", SPLIT),
        ("?firstA@SplitOwner@@QAEXXZ", f"{first}/FirstA.cpp"),
        ("?firstB@SplitOwner@@QAEXXZ", f"{first}/FirstB.cpp"),
        ("?firstC@SplitOwner@@QAEXXZ", f"{first}/FirstC.cpp"),
        ("?secondA@SplitOwner@@QAEXXZ", f"{second}/SecondA.cpp"),
        ("?secondB@SplitOwner@@QAEXXZ", f"{second}/SecondB.cpp"),
    ]
    for _name, source in sources:
        _write(root, source)

    zh_root = queue.ZH
    _write(root, f"{zh_root}/GameEngine/Include/GameClient/SplitOwner.h",
           "class SplitOwner { public: void reset(); };\n")
    _write(root, f"{zh_root}/GameEngine/Source/GameClient/keep-directory.txt")

    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for index, (name, source) in enumerate(sources):
        rows.append(f"{name},,0x{0x100000 + index * 0x10:08X},10,{source},matched,\n")
    _write(root, "reverse/functions.csv", "".join(rows))
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


def test_a_coarse_header_refines_to_one_established_descendant(tmp_path):
    root = _command_set_world(tmp_path)
    single, homes = queue.survey(root)
    zh = queue.zh_directories(root)
    zh_hdr = queue.zh_header_directories(root)

    assert single[COMMAND_SET] == "CommandSet"
    assert homes["CommandSet"][CONTROL_BAR] == 2
    assert zh_hdr["CommandSet"].replace(queue.ZH, "Code", 1) == CLIENT
    assert queue.destination(root, COMMAND_SET, "CommandSet", homes, zh, zh_hdr) == CONTROL_BAR

    queued, _skipped = queue.build(root)
    assert (COMMAND_SET, f"{CONTROL_BAR}/BfmeConv1641.cpp", "CommandSet") in queued


def test_a_coarse_header_does_not_rank_multiple_descendant_homes(tmp_path):
    root = _split_home_world(tmp_path)
    single, homes = queue.survey(root)
    zh = queue.zh_directories(root)
    zh_hdr = queue.zh_header_directories(root)

    assert single[SPLIT] == "SplitOwner"
    assert sorted(homes["SplitOwner"].values(), reverse=True)[:2] == [3, 2]
    assert queue.destination(root, SPLIT, "SplitOwner", homes, zh, zh_hdr) is None

    queued, _skipped = queue.build(root)
    assert all(source != SPLIT for source, _target, _cls in queued)
