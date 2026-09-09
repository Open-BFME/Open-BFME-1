// ?bfmeApplyESP@@YAXPBD0@Z

struct BfmeHdrESP
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPoolESP
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPoolESP *g_bfmeStringPool1284;
extern unsigned char g_bfmeFlagESP;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text);
	BfmeStrVKI(const BfmeStrVKI &other)
	{
		m_data = other.m_data;
		++m_data->m_refCount;
	}
	~BfmeStrVKI()
	{
		BfmeHdrESP *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeHdrESP *m_data;
};

class Rva8CD130String : public BfmeStrVKI
{
public:
	Rva8CD130String(const char *text) : BfmeStrVKI(text) {}
	Rva8CD130String(const Rva8CD130String &other) : BfmeStrVKI(other) {}
	~Rva8CD130String() {}
	Rva8CD130String *operator&()
	{
		return this;
	}
};

class Rva00896AF0Tracker
{
public:
	void rva00896AF0(Rva8CD130String *input, Rva8CD130String text);
};

extern Rva00896AF0Tracker *g_bfmeTracker4310;

void bfmeApplyESP(const char *first, const char *second)
{
	Rva8CD130String secondText(second);
	g_bfmeTracker4310->rva00896AF0(
		&(g_bfmeFlagESP = 0, Rva8CD130String(first)), secondText);
}
