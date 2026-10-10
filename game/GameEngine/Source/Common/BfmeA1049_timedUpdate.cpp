// Retail ILTs14182/4156 reach zero-argument thiscall bodies5337E0/534380;
// ILT12E90 reaches the one-argument cdecl body533EA0. These existing literal
// identities preserve the independently measured receiver/stack contracts.
extern "C" void __cdecl __identifier("?d_005337e0@@YAXXZ")();
extern "C" void __cdecl __identifier("?d_00534380@@YAXXZ")();
extern "C" void __cdecl __identifier("?d_00533ea0@@YAXXZ")(void *);

// Open-BFME5 conversion of the BFME timed update at retail 0x00535150.

typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

// Retail VA 0x01359544 is WINMM.dll!timeGetTime's import slot.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();


class BfmeA1049
{
public:
	void bfmeGo1049B(Bool force);

	char m_bfmePad[0x44];
	void *m_bfmeP;
	char m_bfmePad2[0x54];
	UnsignedInt m_bfmeTime;
};

void BfmeA1049::bfmeGo1049B(Bool force)
{
	unsigned long (__stdcall *nowFunction)() = timeGetTime;

	if (!force) {
		if (m_bfmeTime != 0) {
			UnsignedInt now = nowFunction();
			if (m_bfmeTime + 5000 > now)
				return;
		}
	}

	union
	{
		void (__cdecl *symbol)();
		void (BfmeA1049::*member)();
	} firstStep;
	firstStep.symbol = &__identifier("?d_005337e0@@YAXXZ");
	(this->*firstStep.member)();
	__identifier("?d_00533ea0@@YAXXZ")(m_bfmeP);
	union
	{
		void (__cdecl *symbol)();
		void (BfmeA1049::*member)();
	} secondStep;
	secondStep.symbol = &__identifier("?d_00534380@@YAXXZ");
	(this->*secondStep.member)();
	m_bfmeTime = nowFunction();
}
