// cl: /DNDEBUG /MD /EHsc
// BFME shadow-enable toggle helper, retail 0x006FE140 (150 bytes).
//
// Identity: "this" calls the already-landed Gen_006091B0::bfmeSetEnabled(bool)
// and BfmeThingEMH::bfmeGoEMHa/bfmeGoEMHb(void) (both taking ecx=this with no
// mismatch), so this object shares layout with those callees' "this". The
// g_bfmeGameCW singleton (0x012F706C, already named) is used only as the
// implicit "this" for two BfmeLivingWorldManager particle-system calls; a
// second global at 0x01306EEC (no existing symbol; called as the implicit
// "this" for the landed W3DShadowManager::setTimeOfDay/setLightPosition) is
// declared address-derived here. No caller or vtable slot proves the owning
// method name, so the class and method stay address-derived.

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;
typedef float Real;

extern void j_00044968(void); // Gen_006091B0::bfmeSetEnabled(bool), ecx=this
extern void j_000342a7(void); // BfmeLivingWorldManager::rva00617e30(void), ecx=g_bfmeGameCW
extern void j_0001e312(void); // BfmeLivingWorldManager::rva00617c60(void), ecx=g_bfmeGameCW
extern void j_0003e42d(void); // W3DShadowManager::setTimeOfDay(TimeOfDay), ecx=g_bfmeTheShadowManager
extern void j_0002412c(void); // BfmeThingEMH::bfmeGoEMHb(void), ecx=this
extern void j_0004248d(void); // BfmeThingEMH::bfmeGoEMHa(void), ecx=this
extern void j_00031840(void); // W3DShadowManager::setLightPosition(int,float,float,float), ecx=g_bfmeTheShadowManager

#define g_bfmeGameCW (*(void **)0x012F706C)
#define g_bfmeTheShadowManager (*(void **)0x01306EEC)
#define TheWritableGlobalData (*(unsigned char **)0x012ED5C8)

class Rva006FE140Owner
{
public:
	void rva006fe140(Bool enable);

private:
	unsigned char m_pad0000[8];
	Bool m_enabled;
	unsigned char m_pad0009[0x14c - 9];
	Real m_lightX;
	Real m_lightY;
	Real m_lightZ;
};

template <typename Ret, typename Recv>
static Ret CallOn(Recv *object, void (*function)(void))
{
	union {
		void (*plain)(void);
		Ret (Recv::*member)(void);
	} cast;
	cast.plain = function;
	return (object->*cast.member)();
}

template <typename Ret, typename Recv, typename Arg>
static Ret CallOn(Recv *object, void (*function)(void), Arg arg)
{
	union {
		void (*plain)(void);
		Ret (Recv::*member)(Arg);
	} cast;
	cast.plain = function;
	return (object->*cast.member)(arg);
}

template <typename Ret, typename Recv, typename A0, typename A1, typename A2, typename A3>
static Ret CallOn(Recv *object, void (*function)(void), A0 a0, A1 a1, A2 a2, A3 a3)
{
	union {
		void (*plain)(void);
		Ret (Recv::*member)(A0, A1, A2, A3);
	} cast;
	cast.plain = function;
	return (object->*cast.member)(a0, a1, a2, a3);
}

// ?rva006fe140@Rva006FE140Owner@@QAEXE@Z
void Rva006FE140Owner::rva006fe140(Bool enable)
{
	if (m_enabled == enable)
		return;

	CallOn<void>(this, j_00044968, enable);

	if (enable)
		CallOn<void>(reinterpret_cast<Rva006FE140Owner *>(g_bfmeGameCW), j_000342a7);
	else
		CallOn<void>(reinterpret_cast<Rva006FE140Owner *>(g_bfmeGameCW), j_0001e312);

	if (g_bfmeTheShadowManager == 0)
		return;

	if (*(UnsignedByte *)((unsigned char *)g_bfmeGameCW + 0x164) == 0)
		return;

	if (!enable) {
		Int timeOfDay = *(Int *)(TheWritableGlobalData + 0x218);
		CallOn<void>(reinterpret_cast<Rva006FE140Owner *>(g_bfmeTheShadowManager),
			j_0003e42d, timeOfDay);
		CallOn<void>(this, j_0002412c);
	} else {
		CallOn<void>(this, j_0004248d);
		CallOn<void>(reinterpret_cast<Rva006FE140Owner *>(g_bfmeTheShadowManager),
			j_00031840, 0, m_lightX, m_lightY, m_lightZ);
	}
}
