// cl: /DNDEBUG /MD /GX
// Fuzzy-twin lane: near-twin of createTheNetwork (retail 0x00682320,
// game/GameEngine/Source/GameNetwork/createTheNetwork.cpp) -- same
// operator-new-then-construct-then-vcall(+4) factory shape, but this one:
//   - allocates 0x584 bytes (not 0x40) via ctor thunk 0x0002E7CB
//   - stores into the already address-derived global
//     ?Glo012F4B98@@3PAVGlo012F4B98Type@@A (0x012F4B98, targets/game/reverse/symbols.csv),
//     not TheNetwork
//   - has no "if (existing) delete existing" guard before the new
// Glo012F4B98Type already has several members pinned by address
// (deleteBuildTooltipLayout sub-object @+0x488, report, notifyTarget) from
// prior sessions; this TU only needs size and the vtable slot this body
// proves (a virtual init-like method at slot +4).

// The ctor call (ILT 0x2E7CB) lands on 0x0079D9F0, matched
// ??0AptPalantir@@QAE@XZ (AptPalantirConstructor.cpp): the object is an AptPalantir.
class AptPalantir
{
public:
	AptPalantir();
	virtual ~AptPalantir();
	virtual void init();

private:
	unsigned char m_unreconstructed[0x584 - 4];
};

extern AptPalantir *TheAptPalantir;

// ?Rva006FC330@@YAXXZ -- address-derived TAG, identity unresolved
void Rva006FC330(void)
{
	TheAptPalantir = new AptPalantir;
	TheAptPalantir->init();
}
