// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I.
// Retail 0x00896540, 111 bytes: a by-value ref-counted handle forwarder. It
// hands its handle to the 0x00896470 submitter and lets the implicit parameter
// destructor release the caller's copy. Identity stays address-derived: the
// only name the 0x0089 forwarder family gives it comes from the landed
// ?bfmeRva00896470@@YAXVBfmeRefHolder@@@Z body it calls.

extern void (*TheBfmeBufferFree)(void *p, int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeBufferFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

class BfmeRefHolder
{
public:
	BfmeRefHolder(BfmeDropObjectA *obj) : m_obj(obj)
	{
		if (obj)
			++*(int *)obj;
	}

	BfmeRefHolder(const BfmeRefHolder &other) : m_obj(other.m_obj)
	{
		if (m_obj) ++*(int *)m_obj;
	}

	~BfmeRefHolder()
	{
		if (m_obj && --*(int *)m_obj == 0)
			delete m_obj;
	}

public:
	BfmeDropObjectA *m_obj;
};

extern void __cdecl bfmeRva00896470(BfmeRefHolder obj);

// ?bfmeRva00896540@@YGXVBfmeRefHolder@@@Z
void __stdcall bfmeRva00896540(BfmeRefHolder obj)
{
	bfmeRva00896470(obj);
}
