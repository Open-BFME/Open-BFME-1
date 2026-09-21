// ?checkMember@HordeContainOwner@@QAE_NPAVObject@@@Z
// partial score=0.25 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// HordeContain-family member-eligibility check, retail 0x0023CAA0, size 570.
// Identity: multiple address-derived callees but no named caller, vtable
// slot, or authoritative source owner (per brief). Field offsets and
// pinned callees below come straight from the brief's callee list and
// direct disassembly reading; nothing here is independently proven, so the
// body stays address-keyed.

typedef bool Bool;
typedef int Int;

class Player
{
};

class Object
{
public:
	Bool isKindOf(Int kindOfIndex);		// pinned retail 0x0003AB20 (bfmeAskAIA)
	Object *resolveSecond(Int arg);		// pinned retail 0x00035995
	Player *getControllingPlayer();		// pinned retail 0x00020824

	void *m_vtable;
	unsigned char m_pad04[0x94 - 4];
	Int m_kindOfBits0;				// +0x94
	unsigned char m_pad98[0x1a4 - 0x98];
	Int m_disabledMask;				// +0x1a4
	unsigned char m_pad1a8[0x344 - 0x1a8];
	unsigned char m_statusByte344;			// +0x344
};

extern "C" Bool __cdecl Rva004084B8GetTemplateFieldOffset20(Object *obj);	// pinned retail 0x000084B8
extern "C" void __cdecl Rva000259B9SetName(void *label, void *name);		// pinned retail 0x000259B9
extern "C" Int __cdecl Rva0003251FCheck(Object *obj, Int arg);		// pinned retail 0x0003251F
extern "C" Int __cdecl Rva000289D9Resolve(void *self);			// pinned retail 0x000289D9
extern "C" Bool __cdecl Rva00016A4VeterancyIs(void *obj, Int level);		// pinned retail 0x000016A4

class BfmeRetString
{
public:
	BfmeRetString() { m_data = 0; }
	BfmeRetString(const BfmeRetString &other);		// retail 0x00887B60
	~BfmeRetString() { releaseBuffer(); }
	void set(const BfmeRetString &other);			// retail 0x00887C90

private:
	void releaseBuffer();					// retail 0x00887940
	void *m_data;
};

// Placeholder virtual call surface on the object reached through this-0xe0:
// slot 0x68 called twice with different argument packs, at member offsets
// +0x28c and +0x2b0.
class Rva0023CAA0SlotOwner
{
public:
	virtual void pad00(); virtual void pad04(); virtual void pad08(); virtual void pad0C();
	virtual void pad10(); virtual void pad14(); virtual void pad18(); virtual void pad1C();
	virtual void pad20(); virtual void pad24(); virtual void pad28(); virtual void pad2C();
	virtual void pad30(); virtual void pad34(); virtual void pad38(); virtual void pad3C();
	virtual void pad40(); virtual void pad44(); virtual void pad48(); virtual void pad4C();
	virtual void pad50(); virtual void pad54(); virtual void pad58(); virtual void pad5C();
	virtual void pad60(); virtual void pad64();
	virtual Bool slot68(Int a, void *b, void *c, void *d);
};

class HordeContainOwner
{
public:
	Bool checkMember(Object *candidate);
};

Bool HordeContainOwner::checkMember(Object *candidate)
{
	Object *self = (Object *)this;
	Object *us = *(Object **)((unsigned char *)self - 0xdc);

	if (!candidate)
		return false;
	if (candidate->m_statusByte344 & 1)
		return false;
	if (candidate->m_kindOfBits0 & 0x4000000)
		return false;
	if (candidate->m_kindOfBits0 & 0x20000000)
		return false;

	if (us->m_kindOfBits0 & 0x20000000)
		return false;
	if (candidate->m_disabledMask != 0)
		return false;
	if (!candidate->isKindOf(0xcf))
		return false;

	Object *resolved = candidate->resolveSecond(0);
	Player *p1 = us->getControllingPlayer();
	Player *p2 = candidate->getControllingPlayer();
	if (p1 != p2)
		return false;

	if (resolved == 0)
	{
		Rva0023CAA0SlotOwner *owner = *(Rva0023CAA0SlotOwner **)((unsigned char *)self - 0xe0);

		if (!owner->slot68(0, (void *)((unsigned char *)owner + 0x28c), 0, candidate))
			return false;

		if (owner->slot68(0, (void *)((unsigned char *)owner + 0x2b0), 0, candidate))
		{
			Object *count = *(Object **)((unsigned char *)self - 0xdc);
			count = *(Object **)((unsigned char *)count + 0x210);
			if (*(Int *)((unsigned char *)count + 0x28) <= 1)
				return false;
			if (!(*(unsigned char *)((unsigned char *)owner + 0x2d0)))
				return false;

			if (!Rva0003251FCheck(candidate, 0xb))
				return false;

			void *field20 = 0;
			if (Rva004084B8GetTemplateFieldOffset20(candidate))
				field20 = candidate;

			owner = (Rva0023CAA0SlotOwner *)((unsigned char *)owner + 0x2d4);
			if (!Rva0003251FCheck((Object *)owner, 0))
				return false;

			return true;
		}
	}
	else
	{
		if (us == 0)
			return false;
		if (resolved == us)
			return false;

		BfmeRetString label;
		Rva000259B9SetName(&label, (void *)((unsigned char *)us + 0x20));
		BfmeRetString copy(label);

		if (Rva000289D9Resolve(us) == 0)
			return false;

		if (!Rva00016A4VeterancyIs(us, 2) && !Rva00016A4VeterancyIs(us, 3) &&
			!Rva00016A4VeterancyIs(candidate, 2) && !Rva00016A4VeterancyIs(candidate, 3))
			return false;
	}

	return true;
}
