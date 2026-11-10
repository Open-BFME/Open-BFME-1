extern "C" unsigned char __identifier("??_7stdio_streambuf_base@_SgI@@6B@")[];
extern "C" __declspec(dllimport) int __cdecl fflush(void *stream);

class BfmeThingDFA
{
public:
	BfmeThingDFA *bfmeTailDFA();
	BfmeThingDFA *bfmeGoDFA();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x50];
	void *m_bfmeStream;
};

BfmeThingDFA *BfmeThingDFA::bfmeGoDFA()
{
	void *p = m_bfmeStream;
	m_bfmeVft = __identifier("??_7stdio_streambuf_base@_SgI@@6B@");
	fflush(p);
	return bfmeTailDFA();
}
