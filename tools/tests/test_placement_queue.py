"""Placement requires stronger evidence than a method emitted from a header."""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import placement_queue as queue  # noqa: E402


POPUP = "game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGame.cpp"
MISPLACED = "game/GameEngine/Source/Common/GameInfoReset.cpp"
NETWORK = "game/GameEngine/Source/GameNetwork"
COMMAND_SET = "game/GameEngine/Source/Common/BfmeConv1641.cpp"
CLIENT = "game/GameEngine/Source/GameClient"
CONTROL_BAR = f"{CLIENT}/GUI/ControlBar"
SPLIT = "game/GameEngine/Source/Common/SplitOwner.cpp"
DOMINATE = ("game/GameEngine/Source/GameLogic/Object/SpecialPower/"
            "DominateEnemySpecialPower_slot15.cpp")
SPECIAL_POWER = "game/GameEngine/Source/GameLogic/Object/SpecialPower"
THING = "game/GameEngine/Source/Common/Thing"
REGION_DTOR = "game/GameEngine/Source/GameLogic/AI/RegionOwnerDestructor.cpp"
REGION_DELETING = (
    "game/GameEngine/Source/GameLogic/LivingWorld/RegionOwnerDeleting.cpp"
)
REGION_BEHAVIOR = "game/GameEngine/Source/GameLogic/Object/Behavior"


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
    _write(root, f"{zh_root}/GameEngine/Source/GameNetwork/GameInfo.cpp",
           "void GameInfo::reset() {}\n")
    _write(root, f"{zh_root}/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGame.cpp")

    ledger = (
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        f"?setUseStats@GameInfo@@QAEXH@Z,,0x00100000,10,{POPUP},matched,\n"
        f"?reset@GameInfo@@QAEXXZ,,0x00100010,10,{MISPLACED},matched,\n"
    )
    _write(root, "targets/game/reverse/functions.csv", ledger)
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
    _write(root, "targets/game/reverse/functions.csv", ledger)
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
    _write(root, "targets/game/reverse/functions.csv", "".join(rows))
    return root


def _module_family_world(tmp_path):
    root = tmp_path / "repo"
    sources = [
        ("?action@DominateEnemySpecialPower@@UAEXXZ", DOMINATE),
        ("??0DominateEnemySpecialPowerModuleData@@QAE@XZ",
         f"{SPECIAL_POWER}/DominateEnemySpecialPowerModuleDataConstructor.cpp"),
        ("??0DominateEnemySpecialPower@@QAE@XZ",
         f"{THING}/DominateEnemySpecialPowerConstructor.cpp"),
        ("?factory@DominateEnemySpecialPower@@SAXXZ",
         f"{THING}/DominateEnemySpecialPowerFactory.cpp"),
    ]
    for _name, source in sources:
        _write(root, source)

    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for index, (name, source) in enumerate(sources):
        rows.append(f"{name},,0x{0x100000 + index * 0x10:08X},10,{source},matched,\n")
    _write(root, "targets/game/reverse/functions.csv", "".join(rows))
    return root


def _split_destructor_world(tmp_path):
    root = tmp_path / "repo"
    sources = [
        ("??1RegionOwner@@UAE@XZ", REGION_DTOR),
        ("??_GRegionOwner@@UAEPAXI@Z", REGION_DELETING),
        ("?first@RegionOwner@@QAEXXZ", f"{REGION_BEHAVIOR}/First.cpp"),
        ("?second@RegionOwner@@QAEXXZ", f"{REGION_BEHAVIOR}/Second.cpp"),
        ("?third@RegionOwner@@QAEXXZ", f"{REGION_BEHAVIOR}/Third.cpp"),
    ]
    for _name, source in sources:
        _write(root, source)

    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for index, (name, source) in enumerate(sources):
        rows.append(f"{name},,0x{0x200000 + index * 0x10:08X},10,{source},matched,\n")
    _write(root, "targets/game/reverse/functions.csv", "".join(rows))
    return root


