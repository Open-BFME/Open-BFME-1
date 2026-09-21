// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

enum ObjectID { INVALID_ID = 0 };
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
enum LivingWorldID { INVALID_LIVING_WORLD_ID = 0 };

struct Coord3D { unsigned int x, y, z; };

extern void j_00025306(void);
extern void j_0002c5cf(void);
extern void j_00026f35(void);

// Retail 0x000B2CC0 (AudioEventRTS::AudioEventRTS(const AsciiString&, int),
// landed in AudioEventRTSCopyAndLifetime.cpp) and 0x000B31F0 (~AudioEventRTS,
// landed there too) are both reached here through their own ILT thunks, same
// idiom as Rva003720F0AudioRefresh.cpp's Rva003720F0EventStorage.
class Rva0051BCE0EventStorage
{
public:
	Rva0051BCE0EventStorage(const AsciiString &name, int extra)
	{
		typedef void (Rva0051BCE0EventStorage::*ConstructCall)(const AsciiString &, int);
		union { void *address; ConstructCall member; } call;
		call.address = (void *)j_00025306;
		(this->*call.member)(name, extra);
	}
	~Rva0051BCE0EventStorage()
	{
		typedef void (Rva0051BCE0EventStorage::*DestroyCall)();
		union { void *address; DestroyCall member; } call;
		call.address = (void *)j_00026f35;
		(this->*call.member)();
	}

	void setIsLogicalAudio(bool value)
	{
		typedef void (Rva0051BCE0EventStorage::*SetCall)(bool) throw();
		union { void *address; SetCall member; } call;
		call.address = (void *)j_0002c5cf;
		(this->*call.member)(value);
	}

	unsigned char m_storage[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h (TheAudioClientUpdate's real class)
// TU-local partial vtable: only slots 22 and 33 are proven by this body.
class Rva005A00B0AudioClient
{
public:
#define AC_SLOT(n) virtual void slot##n()
	AC_SLOT(00); AC_SLOT(01); AC_SLOT(02); AC_SLOT(03); AC_SLOT(04);
	AC_SLOT(05); AC_SLOT(06); AC_SLOT(07); AC_SLOT(08); AC_SLOT(09);
	AC_SLOT(10); AC_SLOT(11); AC_SLOT(12); AC_SLOT(13); AC_SLOT(14);
	AC_SLOT(15); AC_SLOT(16); AC_SLOT(17); AC_SLOT(18); AC_SLOT(19);
	AC_SLOT(20); AC_SLOT(21);
#undef AC_SLOT
	virtual void slot22(const void *event) throw();
#define AC_SLOT(n) virtual void slot##n()
	AC_SLOT(23); AC_SLOT(24); AC_SLOT(25); AC_SLOT(26); AC_SLOT(27);
	AC_SLOT(28); AC_SLOT(29); AC_SLOT(30); AC_SLOT(31); AC_SLOT(32);
#undef AC_SLOT
	virtual bool slot33();
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class Display;
extern Display *TheDisplay;

extern void j_00044a53(void);

// Retail 0x0040FD20 BfmeStrVM0::bfmeFlagVM0(unsigned char), landed in
// BfmeConv1435.cpp under a different owner name (ICF-folded); reached here
// through its own ILT thunk with TheDisplay as "this".
class Rva0051BCE0DisplayThunk
{
public:
	void bfmeFlagVM0(unsigned char on)
	{
		typedef void (Rva0051BCE0DisplayThunk::*Fn)(unsigned char);
		union { void (*freeFn)(void); Fn memberFn; } thunk;
		thunk.freeFn = j_00044a53;
		(this->*thunk.memberFn)(on);
	}
};

// Retail 0x0051BCE0 (173B, bounds-high carved dump): __stdcall with one
// unused parameter (matches "ret 4" with no register/stack read of it,
// consistent with a fixed-signature callback). If the audio client's slot33
// query is false, build an AudioEventRTS("Shell2Music", 2) -- the string at
// 0x011060B0 is the Shell menu's background-music event name -- flag it
// non-logical, and dispatch it through the audio client's slot22. Either way,
// flag the display through BfmeStrVM0::bfmeFlagVM0(1). No caller, class or
// method identity survived the identity sweep (blocked once: "bounds-high
// generated dump row has no named caller, source emitter, or independently
// proven owner", t=10m model=Codex); every name here is address-derived.
void __stdcall Rva0051BCE0(void *unused)
{
	if (!TheAudioClientUpdate->slot33())
	{
		Rva0051BCE0EventStorage event(AsciiString("Shell2Music"), 2);
		event.setIsLogicalAudio(false);
		TheAudioClientUpdate->slot22(&event);
	}

	((Rva0051BCE0DisplayThunk *)TheDisplay)->bfmeFlagVM0(1);
}
