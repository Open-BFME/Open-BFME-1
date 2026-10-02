// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x0091F730, 82 bytes. Four arguments (ret 0x10) and six stores, then
// one of two calls.
//
// The first store is the second argument shifted left six and added to a fixed
// address: an index into an array of 0x40-byte entries, which is what the
// shift width says. The rest go straight in, with the third argument stored as
// a word -- the G in the decoration.
//
// The branch tests the FIRST argument against 2 and picks between two
// argument-less members on this. The sorting-array path uses the verified
// Allocate_Sorting_Dynamic_Buffer provider at RVA 0091F040.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

// Match the existing slot-storage owner in DynamicVBAccessClassDeinitBFME.cpp.
class BfmeDynElemXZ
{
public:
	void bfmeResetXZ(unsigned int fvf, int flag);
	unsigned char m_bfmePadXZ[0x40];
};

extern BfmeDynElemXZ BfmeDynamicVBSlots[];				// 0x013467F0

class BoxDynamicVBAccessClass
{
public:
	BoxDynamicVBAccessClass(UnsignedInt type, UnsignedInt fvf, UnsignedShort count, UnsignedInt start);
	void Allocate_Sorting_Dynamic_Buffer(void); // verified provider at RVA 0091F040

private:
	void bfmeAllocateSorting(void);					// retail 0x0091F5B0

	BfmeDynElemXZ *m_bfmeSlot;					// +0x00
	UnsignedInt m_bfmeType;						// +0x04
	UnsignedInt m_bfmeFVF;						// +0x08
	UnsignedInt m_bfmeStart;					// +0x0C
	UnsignedShort m_bfmeCount;					// +0x10
	UnsignedShort m_bfmePad;					// +0x12
	UnsignedInt m_bfme0014;						// +0x14
};

// ??0BoxDynamicVBAccessClass@@QAE@IIGI@Z
BoxDynamicVBAccessClass::BoxDynamicVBAccessClass(UnsignedInt type, UnsignedInt fvf, UnsignedShort count, UnsignedInt start)
	: m_bfmeSlot(&BfmeDynamicVBSlots[fvf]),
	  m_bfmeType(type),
	  m_bfmeFVF(fvf),
	  m_bfmeStart(start),
	  m_bfmeCount(count),
	  m_bfme0014(0)
{
	if (type == 2)
		bfmeAllocateSorting();
	else
		Allocate_Sorting_Dynamic_Buffer();
}
