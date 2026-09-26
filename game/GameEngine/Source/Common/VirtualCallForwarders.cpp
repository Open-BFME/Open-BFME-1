// 33 small bodies that do nothing but re-dispatch a virtual call, in four
// shapes:
//
//     mov ecx,[ecx+<D>] / mov eax,[ecx] / jmp [eax+<SLOT>]     (9)
//     mov ecx,[<address>] / mov eax,[ecx] / jmp [eax+<SLOT>]   (14)
//     mov eax,[ecx] / jmp [eax+<SLOT>]                          (3)
//     mov eax,[ecx+<D>] / add ecx,<D> / jmp [eax+<SLOT>]        (7)
//
// WHAT THE BYTES SHOW.  A vftable is loaded and one slot of it jumped to, with
// no argument touched and nothing pushed: a tail call, so whatever arguments
// the caller passed go through unchanged and the return value is whatever the
// callee returns.  The four shapes differ only in what supplies the object --
// a pointer member, a .data global, `this` itself, or `this` displaced by a
// fixed amount, which is the interior-pointer form and is spelled here as the
// cast it is.
//
// THE CALLEE IS A SLOT, NOT A NAME.  The only thing the instruction stream says
// about the function being called is its byte offset in the vftable, so the
// dispatch target is declared here as a class with the right number of virtual
// members and the call goes to the one at that offset.  `v22` means slot 0x58
// and nothing else; the count of members ahead of it is what places it, and
// none of them is claimed to exist under any name.  Return types are spelled
// `void` because a tail call reveals nothing about them.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class VDispatch
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
};

#define BFME_VCALL_MEMBER( NAME, LEAD, SLOT )                                 \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void forward();                                                       \
                                                                              \
		char       m_lead[ LEAD ];                                            \
		VDispatch *m_target;                                                  \
	};                                                                        \
	void NAME::forward() { m_target->SLOT(); }

#define BFME_VCALL_MEMBER_AT_ZERO( NAME, SLOT )                               \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void forward();                                                       \
                                                                              \
		VDispatch *m_target;                                                  \
	};                                                                        \
	void NAME::forward() { m_target->SLOT(); }

#define BFME_VCALL_SELF( NAME, SLOT )                                         \
	class NAME : public VDispatch                                             \
	{                                                                         \
	public:                                                                   \
		void forward();                                                       \
	};                                                                        \
	void NAME::forward() { SLOT(); }

#define BFME_VCALL_INTERIOR( NAME, DELTA, SLOT )                              \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void forward();                                                       \
	};                                                                        \
	void NAME::forward()                                                      \
	{                                                                         \
		( (VDispatch *)( (char *)this + ( DELTA ) ) )->SLOT();                \
	}

BFME_VCALL_MEMBER( Rva0026F5E0VCall, 0x30, v12 )
BFME_VCALL_MEMBER( Rva002B77C0VCall, 0x28, v4 )
BFME_VCALL_MEMBER( Rva002C8100VCall, 0x424, v6 )
BFME_VCALL_MEMBER( Rva002C8110VCall, 0x420, v6 )
BFME_VCALL_MEMBER( Rva0043BC30VCall, 0x81C, v4 )
BFME_VCALL_MEMBER_AT_ZERO( Rva0048E360VCall, v4 )
BFME_VCALL_MEMBER( Rva00537F20VCall, 0x40, v6 )
BFME_VCALL_MEMBER( Rva005A4410VCall, 0x4DAC, v5 )
BFME_VCALL_MEMBER( Rva007E3A50VCall, 0x2C, v0 )

extern VDispatch *g_Va012F076C;
extern VDispatch *g_Va012F079C;
extern VDispatch *g_Va012F1270;
extern VDispatch *g_Va012F148C;
extern VDispatch *g_Va012F1600;
extern VDispatch *g_Va012F7014;
extern VDispatch *g_Va01336E5C;

void Rva0005BBA0VCall( void )
{
	g_Va01336E5C->v24();
}

void Rva0005BBD0VCall( void )
{
	g_Va01336E5C->v29();
}

void Rva001A3480VCall( void )
{
	g_Va012F7014->v44();
}

void Rva002EDB10VCall( void )
{
	g_Va012F1270->v42();
}

void Rva002EDB30VCall( void )
{
	g_Va012F1270->v43();
}

void Rva002EE860VCall( void )
{
	g_Va012F148C->v77();
}

void Rva002EF6A0VCall( void )
{
	g_Va012F148C->v20();
}

void Rva002EFAD0VCall( void )
{
	g_Va012F1600->v56();
}

void Rva002F0550VCall( void )
{
	g_Va012F076C->v21();
}

void Rva002F06C0VCall( void )
{
	g_Va012F1600->v40();
}

void Rva00323070VCall( void )
{
	g_Va012F079C->v13();
}

void Rva00323080VCall( void )
{
	g_Va012F079C->v14();
}

void Rva008894F0VCall( void )
{
	g_Va01336E5C->v39();
}

BFME_VCALL_SELF( Rva0040DA70VCall, v31 )
BFME_VCALL_SELF( Rva0043B420VCall, v57 )
BFME_VCALL_SELF( Rva00695AA0VCall, v88 )

BFME_VCALL_INTERIOR( Rva00220690VCall, -0x20, v17 )
BFME_VCALL_INTERIOR( Rva0022CDE0VCall, -0x34, v27 )
BFME_VCALL_INTERIOR( Rva00230770VCall, -0xE4, v35 )
BFME_VCALL_INTERIOR( Rva002D4510VCall, 0x10, v7 )
BFME_VCALL_INTERIOR( Rva0073AF80VCall, 0xFC, v5 )
BFME_VCALL_INTERIOR( Rva0073B780VCall, 0xFC, v7 )
BFME_VCALL_INTERIOR( Rva00746130VCall, 0x24B8, v20 )