def _established_split_family_world(tmp_path, cls, current, alternate):
    root = tmp_path / "repo"
    sources = [
        (f"?currentA@{cls}@@QAEXXZ", f"{current}/CurrentA.cpp"),
        (f"??_G{cls}@@UAEPAXI@Z", f"{current}/CurrentDeleting.cpp"),
        (f"?alternateA@{cls}@@QAEXXZ", f"{alternate}/AlternateA.cpp"),
        (f"?alternateB@{cls}@@QAEXXZ", f"{alternate}/AlternateB.cpp"),
        (f"?alternateC@{cls}@@QAEXXZ", f"{alternate}/AlternateC.cpp"),
        (f"?candidate@{cls}@@QAEXXZ", f"{current}/Candidate.cpp"),
    ]
    for _name, source in sources:
        _write(root, source)

    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for index, (name, source) in enumerate(sources):
        rows.append(f"{name},,0x{0x300000 + index * 0x10:08X},10,{source},matched,\n")
    _write(root, "targets/game/reverse/functions.csv", "".join(rows))
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


def test_reference_filename_does_not_move_an_unrelated_class(tmp_path):
    root = tmp_path / "repo"
    source = "game/Libraries/Source/WWVegas/WWDebug/DebugAssert.cpp"
    _write(root, source, "void Debug::AssertBegin() {}\n")
    _write(root, "game/GameEngine/Source/Common/System/keep.txt")
    _write(root, f"{queue.ZH}/GameEngine/Source/Common/System/Debug.cpp",
           '// Debug::AssertBegin() {}\n'
           'const char *message = "Debug::AssertBegin() {}";\n'
           'void DebugLog() { if (Debug::IsEnabled()) {} }\n')
    _write(root, "targets/game/reverse/functions.csv",
           "name,export_rva,target_rva,target_size,source,status,notes\n"
           f"?AssertBegin@Debug@@SAXXZ,,0x00100000,10,{source},matched,\n")

    assert "debug" not in queue.zh_directories(root)
    queued, _skipped = queue.build(root)
    assert queued == []


@pytest.mark.parametrize("body", [
    "Debug::Debug() : m_enabled(true) {}",
    "Debug::~Debug() {}",
    "bool Debug::IsEnabled() const { return true; }",
    "class Debug { public: void run() {} };",
])
def test_reference_class_implementation_is_positive_evidence(body):
    assert queue.implements_class(body, "Debug")


def test_exact_multiclass_zh_source_prevents_a_weak_sibling_reversal(tmp_path):
    root = tmp_path / "repo"
    official = (f"{queue.ZH}/GameEngineDevice/Source/W3DDevice/GameClient/"
                "WorldHeightMap.cpp")
    canonical = "game/GameEngineDevice/Source/W3DDevice/GameClient"
    alternate = "game/GameEngine/Source/GameLogic/Map"
    candidate = f"{canonical}/MapObjectVerify.cpp"
    sources = [
        ("?verify@MapObject@@QAEXXZ", candidate),
        ("?alternateA@MapObject@@QAEXXZ", f"{alternate}/AlternateA.cpp"),
        ("?alternateB@MapObject@@QAEXXZ", f"{alternate}/AlternateB.cpp"),
    ]
    for _name, source in sources:
        _write(root, source)
    _write(
        root,
        official,
        "void WorldHeightMap::reset() {}\n"
        "// void MentionOnly::fromComment() {}\n"
        'const char *text = "void MentionOnly::fromString() {}";\n'
        "void helper() { MentionOnly::fromCall(); }\n"
        "void MapObject::verifyValidTeam() {}\n",
    )
    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for index, (name, source) in enumerate(sources):
        rows.append(f"{name},,0x{0x500000 + index * 0x10:08X},10,{source},matched,\n")
    _write(root, "targets/game/reverse/functions.csv", "".join(rows))

    single, homes = queue.survey(root)
    assert queue.destination(
        root, candidate, single[candidate], homes, {}, {}
    ) == alternate

    zh = queue.zh_directories(root)
    assert zh["mapobject"].replace(queue.ZH, "game", 1) == canonical
    assert "mentiononly" not in zh

    queued, _skipped = queue.build(root)
    assert all(source != candidate for source, _target, _cls in queued)


