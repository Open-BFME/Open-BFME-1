// cl: /DNDEBUG /DWIN32 /MD /EHsc
// The two Player counters that keep their tally by walking every object:
//
//   0x000CE710  adjustCountMask           211 bytes
//   0x000D46E0  rva000D46E0CountVisit      62 bytes  (the visitor)
//   0x000D4730  rva000D4730CountObjects    50 bytes
//
// adjustCountMask keeps the running per-kind counts at Player+0x2C4 and the
// derived bit mask at +0x344, and pushes the result out over the objects;
// rva000D4730CountObjects walks them to count the ones carrying a bit. Both
// reach the walk the same way, and that way is the reason this file holds
// these two and not the rest of the family.
//
// Player::iterateObjects exists under TWO decorations at TWO addresses:
//
//   ?iterateObjects@Player@@QBEHP6AXPAVObject@@PAX@Z1@Z  body,  0x000CDCF0
//   ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z  thunk, 0x0002F1CB
//
// They differ only in the return type, which C++ will not let a translation
// unit hold both of -- so which spelling a caller uses decides which address
// its call reaches, and callers of the two spellings cannot share a TU. These
// two both take the void spelling and so reach the thunk. The int-spelling
// callers live with the definition in PlayerIterateObjects.cpp. The split is a
// fact about the image, not a limit of the merge.
//
// The visitor keeps its address-derived name and, with it, the placeholder
// class in its signature: ?rva000D46E0CountVisit@@YAHPAVRva000D46E0Object@@PAX@Z
// spells Rva000D46E0Object into the symbol, so the name is load-bearing and
// cannot be tidied into Object.
//
// The counting file built without /EHsc and byte-verifies unchanged with it,
// which is what let the two share a TU.

typedef int Int;
typedef unsigned int UnsignedInt;

class Object;

typedef void ( *PlayerObjectVisit )( Object *object, void *userData );

// Address-derived: the object the visitor at 0x000D46E0 is handed. Its name is
// part of that row's mangled name, so it stays exactly as it is.
class Rva000D46E0Object
{
public:
	unsigned char m_unmodelled_000[ 0x110 ];
	UnsignedInt m_bits[ 1 ];				// this+0x110
};

struct Rva000D46E0CountContext
{
	UnsignedInt m_bitIndex;
	Int m_count;
	Int m_limit;
};

// The visitor adjustCountMask hands to the walk; only its address is known.
void rva000C9CC0Visit(Object *obj, void *user);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void adjustCountMask(bool increment, int index);
	Int rva000D4730CountObjects( UnsignedInt bitIndex, Int limit ) const;
	void iterateObjects( PlayerObjectVisit visit, void *userData ) const;

private:
	unsigned char m_unmodelled_000[0x2C4];
	int m_counts[32];					// this+0x2C4
	unsigned short m_mask;					// this+0x344
};

// ?adjustCountMask@Player@@QAEX_NH@Z
// BFME keeps four count-mask entries in each rotated loop iteration; the
// induction variable starts at one so MSVC 7.1 emits the retail EDI/ESI/EBX/EDX
// allocation and back edge.
void Player::adjustCountMask(bool increment, int index)
{
	if (increment)
	{
		if (++m_counts[index] != 1)
			return;
	}
	else
	{
		if (--m_counts[index] != 0)
			return;
	}

	unsigned int mask = 0;
	int i = 1;
	do
	{
		if (m_counts[i - 1] > 0)
			mask |= 1u << (i - 1);
		else
			mask &= ~(1u << (i - 1));
		if (m_counts[i] > 0)
			mask |= 1u << i;
		else
			mask &= ~(1u << i);
		if (m_counts[i + 1] > 0)
			mask |= 1u << (i + 1);
		else
			mask &= ~(1u << (i + 1));
		if (m_counts[i + 2] > 0)
			mask |= 1u << (i + 2);
		else
			mask &= ~(1u << (i + 2));
		i += 4;
	} while (i - 1 < 32);
	m_mask = (unsigned short)mask;
	iterateObjects(rva000C9CC0Visit, 0);
}

// ?rva000D46E0CountVisit@@YAHPAVRva000D46E0Object@@PAX@Z
// The visitor's context is three dwords: a bit index, the running count, and
// the inclusive limit. The object supplies a word-indexed bitset at +0x110. It
// stops the walk only after incrementing beyond the limit.
Int rva000D46E0CountVisit( Rva000D46E0Object *object, void *userData )
{
	Rva000D46E0CountContext *context =
		static_cast<Rva000D46E0CountContext *>( userData );
	UnsignedInt bit = context->m_bitIndex;

	if ( object->m_bits[ bit >> 5 ] & ( 1U << ( bit & 0x1F ) ) )
	{
		++context->m_count;
		if ( context->m_count > context->m_limit )
			return 0;
	}

	return 1;
}

// ?rva000D4730CountObjects@Player@@QBEHIH@Z
Int Player::rva000D4730CountObjects( UnsignedInt bitIndex, Int limit ) const
{
	Rva000D46E0CountContext context = { bitIndex, 0, limit };
	iterateObjects(
		reinterpret_cast<PlayerObjectVisit>( rva000D46E0CountVisit ), &context );
	return context.m_count;
}
