// cl: /DNDEBUG /MD /EHsc
// readable body of ?newCrateTemplateOverride@CrateSystem@@QAEPAVCrateTemplate@@PAV2@@Z: Code/GameEngine/Source/GameLogic/System/CrateSystem.cpp
// Open-BFME: CrateSystem::newCrateTemplateOverride, retail 0x0037A230, 143 bytes.
//
// The reference's body with one BFME addition: a global byte at 0x012ED611 is
// raised across the copy assignment and dropped again straight after, so
// something else in the tree can tell an override copy from an ordinary one.
// What reads it is not visible here, so it carries a descriptive name.
//
// Everything else is the reference. The allocation is the plain global
// operator new with the null check and unwind funclet MSVC emits for `new T`,
// which puts sizeof(CrateTemplate) at 0x3C; markAsOverride and setNextOverride
// are inlined to the Overridable fields at +8 and +4 behind the pool object's
// vptr; and the new override is both returned and linked into the one it
// copies.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// Raised only while an override is being copied over its original.
extern Bool TheBfmeOverrideCopyInProgress;			// 0x012ED611

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();					// pool object vptr, this+0x00

	void markAsOverride(void) { m_isOverride = true; }
	void setNextOverride(Overridable *nextOverride) { m_nextOverride = nextOverride; }

protected:
	Overridable *m_nextOverride;				// this+0x04
	Bool m_isOverride;					// this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateTemplate : public Overridable
{
public:
	CrateTemplate();					// ILT 0x0002A5C2
	CrateTemplate &operator=(const CrateTemplate &that);	// ILT 0x000294A1

private:
	char m_bfme_body[0x3C - 0x0C];				// sizeof(CrateTemplate) is the pushed 0x3C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateSystem
{
public:
	CrateTemplate *newCrateTemplateOverride(CrateTemplate *crateToOverride);
};

CrateTemplate *CrateSystem::newCrateTemplateOverride( CrateTemplate *crateToOverride )
{
	if (!crateToOverride) {
		return 0;
	}

	CrateTemplate *newOverride = new CrateTemplate;

	TheBfmeOverrideCopyInProgress = true;
	*newOverride = *crateToOverride;
	TheBfmeOverrideCopyInProgress = false;

	newOverride->markAsOverride();

	crateToOverride->setNextOverride(newOverride);
	return newOverride;
}
