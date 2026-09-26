// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWLib
//
// TerrainCollisionModule::DoXfer.  The TerrainCollisionModule constructor
// (0x005FD550) installs vtable 0x011132C0 at +0x00 and, after constructing
// the TerrainCollisionModuleInfo base at +0x20, vtable 0x011132A4 there.
// Slot 3 of 0x011132C0 reaches this body; slot 3 of 0x011132A4 reaches the
// same body through the adjustor thunk at 0x005E31F0 (sub ecx,0x20).  Slot 3
// of TerrainCollisionModuleInfo's own vtable (0x011112F8) is
// TerrainCollisionModuleInfo::DoXfer (0x005FCF10), whose version, random
// variable, string and flag transfers this body inlines on its +0x20 base.
// Inlining that base call is what keeps the two +0x34 transfers from sharing
// one cached address: retail recomputes lea eax,[edi+0x34] for both.

#include "xfer.h"
#include "ascii_string.h"
#include "game_client_random_variable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

namespace FXParticleSystem
{

// Primary base at +0x00: its own vtable slot 3 is the same DoXfer slot, so the
// override is introduced here and receives the full object.  Only the two flags
// this body transfers are modelled.
class Rva005FD050Base00
{
public:
	virtual void unmodelledSlot0();
	virtual void unmodelledSlot1();
	virtual void unmodelledSlot2();
	virtual void DoXfer(Xfer &xfer);

protected:
	unsigned int m_unmodelled04[6];
	bool m_bool1C;
	bool m_bool1D;
};

class TerrainCollisionModuleInfo
{
public:
	virtual ~TerrainCollisionModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	// Same transfers as ?DoXfer@TerrainCollisionModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
	// at 0x005FCF10.
	virtual void DoXfer(Xfer &xfer)
	{
		Xfer::Version version;
		version.data[0] = 1;
		version.data[1] = 1;
		xfer == version;
		xferRandomVariable(xfer, m_randomVariable08);
		xfer == m_asciiString04;
		xfer == m_bool14;
	}

protected:
	AsciiString m_asciiString04;
	GameClientRandomVariable m_randomVariable08;
	bool m_bool14;
	unsigned int m_unmodelled18;
};

class TerrainCollisionModule
	: public Rva005FD050Base00,
	  public TerrainCollisionModuleInfo
{
public:
	virtual void DoXfer(Xfer &xfer);

private:
	unsigned int m_uint3C;
	bool m_bool40;
};

// ?DoXfer@TerrainCollisionModule@FXParticleSystem@@UAEXAAVXfer@@@Z
void TerrainCollisionModule::DoXfer(Xfer &xfer)
{
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	xfer == version;
	TerrainCollisionModuleInfo::DoXfer(xfer);
	xfer == m_bool1C;
	xfer == m_bool1D;
	xfer == m_bool14;
	xfer == m_bool40;
	xfer == m_uint3C;
}

}
