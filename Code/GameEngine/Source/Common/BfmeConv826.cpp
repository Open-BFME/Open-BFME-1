
class BfmeMgrF1D
{
public:
	void* registerObj(void *field);
};
extern BfmeMgrF1D *g_mgr12EF1D8;

class BfmeSub4_78F
{
public:
	void* reg25C()
	{
		return g_mgr12EF1D8->registerObj((char*)this + 0x25c);
	}
	void* reg260()
	{
		return g_mgr12EF1D8->registerObj((char*)this + 0x260);
	}
};

struct BfmeThing78F
{
	unsigned char pad[4];
	BfmeSub4_78F *m_sub4;
	void* reg25C();
	void* reg260();
};

void* BfmeThing78F::reg25C()
{
	return m_sub4->reg25C();
}

void* BfmeThing78F::reg260()
{
	return m_sub4->reg260();
}

struct BfmeField58_FCD
{
	unsigned char pad[4];
	void *m_field4;
};

class BfmeSub30_FCD
{
public:
	unsigned char pad[0x58];
	BfmeField58_FCD *m_field58;
	int m_field5C;
	void notify(void *field4, int neg2);
};

struct BfmeThingFCD
{
	unsigned char pad[0x30];
	BfmeSub30_FCD *m_sub30;
	void checkAndNotify();
};

void BfmeThingFCD::checkAndNotify()
{
	BfmeSub30_FCD *sub = m_sub30;
	if (sub->m_field58 && sub->m_field5C == -1) {
		sub->notify(sub->m_field58->m_field4, -2);
	}
}

struct BfmeItem28
{
	int words[7];
};

struct BfmeVector28
{
	void *m_start0;
	BfmeItem28 *m_cur4;
	BfmeItem28 *m_end8;
	void insertHelper(void *edi, const BfmeItem28 *src, void *temp, int one1, int one2);
	void push_back(const BfmeItem28 &item);
};

void BfmeVector28::push_back(const BfmeItem28 &item)
{
	if (m_cur4 != m_end8) {
		if (m_cur4) {
			*m_cur4 = item;
		}
		m_cur4++;
	} else {
		void *temp;
		insertHelper(m_cur4, &item, &temp, 1, 1);
	}
}
