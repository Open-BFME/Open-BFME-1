// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
#include "Common/INI/INI.h"

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int offset = 0);
};

extern const FieldParse g_voiceFieldParse[];

__declspec(noinline) const FieldParse *getVoiceFieldParse()
{
	return g_voiceFieldParse;
}

// Registration and field keys establish the RandomSoundSelectorClientBehavior role; the original class spelling is unknown.
class Rva00607A00ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

extern const FieldParse g_randomSoundSelectorFieldParse[];

void Rva00607A00ModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_randomSoundSelectorFieldParse);
	parse.add(getVoiceFieldParse(), 8);
}

// All entries and the ILT route are verified in identity_evidence/01093870-VoiceFieldParse.md.
extern "C" void __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z")(INI *, void *, void *, const void *);

extern const FieldParse g_voiceFieldParse[] =
{
	{ "VoiceSelect", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "VoiceSelectUnderConstruction", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x4 },
	{ "VoiceSelectGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
	{ "VoiceSelectBattle", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC },
	{ "VoiceSelectBattleGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x10 },
	{ "VoiceMove", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x14 },
	{ "VoiceMoveGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x18 },
	{ "VoiceAttack", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1C },
	{ "VoiceAttackGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x20 },
	{ "VoiceAttackCharge", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x24 },
	{ "VoiceAttackChargeGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x28 },
	{ "VoiceFear", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2C },
	{ "VoiceCreated", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x30 },
	{ "VoiceTaskComplete", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x34 },
	{ "VoiceDefect", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x38 },
	{ "VoiceAttackAir", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x3C },
	{ "VoiceAttackAirGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x40 },
	{ "VoiceGuard", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x44 },
	{ "VoiceGuardGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x48 },
	{ "VoiceAlert", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x4C },
	{ "VoiceFullyCreated", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x50 },
	{ "VoiceRetreatToCastle", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x54 },
	{ "VoiceRetreatToCastleGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x58 },
	{ "VoiceMoveToCamp", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x5C },
	{ "VoiceMoveToCampGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x60 },
	{ "VoiceAttackStructure", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x64 },
	{ "VoiceAttackStructureGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x68 },
	{ "VoiceAttackMachine", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x6C },
	{ "VoiceAttackMachineGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x70 },
	{ "VoiceMoveWhileAttacking", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x74 },
	{ "VoiceMoveWhileAttackingGroup", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x78 },
	{ "VoiceAmbushed", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x7C },
	{ "VoiceCombineWithHorde", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x80 },
	{ "VoiceEnterStateAttack", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x84 },
	{ "VoiceEnterStateAttackCharge", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x88 },
	{ "VoiceEnterStateAttackAir", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x8C },
	{ "VoiceEnterStateAttackStructure", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x90 },
	{ "VoiceEnterStateAttackMachine", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x94 },
	{ "VoiceEnterStateMove", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x98 },
	{ "VoiceEnterStateRetreatToCastle", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x9C },
	{ "VoiceEnterStateMoveToCamp", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA0 },
	{ "VoiceEnterStateMoveWhileAttacking", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA4 },
	{ "VoiceSelect2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA8 },
	{ "VoiceSelectGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xAC },
	{ "VoiceSelectBattle2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB0 },
	{ "VoiceSelectBattleGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB4 },
	{ "VoiceMove2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xB8 },
	{ "VoiceMoveGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xBC },
	{ "VoiceAttack2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC0 },
	{ "VoiceAttackGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC4 },
	{ "VoiceAttackCharge2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC8 },
	{ "VoiceAttackChargeGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xCC },
	{ "VoiceFear2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xD0 },
	{ "VoiceCreated2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xD4 },
	{ "VoiceTaskComplete2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xD8 },
	{ "VoiceDefect2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xDC },
	{ "VoiceAttackAir2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xE0 },
	{ "VoiceAttackAirGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xE4 },
	{ "VoiceGuard2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xE8 },
	{ "VoiceGuardGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xEC },
	{ "VoiceAlert2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xF0 },
	{ "VoiceFullyCreated2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xF4 },
	{ "VoiceRetreatToCastle2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xF8 },
	{ "VoiceRetreatToCastleGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xFC },
	{ "VoiceMoveToCamp2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x100 },
	{ "VoiceMoveToCampGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x104 },
	{ "VoiceAttackStructure2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x108 },
	{ "VoiceAttackStructureGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x10C },
	{ "VoiceAttackMachine2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x110 },
	{ "VoiceAttackMachineGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x114 },
	{ "VoiceMoveWhileAttacking2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x118 },
	{ "VoiceMoveWhileAttackingGroup2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x11C },
	{ "VoiceAmbushed2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x120 },
	{ "VoiceCombineWithHorde2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x124 },
	{ "VoiceEnterStateAttack2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x128 },
	{ "VoiceEnterStateAttackCharge2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x12C },
	{ "VoiceEnterStateAttackAir2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x130 },
	{ "VoiceEnterStateAttackStructure2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x134 },
	{ "VoiceEnterStateAttackMachine2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x138 },
	{ "VoiceEnterStateMove2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x13C },
	{ "VoiceEnterStateRetreatToCastle2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x140 },
	{ "VoiceEnterStateMoveToCamp2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x144 },
	{ "VoiceEnterStateMoveWhileAttacking2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x148 },
	{ "SoundMoveStart", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x14C },
	{ "SoundMoveStartDamaged", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x150 },
	{ "SoundMoveLoop", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x154 },
	{ "SoundMoveLoopDamaged", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x158 },
	{ "SoundAmbient", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x15C },
	{ "SoundAmbientDamaged", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x160 },
	{ "SoundAmbientReallyDamaged", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x164 },
	{ "SoundAmbientRubble", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x168 },
	{ "SoundAmbient2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x16C },
	{ "SoundAmbientDamaged2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x170 },
	{ "SoundAmbientReallyDamaged2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x174 },
	{ "SoundAmbientRubble2", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x178 },
	{ "SoundAmbientBattle", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x17C },
	{ "SoundStealthOn", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x180 },
	{ "SoundStealthOff", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x184 },
	{ "SoundCreated", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x188 },
	{ "SoundOnDamaged", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x18C },
	{ "SoundOnReallyDamaged", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x190 },
	{ "SoundEnter", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x194 },
	{ "SoundExit", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x198 },
	{ "SoundPromotedVeteran", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x19C },
	{ "SoundPromotedElite", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1A0 },
	{ "SoundPromotedHero", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1A4 },
	{ "SoundFallingFromPlane", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1A8 },
	{ "SoundImpact", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1AC },
	{ "SoundCrushing", __identifier("?parse@INIParseDynamicAudioEventRTSShim@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1B0 },
	{ 0, 0, 0, 0 }
};
