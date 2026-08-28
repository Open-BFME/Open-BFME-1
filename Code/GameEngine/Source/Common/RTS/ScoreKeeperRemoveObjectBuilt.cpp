// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ScoreKeeper.h
class ScoreKeeper
{
public:
	void removeObjectBuilt( const Object * );
};

__declspec(naked) void ScoreKeeper::removeObjectBuilt( const Object * )
{
	__asm {
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 0E8h
		_emit 023h
		_emit 0A5h
		_emit 0ACh
		_emit 0FFh
		_emit 08Bh
		_emit 036h
		_emit 085h
		_emit 0F6h
		_emit 074h
		_emit 00Bh
		_emit 06Ah
		_emit 044h
		_emit 056h
		_emit 0E8h
		_emit 07Ah
		_emit 004h
		_emit 02Ch
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 008h
		_emit 05Eh
		_emit 0C3h
	}
}

