// ?dup_0089bbf0@@YAXXZ
// partial score=0.55 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ?dup_0089bbf0@@YAXXZ present-unmatched
//
// The owner of this initializer is not proven by the current evidence.  The
// address-backed name is deliberate.  The body itself proves the registry
// allocation order, the constructor calls, the item pushes, the fixed flag
// and vtable stores, and the two final helpers.

#include <new>

typedef unsigned int UnsignedInt;
typedef void *(__cdecl *Rva008C5D70AllocFunc)(UnsignedInt);

class BfmeItemDX;
class BfmeDerivedKind3
{
public:
	BfmeDerivedKind3();
};

class Rva008D2B10
{
public:
	Rva008D2B10();
};

class BfmeDerivedKindB
{
public:
	BfmeDerivedKindB();
};

class Rva89A2C0Derived
{
public:
	Rva89A2C0Derived();
};

class Rva89A540Derived
{
public:
	Rva89A540Derived();
};

class Rva89A6E0Derived
{
public:
	Rva89A6E0Derived();
};

class Rva89A880Derived
{
public:
	Rva89A880Derived();
};

class Rva89AA20Derived
{
public:
	Rva89AA20Derived();
};

class Rva008A9B00
{
public:
	Rva008A9B00();
};

class Rva00899F00Base
{
public:
	Rva00899F00Base(UnsignedInt argument0, int argument1);
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(UnsignedInt value);
};

class Rva0089BBF0VirtualNode
{
public:
	virtual void invoke();
};

extern void __cdecl bfmePush(BfmeItemDX *item);
extern void __cdecl d_0089abc0();
extern void __cdecl d_008a30c0();

#define RVA_REF(type, address) (*reinterpret_cast<type *>(address))
#define RVA_ALLOC (RVA_REF(Rva008C5D70AllocFunc, 0x01337828))

struct Rva0089BBF0ItemRaw
{
	void *m_vftable;
	UnsignedInt m_flags;
	unsigned char m_unmodelled_008[0x18];
	UnsignedInt m_slot20;
};

struct Rva0089BBF0StringRaw
{
	void *m_data;
};

struct Rva0089BBF0NodeRaw
{
	void **m_vftable;
	UnsignedInt m_flags;
	Rva0089BBF0StringRaw m_string;
	Rva0089BBF0NodeRaw *m_next;
};

struct Rva0089BBF0PoolRaw
{
	int m_capacity;
	int m_count;
	Rva0089BBF0NodeRaw **m_items;
};

static Rva0089BBF0ItemRaw *rva0089BBF0Item(void *memory)
{
	return reinterpret_cast<Rva0089BBF0ItemRaw *>(
		reinterpret_cast<unsigned char *>(memory) + 8);
}

