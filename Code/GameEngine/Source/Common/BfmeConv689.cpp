extern "C" unsigned char bfmeVftDFH[];
extern "C" __declspec(dllimport) int __cdecl fflush(void *stream);

class BfmeThingDFH
{
public:
	BfmeThingDFH *bfmeTailDFH();
	BfmeThingDFH *bfmeGoDFH();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x50];
	void *m_bfmeStream;
};

BfmeThingDFH *BfmeThingDFH::bfmeGoDFH()
{
	void *p = m_bfmeStream;
	m_bfmeVft = bfmeVftDFH;
	fflush(p);
	return bfmeTailDFH();
}
