// cl: /DNDEBUG /MD

// Open-BFME5: 49 more 66-byte __thiscall destructors of the shape already
// converted in game/GameEngine/Source/Common/V3MiDtorsWithListNode.cpp -- an
// IMPLICIT destructor of a class with three polymorphic bases, whose
// base-to-base pointer conversions keep the null-propagating
// test/je/lea/jmp/xor form, and whose first base tail-calls a list unlink:
//
//     eax = this ? this + <OFF3> : 0 ; [eax] = <VFTABLE 3>
//     if (this) { eax = this + 0x14; [eax] = <VFTABLE 2>; }
//     else      { eax = 0;           [eax] = <VFTABLE 2>; }
//     [this] = <VFTABLE 1> ; ecx = this + 4 ; jmp <unlink>
//
// The tail call is the same one that file identified: the REL32 reaches the
// incremental-link thunk at 0x00013994 and through it 0x001DA440, the matched
// ?unlink@GenNode_006fa270@@QAEXXZ.  So this file posits no new entity for it
// and mints no pin -- the node is re-declared with the same layout and the
// destructor resolves to the existing ledger row.
//
// The node runs AFTER the offset-0 vptr store, so it is a member of the FIRST
// base at offset 4, and the first base is 0x14 wide because that is where the
// second begins.  vptr(4) + node(12) leaves one dword unaccounted for, spelled
// as a pad.
//
// What is new here is how many second and third bases there are.  The earlier
// file saw one third-base vftable and two second-base ones; across these 49
// bodies there are 7 and 9.  The third base's OFFSET still tells the second
// base's width -- 0x18 for four bytes, 0x1C for eight -- and the offset-0
// vftable is 0x0111126C in every one of them, as it was there.
//
// IDENTITY IS NOT RECOVERED for the derived classes or for any of the bases.
// Their names come from the body address and from the vftable address the bytes
// store; every vftable dword is a DIR32 relocation site the gate takes from the
// target.

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
class V3Vt1073744
{
public:
	virtual void slot0();
	virtual ~V3Vt1073744() {}
};

// third base -- vftable 0x0107375C
class V3Vt107375C
{
public:
	virtual void slot0();
	virtual ~V3Vt107375C() {}
};

// third base -- vftable 0x01073760
class V3Vt1073760
{
public:
	virtual void slot0();
	virtual ~V3Vt1073760() {}
};

// third base -- vftable 0x0110F978
class V3Vt110F978
{
public:
	virtual void slot0();
	virtual ~V3Vt110F978() {}
};

// third base -- vftable 0x0110F9E4
class V3Vt110F9E4
{
public:
	virtual void slot0();
	virtual ~V3Vt110F9E4() {}
};

// third base -- vftable 0x0110F9E8
class V3Vt110F9E8
{
public:
	virtual void slot0();
	virtual ~V3Vt110F9E8() {}
};

// third base -- vftable 0x0110FA14
class V3Vt110FA14
{
public:
	virtual void slot0();
	virtual ~V3Vt110FA14() {}
};

// second base, width 4 -- vftable 0x0110F97C
class V3Vt110F97C
{
public:
	virtual void slot0();
	virtual ~V3Vt110F97C() {}
};

// second base, width 8 -- vftable 0x0110F9AC
class V3Vt110F9AC
{
public:
	virtual void slot0();
	virtual ~V3Vt110F9AC() {}
	int m_unreconstructed_04;
};

// second base, width 4 -- vftable 0x0110F9CC
class V3Vt110F9CC
{
public:
	virtual void slot0();
	virtual ~V3Vt110F9CC() {}
};

// second base, width 4 -- vftable 0x0111081C
class V3Vt111081C
{
public:
	virtual void slot0();
	virtual ~V3Vt111081C() {}
};

// second base, width 4 -- vftable 0x0111082C
class V3Vt111082C
{
public:
	virtual void slot0();
	virtual ~V3Vt111082C() {}
};

// second base, width 4 -- vftable 0x01110830
class V3Vt1110830
{
public:
	virtual void slot0();
	virtual ~V3Vt1110830() {}
};

// second base, width 4 -- vftable 0x01110834
class V3Vt1110834
{
public:
	virtual void slot0();
	virtual ~V3Vt1110834() {}
};

// second base, width 4 -- vftable 0x01110898
class V3Vt1110898
{
public:
	virtual void slot0();
	virtual ~V3Vt1110898() {}
};

// second base, width 4 -- vftable 0x0111089C
class V3Vt111089C
{
public:
	virtual void slot0();
	virtual ~V3Vt111089C() {}
};

#define V3_MI_NODE_DTOR( NAME, SECOND, THIRD )                            	class NAME : public V3NodeHead, public SECOND, public THIRD           	{                                                                     	public:                                                               		int m_v;                                                          	};                                                                    	void use##NAME()                                                      	{                                                                     		NAME t;                                                           		t.m_v = 1;                                                        	}

V3_MI_NODE_DTOR( Rva005DD400, V3Vt111081C, V3Vt1073760 )
V3_MI_NODE_DTOR( Rva005DD460, V3Vt111081C, V3Vt1073760 )
V3_MI_NODE_DTOR( Rva005DD6E0, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DD740, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DD7A0, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DD800, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DD860, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DD940, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DD9A0, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DDA00, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DDA60, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DDAC0, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005DDB20, V3Vt111082C, V3Vt110F9E4 )
V3_MI_NODE_DTOR( Rva005DDB80, V3Vt111082C, V3Vt110F9E4 )
V3_MI_NODE_DTOR( Rva005DDD00, V3Vt1110830, V3Vt107375C )
V3_MI_NODE_DTOR( Rva005DDD60, V3Vt1110830, V3Vt107375C )
V3_MI_NODE_DTOR( Rva005DEAE0, V3Vt1110834, V3Vt110FA14 )
V3_MI_NODE_DTOR( Rva005E2250, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E22B0, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2310, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2370, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2450, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E27C0, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2820, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2880, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E28E0, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2940, V3Vt110F9CC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E29A0, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2A00, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2A60, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2AC0, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2B20, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2DD0, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E2E30, V3Vt1110898, V3Vt110F978 )
V3_MI_NODE_DTOR( Rva005E2E90, V3Vt111089C, V3Vt110F9E8 )
V3_MI_NODE_DTOR( Rva005E4900, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E4960, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E49C0, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E4A20, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E4A90, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E4D20, V3Vt110F9AC, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E4D80, V3Vt1110898, V3Vt110F978 )
V3_MI_NODE_DTOR( Rva005E4E40, V3Vt111089C, V3Vt110F9E8 )
V3_MI_NODE_DTOR( Rva005E5AB0, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E5B40, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E5BD0, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E5C60, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E5D30, V3Vt110F97C, V3Vt1073744 )
V3_MI_NODE_DTOR( Rva005E6610, V3Vt110F9CC, V3Vt1073744 )
