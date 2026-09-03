// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x007206E0 is the BFME W3DTreeBuffer destructor.  The adjacent
// matched bodies use the same expanded BFME layout: clearAllTrees at
// 0x0071C7E0, freeTreeBuffers at 0x0071C2D0, the two reset-list members at
// +0x1458/+0x1480, and the 64-entry tree-type array at +0x1E1CD4.

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class Rva007206E0TextureRef
{
public:
	Rva007206E0TextureRef(void) : m_p(0) {}
	~Rva007206E0TextureRef(void)
	{
		if (m_p)
			m_p->Release_Ref();
	}

	TextureBaseClass *m_p;
};

// The BFME reset-list object is 0x28 bytes here.  Its destructor is the
// already matched 0x0094CDF0 body; the larger opaque tail preserves the
// W3DTreeBuffer offsets without inventing its node representation.
class Gen_uwm_0094cdf0
{
public:
	~Gen_uwm_0094cdf0(void);

private:
	unsigned char m_body[0x28];
};

// The tree-type element destructor is reached through the existing ILT at
// 0x00432CF9 (which targets the matched 0x0071EA00 destructor).
class Rva007206E0TreeType
{
public:
	~Rva007206E0TreeType(void);

private:
	unsigned char m_body[0x5C];
};

class Rva007206E0Snapshot
{
public:
	virtual void crc(void) = 0;
	virtual void xfer(void) = 0;
	virtual void loadPostProcess(void) = 0;

	~Rva007206E0Snapshot(void)
	{
		*(volatile unsigned int *)this = 0x01073744;
	}

private:
};

class BaseHeightMapResetBuffer
{
public:
	void clear3098(void);
};

class W3DTreeBuffer : public Rva007206E0Snapshot
{
public:
	~W3DTreeBuffer(void);
	void freeTreeBuffers(void);

private:
	unsigned char m_pad0004[0x1450 - 4];
	Rva007206E0TextureRef m_texture1450;
	Rva007206E0TextureRef m_texture1454;
	Gen_uwm_0094cdf0 m_resetList1458;
	Gen_uwm_0094cdf0 m_resetList1480;
	unsigned char m_pad14A8[0x1E1CD4 - 0x14A8];
	Rva007206E0TreeType m_treeTypes[64];
	unsigned char m_pad1E33D4[0x1E3914 - 0x1E33D4];
	Rva007206E0TextureRef m_treeTexture;
};

#pragma comment(linker, "/alternatename:??1Rva007206E0TreeType@@QAE@XZ=?j_00032cf9@@YAXXZ")
// ??1W3DTreeBuffer@@QAE@XZ
W3DTreeBuffer::~W3DTreeBuffer(void)
{
	((BaseHeightMapResetBuffer *)this)->clear3098();
	freeTreeBuffers();
}
