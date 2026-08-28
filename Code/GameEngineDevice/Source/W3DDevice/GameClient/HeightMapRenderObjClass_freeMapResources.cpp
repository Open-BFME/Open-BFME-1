// cl: /DNDEBUG /MD /EHsc
// readable body of ?freeMapResources@HeightMapRenderObjClass@@UAEHXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/HeightMap.cpp

// Open-BFME5: HeightMapRenderObjClass::freeMapResources, retail 0x006D2690, 122
// bytes. The body carried only a machine byte-dump row; reverse/reloc_names.csv
// holds the name with identity=real.
//
// The chunk array at +0x30D8 goes first, between a bare radar-reset lock and
// unlock -- two calls, not the guard object FontLibrary::deleteAllFonts uses:
// a guard would need an unwind frame and there is none here. Its elements are
// 0xC4 bytes and have a destructor, so the delete reads the count from the
// cookie in front of the block and runs the eh vector destructor iterator
// before freeing it; with exception handling off the compiler inlines that loop
// instead and the body grows by a quarter.
//
// Then three words are cleared and the plain array at +0x30D4 is freed with no
// cookie and no element loop.
//
// The mangled name types the return as Int but nothing is ever put in eax: the
// function simply falls off the end.

// The mangled name types the return as Int but the body never sets eax, so the
// missing return has to be allowed through rather than invented.
#pragma warning(disable : 4716)

typedef int Int;

void W3DRadarResetLock(void);					// retail 0x00903090
void W3DRadarResetUnlock(void);					// retail 0x00905B10

class BfmeMapChunk
{
public:
	~BfmeMapChunk();

private:
	char m_bfmeBody[0xC4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/HeightMap.h
class HeightMapRenderObjClass
{
public:
	virtual Int freeMapResources(void);

private:
	char m_bfmeHead[0x30D4 - 0x04];		// the compiler supplies the vptr at +0
	short *m_bfmeIndices;					// +0x30D4
	BfmeMapChunk *m_bfmeChunks;				// +0x30D8
	Int m_bfme30DC;						// +0x30DC
	Int m_bfme30E0;						// +0x30E0
	Int m_bfme30E4;						// +0x30E4
};

// ?freeMapResources@HeightMapRenderObjClass@@UAEHXZ
Int HeightMapRenderObjClass::freeMapResources(void)
{
	if (m_bfmeChunks)
	{
		W3DRadarResetLock();

		delete [] m_bfmeChunks;

		W3DRadarResetUnlock();

		m_bfmeChunks = 0;
	}

	m_bfme30E0 = 0;
	m_bfme30E4 = 0;
	m_bfme30DC = 0;

	if (m_bfmeIndices)
	{
		delete [] m_bfmeIndices;

		m_bfmeIndices = 0;
	}
}
