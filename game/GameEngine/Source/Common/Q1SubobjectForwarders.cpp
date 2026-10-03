// Ten sixteen-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DELTA>+4] / mov ecx,[ecx+<DELTA>] / push eax
//     add ecx,<INNER> / call <REL32> / ret
//
// WHAT THE BYTES SHOW.  Two ADJACENT dwords are read relative to `this`: the
// second one becomes the receiver, the first becomes the argument.  `add ecx`
// then walks the receiver forward by a fixed amount before the call -- an
// addition, not a load, so the callee`s `this` is a SUB-OBJECT OF the pointed-to
// object, at a fixed offset inside it.  The call is followed immediately by
// `ret` with no stack adjustment, so the callee is __thiscall and pops the
// pushed dword.
//
// THREE AXES: the delta at which the pair of dwords sits, the inner offset
// added to the receiver, and the callee.  Only TWO distinct callees appear
// (0x0002E320 and 0x0002EB4F), five members each, and they interleave with the
// inner offsets rather than tracking them -- so the callee is genuinely its own
// axis and not a function of the layout.
//
// WHAT THE BYTES CANNOT DECIDE.  Six of the ten reach their dword pair at a
// NEGATIVE delta (-0x28, -0x1C, -0x14) and four at a positive one (+0x0C).
// Nothing in the bytes says why, exactly as in Q1GuardedReoffsetGetters.cpp, so
// the pair is reached by explicit pointer arithmetic and no inheritance
// relationship is claimed.  The argument is spelled `int`; a pointer compiles
// identically.  Both call targets are five-byte incremental-link thunks in
// retail rather than function bodies, which is what the call sites actually
// encode, so that is what the pins name.
//
// THE CALLEES ARE IDENTIFIED.  Both call targets are ILT thunks into the
// matched UpgradeMuxData bodies: 0x0002E320 -> muxDataProcessUpgradeRemoval
// (0x002D9C40) and 0x0002EB4F -> performUpgradeFX (0x002D9B30), both
// `void __thiscall (Object *) const`.  The pushed dword is that Object*, not
// an int.  The forwarders' own names stay address-derived.

class Object;

// upstream layout: game/GameEngine/Source/Common/Thing/UpgradeMuxData.cpp
class UpgradeMuxData
{
public:
	void performUpgradeFX(Object *object) const;
	void muxDataProcessUpgradeRemoval(Object *object) const;
};

#define Q1_SUBOBJECT_FORWARD( NAME, METHOD, DELTA, INNER )                \
	class Owner##NAME                                                     \
	{                                                                     \
	public:                                                               \
		char m_lead[ INNER ];                                             \
		UpgradeMuxData m_target;                                          \
	};                                                                    \
	class Pair##NAME                                                      \
	{                                                                     \
	public:                                                               \
		Owner##NAME *m_owner;                                             \
		Object *m_value;                                                  \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void go();                                                        \
	};                                                                    \
	void NAME::go()                                                       \
	{                                                                     \
		Pair##NAME *pair = (Pair##NAME *)( (char *)this + ( DELTA ) );    \
		pair->m_owner->m_target.METHOD( pair->m_value );                  \
	}

Q1_SUBOBJECT_FORWARD( Rva0020A9E0, muxDataProcessUpgradeRemoval, -40, 0x58 )
Q1_SUBOBJECT_FORWARD( Rva0027FFF0, performUpgradeFX, -28, 0x28 )
Q1_SUBOBJECT_FORWARD( Rva00280020, muxDataProcessUpgradeRemoval, -28, 0x28 )
Q1_SUBOBJECT_FORWARD( Rva0020A9B0, performUpgradeFX, -40, 0x58 )
Q1_SUBOBJECT_FORWARD( Rva00289AB0, performUpgradeFX, -28, 0x2C )
Q1_SUBOBJECT_FORWARD( Rva00289AE0, muxDataProcessUpgradeRemoval, -28, 0x2C )
Q1_SUBOBJECT_FORWARD( Rva002D3500, performUpgradeFX, -28, 0x14 )
Q1_SUBOBJECT_FORWARD( Rva002D3530, muxDataProcessUpgradeRemoval, -28, 0x14 )
Q1_SUBOBJECT_FORWARD( Rva002D6D10, performUpgradeFX, 12, 0x10 )
Q1_SUBOBJECT_FORWARD( Rva002D6D40, muxDataProcessUpgradeRemoval, 12, 0x10 )
