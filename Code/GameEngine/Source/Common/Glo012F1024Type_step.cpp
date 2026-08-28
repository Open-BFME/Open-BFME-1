// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Glo012F1024Type::step, retail 0x003B3900, 56 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it as the
// niladic member called on the global at 0x012F1024, which is the same object
// V4TwoCallForwarders.cpp calls step on.
//
// Nothing happens unless the flag at +0x8E of TheWritableGlobalData is set and
// the index at +0x0C names a live entry of the vector at +0x10. The entries are
// 32 bytes -- the pointer difference is shifted by five, not divided -- and the
// two bound tests are separate: the negative one signed, the upper one unsigned
// against the count.
//
// The flag at +0x1D is cleared and the entry's own step is a tail jump, which
// is why no frame is set up at all -- and the body keeps no callee-saved
// register either: it reloads the start pointer after the bound test rather
// than holding it across. Reading the two pointers straight off this makes the
// compiler keep that value in esi and pay for the push and pop; reaching them
// through a small vector member with its own size accessor is what lets it
// reload instead.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_bfmeHead[0x8E];
	Bool m_bfmeStepping;					// +0x8E
};

extern GlobalData *TheWritableGlobalData;			// 0x012ED5C8

class Glo012F1024Entry
{
public:
	void bfmeStep(void);					// ILT 0x00015F50

	char m_bfmeBody[0x20];
};

class BfmeEntryVector
{
public:
	Int bfmeSize(void) const { return m_bfmeFinish - m_bfmeStart; }

	Glo012F1024Entry *m_bfmeStart;				// +0x00
	Glo012F1024Entry *m_bfmeFinish;				// +0x04
};

class Glo012F1024Type
{
public:
	void step(void);

private:
	char m_pad00[0x0C];
	Int m_bfmeIndex;					// +0x0C
	BfmeEntryVector m_bfmeEntries;				// +0x10
	char m_pad18[0x1C - 0x18];
	bool m_at1C;						// +0x1C
	Bool m_bfmeArmed;					// +0x1D
};

// ?step@Glo012F1024Type@@QAEXXZ
void Glo012F1024Type::step(void)
{
	if (!TheWritableGlobalData->m_bfmeStepping)
		return;

	if (m_bfmeIndex < 0)
		return;

	if ((unsigned int)m_bfmeIndex >= (unsigned int)m_bfmeEntries.bfmeSize())
		return;

	m_bfmeArmed = false;

	m_bfmeEntries.m_bfmeStart[m_bfmeIndex].bfmeStep();
}
