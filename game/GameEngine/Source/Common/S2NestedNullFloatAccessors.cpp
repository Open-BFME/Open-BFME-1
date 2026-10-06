// Five __thiscall const accessors that walk two pointers, tail-jump to a float
// getter when both are non-null, and load a float constant when either is not:
//
//     mov eax,[ecx+8] / test eax,eax / je zero
//     mov eax,[eax+12024h] / test eax,eax / je zero
//     mov ecx,eax / jmp <REL32>
//     zero: fld dword ptr [<CONST>] / ret
//
// WHAT THE BYTES SHOW.  The outer pointer is loaded ONCE and then indexed, so
// the source named it once and kept it; naming it twice would reload it.  The
// exit is `jmp`, so the callee returns a float on the x87 stack directly to our
// caller and takes no stack arguments.  The default arm is `fld` from a
// four-byte constant, which is a float literal, not a double.  The constant
// address is the same 0x01075350 in all five rows and holds 00000000, i.e. 0.0f.
//
// FIVE CALLEES, ONE OWNER SHAPE.  The two offsets (+8, then +0x12024) are
// identical in all five rows, so one pair of classes covers the family; only
// the getter differs. Each jmp goes through its own incremental-link thunk to
// a matched Transport.cpp statistics getter:
//   0x00681C10 -> ILT 0x00034AF4 -> 0x00683900 Transport::getIncomingBytesPerSecond
//   0x00681C70 -> ILT 0x0004AB79 -> 0x00683C00 Transport::getOutgoingBytesPerSecond
//   0x00681CA0 -> ILT 0x00026B7A -> 0x00683D80 Transport::getOutgoingPacketsPerSecond
//   0x00681CD0 -> ILT 0x0000D82D -> 0x00683F00 Transport::getUnknownBytesPerSecond
//   0x00681D00 -> ILT 0x0001F96A -> 0x00684080 Transport::getUnknownPacketsPerSecond
//
// The inner pointer is therefore a Transport. The two owners stay
// address-derived: the 0x12024 bytes ahead of the Transport pointer are
// unattributed padding here; the bytes only fix where the pointer is.

class Transport
{
public:
	float getIncomingBytesPerSecond( void );
	float getOutgoingBytesPerSecond( void );
	float getOutgoingPacketsPerSecond( void );
	float getUnknownBytesPerSecond( void );
	float getUnknownPacketsPerSecond( void );
};

class GenFloatOwner
{
public:
	char m_lead[ 0x12024 ];
	Transport *m_transport;
};

class Rva00681C10
{
public:
	float at00681C10() const;
	float at00681C70() const;
	float at00681CA0() const;
	float at00681CD0() const;
	float at00681D00() const;
	char m_lead[ 8 ];
	GenFloatOwner *m_owner;
};

#define BFME_NESTED_NULL_FLOAT( NAME, GETTER )                            \
	float Rva00681C10::NAME() const                                       \
	{                                                                     \
		GenFloatOwner *owner = m_owner;                                   \
		if( owner )                                                       \
		{                                                                 \
			Transport *transport = owner->m_transport;                    \
			if( transport )                                               \
				return transport->GETTER();                               \
		}                                                                 \
		return 0.0f;                                                      \
	}

// @?at00681C10@Rva00681C10@@QBEMXZ 0x00681C10
BFME_NESTED_NULL_FLOAT( at00681C10, getIncomingBytesPerSecond )
// @?at00681C70@Rva00681C10@@QBEMXZ 0x00681C70
BFME_NESTED_NULL_FLOAT( at00681C70, getOutgoingBytesPerSecond )
// @?at00681CA0@Rva00681C10@@QBEMXZ 0x00681CA0
BFME_NESTED_NULL_FLOAT( at00681CA0, getOutgoingPacketsPerSecond )
// @?at00681CD0@Rva00681C10@@QBEMXZ 0x00681CD0
BFME_NESTED_NULL_FLOAT( at00681CD0, getUnknownBytesPerSecond )
// @?at00681D00@Rva00681C10@@QBEMXZ 0x00681D00
BFME_NESTED_NULL_FLOAT( at00681D00, getUnknownPacketsPerSecond )
