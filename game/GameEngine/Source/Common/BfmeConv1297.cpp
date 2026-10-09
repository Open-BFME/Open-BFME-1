// Open-BFME5 conversions.

class BfmeSlotSQA
{
public:
	void bfmeOneSQA(int v);
	void bfmeTwoSQA(int v);
};

class BfmeThingSQA
{
public:
	void bfmeGoSQA(int a, int b);
	char m_bfmePad[0x178];
	BfmeSlotSQA m_bfmeSlot;
};

struct Coord3D;

class RadiusDecal
{
public:
	void setPosition( const Coord3D &position );
};

class BfmeTripleCV;

class Gen_004583D0
{
public:
	void bfmeSetTriple( const BfmeTripleCV *value );
};

void BfmeThingSQA::bfmeGoSQA(int a, int b)
{
	((RadiusDecal *)&m_bfmeSlot)->setPosition( *(const Coord3D *)a );
	((Gen_004583D0 *)&m_bfmeSlot)->bfmeSetTriple( (const BfmeTripleCV *)b );
}
