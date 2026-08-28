
class BfmeSubEFB
{
public:
	bool bfmeIsReady();
};

struct BfmeThingEFB
{
	unsigned char m_pad[0x1e8];
	BfmeSubEFB *m_sub;
	bool bfmeCheckReady();
};

bool BfmeThingEFB::bfmeCheckReady()
{
	if (!m_sub)
		return false;
	return m_sub->bfmeIsReady();
}

float __stdcall bfmeCalcEFC(int val);

struct BfmeThingEFC
{
	unsigned char m_pad[0x8];
	float m_f8;
	int m_valC;
	void bfmeUpdate(int val);
};

void BfmeThingEFC::bfmeUpdate(int val)
{
	m_valC = val;
	m_f8 = bfmeCalcEFC(val);
}

void* __cdecl bfmeAllocEFA(unsigned int sz);
void __cdecl bfmeInitSubEFA(void *dst, void *arg);

struct BfmeMadeEFA
{
	int m_zero;
	unsigned char m_buf[0x64];
};

BfmeMadeEFA* __stdcall bfmeMakeEFA(void *arg)
{
	BfmeMadeEFA *p = (BfmeMadeEFA *)bfmeAllocEFA(0x68);
	p->m_zero = 0;
	bfmeInitSubEFA(p->m_buf, arg);
	return p;
}

extern "C" void *bfmeGlobalTable12A6918[];

struct BfmeBitSetEFA
{
	unsigned int m_words[8];
	void* bfmeGetEntry(unsigned int index);
};

void* BfmeBitSetEFA::bfmeGetEntry(unsigned int index)
{
	if (m_words[index >> 5] & (1 << (index & 0x1f)))
		return bfmeGlobalTable12A6918[index];
	return 0;
}

struct BfmeVec
{
	int *start;
	int *end;
	int size() const { return (int)(end - start); }
};

struct BfmeThingEFE
{
	unsigned char m_pad[0xc];
	int m_baseCount;
	BfmeVec *m_vec;
	int bfmeClampIndex(int count);
};

int BfmeThingEFE::bfmeClampIndex(int count)
{
	int diff = count - m_baseCount;
	if (diff <= 0)
		return 0;
	if (diff >= m_vec->size())
		return m_vec->size() - 1;
	return diff;
}

class BfmeSubInnerEFF
{
public:
	void* bfmeGetFinalOverride();
};

struct BfmeSubEFF
{
	unsigned char m_pad[0x4];
	BfmeSubInnerEFF *m_inner;
	unsigned char m_padFC[0xfc - 0x8];
	char m_flagFC;
};

struct BfmeArgEFF
{
	unsigned char m_pad90[0x90];
	int m_mask90;
	unsigned char m_pad1F5[0x1f5 - 0x94];
	char m_byte1F5;
};

struct BfmeThingEFF
{
	unsigned char m_pad[0x4];
	BfmeSubEFF *m_sub;
	char bfmeCheckEFF(BfmeArgEFF *arg);
};

char BfmeThingEFF::bfmeCheckEFF(BfmeArgEFF *arg)
{
	BfmeSubEFF *s = m_sub;
	if (s) {
		BfmeSubInnerEFF *in = s->m_inner;
		if (in)
			s = (BfmeSubEFF*)in->bfmeGetFinalOverride();
	}
	if (s->m_flagFC) {
		if (arg->m_mask90 & 0x400000)
			return 1;
	}
	if (arg)
		return arg->m_byte1F5;
	return 0;
}
