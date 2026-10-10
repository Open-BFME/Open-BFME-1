// Retail vftable at 0x01145744, recorded as ??_7ShdDefFactoryClass@@6B@; the extern binds
// the compiler-emitted symbol by its defining mangle so the DIR32 resolves (same spelling as
// game/GameEngine/Source/Common/BfmeConv1188.cpp).
extern "C" unsigned char __identifier("??_7ShdDefFactoryClass@@6B@")[];

// Retail tail-calls operator delete[] at 0x00881EF0.
void operator delete[](void *what);

class BfmeThingUB
{
public:
	void bfmeResetUB();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeWhat;
};

void BfmeThingUB::bfmeResetUB()
{
	m_bfmeVft = __identifier("??_7ShdDefFactoryClass@@6B@");
	operator delete[](m_bfmeWhat);
}
