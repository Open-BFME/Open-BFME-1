// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class FastCriticalSectionClass
{
public:
	class LockClass
	{
		static void __fastcall spin(unsigned int *lock);
	};
};

void bfmeGoDWI();

void __fastcall FastCriticalSectionClass::LockClass::spin(unsigned int *lock)
{
	unsigned int &flag = *lock;
	__asm mov ebx, [flag]
	__asm lock bts dword ptr [ebx], 0
	__asm jc retry
	__asm jmp acquired

retry:
	bfmeGoDWI();
	__asm mov ebx, [flag]
	__asm lock bts dword ptr [ebx], 0
	__asm jc retry

acquired:
	;
}
