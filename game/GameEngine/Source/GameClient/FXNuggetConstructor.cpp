// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: clean C++ reconstruction of the BFME FXNugget base constructor
// at 0x00428590 (225 bytes).
//
// BFME's base owns two four-byte filter
// members at +8/+C, four BitFlags<320> members at +10/+38/+60/+88, the stop
// flag at +B0, and the nugget discriminator at +4.  The shared FXList field
// table at 0x00CF2480 names those offsets; the BFME vftable at 0x010F23A0 and
// the 24 named nugget parser callers establish this constructor's identity.
//
// `HRBMD_Buffer` is the existing TU-local spelling for the four-byte BFME
// member whose constructor is the ICF-folded ILT at 0x0003747A.  It is used
// here only to select that already-pinned constructor call; the public owner
// recovered by this body is FXNugget.  STLport's bitset default constructor
// performs the four ten-word zeroing sequences in retail's register order.

#include <bitset>

typedef unsigned int UnsignedInt;
typedef bool Bool;

// Existing BFME ICF-folded four-byte member constructor spelling.  The actual
// body is shared by several unrelated member classes at ILT 0x0003747A.
class HRBMD_Buffer
{
public:
	HRBMD_Buffer();
	~HRBMD_Buffer();

private:
	UnsignedInt m_value;
};

// upstream layout: inputs/reference/.../game/GameEngine/Include/Common/BitFlags.h
// The shipped game used STLport's std::bitset implementation.  Its default
// constructor is intentionally empty here; std::bitset's member constructor
// supplies the retail zeroing stores.
template <size_t NUMBITS>
class BitFlags
{
public:
	BitFlags() {}

private:
	std::bitset<NUMBITS> m_bits;
};

// upstream layout: inputs/reference/.../game/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

private:
	UnsignedInt m_nuggetType;                         // +0x04
	HRBMD_Buffer m_sourceObjectFilter;               // +0x08
	HRBMD_Buffer m_objectFilter;                      // +0x0C
	BitFlags<320> m_requiredSourceModelConditions;   // +0x10
	BitFlags<320> m_excludedSourceModelConditions;   // +0x38
	BitFlags<320> m_requiredSecondaryModelConditions;// +0x60
	BitFlags<320> m_excludedSecondaryModelConditions;// +0x88
	Bool m_stopIfNuggetPlayed;                        // +0xB0
};

// ??0FXNugget@@QAE@XZ
FXNugget::FXNugget()
{
	m_stopIfNuggetPlayed = false;
	m_nuggetType = 0;
}
