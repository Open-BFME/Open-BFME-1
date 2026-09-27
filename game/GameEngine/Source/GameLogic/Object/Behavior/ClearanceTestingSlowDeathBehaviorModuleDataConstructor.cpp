// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/System
// Retail 001F72D0, 149 bytes. Matched factory 00117310 constructs this 0x220-byte type.
// GeometryInfo's BFME extent is 0x5C: its constructors FFD10/100580 store through
// +0x58, and this owner's first following field is +0x204 after member +0x1A8.
// geometry.h describes a different, 0x20-byte layout; use the BFME extent here.
// Both float pairs initialize their second word before the body assigns the first.
#include "snapshot.h"

enum GeometryType
{
	GEOMETRY_SPHERE = 0
};

class GeometryInfo : public Snapshot
{
public:
	GeometryInfo(GeometryType type, bool, float, float, float);
	virtual ~GeometryInfo();

	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

private:
	unsigned char m_pad[0x58];
};

class Rva001F72D0FloatPair
{
public:
	Rva001F72D0FloatPair() : m_f214(1.1f) {}

	float m_f210;

private:
	float m_f214;
};

class SlowDeathBehaviorModuleData
{
public:
	SlowDeathBehaviorModuleData();
	virtual ~SlowDeathBehaviorModuleData();

private:
	unsigned char m_pad[0x1a4];
};

class ClearanceTestingSlowDeathBehaviorModuleData
	: public SlowDeathBehaviorModuleData
{
public:
	ClearanceTestingSlowDeathBehaviorModuleData();

private:
	GeometryInfo m_geometry;
	unsigned int m_dword204;
	unsigned int m_dword208;
	unsigned int m_dword20c;
	Rva001F72D0FloatPair m_pair210;
	Rva001F72D0FloatPair m_pair218;
};

ClearanceTestingSlowDeathBehaviorModuleData::ClearanceTestingSlowDeathBehaviorModuleData()
	: m_geometry(GEOMETRY_SPHERE, false, 1.0f, 1.0f, 1.0f),
	  m_dword204(0),
	  m_dword208(0),
	  m_dword20c(0),
	  m_pair210(),
	  m_pair218()
{
	m_pair210.m_f210 = 20.0f;
	m_pair218.m_f210 = -20.0f;
}