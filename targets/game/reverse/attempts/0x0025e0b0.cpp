// ?update@Rva0025E0B0Module@@QAEXPAVObject@@@Z
// partial score=0.78 date=2026-09-15
// Clean scratch reconstruction for retail RVA 0x0025E0B0, exact extent 128B.
// This is intentionally address-labelled; the original module owner is not
// asserted from dump adjacency.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#include "Lib/BaseType.h"
#include "Common/BitFlags.h"

// BFME's object status storage is BitFlags<86> (three words).  Do not use the
// smaller ZH ObjectStatusTypes.h typedef in this ABI slice.
typedef BitFlags<86> ObjectStatusMaskType;
typedef char RvaNativeBitFlags86SizeCheck[(sizeof(ObjectStatusMaskType) == 12) ? 1 : -1];

class Object;
class Matrix3D;

class FXList
{
public:
	bool bfmeIsBlocked(); // ILT 0x00011F77 -> non-const culling predicate 0x0042DAA0
	void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	// ILT 0x0001BB21 -> body 0x004280D0
};

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
};

// Existing matched address-labelled member at RVA 0x0025DF30.  Its retail
// body consumes ECX immediately; preserve that thiscall receiver through the
// existing ILT 0x00008E90 route.
class Rva0025DF30GiveUpgradeUpdate
{
public:
	void update();
};

struct Rva0025E0B0ModuleData
{
	unsigned char m_unmodelled[0x264];
	FXList *m_fxList;
};

class Rva0025E0B0Module
{
public:
	void update(Object *position);

private:
	unsigned char m_unmodelled00[4];
	Rva0025E0B0ModuleData *m_moduleData;
	unsigned char m_unmodelled08[0xe0];
	unsigned char m_flagE8;
	unsigned char m_flagE9;
	unsigned char m_unmodelledEA[2];
	float m_valueEC;
};

void Rva0025E0B0Module::update(Object *position)
{
	if (position == 0)
		return;

	reinterpret_cast<Rva0025DF30GiveUpgradeUpdate *>(this)->update();
	m_flagE9 = 0;

	FXList *fxList = m_moduleData->m_fxList;
	if (fxList != 0 && !fxList->bfmeIsBlocked())
		fxList->doFXPos((const Coord3D *)((const char *)position + 0x38), 0, 0, 0);

	ObjectStatusMaskType status(ObjectStatusMaskType::kInit, 3);
	position->setStatus(status, true);
	m_flagE8 = 1;
	m_valueEC = 1.0f;
}
