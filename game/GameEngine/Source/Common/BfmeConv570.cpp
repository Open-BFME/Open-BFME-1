// cl: /Igame /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad
// WW3D::Set_Texture_Reduction is the matched body at 0x008FE0E0 (WW3D2/ww3d.cpp);
// the real header declares it, so include it rather than respelling a stand-in.
#include "WW3D2/ww3d.h"

// TU-local VIEW of the real GlobalData, kept only for its offsets.
class BfmeGlobalCBE
{
public:
	unsigned char m_bfmeHead[0x68];
	void *m_bfmeCur;
};

// retail 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`, defined once
// in Common/GlobalData.cpp.  In the linked build this TU must spell the global
// exactly that way or nothing defines it.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

// retail calls 0x008FD440, the body the ledger defines as
// ?Rva008FD440Get@@YAHXZ (Common/GlobalDwordGetters.cpp): a six-byte getter
// that reads the dword at 0x0133F460 and returns it.  It is compared against
// the member at +0x68 as a 32-bit value, so the call is spelled with that
// defining name and its int return.
int Rva008FD440Get();

void __stdcall bfmeGoCBE(void *spare)
{
	if (TheWritableGlobalData != 0)
	{
		void *cur = ((BfmeGlobalCBE *)TheWritableGlobalData)->m_bfmeCur;
		if ((void *)Rva008FD440Get() != cur)
			WW3D::Set_Texture_Reduction((int)cur, 6);
	}
}
