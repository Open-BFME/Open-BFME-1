// ?update@AimWeaponBehavior@@QAE?AW4UpdateSleepTime@@XZ
// partial score=0.45 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX-
// AimWeaponBehavior::update, retail 0x001ED230 size 570, dump d_001e7c30.
// this is the UpdateModule interface at +0x10: Object* at this-8, ModuleData*
// at this-0xC, sticky-aim flag at this+0x10. Pitch vs ModuleData +0x8/+0xC
// writes Object+0x124 bits 0x100/0x200/0x400 (model conditions 0xA8/0xA9/0xAA).
// XY range vs +0x10/+0x14 clear-and-sets 0xAB/0xAC. Sleep forever when AI or
// drawable is missing.

#include <math.h>

typedef int Int;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Drawable
{
public:
	void bfmeApplyModelConditionFlags(Bool immediate);
};

class WeaponTemplate
{
public:
	char m_pad[0x51E];
	unsigned char m_useAimConditions;
};

class Weapon
{
public:
	WeaponTemplate *m_pad00;
	WeaponTemplate *m_template;
};

class Object;

class AIUpdateInterface
{
public:
#define BFME_SLOT(n) virtual Int bfmeSlot##n() = 0
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
	BFME_SLOT(64); BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67);
	BFME_SLOT(68); BFME_SLOT(69); BFME_SLOT(70); BFME_SLOT(71);
	BFME_SLOT(72); BFME_SLOT(73); BFME_SLOT(74); BFME_SLOT(75);
	BFME_SLOT(76); BFME_SLOT(77); BFME_SLOT(78); BFME_SLOT(79);
	BFME_SLOT(80); BFME_SLOT(81); BFME_SLOT(82); BFME_SLOT(83);
	BFME_SLOT(84); BFME_SLOT(85); BFME_SLOT(86); BFME_SLOT(87);
	BFME_SLOT(88); BFME_SLOT(89); BFME_SLOT(90); BFME_SLOT(91);
	BFME_SLOT(92); BFME_SLOT(93); BFME_SLOT(94); BFME_SLOT(95);
#undef BFME_SLOT
	virtual Bool isIdle() const = 0;
	virtual Bool isAttacking() const = 0;
	Bool bfmeBlocksFormationRefresh();
};

class Rva00170C70BitSet
{
public:
	Rva00170C70BitSet(void *unused, unsigned index);
	unsigned m_words[10];
};

class BfmeE1166
{
public:
	BfmeE1166(int tag, unsigned a02, unsigned a03, unsigned a04, unsigned a05, unsigned a06);
	unsigned m_bfme00[10];
};

extern const float g_bfmeK1254;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Drawable *getDrawable();

	Weapon *getCurrentWeapon(WeaponSlotType *wslot);
	void notifyModelConditionChanged();
	void clearAndSetModelConditionFlags(const Rva00170C70BitSet &clr,
		const Rva00170C70BitSet &set);
	void clearModelConditionFlags(const BfmeE1166 &clr);

	char m_pad004[0x38 - 4];
	Coord3D m_position;
	char m_pad044[0x124 - 0x44];
	unsigned m_conditionWord5;
	char m_pad128[0x204 - 0x128];
	AIUpdateInterface *m_ai;
	char m_pad208[0x2A8 - 0x208];
	Coord3D m_aimPos;
};

class AimWeaponBehaviorModuleData
{
public:
	virtual ~AimWeaponBehaviorModuleData();
	int m_gap4;
	float m_pitchLow;
	float m_pitchHigh;
	float m_rangeMin;
	float m_rangeMax;
};

class AimWeaponBehavior
{
public:
	UpdateSleepTime update();

	char m_pad00[0x10];
	unsigned char m_aiming;
};

// ?update@AimWeaponBehavior@@QAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime AimWeaponBehavior::update()
{
	Object *obj = *(Object **)((char *)this - 8);
	AIUpdateInterface *ai = obj->m_ai;
	Drawable *drawStash[1];
	drawStash[0] = obj->getDrawable();
	if (ai && drawStash[0])
	{
		Weapon *weapon = obj->getCurrentWeapon(0);
		if (weapon && weapon->m_template->m_useAimConditions
			&& ai->isAttacking() && !ai->bfmeBlocksFormationRefresh() && !ai->isIdle())
		{
			float ten = 10.0f;
			float dx = obj->m_aimPos.x - obj->m_position.x;
			float dy = obj->m_aimPos.y - obj->m_position.y;
			float dz = obj->m_aimPos.z - obj->m_position.z;
			float len = (float)sqrt(dy * dy + dx * dx);
			float *chosen = (g_bfmeK1254 > len) ? &ten : &len;
			float denom = *chosen;
			AimWeaponBehaviorModuleData *data =
				*(AimWeaponBehaviorModuleData **)((char *)this - 0xC);
			float pitch = dz / denom;
			unsigned mask;
			if (pitch > data->m_pitchHigh)
				mask = 0x100;
			else if (pitch < data->m_pitchLow)
				mask = 0x400;
			else
				mask = 0x200;
			m_aiming = 1;
			unsigned word = obj->m_conditionWord5;
			if ((word & mask) == 0)
			{
				obj->m_conditionWord5 = word | mask;
				obj->notifyModelConditionChanged();
			}
			if (denom < data->m_rangeMin)
			{
				Rva00170C70BitSet clr(0, 0xAB);
				Rva00170C70BitSet setf(0, 0xAC);
				m_aiming = 1;
				obj->clearAndSetModelConditionFlags(clr, setf);
			}
			else if (denom > data->m_rangeMax)
			{
				Rva00170C70BitSet clr(0, 0xAC);
				Rva00170C70BitSet setf(0, 0xAB);
				m_aiming = 1;
				obj->clearAndSetModelConditionFlags(clr, setf);
			}
			drawStash[0]->bfmeApplyModelConditionFlags(0);
		}

		if (m_aiming)
		{
			if (!ai->isAttacking() || ai->bfmeBlocksFormationRefresh() || ai->isIdle())
			{
				BfmeE1166 clr(0, 0xAB, 0xAC, 0xAA, 0xA9, 0xA8);
				m_aiming = 0;
				obj->clearModelConditionFlags(clr);
				drawStash[0]->bfmeApplyModelConditionFlags(0);
			}
		}

		return UPDATE_SLEEP_NONE;
	}
	return UPDATE_SLEEP_FOREVER;
}
