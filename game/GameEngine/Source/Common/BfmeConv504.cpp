// Retail ILTs14182/4156 reach zero-argument thiscall bodies5337E0/534380;
// ILT12E90 reaches the one-argument cdecl body533EA0. These existing literal
// identities preserve the independently measured receiver/stack contracts.
extern "C" void __cdecl __identifier("?d_005337e0@@YAXXZ")();
extern "C" void __cdecl __identifier("?d_00534380@@YAXXZ")();
extern "C" void __cdecl __identifier("?d_00533ea0@@YAXXZ")(void *);



class BfmeThingBOF
{
public:
	void bfmeGoBOF();
	unsigned char m_bfmeHead[0x44];
	void *m_bfmeWhat;
};

void BfmeThingBOF::bfmeGoBOF()
{
	union
	{
		void (__cdecl *symbol)();
		void (BfmeThingBOF::*member)();
	} firstStep;
	firstStep.symbol = &__identifier("?d_005337e0@@YAXXZ");
	(this->*firstStep.member)();
	__identifier("?d_00533ea0@@YAXXZ")(m_bfmeWhat);
	union
	{
		void (__cdecl *symbol)();
		void (BfmeThingBOF::*member)();
	} secondStep;
	secondStep.symbol = &__identifier("?d_00534380@@YAXXZ");
	(this->*secondStep.member)();
}
