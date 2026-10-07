// Open-BFME5 conversions.

class Object;
struct BfmeArg1002;

struct BfmeSub1002
{
	char m_bfmePad[0x10];
	int m_bfmeVal;
};

struct BfmeX1002
{
	char m_bfmePad[4];
	BfmeSub1002 *m_bfmeSub;
};

class HordeContain
{
protected:
	void checkSpecialUnitDeath(const Object &obj);

public:
	char m_bfmePad[0x1b4];
	int m_bfmeA;
	char m_bfmePad2[4];
	int m_bfmeB;
	char m_bfmePad3[0xc];
	int m_bfmeC;
};

struct BfmeArg1002
{
	char m_bfmePad[0x74];
	int m_bfmeId;
};

// Retail's call at +0x35 of ?checkSpecialUnitDeath@HordeContain@@IAEXABVObject@@@Z
// lands on the ILT thunk ?j_0003f5da@@YAXXZ (0x0003F5DA), whose matched
// five-byte body lives in game/gen_small/thunks_030.cpp.  That decorated
// symbol is what the call must relocate against, so the reference is spelled
// with that name; VC7.1 reserves __thiscall in a free-function-pointer
// typedef, so the pointer-to-member cast idiom (as
// GameEngineDevice/Source/W3DDevice/GameClient/RTS3DScene_Render_Thunk.cpp
// uses for the same ?j_0002d961@@YAXXZ ILT) keeps the proven shape: ECX holds
// the receiver and the single argument stays on the stack for the callee to
// pop.
extern void j_0003f5da();
struct BfmeFindThunk1002 { BfmeX1002 *Call(BfmeArg1002 *arg); };
typedef BfmeX1002 *(BfmeFindThunk1002::*BfmeFindCall1002)(BfmeArg1002 *arg);

// EA's name (ea_evidence.csv); retail's thunk table confirms the protected
// const Object& decoration, and Object+0x74 is m_id.
void HordeContain::checkSpecialUnitDeath(const Object &obj)
{
	BfmeArg1002 *a = (BfmeArg1002 *)&obj;
	int id = a->m_bfmeId;

	if (m_bfmeA == id) {
		m_bfmeA = 0;
		return;
	}

	if (m_bfmeB != id)
		return;

	m_bfmeB = 0;

	union { void (*asFunction)(); BfmeFindCall1002 asMember; } fnCast;
	fnCast.asFunction = j_0003f5da;
	BfmeX1002 *x = (reinterpret_cast<BfmeFindThunk1002 *>(this)->*fnCast.asMember)(a);

	if (x)
		m_bfmeC = x->m_bfmeSub->m_bfmeVal;
}

// Retail spells this accessor ?getFinalOverride@Overridable@@QBEPBV1@XZ
// (public const, upstream Overridable.h); the TU-local stand-in is the class
// that owns it, so it takes the defining class/member name.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

struct BfmeVal1002
{
	char m_bfmePad[4];
	Overridable *m_bfmeMid;
	char m_bfmePad2[0xcc];
	int m_bfmeFlags;
};

struct BfmeHold1002
{
	char m_bfmePad[4];
	BfmeVal1002 *m_bfmeVal;
};

class BfmeB1002
{
public:
	char bfmeGo1002B(BfmeHold1002 *a, int b);
};

// The second retail call, at +0x35 of
// ?bfmeGo1002B@BfmeB1002@@QAEDPAUBfmeHold1002@@H@Z, lands on the ILT thunk
// ?j_0000583a@@YAXXZ (0x0000583A, game/gen_small/thunks_002.cpp): the
// receiver in ECX and the two arguments on the stack, popped by the callee.
extern void j_0000583a();
struct BfmeSendThunk1002 { char Call(BfmeHold1002 *arg, int value); };
typedef char (BfmeSendThunk1002::*BfmeSendCall1002)(BfmeHold1002 *arg, int value);

char BfmeB1002::bfmeGo1002B(BfmeHold1002 *a, int b)
{
	BfmeVal1002 *p = a->m_bfmeVal;

	if (p && p->m_bfmeMid)
		p = const_cast<BfmeVal1002 *>(
			reinterpret_cast<const BfmeVal1002 *>( p->m_bfmeMid->getFinalOverride() ) );

	if (p->m_bfmeFlags & 0x1000)
		return 0;

	union { void (*asFunction)(); BfmeSendCall1002 asMember; } fnCast;
	fnCast.asFunction = j_0000583a;
	return (reinterpret_cast<BfmeSendThunk1002 *>(this)->*fnCast.asMember)(a, b);
}
