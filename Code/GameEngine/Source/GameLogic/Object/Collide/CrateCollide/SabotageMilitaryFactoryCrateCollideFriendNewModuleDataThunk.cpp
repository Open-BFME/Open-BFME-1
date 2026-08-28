// cl: /DNDEBUG /MD /GX-
// Open-BFME-DS06: SabotageMilitaryFactoryCrateCollide::friend_newModuleData factory
// Retail inlines the ModuleData ctor (base construct at +8, vptr at +0, two
// 12-byte zero groups at +0x70 and +0x7c) with a lea-based store shape MSVC
// 7.1 will not emit from C++ (it folds to [esi+disp] and allocates a
// callee-saved zero register), so the body is a naked dump like the other
// base-at-+8 module-data ctors in this family.

class INI;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SabotageMilitaryFactoryCrateCollide.h
class SabotageMilitaryFactoryCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SabotageMilitaryFactoryCrateCollide@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *SabotageMilitaryFactoryCrateCollide::friend_newModuleData(INI *ini)
{
	__asm {
		__emit 0x56;
		__emit 0x68;
		__emit 0x88;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xE8;
		__emit 0xD5;
		__emit 0x68;
		__emit 0x75;
		__emit 0x00;
		__emit 0x8B;
		__emit 0xF0;
		__emit 0x83;
		__emit 0xC4;
		__emit 0x04;
		__emit 0x85;
		__emit 0xF6;
		__emit 0x74;
		__emit 0x2A;
		__emit 0x8D;
		__emit 0x4E;
		__emit 0x08;
		__emit 0xE8;
		__emit 0x3A;
		__emit 0x3A;
		__emit 0xEE;
		__emit 0xFF;
		__emit 0x33;
		__emit 0xC0;
		__emit 0xC7;
		__emit 0x06;
		__emit 0xF0;
		__emit 0xF4;
		__emit 0x08;
		__emit 0x01;
		__emit 0x8D;
		__emit 0x4E;
		__emit 0x70;
		__emit 0x89;
		__emit 0x01;
		__emit 0x89;
		__emit 0x41;
		__emit 0x04;
		__emit 0x89;
		__emit 0x41;
		__emit 0x08;
		__emit 0x33;
		__emit 0xD2;
		__emit 0x8D;
		__emit 0x46;
		__emit 0x7C;
		__emit 0x89;
		__emit 0x10;
		__emit 0x89;
		__emit 0x50;
		__emit 0x04;
		__emit 0x89;
		__emit 0x50;
		__emit 0x08;
		__emit 0xEB;
		__emit 0x02;
		__emit 0x33;
		__emit 0xF6;
		__emit 0x8B;
		__emit 0x4C;
		__emit 0x24;
		__emit 0x08;
		__emit 0x85;
		__emit 0xC9;
		__emit 0x74;
		__emit 0x0B;
		__emit 0x68;
		__emit 0xC6;
		__emit 0x02;
		__emit 0x41;
		__emit 0x00;
		__emit 0x56;
		__emit 0xE8;
		__emit 0x8D;
		__emit 0x6A;
		__emit 0x72;
		__emit 0x00;
		__emit 0x8B;
		__emit 0xC6;
		__emit 0x5E;
		__emit 0xC3;
	}
}
