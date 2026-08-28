// cl: /DNDEBUG /MD /EHsc

// Open-BFME1: W3DDebrisDraw module ctor.
//
// Shape: `class W3DDebrisDraw : public DrawModule, public DebrisDrawInterface`.
// DrawModule owns +0x00..+0x0B (vptr + two words) and its ctor is the pinned
// call; DebrisDrawInterface is a second polymorphic base at +0x0C -- proved by
// that slot being written twice, once by the base's own inlined default ctor
// (+0x0C = its vftable) and once by the derived vptr pair (+0x00, +0x0C).
// Members run +0x10..+0x47 and mirror the Generals W3DDebrisDraw.h field list.
//
// Retail emits, in strict source order:
//   [+0x0C]=iface vftable, [+0x00]=primary, [+0x0C]=secondary,
//   [+0x10]=0, [+0x14]=-1, [+0x18]=0 ... [+0x44]=0, then m_anims[0..2].
// MSVC 7.1 will not reproduce that from the natural spelling: `mov mem, imm32`
// stores it considers unread sink to the end of the block, so both derived vptr
// writes and the m_modelColor(-1) write end up after every `mov mem, eax`. Only
// volatile stores keep their relative order, so:
//   * the class is __declspec(novtable) and the two derived vptr writes are
//     spelled explicitly as volatile stores at their retail offsets (they carry
//     the same DIR32 vftable relocations retail does), and
//   * the members are volatile so the -1 store stays wedged between the zero
//     stores instead of being hoisted over.
// The instruction stream is unchanged by either device; both only pin order.

class Thing;
class ModuleData;
class Drawable;

// The two vftables W3DDebrisDraw installs. Only the relocation site matters
// here -- the linker-resolved address is supplied by retail.
extern int W3DDebrisDraw_vftable;
extern int W3DDebrisDraw_DebrisDrawInterface_vftable;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void drawModuleAnchor();
	DrawModule(Thing *, const ModuleData *);

protected:
	const ModuleData *m_moduleData;				///< retail this+0x04
	Drawable *m_drawable;						///< retail this+0x08
};

// Polymorphic and not novtable: retail stores this base's own vftable at +0x0C
// before the derived pair of vptr writes.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DebrisDrawInterface
{
public:
	virtual void debrisDrawInterfaceAnchor();
};

class __declspec(novtable) W3DDebrisDraw : public DrawModule, public DebrisDrawInterface
{
public:
	W3DDebrisDraw(Thing *thing, const ModuleData *moduleData);

private:
	void *volatile m_modelName;					///< retail this+0x10
	volatile int m_modelColor;					///< retail this+0x14
	void *volatile m_animInitial;				///< retail this+0x18
	void *volatile m_animFlying;				///< retail this+0x1c
	void *volatile m_animFinal;					///< retail this+0x20
	void *volatile m_renderObject;				///< retail this+0x24
	void *volatile m_anims[3];					///< retail this+0x28 .. +0x30
	void *volatile m_fxFinal;					///< retail this+0x34
	volatile int m_state;						///< retail this+0x38
	volatile int m_frames;						///< retail this+0x3c
	volatile bool m_finalStop;					///< retail this+0x40
	void *volatile m_shadow;					///< retail this+0x44
};

// ??0W3DDebrisDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DDebrisDraw::W3DDebrisDraw(Thing *thing, const ModuleData *moduleData)
	: DrawModule(thing, moduleData)
{
	*(void *volatile *)this = &W3DDebrisDraw_vftable;
	*(void *volatile *)((char *)this + 12) = &W3DDebrisDraw_DebrisDrawInterface_vftable;
	m_modelName = 0;
	m_modelColor = -1;
	m_animInitial = 0;
	m_animFlying = 0;
	m_animFinal = 0;
	m_renderObject = 0;
	m_fxFinal = 0;
	m_state = 0;
	m_frames = 0;
	m_finalStop = false;
	m_shadow = 0;
	m_anims[0] = 0;
	m_anims[1] = 0;
	m_anims[2] = 0;
}
