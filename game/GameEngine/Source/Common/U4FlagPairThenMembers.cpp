// Three more members of the family
// game/GameEngine/Source/Common/PairedFlagVirtualCallers.cpp reads out: a
// two-byte object with both fields set true is handed to a virtual slot 0x28,
// and one or more of the caller's own members follow through higher slots.
// That file's evidence carries over unchanged and is not restated here; what
// these three add is a different member offset, a different tail slot, and one
// row that CHAINS onto a body that file already landed.
//
// 0x005FC5E0 and 0x005FDB60 (48 bytes each) are its 48-byte shape with the
// member at +4 instead of +0x24:
//
//     push ecx / push esi / mov esi,[esp+0xC] / push edi / mov edi,ecx
//     mov al,1 / lea ecx,[esp+8] / mov [esp+8],al / mov [esp+9],al
//     mov eax,[esi] / push ecx / mov ecx,esi / call dword ptr [eax+0x28]
//     mov edx,[esi] / add edi,4 / push edi / mov ecx,esi
//     call dword ptr [edx+<TAIL>] / pop edi / pop esi / pop ecx / ret 4
//
// THE TAIL SLOT IS THE ONLY THING SEPARATING THEM -- 0x74 and 0x6C -- so they
// dispatch to different positions in their targets' vtables and are therefore
// two different target types, not one type called twice.  Slot number is
// vtable INDEX times four, so 0x6C is the twenty-eighth virtual and 0x74 the
// thirtieth; the padding slots below exist only to put `takeMember` there.
//
// 0x00607CE0 (63 bytes) puts three calls after one:
//
//     push esi / mov esi,[esp+8] / push edi / push esi / mov edi,ecx
//     call 0x00113E70                         ; this->invoke(target)
//     <flag pair into [esp+0xC]> / call dword ptr [eax+0x28]
//     lea eax,[edi+0x10] / push eax / call dword ptr [edx+0x6C]
//     add edi,0x14 / push edi / call dword ptr [edx+0x74]
//     pop edi / pop esi / ret 4
//
// THE FIRST CALL IS NOT VIRTUAL and it is not to the target: ecx still holds
// the receiver when it is made, and its one pushed argument is the target.  Its
// REL32 resolves to 0x00113E70, which the ledger already carries as
// `?invoke@Rva00113E70Caller@@QAEXPAVRva00113E70Target@@@Z` -- one of
// PairedFlagVirtualCallers.cpp's own rows.  A non-virtual __thiscall on `this`
// whose parameter is this row's parameter is an INHERITED member function
// called by name, so this caller derives from that one and this target from
// that target.  The inheritance is also why slot 0x28 still holds `applyFlags`
// here: it is the base's eleventh virtual, and the derived target only appends.
//
// TWO MEMBERS FOLLOW, at +0x10 and +0x14, through two DIFFERENT slots (0x6C and
// 0x74) -- so they are two distinct entry points taking two distinct members,
// not one call in a loop.  Both are passed by address with no null guard, which
// is a reference to a member, matching the family's existing reading.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the
// `slotNN` declarations carry vtable positions and nothing else.

#define U4_TEN_LEADING_SLOTS                                                  \
	virtual void slot00(); virtual void slot04();                             \
	virtual void slot08(); virtual void slot0C();                             \
	virtual void slot10(); virtual void slot14();                             \
	virtual void slot18(); virtual void slot1C();                             \
	virtual void slot20(); virtual void slot24();

#define U4_SIXTEEN_TAIL_SLOTS                                                 \
	virtual void slot2C(); virtual void slot30();                             \
	virtual void slot34(); virtual void slot38();                             \
	virtual void slot3C(); virtual void slot40();                             \
	virtual void slot44(); virtual void slot48();                             \
	virtual void slot4C(); virtual void slot50();                             \
	virtual void slot54(); virtual void slot58();                             \
	virtual void slot5C(); virtual void slot60();                             \
	virtual void slot64(); virtual void slot68();

#define U4_FLAGS( NAME ) struct NAME##Flags { bool m_first; bool m_second; };

// takeMember at slot 0x6C
#define U4_TARGET_6C( NAME )                                                  \
	U4_FLAGS( NAME )                                                          \
	class NAME##Target                                                        \
	{                                                                         \
	public:                                                                   \
		U4_TEN_LEADING_SLOTS                                                  \
		virtual void applyFlags( const NAME##Flags &flags );                  \
		U4_SIXTEEN_TAIL_SLOTS                                                 \
		virtual void takeMember( const int &member );                         \
	};

// takeMember at slot 0x74
#define U4_TARGET_74( NAME )                                                  \
	U4_FLAGS( NAME )                                                          \
	class NAME##Target                                                        \
	{                                                                         \
	public:                                                                   \
		U4_TEN_LEADING_SLOTS                                                  \
		virtual void applyFlags( const NAME##Flags &flags );                  \
		U4_SIXTEEN_TAIL_SLOTS                                                 \
		virtual void slot6C(); virtual void slot70();                         \
		virtual void takeMember( const int &member );                         \
	};

#define U4_CALLER( NAME )                                                     \
	class NAME##Caller                                                        \
	{                                                                         \
	public:                                                                   \
		void invoke( NAME##Target *target );                                  \
		char m_leading[ 0x04 ];                                               \
		int m_member;                                                         \
	};                                                                        \
	void NAME##Caller::invoke( NAME##Target *target )                         \
	{                                                                         \
		NAME##Flags flags;                                                    \
		flags.m_first = true;                                                 \
		flags.m_second = true;                                                \
		target->applyFlags( flags );                                          \
		target->takeMember( m_member );                                       \
	}

U4_TARGET_74( Rva005FC5E0 )
U4_CALLER( Rva005FC5E0 )
U4_TARGET_6C( Rva005FDB60 )
U4_CALLER( Rva005FDB60 )

U4_FLAGS( Rva00113E70 )
class Rva00113E70Target
{
public:
	U4_TEN_LEADING_SLOTS
	virtual void applyFlags( const Rva00113E70Flags &flags );
};

class Rva00113E70Caller
{
public:
	void invoke( Rva00113E70Target *target );
};

class U4Target00607CE0 : public Rva00113E70Target
{
public:
	U4_SIXTEEN_TAIL_SLOTS
	virtual void takeFirst( const int &member );
	virtual void slot70();
	virtual void takeSecond( const int &member );
};

class U4Caller00607CE0 : public Rva00113E70Caller
{
public:
	void invokeAll( U4Target00607CE0 *target );
	char m_leading[ 0x10 ];
	int m_first;
	int m_second;
};

void U4Caller00607CE0::invokeAll( U4Target00607CE0 *target )
{
	Rva00113E70Caller::invoke( target );
	Rva00113E70Flags flags;
	flags.m_first = true;
	flags.m_second = true;
	target->applyFlags( flags );
	target->takeFirst( m_first );
	target->takeSecond( m_second );
}
