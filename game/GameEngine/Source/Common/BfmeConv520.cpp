class BfmeThingBRF
{
public:
	void bfmeGoBRF();
	bool m_bfmeFlag;
	unsigned char m_bfmePad[3];
	void *m_bfmeWhat;
};

// The matching implementation is BfmeThingCDA::bfmeStepCDA in BfmeConv578.cpp.
class BfmeThingCDA
{
public:
	void bfmeStepCDA();
};

void BfmeThingBRF::bfmeGoBRF()
{
	void *saved = m_bfmeWhat;
	m_bfmeWhat = 0;
	m_bfmeFlag = false;
	reinterpret_cast<BfmeThingCDA *>( this )->bfmeStepCDA();
	m_bfmeWhat = saved;
	m_bfmeFlag = true;
}
