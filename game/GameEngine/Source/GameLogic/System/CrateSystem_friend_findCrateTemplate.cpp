// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?friend_findCrateTemplate@CrateSystem@@QAEPAVCrateTemplate@@VAsciiString@@@Z: game/GameEngine/Source/GameLogic/System/CrateSystem.cpp
// Open-BFME: CrateSystem::friend_findCrateTemplate, retail 0x003795E0, 320
// bytes.
//
// The reference's body unchanged: walk the template vector at this+0x08 by
// index, and on the first name that matches hand back the end of that
// template's override chain. The index is compared unsigned against the
// element count, which is what the reference's signed loop variable against
// size() comes to.
//
// The name comparison is the inlined case-sensitive compare this tree has
// landed four times now, on an AsciiString the template returns by value and
// releases on the way out -- the answer riding in bl across that release.
//
// The dumped boundary here was three bytes short: the body runs to 0x00379723
// and the `ret 4` at 0x00379720 was left outside it, unclaimed. This row takes
// the whole 323.
//
// The override step is two tests and one call: a null template gives null, a
// template with no next override is its own final override, and only a real
// chain reaches the walker the ledger already pins.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

	void toLower(void);					// retail 0x00887DA0

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Bool isEmpty(void) const { return m_data == 0 || m_data->m_len == 0; }

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

	Bool operator==(const AsciiString &rhs) const { return compare(rhs) == 0; }

private:
	BfmeAsciiStringData *m_data;
};

// The shared override-chain walker. Retail spells it
// ?getFinalOverride@Overridable@@QBEPBV1@XZ -- public, const, returning a const
// pointer -- and ILT 0x000022BB reaches the matched out-of-line body at
// 0x00087A80, which is the recursive step this inlines one level of. This TU
// includes no game header, so the defining class is declared here under its real
// name with upstream's own recursive inline body; declaring it const and
// returning const is what makes the mangling match the ledger.
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

protected:
	char m_bfme_vptr[4];					// this+0x00
	Overridable *m_nextOverride;				// this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateTemplate : public Overridable
{
public:
	AsciiString getName(void) const;			// ILT 0x000259D7
};

// The reference's OVERRIDE wrapper, for this one element type.
class CrateTemplateOverride
{
public:
	CrateTemplateOverride(CrateTemplate *t) : m_ptr(t) {}

	operator const CrateTemplate *(void) const
	{
		if (m_ptr == 0)
			return 0;

		return (const CrateTemplate *)m_ptr->getFinalOverride();
	}

private:
	CrateTemplate *m_ptr;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateSystem
{
public:
	const CrateTemplate *findCrateTemplate(AsciiString name) const;
	CrateTemplate *friend_findCrateTemplate(AsciiString name);

private:
	char m_slice_pad[8];					// retail this+0x00 .. +0x07, untouched
	_STL::vector<CrateTemplate *> m_crateTemplateVector;	// this+0x08
};

// readable body of ?findCrateTemplate@CrateSystem@@QBEPBVCrateTemplate@@VAsciiString@@@Z: game/GameEngine/Source/GameLogic/System/CrateSystem.cpp
// The const twin, retail 0x00379440, 323 bytes, immediately before
// friend_findCrateTemplate as in the reference's source order. Its bytes are
// the same as friend_findCrateTemplate's; CrateSystem::newCrateTemplate
// (call at 0x0037A3B9) reaches it through ILT 0x0001B8CE, which the ledger
// pins under this name.
const CrateTemplate *CrateSystem::findCrateTemplate(AsciiString name) const
{
	// search weapon list for name
	for (Int i = 0; i < m_crateTemplateVector.size(); i++)
		if(m_crateTemplateVector[i]->getName() == name) {
			CrateTemplateOverride overridable(m_crateTemplateVector[i]);
			return overridable;
		}
	return 0;
}

CrateTemplate *CrateSystem::friend_findCrateTemplate(AsciiString name)
{
	// search weapon list for name
	for (Int i = 0; i < m_crateTemplateVector.size(); i++)
		if(m_crateTemplateVector[i]->getName() == name) {
			CrateTemplateOverride overridable(m_crateTemplateVector[i]);
			return (CrateTemplate *)(const CrateTemplate *)overridable;
		}
	return 0;
}
