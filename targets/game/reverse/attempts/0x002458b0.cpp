// ?rva002458b0@Rva002458B0Host@@QAEPAUCoord3D@@PAU2@PAVObject@@M@Z
// partial score=0.22 date=2026-09-22
// ?rva002458b0@Rva002458B0Host@@QAEPAUCoord3D@@PAU2@PAVObject@@M@Z
// Retail BFME RVA 0x002458B0 (221 bytes), dump d_002439f0.asm.
// Identity: shared HordeContain/HorseHordeContain vtable slot7 base
// (see reverse/re_attempts.log 0x002310F0 investigation): this object is
// an AODHordeContain-family interface subobject embedded at owner+0xE4;
// the true fallback path calls the owner at this-0xE4 through the
// still-dump helper at 0x00242A30, gated by a ready flag at +0x118.
// When ready, the body ALWAYS looks up an index via a this+0x3c index
// map (still-dump BfmeSubDSU::bfmeTwoDSU) and starts from member's own
// position-ish fields at +0x38/+0x3c/+0x40; only when that index is
// non-negative, in range against a formation-slot array (begin/end at
// +0xF4/+0xF8, stride 0x1c) and the slot is not flagged invalid (+0x10)
// does it overwrite those defaults with the formation slot's position.
// cl: /DNDEBUG /MD

typedef unsigned char UnsignedByte;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	UnsignedByte m_pad000[0x38];
	float m_defaultX;
	float m_defaultY;
	float m_defaultZ;
	UnsignedByte m_pad044[0x74 - 0x44];
	int m_formationSlot;
};

struct FormationSlot
{
	UnsignedByte m_pad0[4];
	float x;
	float y;
	float z;
	UnsignedByte m_invalid;
	UnsignedByte m_padTail[0x1c - 0x11];
};

// still a dump: 0x0001F91F -> pinned ?bfmeTwoDSU@BfmeSubDSU@@QAEPAPAXPAPAX@Z
class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **key);
};

// owning object embedded at this-0xE4; real identity unproven (AOD layout
// unwitnessed), so address-qualified.
class Rva002458B0Owner
{
public:
	Coord3D *rva00242a30(Coord3D *out, Object *member, float scalar);
};

class Rva002458B0Host
{
public:
	Coord3D *rva002458b0(Coord3D *out, Object *member, float scalar);

private:
	UnsignedByte m_pad000[0x3c];
	UnsignedByte m_pad03c[0xf4 - 0x3c];
	FormationSlot *m_formationBegin;
	FormationSlot *m_formationEnd;
	UnsignedByte m_pad0fc[0x118 - 0xfc];
	bool m_ready;
};

Coord3D *Rva002458B0Host::rva002458b0(Coord3D *out, Object *member, float scalar)
{
	struct Key
	{
		void *m_member;
		int m_slot;
	};
	Key key;
	key.m_slot = member->m_formationSlot;

	void **found = ((BfmeSubDSU *)((char *)this + 0x3c))->bfmeTwoDSU((void **)&key);
	int index = (int)*found;

	if (!m_ready)
		goto ownerFallback;

	int rx = *(int *)&member->m_defaultX;
	int ry = *(int *)&member->m_defaultY;
	int rz = *(int *)&member->m_defaultZ;

	if (index < 0)
		goto writeOut;

	{
		int count = (int)(m_formationEnd - m_formationBegin);
		if ((unsigned int)index > (unsigned int)count)
			goto writeOut;

		FormationSlot *slot = m_formationBegin + index;
		if (slot->m_invalid)
			goto writeOut;

		rx = *(int *)&slot->x;
		ry = *(int *)&slot->y;
		rz = *(int *)&slot->z;
	}

writeOut:
	*(int *)&out->x = rx;
	out->y = *(float *)&ry;
	out->z = *(float *)&rz;
	return out;

ownerFallback:
	return ((Rva002458B0Owner *)((char *)this - 0xe4))->rva00242a30(out, member, scalar);
}
