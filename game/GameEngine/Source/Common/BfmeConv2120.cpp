extern "C" void *BfmeBaseVUQVft[];

class BfmeMemAAO
{
public:
	void bfmeDtorAAO();
};

class BfmeMemBAAO
{
public:
	void bfmeDtorBAAO();
};

struct BfmeStaticAAO
{
	void *m_bfmeVftAAO;
	unsigned char m_bfmeHeadAAO[0x2c - 4];
	BfmeMemBAAO m_bfme2CAAO;
	unsigned char m_bfmeGapAAO[0x38 - 0x2c - 1];
	BfmeMemAAO m_bfme38AAO;
};

extern BfmeStaticAAO g_bfmeStaticAAO;

void bfmeTeardownAAO();

void bfmeTeardownAAO()
{
	g_bfmeStaticAAO.m_bfme38AAO.bfmeDtorAAO();
	g_bfmeStaticAAO.m_bfme2CAAO.bfmeDtorBAAO();

	g_bfmeStaticAAO.m_bfmeVftAAO = BfmeBaseVUQVft;
}
