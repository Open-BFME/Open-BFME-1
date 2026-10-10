// ILT00020B80 reaches the separate thunk function002D9B70, which jumps
// through ILT0004049E to the one-byte RET body001EF410. Keep the thunk's
// ledger identity and the caller's ECX/no-argument contract. The conditional
// tail jump reaches001F96E0, independently measured thiscall/RET0.
extern "C" void __cdecl __identifier("?j_002d9b70@@YAXXZ")();
extern "C" void __cdecl __identifier("?d_001f96e0@@YAXXZ")();

struct BfmeOwnerRK
{
	unsigned char m_bfmeHead[0xc4];
	bool m_bfmeForce;
};

class BfmeThingRK
{
public:
	void bfmeGoRK();
	unsigned char m_bfmeHead[4];
	BfmeOwnerRK *m_bfmeOwner;
	unsigned char m_bfmeGap[0x34];
	bool m_bfmeWant;
	bool m_bfmeDone;
};

void BfmeThingRK::bfmeGoRK()
{
	union
	{
		void (__cdecl *symbol)();
		void (BfmeThingRK::*member)();
	} first;
	first.symbol = &__identifier("?j_002d9b70@@YAXXZ");
	(this->*first.member)();
	if (m_bfmeDone)
		return;
	if (m_bfmeOwner->m_bfmeForce || m_bfmeWant)
	{
		union
		{
			void (__cdecl *symbol)();
			void (BfmeThingRK::*member)();
		} second;
		second.symbol = &__identifier("?d_001f96e0@@YAXXZ");
		(this->*second.member)();
	}
}
