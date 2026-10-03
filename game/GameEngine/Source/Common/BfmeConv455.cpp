extern void j_000286a0();

class BfmeThingBFG
{
public:
	void bfmeGoBFG();
	unsigned char m_bfmeHead[0x18];
	int m_bfmeWidth;
	int m_bfmeHeight;
};

void BfmeThingBFG::bfmeGoBFG()
{
	m_bfmeWidth = 0x280;
	m_bfmeHeight = 0x1e0;
	((void (__fastcall *)(BfmeThingBFG *))j_000286a0)(this);
}
