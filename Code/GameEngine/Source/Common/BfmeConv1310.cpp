// Open-BFME5 conversions.

class BfmeThingTED
{
public:
	void bfmeGoTED();
	void bfmeOneTED(int a);
	void bfmeTwoTED();
	void bfmeThreeTED();
	char m_bfmePad[0x618];
	int m_bfmeState;
};

void BfmeThingTED::bfmeGoTED()
{
	bfmeOneTED(7);
	bfmeTwoTED();
	bfmeThreeTED();
	m_bfmeState = 0;
}
