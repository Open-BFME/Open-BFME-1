// cl: /DNDEBUG /MD /GX
// Fuzzy-twin lane: near-twin of createTheNetwork (retail 0x00682320,
// Code/GameEngine/Source/GameNetwork/createTheNetwork.cpp) -- same
// operator-new-then-construct-then-vcall(+4) factory shape, but this one:
//   - allocates 0x584 bytes (not 0x40) via ctor thunk 0x0002E7CB
//   - stores into the already address-derived global
//     ?Glo012F4B98@@3PAVGlo012F4B98Type@@A (0x012F4B98, reverse/symbols.csv),
//     not TheNetwork
//   - has no "if (existing) delete existing" guard before the new
// Glo012F4B98Type already has several members pinned by address
// (deleteBuildTooltipLayout sub-object @+0x488, report, notifyTarget) from
// prior sessions; this TU only needs size and the vtable slot this body
// proves (a virtual init-like method at slot +4).

class Glo012F4B98Type
{
public:
	Glo012F4B98Type();
	virtual ~Glo012F4B98Type();
	virtual void init();

private:
	unsigned char m_unreconstructed[0x584 - 4];
};

extern Glo012F4B98Type *Glo012F4B98;

// ?Rva006FC330@@YAXXZ -- address-derived TAG, identity unresolved
void Rva006FC330(void)
{
	Glo012F4B98 = new Glo012F4B98Type;
	Glo012F4B98->init();
}
