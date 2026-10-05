// Open-BFME5 conversions.

class BfmeHub993
{
public:
	virtual void bfmeVH0993();
	virtual void bfmeVH1993();
	virtual void bfmeVH2993();
	virtual void bfmeVH3993();
	virtual void bfmeVH4993();
	virtual void bfmeVH5993();
	virtual void bfmeVH6993();
	virtual void bfmeVH7993();
	virtual void bfmeVH8993();
	virtual void bfmeVH9993();
	virtual void bfmeVH10993();
	virtual void bfmeVH11993();
	virtual void bfmeVH12993();
	virtual void bfmeVH13993();
	virtual void bfmeVH14993();
	virtual void bfmeVH15993();
	virtual void bfmeVH16993();
	virtual void bfmeVH17993();
	virtual void bfmeVH18993();
	virtual void bfmeVH19993();
	virtual void bfmeVH20993();
	virtual void bfmeVH21993();
	virtual void bfmeVH22993();
	virtual void bfmeVH23993();
	virtual void bfmeVH24993();
	virtual void bfmeVH25993();
	virtual void bfmeVH26993();
	virtual void bfmeVH27993();
	virtual void bfmeVH28993();
	virtual void bfmeVH29993();
	virtual void bfmeVH30993();
	virtual void bfmeVH31993();
	virtual void bfmeVH32993();
	virtual void bfmeVH33993();
	virtual void bfmeVH34993();
	virtual void bfmeVH35993();
	virtual void bfmeVH36993();
	virtual void bfmeVH37993();
	virtual void bfmeVH38993();
	virtual void bfmeVH39993();
	virtual void bfmeVH40993();
	virtual void bfmeVH41993();
	virtual void bfmeVH42993();
	virtual void bfmeVH43993();
	virtual void bfmeVH44993();
	virtual void bfmeVH45993();
	virtual void bfmeFix993(int r);
	virtual void bfmeVH47993();
	virtual void bfmeEnd993(int a, int b);
	virtual void bfmeVH49993();
	virtual void bfmeVH50993();
	virtual void bfmeVH51993();
	virtual void bfmeVH52993();
	virtual void bfmeVH53993();
	virtual void bfmeVH54993();
	virtual void bfmeVH55993();
	virtual void bfmeVH56993();
	virtual void bfmeVH57993();
	virtual void bfmeVH58993();
	virtual void bfmeVH59993();
	virtual int bfmeAsk993();
};

// The global at retail 0x012F148C is InGameUI *TheInGameUI, defined once in
// game/GameEngine/Source/GameClient/InGameUI.cpp.  Only the linked name may be
// referenced here; BfmeHub993 above stays as this TU's local view of the
// pointee, so the uses cast.
class InGameUI;

extern InGameUI *TheInGameUI;

class BfmeA993
{
public:
	void bfmeGo993A(int unused);

	char m_bfmePad[0x24];
	char m_bfmeOn;
};

void BfmeA993::bfmeGo993A(int unused)
{
	m_bfmeOn = 1;

	int r = ((BfmeHub993 *)TheInGameUI)->bfmeAsk993();

	if (!r)
		((BfmeHub993 *)TheInGameUI)->bfmeFix993(r);

	((BfmeHub993 *)TheInGameUI)->bfmeEnd993(0, 0);
}

// Both helpers bfmeGo993B reaches are called through retail's own
// incremental-link thunks, which the ledger owns as ?j_<rva>@@YAXXZ; retail
// carries no body name for either callee.
//
// The first takes only its object, so the thiscall is spelled as a
// one-argument __fastcall and the pointer still lands in ECX. The second also
// pushes eight arguments, so its object goes through a pointer-to-member taken
// out of a union, the pattern the other matched bodies in the tree already use.
extern void j_00008ed1();
extern void j_00015235();

// Both calls take their object through ECX only, so both go through a
// pointer-to-member taken out of a union; the tree's other matched bodies use
// the same pattern for retail thunks.
class BfmeAskB993;
class BfmeLog993;

// VC7.1 has no __thiscall function-pointer type, so each call is spelled as a
// pointer-to-member taken out of a union; the tree's other matched bodies use
// the same pattern for retail thunks.
class Rva00564700Receiver {};

typedef char (Rva00564700Receiver::*Rva00008ED1)();
typedef void (Rva00564700Receiver::*Rva00015235)(int, char *, int, char *, int, int, int, int);

template<class T> __forceinline T Rva00564700Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}
#define CALL993(T, obj, fn) (((Rva00564700Receiver*)(obj))->*Rva00564700Member<T>(fn))

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the log call through it, so the pointee stays the local BfmeLog993 view and
// the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

// Retail 0x012F4B98 is the AptPalantir singleton EA defines as
// `AptPalantir *TheAptPalantir` in
// game/GameEngine/Source/GameClient/GUI/AptPalantirConstructor.cpp; this TU
// only asks it a question, so the pointee stays the local BfmeAskB993 view and
// the access is cast at the use.
class AptPalantir;

extern AptPalantir *TheAptPalantir;
// Retail 0x012B7D80; canonical spelling `int g_aptPalantirWindow`
// (?g_aptPalantirWindow@@3HA), defined in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp.
extern int g_aptPalantirWindow;
// Retail 0x01081238 contains the NUL-terminated literal "0".
extern const char g_rva01080FC0[2];
extern char g_bfmeFmt993B[];

void bfmeGo993B(void)
{
	char asked = CALL993(Rva00008ED1, TheAptPalantir, j_00008ed1)();

	char *s = asked ? "0" : const_cast<char *>(g_rva01080FC0);

	CALL993(Rva00015235, g_rva012F19E8WindowManager, j_00015235)
		(g_aptPalantirWindow, g_bfmeFmt993B, 1, s, 0, 0, 0, 0);
}
