// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib

// BFME's base here is SubsystemInterface itself, not Zero Hour's Snapshot: the
// base destructor call goes to the 14-byte body at 0x009A1A40, which is
// ??1SubsystemInterface@@UAE@XZ.  SubsystemInterface is vptr + m_name, i.e.
// eight bytes, so the render object this body deletes sits at +0x08.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
#include "PreRTS.h"

#include "subsystem_interface.h"

class AssetManagerImpl
{
public:
	~AssetManagerImpl();
};

class Rva009EB960 : public SubsystemInterface
{
public:
	virtual ~Rva009EB960();

private:
	AssetManagerImpl *m_renderObject;			// +0x08
};

Rva009EB960::~Rva009EB960()
{
	delete m_renderObject;
}