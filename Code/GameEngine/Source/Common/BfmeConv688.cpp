extern "C" unsigned char bfmeVftDFG[];
extern "C" __declspec(dllimport) int __cdecl fflush(void *stream);

class BfmeThingDFG
{
public:
	BfmeThingDFG *bfmeTailDFG();
	BfmeThingDFG *bfmeGoDFG();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x50];
	void *m_bfmeStream;
};

BfmeThingDFG *BfmeThingDFG::bfmeGoDFG()
{
	void *p = m_bfmeStream;
	m_bfmeVft = bfmeVftDFG;
	fflush(p);
	return bfmeTailDFG();
}
