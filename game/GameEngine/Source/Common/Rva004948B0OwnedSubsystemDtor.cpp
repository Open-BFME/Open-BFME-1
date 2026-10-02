// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib

// The base destructor this body chains to at the end is the one at 0x009A1A40,
// which is ??1SubsystemInterface@@UAE@XZ; SubsystemInterface is vptr + m_name,
// eight bytes, so the owned resource pointer stays at +0x08.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
#include "PreRTS.h"

#include "subsystem_interface.h"

class Rva004948B0Resource
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6();
	virtual void release(void);
};

class Rva004948B0OwnedSubsystem : public SubsystemInterface
{
public:
	virtual ~Rva004948B0OwnedSubsystem();
private:
	Rva004948B0Resource *m_resource;
	unsigned char m_padding[0x14];
	unsigned char m_flags;
};

Rva004948B0OwnedSubsystem::~Rva004948B0OwnedSubsystem()
{
	if (m_resource)
		m_resource->release();
	m_resource = 0;
	m_flags &= 0xfc;
}
