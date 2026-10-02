// Retail's bytes prove this call targets the same factory body as the other
// TUs in this family: the defining name and return type live in
// game/GameEngine/Source/Common/Bfme5FactoryStubs.cpp.
struct Bfme5Obj18;

struct Bfme5Obj18 * __cdecl bfme5MakeObj18(void);

class BfmeThingBCE
{
public:
	void bfmeGoBCE();
	unsigned char m_bfmeHead[0x2a0];
	void *m_bfmeWhat;
};

void BfmeThingBCE::bfmeGoBCE()
{
	m_bfmeWhat = bfme5MakeObj18();
}
