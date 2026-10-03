// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen00024B7C
{
public:
	unsigned char handle(int a);
};

class LANAPI;
extern LANAPI *TheLAN;
extern void j_00024b7c();

class Rva005169E0
{
public:
	unsigned char wrap(int a);
};

unsigned char Rva005169E0::wrap(int a)
{
	if (TheLAN)
	{
		typedef unsigned char (Gen00024B7C::*HandleCall)(int);
		union { void (*function)(); HandleCall member; } handleCall;
		handleCall.function = j_00024b7c;
		return (reinterpret_cast<Gen00024B7C *>(TheLAN)->*handleCall.member)(a);
	}
	return 0;
}
