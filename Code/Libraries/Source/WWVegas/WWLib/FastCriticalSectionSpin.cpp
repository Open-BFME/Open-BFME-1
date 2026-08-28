// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class FastCriticalSectionClass
{
public:
	class LockClass
	{
		static void __fastcall spin(unsigned int *lock);
	};
};

__declspec(naked) void __fastcall FastCriticalSectionClass::LockClass::spin(unsigned int *)
{
	__asm {
		_emit 055h
		_emit 08Bh
		_emit 0ECh
		_emit 083h
		_emit 0ECh
		_emit 008h
		_emit 053h
		_emit 089h
		_emit 04Dh
		_emit 0F8h
		_emit 08Bh
		_emit 045h
		_emit 0F8h
		_emit 089h
		_emit 045h
		_emit 0FCh
		_emit 08Bh
		_emit 05Dh
		_emit 0FCh
		_emit 0F0h
		_emit 00Fh
		_emit 0BAh
		_emit 02Bh
		_emit 000h
		_emit 072h
		_emit 002h
		_emit 0EBh
		_emit 00Fh
		_emit 0E8h
		_emit 06Fh
		_emit 0A4h
		_emit 030h
		_emit 000h
		_emit 08Bh
		_emit 05Dh
		_emit 0FCh
		_emit 0F0h
		_emit 00Fh
		_emit 0BAh
		_emit 02Bh
		_emit 000h
		_emit 072h
		_emit 0F1h
		_emit 05Bh
		_emit 08Bh
		_emit 0E5h
		_emit 05Dh
		_emit 0C3h
	}
}
