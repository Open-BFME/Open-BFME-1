// cl: /DNDEBUG /MD /EHsc
//
// The retail routine at 0x00612560 tests the shared BFME state object, calls
// its virtual slot 9, compares the by-value AsciiString argument with the
// data literal at 0x00CF9410 ("ACTIVE"), and updates the byte at +0x1c.
// The complete BfmeGlobCC0 interface is the one independently used by
// Rva00410CC0Fetch.cpp; the fields below only name the two offsets touched by
// this body.

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class AsciiString : private BFMERetailAsciiString
{
public:
	int bfmeCompare1294(const char *text) const;
	~AsciiString() {}
};

class BfmeGlobCC0
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual bool bfmePredCC0();
	virtual int v11();
	virtual int v12();
	virtual void *bfmeGetCC0(void *);

	unsigned char m_pad04[0x18];
	unsigned char m_active;
	unsigned char m_pad1d[0x8b];
	void *m_stateA8;
};

extern BfmeGlobCC0 *g_bfmeGlobCC0;
extern const char g_bfmeActiveLiteral[];

// ?Rva00612560@@YGXVAsciiString@@@Z
void __stdcall Rva00612560(AsciiString text)
{
	if (g_bfmeGlobCC0 != 0)
	{
		g_bfmeGlobCC0->v9();
		if (text.bfmeCompare1294(g_bfmeActiveLiteral) == 0)
		{
			g_bfmeGlobCC0->m_active = 1;
			if (g_bfmeGlobCC0->m_stateA8 == 0)
				g_bfmeGlobCC0->v11();
		}
		else
		{
			g_bfmeGlobCC0->m_active = 0;
		}
	}
}