void __cdecl dup_0089bbf0()
{
	void *memory;
	Rva0089BBF0ItemRaw *item;
	Rva0089BBF0NodeRaw *node;

	memory = RVA_ALLOC(8);
	if (memory != 0)
		new (memory) BfmeDerivedKind3();

	RVA_REF(void *, 0x013379BC) = 0;
	memory = RVA_ALLOC(0x3c0);
	if (memory != 0)
		new (memory) Rva008D2B10();

	RVA_REF(void *, 0x01337A04) = 0;
	memory = RVA_ALLOC(8);
	if (memory != 0)
		new (memory) BfmeDerivedKindB();

	RVA_REF(void *, 0x01337A20) = 0;
	memory = RVA_ALLOC(0x20);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
		new (item) Rva89A2C0Derived();

	RVA_REF(void *, 0x013379B4) = 0;
	memory = RVA_ALLOC(0x28);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
	{
		new (item) Rva00899F00Base(0x18, 8);
		item->m_vftable = reinterpret_cast<void *>(0x01136238);
		item->m_flags = (item->m_flags & 0xffffc07f) | 0x0fff0040;
	}

	RVA_REF(void *, 0x013379FC) = 0;
	memory = RVA_ALLOC(0x20);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
		new (item) Rva89A540Derived();

	RVA_REF(void *, 0x013379AC) = 0;
	memory = RVA_ALLOC(0x20);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
		new (item) Rva89A6E0Derived();

	RVA_REF(void *, 0x013387D8) = 0;
	memory = RVA_ALLOC(0x20);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
		new (item) Rva89A880Derived();

	RVA_REF(void *, 0x0133846C) = 0;
	memory = RVA_ALLOC(0x20);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
		new (item) Rva89AA20Derived();

	node = RVA_REF(Rva0089BBF0NodeRaw *, 0x01338478);
	RVA_REF(Rva0089BBF0NodeRaw *, 0x01337A00) = 0;
	if (node != 0)
	{
		RVA_REF(Rva0089BBF0NodeRaw *, 0x01338478) = node->m_next;
		Rva0089BBF0PoolRaw *pool =
			RVA_REF(Rva0089BBF0PoolRaw *, 0x01337810);
		if (pool->m_count < pool->m_capacity)
			node->m_flags &= 0xbfffffff;
		else
		{
			pool->m_items[pool->m_count] = node;
			++pool->m_count;
		}

		if (node->m_string.m_data !=
			reinterpret_cast<void *>(0x012D5298))
			reinterpret_cast<BfmeStrVKK *>(&node->m_string)->bfmeTruncVKK(0);
	}
	else
	{
		memory = RVA_ALLOC(0x10);
		node = reinterpret_cast<Rva0089BBF0NodeRaw *>(memory);
		if (node != 0)
			new (node) Rva008A9B00();
	}

	RVA_REF(Rva0089BBF0NodeRaw *, 0x013379F0) = node;
	node->m_flags = (node->m_flags & 0xffffc07f) | 0x40;
	reinterpret_cast<Rva0089BBF0VirtualNode *>(node)->invoke();
	RVA_REF(void *, 0x01337A28) = 0;
	d_0089abc0();

	RVA_REF(float, 0x013379CC) = 1.0f;
	RVA_REF(float, 0x013379D0) = 1.0f;
	RVA_REF(float, 0x013379D4) = 1.0f;
	RVA_REF(float, 0x013379D8) = 1.0f;
	RVA_REF(float, 0x013379DC) = 0.0f;
	RVA_REF(float, 0x013379E0) = 0.0f;
	RVA_REF(float, 0x013379E4) = 0.0f;
	RVA_REF(float, 0x013379E8) = 0.0f;
	RVA_REF(float, 0x01337A08) = 1.0f;
	RVA_REF(float, 0x01337A0C) = 0.0f;
	RVA_REF(float, 0x01337A10) = 0.0f;
	RVA_REF(float, 0x01337A14) = 1.0f;
	RVA_REF(float, 0x01337A18) = 0.0f;
	RVA_REF(float, 0x01337A1C) = 0.0f;

	RVA_REF(void *, 0x013379EC) = 0;
	memory = RVA_ALLOC(0x2c);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
	{
		new (item) Rva00899F00Base(9, 8);
		item->m_vftable = reinterpret_cast<void *>(0x01136128);
		item->m_slot20 = 0x00CC64C0;
		RVA_REF(void *, 0x013379EC) = item;
		item->m_flags = (item->m_flags & 0xf064ffff) | 0x00640000;
		item->m_flags = item->m_flags & 0xffffc03f;
		item->m_flags = item->m_flags | 0x40;
	}

	RVA_REF(void *, 0x013379C4) = 0;
	memory = RVA_ALLOC(0x2c);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
	{
		new (item) Rva00899F00Base(9, 8);
		item->m_vftable = reinterpret_cast<void *>(0x01136128);
		item->m_slot20 = 0x00CC66A0;
		RVA_REF(void *, 0x013379C4) = item;
		item->m_flags = (item->m_flags & 0xf064ffff) | 0x00640000;
		item->m_flags = item->m_flags & 0xffffc03f;
		item->m_flags = item->m_flags | 0x40;
	}

	RVA_REF(void *, 0x013379C8) = 0;
	memory = RVA_ALLOC(0x2c);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
	{
		new (item) Rva00899F00Base(9, 8);
		item->m_vftable = reinterpret_cast<void *>(0x01136128);
		item->m_slot20 = 0x00CC6800;
		RVA_REF(void *, 0x013379C8) = item;
		item->m_flags = (item->m_flags & 0xf064ffff) | 0x00640000;
		item->m_flags = item->m_flags & 0xffffc03f;
		item->m_flags = item->m_flags | 0x40;
	}

	RVA_REF(void *, 0x013379F8) = 0;
	memory = RVA_ALLOC(0x2c);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
	{
		new (item) Rva00899F00Base(9, 8);
		item->m_vftable = reinterpret_cast<void *>(0x01136128);
		item->m_slot20 = 0x00CC6840;
		RVA_REF(void *, 0x013379F8) = item;
		item->m_flags = (item->m_flags & 0xf064ffff) | 0x00640000;
		item->m_flags = item->m_flags & 0xffffc03f;
		item->m_flags = item->m_flags | 0x40;
	}

	RVA_REF(void *, 0x013379B8) = 0;
	memory = RVA_ALLOC(0x2c);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
	{
		new (item) Rva00899F00Base(9, 8);
		item->m_vftable = reinterpret_cast<void *>(0x01136128);
		item->m_slot20 = 0x00CC6990;
		RVA_REF(void *, 0x013379B8) = item;
		item->m_flags = (item->m_flags & 0xf064ffff) | 0x00640000;
		item->m_flags = item->m_flags & 0xffffc03f;
		item->m_flags = item->m_flags | 0x40;
	}

	RVA_REF(void *, 0x013379B0) = 0;
	memory = RVA_ALLOC(0x2c);
	item = rva0089BBF0Item(memory);
	bfmePush(reinterpret_cast<BfmeItemDX *>(item));
	if (item != 0)
	{
		new (item) Rva00899F00Base(9, 8);
		item->m_vftable = reinterpret_cast<void *>(0x01136128);
		item->m_slot20 = 0x00CC4F90;
		RVA_REF(void *, 0x013379B0) = item;
		item->m_flags = (item->m_flags & 0xf064ffff) | 0x00640000;
		item->m_flags = item->m_flags & 0xffffc03f;
		item->m_flags = item->m_flags | 0x40;
	}

	RVA_REF(void *, 0x01337A2C) = item;
	item->m_flags = (item->m_flags & 0xf064ffff) | 0x00640000;
	Rva0089BBF0ItemRaw *tail =
		RVA_REF(Rva0089BBF0ItemRaw *, 0x01337A2C);
	tail->m_flags = (tail->m_flags & 0xffffc03f) | 0x40;

	RVA_REF(void *, 0x013387B0) = 0;
	RVA_REF(void *, 0x013387B4) = 0;
	RVA_REF(void *, 0x013387B8) = 0;
	RVA_REF(void *, 0x013387BC) = 0;
	d_008a30c0();
}
