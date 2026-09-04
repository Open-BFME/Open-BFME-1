// cl: /DNDEBUG /MD /EHsc

// LaserUpdate's client-update-module constructor at retail 0x00603790.
// ModuleFactory calls the 0x00006780 ILT, which jumps here; the class's matched
// destructor installs the same vftable and returns the "LaserUpdate" name.
//
// SHAPE. The base is ClientUpdateModule(Thing *, const ModuleData *), already
// pinned at the 0x00002874 thunk. Its subobject ends at +0x0C; everything from
// +0x0C to +0x50 is this class's own, all zeroed except 1.0f at +0x3C.
//
// WHY THIS ROW KEEPS THE CONTRIVED SPELLING WHEN ITS SIBLINGS NO LONGER DO.
// Taint (0x0026B870), CloudBreak (0x002592A0) and Keyboard (0x005A3AC0) were
// landed with the same __declspec(novtable) plus hand-written vftable plus
// volatile-lvalue construct and have since been rewritten as ordinary C++,
// because MSVC 7.1's real rule is that it SINKS a constructor's vptr store
// forward until a barrier stops it, and a member sub-object's construction is
// such a barrier -- emitted after the vptr store and before the constructor
// body. This body is the one of the four that cannot be reached that way, and
// the reason is a layout contradiction, not a missing spelling.
//
// Retail writes the byte at +0x24 BEFORE the vftable pointer and the dword at
// +0x18 immediately AFTER it. Only two things put a store ahead of the vptr
// store: a base-class constructor (bases are constructed first) or a store the
// compiler cannot prove stays inside the object. Only those same two things,
// plus a member sub-object's construction, stop the sink. A base holding +0x24
// must extend to at least +0x28, which forces every member sub-object to +0x28
// or beyond -- so the barrier can never be the +0x18 store. Probed directly:
// an intermediate base setting +0x24 with a sub-object at +0x28 emits
// `88 46 24 / c7 06 vtbl / 89 46 28 / 89 46 18`, the barrier's own field
// wedged between the vftable and +0x18. And +0x18 cannot be made a barrier by
// itself: declaring it volatile, or writing it through a volatile lvalue,
// leaves the vptr store sinking to the head of the immediate-store group,
// because volatile orders only the volatile accesses among themselves and the
// compiler's own vptr store is not one of them. That last point is why
// novtable is load-bearing here rather than decorative -- it removes the
// compiler's vptr store from the problem so a hand-written one can hold a
// position. The hand-written store must be volatile ALONG WITH the members:
// probed plain, and probed volatile with plain members, it sinks to the head
// of the immediate group in both cases. Retail also puts +0x31 between +0x38
// and +0x40, which the written order reproduces for free.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h
class ClientUpdateModule
{
public:
	ClientUpdateModule( Thing *thing, const ModuleData *moduleData );

	virtual void clientUpdateModuleAnchor();

private:
	unsigned char m_unmodelled_04[ 0x0C - 4 ];
};

extern "C" char LaserUpdate_vftable;

class __declspec(novtable) LaserUpdate : public ClientUpdateModule
{
public:
	LaserUpdate( Thing *thing, const ModuleData *moduleData );

private:
	unsigned int m_startPosX;
	unsigned int m_startPosY;
	unsigned int m_startPosZ;
	unsigned int m_endPosX;
	unsigned int m_endPosY;
	unsigned int m_endPosZ;
	unsigned char m_dirty;
	unsigned char m_pad_25[ 3 ];
	unsigned int m_particleSystemID;
	unsigned int m_targetParticleSystemID;
	unsigned char m_widening;
	unsigned char m_decaying;
	unsigned char m_pad_32[ 2 ];
	unsigned int m_widenStartFrame;
	unsigned int m_widenFinishFrame;
	float m_currentWidthScalar;
	unsigned int m_decayStartFrame;
	unsigned int m_decayFinishFrame;
	unsigned int m_parentID;
	unsigned int m_targetID;
	unsigned int m_parentBoneNameData;
};

LaserUpdate::LaserUpdate( Thing *thing, const ModuleData *moduleData )
	: ClientUpdateModule( thing, moduleData )
{
	*reinterpret_cast<unsigned char volatile *>(&m_dirty) = 0;
	*reinterpret_cast<char *volatile *>(this) = &LaserUpdate_vftable;
	*reinterpret_cast<unsigned int volatile *>(&m_endPosX) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_endPosY) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_endPosZ) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_startPosX) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_startPosY) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_startPosZ) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_particleSystemID) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_targetParticleSystemID) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_widening) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_widenStartFrame) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_widenFinishFrame) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_decaying) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_decayStartFrame) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_decayFinishFrame) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_parentID) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_targetID) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_parentBoneNameData) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_currentWidthScalar) = 0x3F800000u;
}
