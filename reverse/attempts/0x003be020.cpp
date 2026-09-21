// ?run@Gen_003BE020@@QAEXPAX@Z
// partial score=0.34 date=2026-09-21
// cl: /DNDEBUG /MD

// Retail RVA 0x003BE020 (239 bytes). No named caller, vtable slot, string,
// or source emitter identifies this body's owner (tools/callers_of.py finds
// no reaching caller). This-relative fields proven: +0x0 (this object's own
// prefix, unused here beyond +0x28) and +0x28, a Rva003C9470Owner* -- the
// same class the already-landed Code/GameEngine/Source/Common/
// Rva003C9470StatusFallback.cpp gives fallback(Rva003C9470Key*,
// Rva003C9470Output*). The single stack parameter's own +0x4 offset is
// handed to fallback as the key, so the parameter is itself a
// key-plus-prefix wrapper whose layout is otherwise unproven.
//
// WHAT THE BYTES SHOW. fallback() fills a 2-float (x,y) output; the global
// g_bfmeStateDF (already typed in Rva006187D0MoveArmyToPosition.cpp) fills a
// Coord3D position through a second, previously-unrecorded vslot (+0x44).
// The position's x/y are reduced by fallback's output (z is left as-is), the
// three components are combined as sqrt(z*z + y*y + x*x) and scaled, then
// clamped: capped at 5.0f if the scaled distance is not below a threshold
// constant (0x01075344, no established name), and floored at g_bfmeDefaultBU
// if it is below that. The floored value is scaled again and handed both to
// g_bfmeStateDF's vslot +0x3C (as a rounded int, through the same __ftol2
// every retail float-to-int conversion in this codebase already uses) and
// to vslot +0x60 (as the float itself plus a second, unread output pointer).

typedef float Real;

struct Coord3D
{
	Real x, y, z;
};

class Rva003C9470Key;

struct Rva003C9470Output
{
	volatile Real m_x;
	volatile Real m_y;
};

class Rva003C9470Owner
{
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);
};

extern "C" float __cdecl sqrtf(float);

#define BFME_VSLOT(n) virtual void slot##n();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h (address-derived; no upstream match proven)
// Extends the view Code/GameEngine/Source/Common/Rva006187D0MoveArmyToPosition.cpp
// already established (dtor + slot04..slot1C + buildFramePoint at +0x20)
// with three more proven slots.
class BfmeStateDF
{
public:
	virtual ~BfmeStateDF();
	BFME_VSLOT(04) BFME_VSLOT(08) BFME_VSLOT(0C)
	BFME_VSLOT(10) BFME_VSLOT(14) BFME_VSLOT(18) BFME_VSLOT(1C)
	virtual void buildFramePoint(void *source, Coord3D *point);  // +0x20
	BFME_VSLOT(24) BFME_VSLOT(28) BFME_VSLOT(2C)
	BFME_VSLOT(30) BFME_VSLOT(34) BFME_VSLOT(38)
	virtual void reportRounded(int value);                       // +0x3C
	BFME_VSLOT(40)
	virtual void fillPosition(Coord3D *point);                    // +0x44
	BFME_VSLOT(48) BFME_VSLOT(4C) BFME_VSLOT(50) BFME_VSLOT(54)
	BFME_VSLOT(58) BFME_VSLOT(5C)
	virtual void reportFinal(Real value, void *unread);            // +0x60
};

#undef BFME_VSLOT

extern "C" BfmeStateDF *g_bfmeStateDF;

class Gen_003BE020
{
public:
	void run(void *param1);

private:
	unsigned char m_pad00[0x28];
	Rva003C9470Owner *m_owner;   // +0x28
};

#define g_bfmeDefaultBURef (*(const Real *)0x01075334)
#define g_bfme1075344Ref (*(const Real *)0x01075344)
#define g_bfme10E7F4CRef (*(const Real *)0x010E7F4C)
#define g_bfme108615CRef (*(const Real *)0x0108615C)

struct Rva003BE020Frame
{
	Real m_scratch;             // +0x0
	Rva003C9470Output m_out;    // +0x4
	Coord3D m_pos;               // +0xC
	Coord3D m_outPad;            // +0x18
};

// ?run@Gen_003BE020@@QAEXPAX@Z
void Gen_003BE020::run(void *param1)
{
	Rva003BE020Frame f;
	m_owner->fallback((Rva003C9470Key *)((unsigned char *)param1 + 4), &f.m_out);

	g_bfmeStateDF->fillPosition(&f.m_pos);

	f.m_pos.x -= f.m_out.m_x;
	f.m_outPad.x = f.m_out.m_x;
	f.m_pos.y -= f.m_out.m_y;
	f.m_outPad.y = f.m_out.m_y;
	f.m_outPad.z = 0.0f;

	Real distValue = sqrtf(f.m_pos.z * f.m_pos.z + f.m_pos.y * f.m_pos.y + f.m_pos.x * f.m_pos.x)
		* g_bfme10E7F4CRef;

	Real clamped1 = (distValue < g_bfme1075344Ref) ? distValue : 5.0f;
	Real clamped2 = (clamped1 < g_bfmeDefaultBURef) ? g_bfmeDefaultBURef : clamped1;
	Real final = clamped2 * g_bfme108615CRef;

	g_bfmeStateDF->reportRounded((int)final);
	g_bfmeStateDF->reportFinal(final, &f.m_scratch);
}
