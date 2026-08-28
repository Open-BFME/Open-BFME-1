struct BfmeHolderRM
{
	unsigned char m_bfmeHead[0x64];
	void *m_bfmeWhat;
};

struct BfmeSinkRM
{
	void bfmeSendRM(void *what, int many);
};

struct BfmeOuterRM
{
	BfmeHolderRM *m_bfmeHolder;
	BfmeSinkRM *m_bfmeSink;
};

class BfmeThingRM
{
public:
	bool bfmeDrainRM();
	unsigned char m_bfmeHead[0xb8];
	int m_bfmeCount;
};

bool BfmeThingRM::bfmeDrainRM()
{
	int many = m_bfmeCount;
	if (many == 0)
		return false;
	m_bfmeCount = --many;
	((BfmeOuterRM *)((char *)this - 0x340))->m_bfmeSink->bfmeSendRM(
		((BfmeOuterRM *)((char *)this - 0x340))->m_bfmeHolder->m_bfmeWhat, many);
	return true;
}
