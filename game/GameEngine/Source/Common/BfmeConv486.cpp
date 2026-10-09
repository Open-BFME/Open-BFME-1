// Callees (tools/callees.py 0x610050 25): ILT 0x105F5 -> 0x0060FFF0
// Rva0060FFF0Owner::updateElements, tail jump -> 0x0060C2A0 Rva0060C2A0::reset.
class Rva0060C2A0
{
public:
	void reset();
};

class Rva0060FFF0Owner
{
public:
	void updateElements();
};

class BfmeThingBLE
{
public:
	void bfmeGoBLE();
	unsigned char m_bfmeHead[0x28c];
	Rva0060C2A0 *m_bfmeSub;
};

void BfmeThingBLE::bfmeGoBLE()
{
	reinterpret_cast<Rva0060FFF0Owner *>(this)->updateElements();
	Rva0060C2A0 *sub = m_bfmeSub;
	if (sub != 0)
		sub->reset();
}
