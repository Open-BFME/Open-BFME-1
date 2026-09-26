// cl: /DNDEBUG /MD
// Ten 66-byte __thiscall destructors, one shape, two variants.  Retail:
//
//     eax = this ? this + <OFF3> : 0 ; [eax]   = <VFTABLE 3>
//     if (this) { eax = this + 0x14; [eax] = <VFTABLE 2>; }
//     else      { eax = 0;           [eax] = <VFTABLE 2>; }
//     [this] = <VFTABLE 1> ; ecx = this + 4 ; jmp <unlink>
//
// Same family as BigMiImplicitDtors.cpp -- an IMPLICIT destructor of a class
// with three polymorphic bases, whose base-to-base pointer conversions keep the
// null-propagating test/je/lea/jmp/xor form -- with ONE extra fact: the first
// base's inlined destructor does not end at its vptr store, it tail-calls a
// function at this+4.
//
// THE TAIL CALL IS ALREADY IDENTIFIED IN THE TREE.  The REL32 encodes the
// incremental-link thunk 0x00013994, which jumps to 0x001DA440 -- the matched
// row ?unlink@GenNode_006fa270@@QAEXXZ, the 12-byte intrusive doubly-linked
// list node whose owner keeps head at +0x98 and tail at +0x9C (see
// game/GameEngine/Source/Common/Gen_006fa270.cpp).  That file's node already
// spells `~GenNode_006fa270(void) { unlink(); }`, which is exactly the shape
// needed here, so this file posits NO new entity and mints NO pin: the node is
// re-declared with the same layout and the destructor resolves to the existing
// ledger row.  (unlink is declared without its body here so that this TU emits
// no second copy of that COMDAT.)
//
// WHERE THE NODE SITS.  The call runs AFTER the offset-0 vptr store, i.e. after
// the last base destructor has begun, not before the bases as a member of the
// derived class would.  So the node is a member of the FIRST base, at offset 4,
// and the first base is 0x14 bytes wide because that is where the second base
// starts.  vptr(4) + node(12) leaves one dword of the first base unaccounted
// for; it is spelled as a pad int.
//
// TWO VARIANTS, exactly the BigMi axis: the third base sits at 0x18 or 0x1C, so
// the second base is four or eight bytes wide, and the second base's vftable
// changes with it (0x0110F9CC at width 4, 0x0110F9AC at width 8).  The offset-0
// vftable (0x0111126C) and the third base's (0x01073744) are the same address
// in all ten bodies, so those two classes are declared once.
//
// ONE CLASS PER ROW.  The four width-4 bodies are byte-identical to each other
// and so are the six width-8 bodies; one class cannot have two destructor
// bodies, so each row gets its own derived class, exactly as
// Q2MultipleBaseVtableSetters.cpp and BigMiImplicitDtors.cpp do.
//
// IDENTITY IS NOT RECOVERED for the derived classes or for the three bases;
// their names come from the body address and from the vftable address the bytes
// store.  All vftable dwords are DIR32 relocation sites the gate takes from the
// target.

// The three-base implicit destructor inlines the head's, which needs the node's
// inline destructor; this TU emits it out of line and no ledger row claims it here.
// ??1GenNode_006fa270@@QAE@XZ present-unmatched

struct GenOwner_006fa270;

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner;	// +0
	GenNode_006fa270 *m_prev;	// +4
	GenNode_006fa270 *m_next;	// +8

	void unlink(void);

	~GenNode_006fa270(void) { unlink(); }
};

// first base -- vftable 0x0111126C, 0x14 bytes wide
class V3NodeHead
{
public:
	virtual ~V3NodeHead() {}
	GenNode_006fa270 m_node;		// +4
	int m_unreconstructed_10;		// +0x10
};

// third base -- vftable 0x01073744
class V3Vt01073744
{
public:
	virtual void slot0();
	virtual ~V3Vt01073744() {}
};

// second base, width 4 -- vftable 0x0110F9CC
class V3Vt0110F9CC
{
public:
	virtual void slot0();
	virtual ~V3Vt0110F9CC() {}
};

// second base, width 8 -- vftable 0x0110F9AC
class V3Vt0110F9AC
{
public:
	virtual void slot0();
	virtual ~V3Vt0110F9AC() {}
	int m_unreconstructed_04;
};

#define V3_MI_NODE_DTOR( NAME, SECOND )                                   \
	class NAME : public V3NodeHead, public SECOND, public V3Vt01073744    \
	{                                                                     \
	public:                                                               \
		int m_v;                                                          \
	};                                                                    \
	void use##NAME()                                                      \
	{                                                                     \
		NAME t;                                                           \
		t.m_v = 1;                                                        \
	}

V3_MI_NODE_DTOR( Rva005E6700, V3Vt0110F9CC )
V3_MI_NODE_DTOR( Rva005E67F0, V3Vt0110F9CC )
V3_MI_NODE_DTOR( Rva005E68E0, V3Vt0110F9CC )
V3_MI_NODE_DTOR( Rva005E69D0, V3Vt0110F9CC )
V3_MI_NODE_DTOR( Rva005E6AD0, V3Vt0110F9AC )
V3_MI_NODE_DTOR( Rva005E6BD0, V3Vt0110F9AC )
V3_MI_NODE_DTOR( Rva005E6CD0, V3Vt0110F9AC )
V3_MI_NODE_DTOR( Rva005E6DD0, V3Vt0110F9AC )
V3_MI_NODE_DTOR( Rva005E6ED0, V3Vt0110F9AC )
V3_MI_NODE_DTOR( Rva005E7110, V3Vt0110F9AC )