def test_a_source_rejected_by_the_placement_gate_is_not_requeued(tmp_path):
    root = _world(tmp_path)
    _write(root, queue.BLOCKED,
           f"{MISPLACED}\tdefines a function no ledger row declares\n")

    queued, skipped = queue.build(root)

    assert all(source != MISPLACED for source, _target, _cls in queued)
    assert skipped["a previous placement gate rejected the source"] == 1


def test_a_malformed_placement_blocker_fails_explicitly(tmp_path):
    root = _world(tmp_path)
    _write(root, queue.BLOCKED, f"{MISPLACED}\n")

    with pytest.raises(ValueError, match="expected source<TAB>reason"):
        queue.build(root)


def test_a_sibling_include_prevents_moving_its_source_on_every_host(tmp_path):
    root = _world(tmp_path)
    _write(root, "game/GameEngine/Source/Common/GameInfoWrapper.cpp",
           '#include "GameInfoReset.cpp"\n')

    assert MISPLACED in queue.included_by_siblings(root)
    queued, skipped = queue.build(root)
    assert all(source != MISPLACED for source, _target, _cls in queued)
    assert skipped["a sibling includes it by bare name"] == 1


def test_a_coarse_header_refines_to_one_established_descendant(tmp_path):
    root = _command_set_world(tmp_path)
    single, homes = queue.survey(root)
    zh = queue.zh_directories(root)
    zh_hdr = queue.zh_header_directories(root)

    assert single[COMMAND_SET] == "CommandSet"
    assert homes["CommandSet"][CONTROL_BAR] == 2
    assert zh_hdr["CommandSet"].replace(queue.ZH, "game", 1) == CLIENT
    assert queue.destination(root, COMMAND_SET, "CommandSet", homes, zh, zh_hdr) == CONTROL_BAR

    queued, _skipped = queue.build(root)
    assert (COMMAND_SET, f"{CONTROL_BAR}/BfmeConv1641.cpp", "CommandSet") in queued


def test_a_coarse_header_keeps_a_source_in_its_descendant_family(tmp_path):
    root = tmp_path / "repo"
    current = "game/GameEngine/Source/GameNetwork/GameSpy/Thread"
    alternate = "game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus"
    candidate = f"{current}/PeerResponseCopies.cpp"
    sources = [
        ("??0PeerResponse@@QAE@ABV0@@Z", candidate),
        ("??0PeerResponse@@QAE@XZ", f"{alternate}/PeerResponseConstructor.cpp"),
        ("??1PeerResponse@@QAE@XZ", f"{alternate}/PeerResponseDestructor.cpp"),
    ]
    for _name, source in sources:
        _write(root, source)

    zh_root = queue.ZH
    _write(root, f"{zh_root}/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h",
           "class PeerResponse { public: PeerResponse(); };\n")
    _write(root, f"{zh_root}/GameEngine/Source/GameNetwork/GameSpy/keep-directory.txt")

    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for index, (name, source) in enumerate(sources):
        rows.append(f"{name},,0x{0x180000 + index * 0x10:08X},10,{source},matched,\n")
    _write(root, "targets/game/reverse/functions.csv", "".join(rows))

    single, homes = queue.survey(root)
    zh_hdr = queue.zh_header_directories(root)
    assert zh_hdr["PeerResponse"].replace(queue.ZH, "game", 1) == current.rsplit("/", 1)[0]
    assert queue.destination(
        root, candidate, single[candidate], homes, {}, zh_hdr
    ) is None

    queued, _skipped = queue.build(root)
    assert all(source != candidate for source, _target, _cls in queued)


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


