// cl: /DNDEBUG /MD /EHsc
// Retail 0x00249250. This Horde containment hook refreshes the owner's frame
// after it applies or falls back for the supplied object.

typedef unsigned int UnsignedInt;

class BfmeRva49250Object;
class BfmeRva49250AI;
class BfmeRva49250HordeInterface;
class BfmeRva491F0Object;

class BfmeRva49250Contain
{
public:
#define BFME_SLOT(N) virtual void slot##N() = 0
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25);
	virtual BfmeRva49250HordeInterface *getHordeInterface(void) = 0;
#undef BFME_SLOT
};

class BfmeRva49250HordeInterface
{
public:
#define BFME_SLOT(N) virtual void slot##N() = 0
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	BFME_SLOT(64);
	virtual void finishObject(void) = 0;
#undef BFME_SLOT
};

// Retail ILTs 0x00012E3B and 0x00008337 reach these existing matched
// address-derived views at 0x00410BA0 and 0x00411DD0.
class Gen_00410BA0
{
public:
	int isDrawableEffectivelyHidden(void) const;
};

class Gen_00411DD0
{
public:
	void bfmeSet(bool value);
};

class BfmeRva49250Object
{
public:
#define BFME_SLOT(N) virtual void slot##N() = 0
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09);
	virtual BfmeRva49250AI *getAI(void) = 0;
#undef BFME_SLOT
	char m_gap04[0x94 - 0x04];
	unsigned char m_status94;
	char m_gap95[0x1fc - 0x95];
	BfmeRva49250Contain *m_contain;
};

// ILT 0x0003F0FD reaches the matched pointer-taking body at 0x00248AA0.
class BfmeArgCQE;
class BfmeThingCQE
{
public:
	void bfmeGoCQE(BfmeArgCQE *object);
};

class Rva002491F0
{
public:
	void apply(BfmeRva491F0Object *object);
};

class BfmeRva49250Owner
{
public:
	char m_gap00[0x180];
	UnsignedInt m_frame;
};

class BfmeRva49250Global
{
public:
	char m_gap00[0x3c];
	UnsignedInt m_frame;
};

class GameLogic;

// retail 0x012F0898; the TU-local view above is BfmeRva49250Global
extern GameLogic *TheGameLogic;

class BfmeRva49250Base
{
public:
	void bfmeApplyObject(BfmeRva49250Object *object, void *unused);
};

void BfmeRva49250Base::bfmeApplyObject(BfmeRva49250Object *object, void *)
{
	if (object != 0)
	{
		BfmeRva49250Contain *contain = object->m_contain;
		if (contain != 0)
		{
			BfmeRva49250HordeInterface *horde =
				(BfmeRva49250HordeInterface *)contain->getHordeInterface();
			if (horde != 0)
			{
				((Rva002491F0 *)((char *)this - 0x20))->apply(
					(BfmeRva491F0Object *)object);
				horde->finishObject();
				goto done;
			}
		}
		if ((object->m_status94 & 0x20) != 0)
		{
			((BfmeThingCQE *)((char *)this - 0x20))->bfmeGoCQE(
				(BfmeArgCQE *)object);
		}
		else
		{
			((Rva002491F0 *)((char *)this - 0x20))->apply(
				(BfmeRva491F0Object *)object);
			BfmeRva49250AI *ai = object->getAI();
			// Retail consumes AL; the matched provider returns only 0 or 1.
			if (ai != 0 && (char)((Gen_00410BA0 *)ai)->isDrawableEffectivelyHidden() == 1)
				((Gen_00411DD0 *)ai)->bfmeSet(false);
		}

	done:
		BfmeRva49250Owner *owner =
			*(BfmeRva49250Owner **)((char *)this - 0x1c);
		*(UnsignedInt *)((char *)this + 0x998) =
			owner->m_frame + ((BfmeRva49250Global *)TheGameLogic)->m_frame;
	}
}
