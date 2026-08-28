// cl: /DNDEBUG /MD /EHsc
// readable body of ?deleteAllFonts@FontLibrary@@IAEXXZ: Code/GameEngine/Source/GameClient/GUI/GameFont.cpp

// Open-BFME5: FontLibrary::deleteAllFonts, retail 0x00722190, 90 bytes, from
// the thunk queue -- the name sat on a five-byte thunk and this is the body it
// jumps to.
//
// The lock and unlock at either end are a guard object, not two bare calls:
// that is what gives the body its SEH frame and the two unwind writes, which
// bracket exactly the region between the constructor and the destructor. Both
// halves are free functions the ledger already names.
//
// Between them one reference-counted handle at +0x34 is released -- the count
// at +0x04 of the target dropped in place, slot 0 of its table entered with no
// argument when it reaches zero -- and the pointer cleared.

typedef int Int;

void W3DRadarResetLock(void);					// retail 0x00903090
void W3DRadarResetUnlock(void);					// retail 0x00905B10

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock() { W3DRadarResetLock(); }
	~BfmeRadarResetLock() { W3DRadarResetUnlock(); }
};

class BfmeFontRef
{
public:
	virtual void bfmeDestroy(void);				// slot 0

	Int m_bfmeRefCount;					// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameFont.h
class FontLibrary
{
protected:
	void deleteAllFonts(void);

private:
	char m_bfmeHead[0x34];
	BfmeFontRef *m_bfmeFont;				// +0x34
};

// ?deleteAllFonts@FontLibrary@@IAEXXZ
void FontLibrary::deleteAllFonts(void)
{
	BfmeRadarResetLock lock;

	// The handle goes into a local: read through the member the compiler
	// cannot use the decrement's own flags and reloads the count to test it.
	BfmeFontRef *font = m_bfmeFont;

	if (font)
	{
		if (--font->m_bfmeRefCount == 0)
			font->bfmeDestroy();

		m_bfmeFont = 0;
	}
}
