// BFME Object DLINK pointer-to-member layout — cracks the {pfn, -100, 0} wall.
//
// A dozen bodies in d_002f6330.asm (ScriptActions team walks) materialize the
// literal constants 0x00401140 / 0xFFFFFF9C (-100) / 0 and then run MSVC 7.1's
// generic virtual-inheritance PMF dispatch:
//
//     mov  eax, [obj+0x68]        ; Object's vbptr
//     mov  ecx, [eax+vbindex]     ; vbtable[0] == 0
//     add  ecx, delta             ; -100
//     lea  ecx, [ecx+obj+0x68]    ; this = obj + 0x68 + 0 - 100 = obj + 4
//     call pfn                    ; ILT 0x1140 -> 0x000C8980: mov eax,[ecx+0x260]; ret
//
// The encoding law, measured against MSVC 7.1 (build/_pmf_v6.cpp probe):
//   * delta -100 with vbindex 0 requires the vbptr to be INHERITED from a base
//     class placed at +0x68 whose own vbptr sits at its +0 (it introduces the
//     virtual base), making vbtable[0] == 0. MSVC then encodes the DLINK
//     member's delta as (member-class offset) - (vbptr offset) = 4 - 0x68.
//   * A most-derived-introduced vbptr instead gives vbtable[0] == -vbptr and
//     delta == member-class offset — the +4/vbindex-4 shapes that do NOT match.
//
// So BFME's Object is, structurally:
//     vptr @ +0, DLINK base @ +4 (link field read at [this+0x260] from there),
//     ... fields ..., vbptr-carrying base @ +0x68, virtual base beyond.
//
// Use exactly this skeleton; sizes of VB/Carrier tails are free, offsets are not.

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

// Introduces the vbptr at its own +0; lands at +0x68 inside Object.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0( void ); };

// Sits at +4; the retail pfn body is: mov eax,[this+0x260]; ret
class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)( void ) const;
