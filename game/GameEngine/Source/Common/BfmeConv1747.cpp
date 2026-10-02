class BfmeThingAW
{
public:
	unsigned char m_bfmeHeadAW[0x74];
	int m_bfmeIdAW;
};

class BfmeThingCDA
{
public:
	void bfmeStepCDA(void);
};

class BfmeOwnAW
{
public:
	void bfmeUpdateAW(BfmeThingAW *thing);

	char m_bfmeSetAW;
	unsigned char m_bfmePadAW[3];
	int m_bfmeIdAW;
};

void BfmeOwnAW::bfmeUpdateAW(BfmeThingAW *thing)
{
	int id = thing ? thing->m_bfmeIdAW : 0;

	if (id != m_bfmeIdAW || m_bfmeSetAW == 0)
	{
		((BfmeThingCDA *)this)->bfmeStepCDA();

		m_bfmeIdAW = id;
		m_bfmeSetAW = 1;
	}
}
