// One __thiscall constructor that opens with the vftable-plus-zeroed-dword
// head and then fills a twelve-byte block and three scalars from four
// arguments.
//
// Read VptrZeroPrefixCtors.cpp's header for the head.  Retail:
//
//     mov eax,ecx / mov ecx,[esp+4] / mov [eax+4],0 / mov [eax],<vftable>
//     mov edx,[ecx]     / mov [eax+8],edx
//     mov edx,[ecx+4]   / mov [eax+0xC],edx
//     mov ecx,[ecx+8]   / mov edx,[esp+8]
//     mov [eax+0x10],ecx / mov ecx,[esp+0xC]
//     mov [eax+0x14],edx / mov dl,[esp+0x10]
//     mov [eax+0x18],ecx / mov [eax+0x1C],dl / ret 0x10
//
// `ret 0x10` is four dword argument slots.  The first is dereferenced at
// +0x00, +0x04 and +0x08, so it is a reference to a twelve-byte aggregate and
// lands at +0x08..+0x13; the remaining three are stored as they arrive, two
// dwords at +0x14 and +0x18 and a byte at +0x1C.  The stores stay in
// declaration order while the loads run ahead of them -- the interleaving is
// scheduling, not a different member order.
//
// The twelve bytes are NOT one sub-object.  Spelling them as an embedded
// aggregate initialised from the reference emits the inlined copy constructor
// the block constructors in VptrZeroPrefixBlockCtors.cpp use --
// `push esi / lea ecx,[eax+8] / mov [ecx],esi ...`, which reorders the whole
// body and is measurably not retail.  Three separate dword members, each
// initialised from its own field of the argument, are what emit retail's plain
// stores through `this`.  The argument stays a reference to a twelve-byte
// aggregate: it is dereferenced three times, never stored.
//
// The body is named for its own address; no class name has been recovered.

struct VptrZeroMixedBlock12
{
	unsigned int m_dword_00;
	unsigned int m_dword_04;
	unsigned int m_dword_08;
};

class VptrZeroMixedHead
{
public:
	VptrZeroMixedHead() : m_unmodelled_04( 0 ) {}

	virtual void vptrZeroMixedAnchor();

	unsigned int m_unmodelled_04;
};

class Rva000FBCB0VptrZeroMixedObject : public VptrZeroMixedHead
{
public:
	Rva000FBCB0VptrZeroMixedObject( const VptrZeroMixedBlock12 &block,
		void *first, void *second, unsigned char flag );

	unsigned int   m_dword_08;
	unsigned int   m_dword_0C;
	unsigned int   m_dword_10;
	void          *m_first;
	void          *m_second;
	unsigned char  m_flag;
};

Rva000FBCB0VptrZeroMixedObject::Rva000FBCB0VptrZeroMixedObject(
	const VptrZeroMixedBlock12 &block, void *first, void *second, unsigned char flag )
	: m_dword_08( block.m_dword_00 ),
	  m_dword_0C( block.m_dword_04 ),
	  m_dword_10( block.m_dword_08 ),
	  m_first( first ), m_second( second ), m_flag( flag ) {}
