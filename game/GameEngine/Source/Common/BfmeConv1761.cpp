extern "C" int _bfmeVftAVBb[];
extern "C" int _bfmeVftAVBc[];
extern "C" int _bfmeVftARCa[];

class SubsystemInterface
{
public:
	SubsystemInterface(void);

	unsigned char m_bfmeHeadBY[8];
};

class BfmeBaseVUQ
{
public:
	BfmeBaseVUQ(void)
	{
		m_bfmeVfVUQ = _bfmeVftARCa;
		m_bfmeCVUQ = 0;
	}

	int *volatile m_bfmeVfVUQ;
	volatile int m_bfmeCVUQ;
};

class BfmeOwnBY : public SubsystemInterface, public BfmeBaseVUQ
{
public:
	BfmeOwnBY(void);

	volatile int m_bfmeDBY;
	volatile int m_bfmeEBY;
	volatile int m_bfmeFBY;
	volatile char m_bfmeGBY;
	volatile char m_bfmeHBY;
	unsigned char m_bfmePadBY[2];
	volatile int m_bfmeIBY;
	volatile int m_bfmeJBY;
	volatile int m_bfmeKBY;
};

BfmeOwnBY::BfmeOwnBY(void)
{
	*(int *volatile *)this = _bfmeVftAVBb;
	m_bfmeVfVUQ = _bfmeVftAVBc;
	m_bfmeDBY = 0;
	m_bfmeEBY = 0;
	m_bfmeFBY = 0;
	m_bfmeGBY = 0;
	m_bfmeHBY = 0;
	m_bfmeIBY = 0;
	m_bfmeJBY = 0;
	m_bfmeKBY = 0;
}
