// ?addToContainList@SiegeEngineContain@@UAEXPAVObject@@@Z
// partial score=0.95 date=2026-09-08
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: SiegeEngineContain::addToContainList at retail 0x0022C160.
// The constructor installs the secondary vtable at 0x010ACE08.  Its slot 35
// points through ILT 0x0003BF16 to this body, while slot 33 already names
// SiegeEngineContain::isValidContainerFor.  The list, count, and marker fields
// use the offsets confirmed by the neighbouring remove body at 0x0022BE30.

typedef bool Bool;

enum KindOfType
{
	KINDOF_INVALID = 0
};

enum WeaponSetType
{
	WEAPONSET_INVALID = 0
};

class Player;

class Thing
{
public:
	Bool isKindOf(KindOfType type) const;
	Bool bfmeHasWeaponTemplateSet(WeaponSetType type) const;

private:
	char m_pad[0x90];
};

class SiegeEngineMemberAI;

class BfmeRvaA760Object : public Thing
{
public:
	unsigned char m_typeFlags;
	char m_pad91[0x128 - 0x91];
	union
	{
		unsigned char m_flagsByte;
		unsigned int m_flags;
	};
	unsigned int m_status;
	char m_pad130[0x204 - 0x130];
	SiegeEngineMemberAI *m_ai;

	void notify(void);
};

class Object : public BfmeRvaA760Object
{
	public:
	Player *getControllingPlayer() const;
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
};

class SiegeEngineModuleData
{
public:
	char m_pad[0x224];
	Rva2225E0Filter m_filter;
	int m_capacity;
};

class BfmeObjE10
{
public:
	void actionA(int value);
};

class BfmeRvaAA70Owner
{
public:
	void finish(Object *object);
};

class BfmeContainList
{
public:
	void push_back(Object *const &object);
};

