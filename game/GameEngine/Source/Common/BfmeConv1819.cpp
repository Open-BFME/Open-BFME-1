// Retail 0x00662C80: the held thing is torn down through the ILT thunk at
// 0x0003A48B, which lands on Transport::reset (0x00683450, the ledger's owner
// of that address) and then on the global operator delete. The receiver is
// therefore a Transport view, not a class of its own destructor.
class Transport
{
public:
	void reset();
};

class BfmeThingHT;

class BfmeOwnerHT
{
public:
	void bfmeSetHT(BfmeThingHT *value);

	unsigned char m_bfmeHeadHT[0x12024];
	BfmeThingHT *m_bfmeThingHT;
};

void BfmeOwnerHT::bfmeSetHT(BfmeThingHT *value)
{
	if (m_bfmeThingHT != 0)
	{
		BfmeThingHT *thing = m_bfmeThingHT;

		((Transport *)thing)->reset();
		::operator delete(thing);
		m_bfmeThingHT = 0;
	}

	m_bfmeThingHT = value;
}