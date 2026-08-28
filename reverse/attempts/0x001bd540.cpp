// ?d_001bd540@@YAXXZ
// partial score=0.65 date=2026-08-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: retail 0x001BD540 (14 bytes), two-word record reset.

class Rva001BD540
{
public:
	void reset(void);

private:
	unsigned char m_beforePair[0x390];
	struct Pair
	{
		int first;
		int second;
	};
	Pair m_pair;
};

void Rva001BD540::reset(void)
{
	volatile Pair *pair = &m_pair;
	pair->first = 0;
	pair->second = 0;
}
