// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BoxDynamicVBAccessClass::~BoxDynamicVBAccessClass, retail
// 0x0091D9E0, 79 bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// It is WW3D's dynamic vertex-buffer release, with one BFME change: the
// dynamic-DX8 arm indexes a pair of globals by the slot at +8 rather than
// using single variables, so this build keeps several dynamic buffers rather
// than one. The sorting arm still uses the plain pair of globals.
//
// The two arms also order their stores differently -- the indexed arm clears
// the in-use flag first, the sorting arm adds the count first -- and the
// indexed arm reloads the slot from +8 for the second global rather than
// keeping it, because the store to the first may alias it.
//
// The release at the end is the ordinary reference-count drop: the buffer has
// its vtable at +0 and its count at +4, and slot 0 is called with no argument
// when the count reaches zero.

typedef unsigned short UnsignedShort;

enum { BFME_MAX_DYNAMIC_BUFFERS = 21 };

class BfmeDynamicVertexBuffer
{
public:
	virtual void bfmeDeleteThis(void);			// vtable slot 0

	int m_bfmeNumRefs;					// +0x04

	void bfmeReleaseRef(void)
	{
		--m_bfmeNumRefs;
		if (m_bfmeNumRefs == 0)
			bfmeDeleteThis();
	}
};

extern bool BfmeDynamicDX8VertexBufferInUse[BFME_MAX_DYNAMIC_BUFFERS];		// 0x01346740
extern UnsignedShort BfmeDynamicDX8VertexBufferOffset[BFME_MAX_DYNAMIC_BUFFERS];	// 0x01346794
extern UnsignedShort BfmeDynamicSortingVertexArrayOffset;			// 0x013467E4
extern bool BfmeDynamicSortingVertexArrayInUse;					// 0x013467D8

enum { BFME_BUFFER_TYPE_DYNAMIC_DX8 = 2 };

class BoxDynamicVBAccessClass
{
public:
	~BoxDynamicVBAccessClass(void);

private:
	int m_bfmeField00;					// +0x00
	int m_bfmeType;						// +0x04
	int m_bfmeSlot;						// +0x08
	int m_bfmeField0C;					// +0x0C
	UnsignedShort m_bfmeVertexCount;			// +0x10
	UnsignedShort m_bfmeField12;
	BfmeDynamicVertexBuffer *m_bfmeVertexBuffer;		// +0x14
};

// ??1BoxDynamicVBAccessClass@@QAE@XZ
BoxDynamicVBAccessClass::~BoxDynamicVBAccessClass(void)
{
	if (m_bfmeType == BFME_BUFFER_TYPE_DYNAMIC_DX8)
	{
		BfmeDynamicDX8VertexBufferInUse[m_bfmeSlot] = false;
		BfmeDynamicDX8VertexBufferOffset[m_bfmeSlot] =
			(UnsignedShort)(BfmeDynamicDX8VertexBufferOffset[m_bfmeSlot] + m_bfmeVertexCount);
	}
	else
	{
		BfmeDynamicSortingVertexArrayOffset =
			(UnsignedShort)(BfmeDynamicSortingVertexArrayOffset + m_bfmeVertexCount);
		BfmeDynamicSortingVertexArrayInUse = false;
	}

	if (m_bfmeVertexBuffer)
	{
		m_bfmeVertexBuffer->bfmeReleaseRef();
		m_bfmeVertexBuffer = 0;
	}
}