def test_sibling_counts_do_not_split_a_module_from_its_module_data(tmp_path):
    root = _module_family_world(tmp_path)
    single, homes = queue.survey(root)

    assert single[DOMINATE] == "DominateEnemySpecialPower"
    assert homes["DominateEnemySpecialPower"][THING] == 2
    assert homes["DominateEnemySpecialPowerModuleData"][SPECIAL_POWER] == 1
    assert queue.destination(
        root, DOMINATE, "DominateEnemySpecialPower", homes, {}, {}) is None

    queued, _skipped = queue.build(root)
    assert all(source != DOMINATE for source, _target, _cls in queued)

    homes["DominateEnemySpecialPowerModuleData"].clear()
    assert queue.destination(
        root, DOMINATE, "DominateEnemySpecialPower", homes, {}, {}) is None


def test_weak_sibling_inference_never_moves_back_into_legacy_common(tmp_path):
    root = tmp_path / "repo"
    current = "game/GameEngine/Source/GameClient/System"
    legacy = "game/GameEngine/Source/Common/System"
    candidate = f"{current}/RadarCandidate.cpp"
    sources = [
        ("?candidate@Radar@@QAEXXZ", candidate),
        ("?legacyA@Radar@@QAEXXZ", f"{legacy}/LegacyA.cpp"),
        ("?legacyB@Radar@@QAEXXZ", f"{legacy}/LegacyB.cpp"),
        ("?legacyC@Radar@@QAEXXZ", f"{legacy}/LegacyC.cpp"),
    ]
    for _name, source in sources:
        _write(root, source)
    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for index, (name, source) in enumerate(sources):
        rows.append(f"{name},,0x{0x400000 + index * 0x10:08X},10,{source},matched,\n")
    _write(root, "targets/game/reverse/functions.csv", "".join(rows))

    single, homes = queue.survey(root)
    assert single[candidate] == "Radar"
    assert queue.destination(root, candidate, "Radar", homes, {}, {}) is None
    queued, _skipped = queue.build(root)
    assert all(source != candidate for source, _target, _cls in queued)


def test_weak_sibling_inference_does_not_rank_split_class_homes(tmp_path):
    root = _split_destructor_world(tmp_path)
    single, homes = queue.survey(root)
    deleting_homes = queue.deleting_destructor_homes(root)

    assert REGION_DELETING not in single
    assert homes["RegionOwner"][REGION_BEHAVIOR] == 3
    assert deleting_homes["RegionOwner"] == {
        Path(REGION_DELETING).parent.as_posix()
    }
    assert queue.destination(
        root, REGION_DTOR, "RegionOwner", homes, {}, {}, deleting_homes
    ) is None

    queued, _skipped = queue.build(root)
    assert all(source != REGION_DTOR for source, _target, _cls in queued)


@pytest.mark.parametrize("cls,current,alternate", [
    (
        "LivingWorldRegion",
        "game/GameEngine/Source/GameLogic/LivingWorld",
        "game/GameEngine/Source/GameLogic/Object/Behavior",
    ),
    (
        "BoneFXUpdateModuleData",
        "game/GameEngine/Source/GameLogic/Object/Update",
        "game/GameEngine/Source/Common/RTS",
    ),
])
def test_sibling_counts_do_not_move_an_established_split_family(
        tmp_path, cls, current, alternate):
    root = _established_split_family_world(tmp_path, cls, current, alternate)
    single, homes = queue.survey(root)
    candidate = f"{current}/Candidate.cpp"
    deleting_homes = queue.deleting_destructor_homes(root)

    assert homes[cls][current] == 2
    assert homes[cls][alternate] == 3
    assert deleting_homes[cls] == {current}
    assert queue.destination(
        root, candidate, cls, homes, {}, {}, deleting_homes
    ) is None

    queued, _skipped = queue.build(root)
    assert all(source != candidate for source, _target, _cls in queued)