class SiegeEngineMemberAI
{
public:
#define SIEGE_ENGINE_AI_PAD(N) virtual void slot##N();
	SIEGE_ENGINE_AI_PAD(000) SIEGE_ENGINE_AI_PAD(001)
	SIEGE_ENGINE_AI_PAD(002) SIEGE_ENGINE_AI_PAD(003)
	SIEGE_ENGINE_AI_PAD(004) SIEGE_ENGINE_AI_PAD(005)
	SIEGE_ENGINE_AI_PAD(006) SIEGE_ENGINE_AI_PAD(007)
	SIEGE_ENGINE_AI_PAD(008) SIEGE_ENGINE_AI_PAD(009)
	SIEGE_ENGINE_AI_PAD(010) SIEGE_ENGINE_AI_PAD(011)
	SIEGE_ENGINE_AI_PAD(012) SIEGE_ENGINE_AI_PAD(013)
	SIEGE_ENGINE_AI_PAD(014) SIEGE_ENGINE_AI_PAD(015)
	SIEGE_ENGINE_AI_PAD(016) SIEGE_ENGINE_AI_PAD(017)
	SIEGE_ENGINE_AI_PAD(018) SIEGE_ENGINE_AI_PAD(019)
	SIEGE_ENGINE_AI_PAD(020) SIEGE_ENGINE_AI_PAD(021)
	SIEGE_ENGINE_AI_PAD(022) SIEGE_ENGINE_AI_PAD(023)
	SIEGE_ENGINE_AI_PAD(024) SIEGE_ENGINE_AI_PAD(025)
	SIEGE_ENGINE_AI_PAD(026) SIEGE_ENGINE_AI_PAD(027)
	SIEGE_ENGINE_AI_PAD(028) SIEGE_ENGINE_AI_PAD(029)
	SIEGE_ENGINE_AI_PAD(030) SIEGE_ENGINE_AI_PAD(031)
	SIEGE_ENGINE_AI_PAD(032) SIEGE_ENGINE_AI_PAD(033)
	SIEGE_ENGINE_AI_PAD(034) SIEGE_ENGINE_AI_PAD(035)
	SIEGE_ENGINE_AI_PAD(036) SIEGE_ENGINE_AI_PAD(037)
	SIEGE_ENGINE_AI_PAD(038) SIEGE_ENGINE_AI_PAD(039)
	SIEGE_ENGINE_AI_PAD(040) SIEGE_ENGINE_AI_PAD(041)
	SIEGE_ENGINE_AI_PAD(042) SIEGE_ENGINE_AI_PAD(043)
	SIEGE_ENGINE_AI_PAD(044) SIEGE_ENGINE_AI_PAD(045)
	SIEGE_ENGINE_AI_PAD(046) SIEGE_ENGINE_AI_PAD(047)
	SIEGE_ENGINE_AI_PAD(048) SIEGE_ENGINE_AI_PAD(049)
	SIEGE_ENGINE_AI_PAD(050) SIEGE_ENGINE_AI_PAD(051)
	SIEGE_ENGINE_AI_PAD(052) SIEGE_ENGINE_AI_PAD(053)
	SIEGE_ENGINE_AI_PAD(054) SIEGE_ENGINE_AI_PAD(055)
	SIEGE_ENGINE_AI_PAD(056) SIEGE_ENGINE_AI_PAD(057)
	SIEGE_ENGINE_AI_PAD(058) SIEGE_ENGINE_AI_PAD(059)
	SIEGE_ENGINE_AI_PAD(060) SIEGE_ENGINE_AI_PAD(061)
	SIEGE_ENGINE_AI_PAD(062) SIEGE_ENGINE_AI_PAD(063)
	SIEGE_ENGINE_AI_PAD(064) SIEGE_ENGINE_AI_PAD(065)
	SIEGE_ENGINE_AI_PAD(066) SIEGE_ENGINE_AI_PAD(067)
	SIEGE_ENGINE_AI_PAD(068) SIEGE_ENGINE_AI_PAD(069)
	SIEGE_ENGINE_AI_PAD(070) SIEGE_ENGINE_AI_PAD(071)
	SIEGE_ENGINE_AI_PAD(072) SIEGE_ENGINE_AI_PAD(073)
	SIEGE_ENGINE_AI_PAD(074) SIEGE_ENGINE_AI_PAD(075)
	SIEGE_ENGINE_AI_PAD(076) SIEGE_ENGINE_AI_PAD(077)
	SIEGE_ENGINE_AI_PAD(078) SIEGE_ENGINE_AI_PAD(079)
	SIEGE_ENGINE_AI_PAD(080) SIEGE_ENGINE_AI_PAD(081)
	SIEGE_ENGINE_AI_PAD(082) SIEGE_ENGINE_AI_PAD(083)
	SIEGE_ENGINE_AI_PAD(084) SIEGE_ENGINE_AI_PAD(085)
	SIEGE_ENGINE_AI_PAD(086) SIEGE_ENGINE_AI_PAD(087)
	SIEGE_ENGINE_AI_PAD(088) SIEGE_ENGINE_AI_PAD(089)
	SIEGE_ENGINE_AI_PAD(090) SIEGE_ENGINE_AI_PAD(091)
	SIEGE_ENGINE_AI_PAD(092) SIEGE_ENGINE_AI_PAD(093)
	SIEGE_ENGINE_AI_PAD(094) SIEGE_ENGINE_AI_PAD(095)
	SIEGE_ENGINE_AI_PAD(096) SIEGE_ENGINE_AI_PAD(097)
	SIEGE_ENGINE_AI_PAD(098) SIEGE_ENGINE_AI_PAD(099)
	SIEGE_ENGINE_AI_PAD(100) SIEGE_ENGINE_AI_PAD(101)
	SIEGE_ENGINE_AI_PAD(102) SIEGE_ENGINE_AI_PAD(103)
	SIEGE_ENGINE_AI_PAD(104) SIEGE_ENGINE_AI_PAD(105)
	SIEGE_ENGINE_AI_PAD(106) SIEGE_ENGINE_AI_PAD(107)
	SIEGE_ENGINE_AI_PAD(108) SIEGE_ENGINE_AI_PAD(109)
	SIEGE_ENGINE_AI_PAD(110) SIEGE_ENGINE_AI_PAD(111)
	SIEGE_ENGINE_AI_PAD(112) SIEGE_ENGINE_AI_PAD(113)
	SIEGE_ENGINE_AI_PAD(114) SIEGE_ENGINE_AI_PAD(115)
	SIEGE_ENGINE_AI_PAD(116) SIEGE_ENGINE_AI_PAD(117)
	SIEGE_ENGINE_AI_PAD(118) SIEGE_ENGINE_AI_PAD(119)
	SIEGE_ENGINE_AI_PAD(120) SIEGE_ENGINE_AI_PAD(121)
	SIEGE_ENGINE_AI_PAD(122) SIEGE_ENGINE_AI_PAD(123)
	SIEGE_ENGINE_AI_PAD(124) SIEGE_ENGINE_AI_PAD(125)
	SIEGE_ENGINE_AI_PAD(126)
	virtual void __declspec(nothrow) invoke(int value);
#undef SIEGE_ENGINE_AI_PAD
};

