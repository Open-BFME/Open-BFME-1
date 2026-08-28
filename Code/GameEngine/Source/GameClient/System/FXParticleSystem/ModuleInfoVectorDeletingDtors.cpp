// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Two 87-byte vector deleting destructors, 0x005D50F0 and 0x005D54B0.  Retail
// (the 0x84 arity):
//
//     push ebx / mov bl,[esp+8] / test bl,2 / push esi / mov esi,ecx / je scalar
//     mov eax,[esi-4] / push edi / push offset <DTOR> / lea edi,[esi-4]
//     push eax / push <SIZE> / push esi / call `eh vector destructor iterator`
//     test bl,1 / je keep
//     push edi / call operator delete[] / add esp,4
//     keep: mov eax,edi / pop edi / pop esi / pop ebx / ret 4
//     scalar: mov ecx,esi / call <DTOR> / test bl,1 / je out
//     push esi / call operator delete / add esp,4
//     out: mov eax,esi / pop esi / pop ebx / ret 4
//
// WHAT THE BYTES SHOW.  A __thiscall member taking one dword and testing only
// its BIT 1 and BIT 0, choosing between an array walk and a single destructor
// call on the first and between `operator delete[]` and `operator delete` on
// the second, is the MSVC vector deleting destructor `??_E` and nothing else.
// The array arm reads the element COUNT from the dword immediately before the
// object (`mov eax,[esi-4]`) and frees from that address, which is the
// array-new cookie layout; the element size it passes is the class size.
//
// THE TWO ROWS ARE NAMED, not address-derived.  Each one calls a destructor
// that the ledger already claims:
//
//     0x005D50F0 -> 0x005D4F50  FXParticleSystem::~DefaultAlphaModuleInfo
//     0x005D54B0 -> 0x005D52D0  FXParticleSystem::~DefaultColorModuleInfo
//
// and the sizes it pushes, 0x84 and 0x90, are exactly what those two classes
// measure as they are already spelled in this directory -- 4 bytes of vptr
// plus eight 16-byte keyframes for the alpha info, and the same plus a
// 12-byte GameClientRandomVariable for the colour info.  A wrong class would
// push a wrong immediate, so the size is independent confirmation of the
// destructor the call names.
//
// WHY THE SCAFFOLDING BELOW IS NEEDED.  MSVC 7.1 emits `??_E` only into a
// translation unit that both instantiates the class and applies `delete[]` to
// it; with only the `delete[]`, the compiler routes through the vftable slot
// and emits no body at all.  The four helpers exist to force that and
// correspond to nothing in retail.
//
// A THIRD ROW OF THIS SHAPE, 0x005CE780, IS NOT CLAIMED HERE.  It is
// FXParticleSystem::ParticleSystemTemplate`s `??_E` -- it calls 0x005CE4D0,
// the claimed destructor -- and it gates green, but only against a class four
// bytes LARGER than ParticleSystemTemplateCtorThunk.cpp spells (it pushes
// 0xD0 where that class measures 0xCC) and only with a default constructor
// declared that retail has no body for.  Landing it would put two different
// sizes for one real class into the tree, so the size discrepancy is reported
// instead: whichever member ParticleSystemTemplate has after `m_a0` is missing
// from the sibling thunk, and 0x005CE780 is free the moment it is found.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ClientRandomValue.h
class GameClientRandomVariable
{
public:
	enum DistributionType { CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS };

	GameClientRandomVariable() : m_type(CONSTANT), m_low(0.0f), m_high(0.0f) {}
	void setRange(float low, float high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class RGBColor
{
public:
	float red;
	float green;
	float blue;
};

namespace FXParticleSystem {

struct RandomAlphaKeyframe
{
	RandomAlphaKeyframe()
	{
		var.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
		frame = 0.0f;
	}

	GameClientRandomVariable var;
	float frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
struct RGBColorKeyframe
{
	RGBColor color;
	float frame;
};

class Xfer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
protected:
	~Snapshot();
};

class DefaultAlphaModuleInfo : public Snapshot
{
public:
	DefaultAlphaModuleInfo();
	virtual ~DefaultAlphaModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &);

private:
	RandomAlphaKeyframe m_alphaKey[8];
};

class DefaultColorModuleInfo
{
public:
	DefaultColorModuleInfo();
	virtual ~DefaultColorModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

	RGBColorKeyframe m_colorKey[8];
	GameClientRandomVariable m_colorScale;
};

// ?u1MakeAlphaArray@FXParticleSystem@@YAPAVDefaultAlphaModuleInfo@1@H@Z absent-from-retail
DefaultAlphaModuleInfo *u1MakeAlphaArray( int count )
{
	return new DefaultAlphaModuleInfo[ count ];
}

// ?u1MakeColorArray@FXParticleSystem@@YAPAVDefaultColorModuleInfo@1@H@Z absent-from-retail
DefaultColorModuleInfo *u1MakeColorArray( int count )
{
	return new DefaultColorModuleInfo[ count ];
}

// ?u1DeleteAlphaArray@FXParticleSystem@@YAXPAVDefaultAlphaModuleInfo@1@@Z absent-from-retail
void u1DeleteAlphaArray( DefaultAlphaModuleInfo *array )
{
	delete[] array;
}

// ?u1DeleteColorArray@FXParticleSystem@@YAXPAVDefaultColorModuleInfo@1@@Z absent-from-retail
void u1DeleteColorArray( DefaultColorModuleInfo *array )
{
	delete[] array;
}

}
