// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

class Thing {};
class ModuleData {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h
class AutoDepositUpdate
{
public:
	AutoDepositUpdate( Thing *thing, const ModuleData *data );
};

__declspec(naked) AutoDepositUpdate::AutoDepositUpdate( Thing *, const ModuleData * )
{
	__asm {
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 008h
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 008h
		_emit 050h
		_emit 051h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 040h
		_emit 063h
		_emit 0D9h
		_emit 0FFh
		_emit 0C7h
		_emit 046h
		_emit 00Ch
		_emit 0D0h
		_emit 0C9h
		_emit 009h
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 010h
		_emit 0A0h
		_emit 0CBh
		_emit 009h
		_emit 001h
		_emit 08Bh
		_emit 056h
		_emit 004h
		_emit 033h
		_emit 0C0h
		_emit 089h
		_emit 046h
		_emit 014h
		_emit 088h
		_emit 046h
		_emit 024h
		_emit 088h
		_emit 046h
		_emit 025h
		_emit 083h
		_emit 0C9h
		_emit 0FFh
		_emit 089h
		_emit 04Eh
		_emit 018h
		_emit 089h
		_emit 04Eh
		_emit 01Ch
		_emit 0C7h
		_emit 006h
		_emit 0D4h
		_emit 0B1h
		_emit 00Bh
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 00Ch
		_emit 010h
		_emit 0B1h
		_emit 00Bh
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 010h
		_emit 000h
		_emit 0B1h
		_emit 00Bh
		_emit 001h
		_emit 08Bh
		_emit 042h
		_emit 008h
		_emit 08Bh
		_emit 00Dh
		_emit 098h
		_emit 008h
		_emit 02Fh
		_emit 001h
		_emit 003h
		_emit 041h
		_emit 03Ch
		_emit 089h
		_emit 046h
		_emit 020h
		_emit 08Bh
		_emit 0C6h
		_emit 05Eh
		_emit 0C2h
		_emit 008h
		_emit 000h
	}
}
