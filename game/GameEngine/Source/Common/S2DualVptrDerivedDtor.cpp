// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib
// Destructor twin of the dual-vptr constructor at 0x00694E00
// (S2DualVptrDerivedCtors.cpp). Restores the second-base vtable at +8 to
// 0x01073744 then tails into the first-base destructor at 0x009A1A40.
//
// That first-base destructor is SubsystemInterface's own body, so the base is
// the real class (subsystem_interface.h) rather than a local stand-in with an
// address-derived name: its vptr + m_name make it eight bytes, which is what
// keeps the second base at +8.
#include "PreRTS.h"
#include "subsystem_interface.h"

class GenBase01073744
{
public:
	virtual ~GenBase01073744() {}
	virtual void keepSecond();
};

class __declspec(novtable) Rva00694E00 : public SubsystemInterface, public GenBase01073744
{
public:
	virtual ~Rva00694E00();
	virtual void keepOwn();
};

// @??1Rva00694E00@@UAE@XZ 0x00694E30
Rva00694E00::~Rva00694E00()
{
}
