// cl: /EHsc
// One 125-byte __thiscall copy constructor, the same chain
// V3ThirdBaseInlineCopyCtors.cpp landed, with the base at 0x18 wide enough that
// its copy constructor is a CALL instead of being inlined.  Retail:
//
//     push -1 ; push <__ehhandler> ; mov eax,fs:[0] ; push eax ; mov fs:[0],esp
//     push ecx                              ; the one local: `this` for unwind
//     push ebx ; mov ebx,[esp+0x18] ; push esi ; push edi ; mov esi,ecx
//     push ebx ; mov [esp+0x10],esi
//     call 0x005EB7B0                       ; first base's copy ctor, arg at 0
//     mov [esi],     0x01112FA8             ; the middle class's pair
//     mov [esi+0x14],0x01112FA4
//     xor eax,eax ; cmp ebx,eax ; mov [esp+0x18],eax  ; unwind state := 0
//     je L ; lea eax,[ebx+0x18] ; L: lea edi,[esi+0x18]
//     push eax ; mov ecx,edi
//     call 0x005DE270                       ; FXParticleSystem::RenderObject-
//                                           ; DrawModuleInfo's copy ctor
//     mov ecx,[esp+0x10]                    ; the saved SEH link
//     mov [esi],     0x01112F80             ; the derived class's three
//     mov [esi+0x14],0x01112F7C
//     mov [edi],     0x01112F68
//     mov eax,[ebx+0x58] ; mov [esi+0x58],eax
//     pop edi ; mov eax,esi ; pop esi ; pop ebx
//     mov fs:[0],ecx ; add esp,0x10 ; ret 4
//
// WHAT THE BYTES SHOW.  Two rounds of vptr stores over one out-of-line first
// base, so the same three-level chain the inline file describes: a middle class
// deriving from Rva005EB7B0 alone (its round rewrites only 0 and 0x14) and the
// most derived class rewriting 0, 0x14 and 0x18.  The thing at 0x18 is a BASE,
// not a member: its address is taken through the null-propagating conversion,
// and it is reached with an argument-taking call rather than inline stores
// because its own copy constructor is out of line.
//
// THE EH FRAME IS THE SECOND BASE'S DOING.  If its copy constructor throws, the
// first base has to be destroyed, so MSVC wraps the body in an EH3 frame, keeps
// `this` in the single local at [esp+0x10] for the unwind funclet, and sets the
// unwind state to 0 immediately before the call.  That is why this row cannot
// share a translation unit with the inline ones: they compile /EHs-c-.
//
// BOTH CALLEES ARE ALREADY LEDGER ROWS.  0x005EB7B0 is the two-base head
// V3HeadNodeCopyCtors.cpp landed, 0x18 wide with slots at 0 and 0x14 -- exactly
// the pair the middle round rewrites.  0x005DE270 is
// ??0RenderObjectDrawModuleInfo@FXParticleSystem@@QAE@ABV01@@Z, and that body
// copies fields up to +0x3C, so the class is 0x40 wide.  0x18 + 0x40 = 0x58,
// which is where the trailing dword this constructor copies lands, making the
// derived class 0x5C -- and 0x5C is the allocation size the 99-byte caller in
// Q4NewInlineCtorMembers.cpp pushes.  Nothing here is padded to reach it.
//
// IDENTITY IS NOT RECOVERED beyond the second base.  Names come from addresses;
// five vftable dwords and the EH handler address are DIR32 sites the gate takes
// from the target, leaving 101 of the 125 bytes concrete.

typedef int Int;

// ---- the first base, landed in V3HeadNodeCopyCtors.cpp; declared only -------

class V3Head14
{
public:
	virtual ~V3Head14();
	Int m_unreconstructed_04, m_unreconstructed_08;
	Int m_unreconstructed_0C, m_unreconstructed_10;
};

class V3Vt0110F97C
{
public:
	virtual void s0();
};

class Rva005EB7B0 : public V3Head14, public V3Vt0110F97C
{
public:
	Rva005EB7B0( const Rva005EB7B0 & );
};

class V3Mid01112FA8 : public Rva005EB7B0
{
};

// ---- the second base, landed under GameClient/System/FXParticleSystem -------

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModuleInfo( const RenderObjectDrawModuleInfo & );
	virtual ~RenderObjectDrawModuleInfo();

	char m_unreconstructed_04[ 0x3c ];
};

}

// --------------------------------------------------------------- the row ----

class Rva005EBBB0
	: public V3Mid01112FA8, public FXParticleSystem::RenderObjectDrawModuleInfo
{
public:
	Rva005EBBB0( const Rva005EBBB0 &o );

	Int m_field58;
};

Rva005EBBB0::Rva005EBBB0( const Rva005EBBB0 &o )
	: V3Mid01112FA8( o ), FXParticleSystem::RenderObjectDrawModuleInfo( o )
{
	m_field58 = o.m_field58;
}