class SiegeEngineContain
{
public:
	#define CONTAIN_SLOT(N) virtual void slot##N();
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02)
	CONTAIN_SLOT(03) CONTAIN_SLOT(04) CONTAIN_SLOT(05)
	CONTAIN_SLOT(06) CONTAIN_SLOT(07) CONTAIN_SLOT(08)
	CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14)
	CONTAIN_SLOT(15) CONTAIN_SLOT(16) CONTAIN_SLOT(17)
	CONTAIN_SLOT(18) CONTAIN_SLOT(19) CONTAIN_SLOT(20)
	CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26)
	CONTAIN_SLOT(27) CONTAIN_SLOT(28) CONTAIN_SLOT(29)
	CONTAIN_SLOT(30) CONTAIN_SLOT(31) CONTAIN_SLOT(32)
#undef CONTAIN_SLOT
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
	virtual void addToContain(Object *object);
	virtual void addToContainList(Object *object);

	char m_pad04[0xc4 - 4];
	BfmeContainList m_list;
	int m_count;
	unsigned char m_special;

	SiegeEngineModuleData *getModuleData(void) const
	{
		return *(SiegeEngineModuleData **)((const char *)this - 0x1c);
	}

	Object *getObject(void) const
	{
		return *(Object **)((const char *)this - 0x18);
	}
};

extern void j_00020824(void);
extern void j_0001da34(void);
extern void j_0001de71(void);
extern void j_0002191d(void);
extern void j_0003251f(void);
extern void j_000348ec(void);
extern void j_00034955(void);
extern void j_0004a74b(void);

union GetPlayerCall
{
	void (*raw)(void);
	Player *(Object::*fn)(void) const;
};

union AcceptsCall
{
	void (*raw)(void);
	Bool (Rva2225E0Filter::*fn)(Object *, Player *);
};

union PushBackCall
{
	void (*raw)(void);
	void (BfmeContainList::*fn)(Object *const &);
};

union NotifyCall
{
	void (*raw)(void);
	void (BfmeRvaA760Object::*fn)(void);
};

union KindCall
{
	void (*raw)(void);
	Bool (Thing::*fn)(KindOfType) const;
};

union WeaponSetCall
{
	void (*raw)(void);
	Bool (Thing::*fn)(WeaponSetType) const;
};

union ActionCall
{
	void (*raw)(void);
	void (BfmeObjE10::*fn)(int);
};

union FinishCall
{
	void (*raw)(void);
	void (BfmeRvaAA70Owner::*fn)(Object *);
};

void SiegeEngineContain::addToContainList(Object *object)
{
	Object *member = object;
	if (member == 0)
		return;
	Object *owner = getObject();
	if ((owner->m_typeFlags & 1) != 0)
		return;
	if ((member->m_typeFlags & 1) != 0)
		return;

	SiegeEngineModuleData *data = getModuleData();
	GetPlayerCall getPlayer = { j_00020824 };
	AcceptsCall accepts = { j_0001da34 };
	if ((data->m_filter.*accepts.fn)(member,
		(owner->*getPlayer.fn)()))
	{
		if (data->m_capacity > 0)
		{
			PushBackCall pushBack = { j_0001de71 };
			(m_list.*pushBack.fn)(object);
			++m_count;
			WeaponSetCall hasWeaponSet = { j_0004a74b };
			if ((((Thing *)member)->*hasWeaponSet.fn)((WeaponSetType)0x14))
			{
				ActionCall actionA = { j_000348ec };
				(((BfmeObjE10 *)member)->*actionA.fn)(0x14);
				unsigned char status = (unsigned char)member->m_status;
				if ((status & 0x80) == 0)
				{
					member->m_status |= 0x80;
					NotifyCall notify = { j_0002191d };
					(((BfmeRvaA760Object *)member)->*notify.fn)();
				}
			}
			if (member->m_ai == 0)
				goto fallback;
			return member->m_ai->invoke(10);
		}
	}

fallback:
	unsigned char flags = (unsigned char)member->m_flags;
	if ((flags & 0x40) == 0)
	{
		member->m_flags |= 0x40;
		NotifyCall notify = { j_0002191d };
		(((BfmeRvaA760Object *)member)->*notify.fn)();
	}
	FinishCall finish = { j_00034955 };
	(((BfmeRvaAA70Owner *)this)->*finish.fn)(member);
	KindCall isKindOf = { j_0003251f };
	if ((((Thing *)member)->*isKindOf.fn)((KindOfType)0x36))
		m_special = 1;
	return;
}
