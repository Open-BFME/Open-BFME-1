// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
};

class ModelConditionSoundSelectorClientBehavior
{
public:
	ModelConditionSoundSelectorClientBehavior(Thing *, const ModuleData *);
};

class UpgradeSoundSelectorClientBehavior
{
public:
	UpgradeSoundSelectorClientBehavior(Thing *, const ModuleData *);
};

__declspec(naked) ModelConditionSoundSelectorClientBehavior::ModelConditionSoundSelectorClientBehavior(Thing *, const ModuleData *)
{
	__asm {
		_emit 06Ah
		_emit 0FFh
		_emit 068h
		_emit 068h
		_emit 0E0h
		_emit 0FFh
		_emit 000h
		_emit 064h
		_emit 0A1h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 050h
		_emit 064h
		_emit 089h
		_emit 025h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 083h
		_emit 0ECh
		_emit 00Ch
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 020h
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 074h
		_emit 024h
		_emit 004h
		_emit 089h
		_emit 046h
		_emit 004h
		_emit 085h
		_emit 0C0h
		_emit 0C7h
		_emit 044h
		_emit 024h
		_emit 018h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C7h
		_emit 006h
		_emit 0B4h
		_emit 097h
		_emit 008h
		_emit 001h
		_emit 075h
		_emit 023h
		_emit 068h
		_emit 050h
		_emit 097h
		_emit 008h
		_emit 001h
		_emit 08Dh
		_emit 044h
		_emit 024h
		_emit 00Ch
		_emit 06Ah
		_emit 003h
		_emit 050h
		_emit 0E8h
		_emit 017h
		_emit 0C8h
		_emit 073h
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 00Ch
		_emit 068h
		_emit 030h
		_emit 0FCh
		_emit 01Dh
		_emit 001h
		_emit 08Dh
		_emit 04Ch
		_emit 024h
		_emit 00Ch
		_emit 051h
		_emit 0E8h
		_emit 005h
		_emit 02Fh
		_emit 08Eh
		_emit 000h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 020h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 007h
		_emit 08Bh
		_emit 011h
		_emit 0FFh
		_emit 052h
		_emit 010h
		_emit 0EBh
		_emit 002h
		_emit 033h
		_emit 0C0h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 010h
		_emit 089h
		_emit 046h
		_emit 008h
		_emit 08Bh
		_emit 0C6h
		_emit 05Eh
		_emit 064h
		_emit 089h
		_emit 00Dh
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 018h
		_emit 0C2h
		_emit 008h
		_emit 000h
	}
}

__declspec(naked) UpgradeSoundSelectorClientBehavior::UpgradeSoundSelectorClientBehavior(Thing *, const ModuleData *)
{
	__asm {
		_emit 06Ah
		_emit 0FFh
		_emit 068h
		_emit 068h
		_emit 0E0h
		_emit 0FFh
		_emit 000h
		_emit 064h
		_emit 0A1h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 050h
		_emit 064h
		_emit 089h
		_emit 025h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 083h
		_emit 0ECh
		_emit 00Ch
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 020h
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 074h
		_emit 024h
		_emit 004h
		_emit 089h
		_emit 046h
		_emit 004h
		_emit 085h
		_emit 0C0h
		_emit 0C7h
		_emit 044h
		_emit 024h
		_emit 018h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C7h
		_emit 006h
		_emit 0B4h
		_emit 097h
		_emit 008h
		_emit 001h
		_emit 075h
		_emit 023h
		_emit 068h
		_emit 050h
		_emit 097h
		_emit 008h
		_emit 001h
		_emit 08Dh
		_emit 044h
		_emit 024h
		_emit 00Ch
		_emit 06Ah
		_emit 003h
		_emit 050h
		_emit 0E8h
		_emit 017h
		_emit 0C8h
		_emit 073h
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 00Ch
		_emit 068h
		_emit 030h
		_emit 0FCh
		_emit 01Dh
		_emit 001h
		_emit 08Dh
		_emit 04Ch
		_emit 024h
		_emit 00Ch
		_emit 051h
		_emit 0E8h
		_emit 005h
		_emit 02Fh
		_emit 08Eh
		_emit 000h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 020h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 007h
		_emit 08Bh
		_emit 011h
		_emit 0FFh
		_emit 052h
		_emit 010h
		_emit 0EBh
		_emit 002h
		_emit 033h
		_emit 0C0h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 010h
		_emit 089h
		_emit 046h
		_emit 008h
		_emit 08Bh
		_emit 0C6h
		_emit 05Eh
		_emit 064h
		_emit 089h
		_emit 00Dh
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 018h
		_emit 0C2h
		_emit 008h
		_emit 000h
	}
}
