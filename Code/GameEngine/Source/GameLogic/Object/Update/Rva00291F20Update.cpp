// cl: /DNDEBUG /MD /EHsc
// ?Rva00291F20@Rva00291F20Self@@QAEIXZ
// Module update whose this is the interface subobject at base+0x10; base fields are read at negative offsets.

class Player;
class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum DisabledType { DISABLED_TYPE_ZERO };

class Rva00291F20Vt204
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127(int mode);
};

class Rva00291F20Vt200
{
public:
	virtual void w0();
	virtual void w1();
	virtual void w2();
	virtual void w3();
	virtual void w4();
	virtual double w5();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void clearModelConditionState(int flag);
	void setMode(int flag, int value);
	void clearCondition(int flag);
	bool testStatus(int status) const;
	void setDisabledUntil(DisabledType type, unsigned int frame);

	unsigned char m_pad00[0x90];
	unsigned int m_status;
	unsigned char m_pad94[0x84];
	unsigned int m_flags118;
	unsigned char m_pad11c[0x10];
	unsigned int m_shroudRange;
	unsigned char m_pad130[0xd0];
	Rva00291F20Vt200 *m_slot200;
	Rva00291F20Vt204 *m_slot204;
	unsigned char m_pad208[0x13c];
	unsigned int m_flags344;
};

class BfmeRvaBA00Object
{
public:
	void action(int flag);
};

class BfmeItemRY
{
public:
	void bfmeDoRY(void *a, void *b);
};

void bfmeLinkRelation(void *list, Object *primary, int offset);

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Rva00291F20ModuleData
{
public:
	unsigned char m_pad00[0x0c];
	unsigned int m_delay0c;
	unsigned int m_delay10;
	float m_range14;
	void *m_filter18;
	void *m_filter1c;
	unsigned int m_delay20;
	void *m_fx24;
	void *m_fx28;
	void *m_fx2c;
};

// ABI views of retail filters. Vtables 010A5158/01085DC0/010BE58C
// have deleting destructors that route to 00201F10/000EC7A0/00291880;
// each restores the actual base vtable 01083B5C.
class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);

	unsigned int m_vptr;
	PartitionFilter *m_next;
};

class PartitionFilterA00291F20 : public PartitionFilter
{
public:
	__forceinline PartitionFilterA00291F20(const void *field, Player *player, bool match)
	{
		m_next = 0;
		*reinterpret_cast<unsigned int *>(this) = 0x010A5158;
		m_field = field;
		m_player = player;
		m_match = match;
	}

	~PartitionFilterA00291F20()
	{
		m_vptr = 0x01083B5C;
	}

	const void *m_field;
	Player *m_player;
	bool m_match;
};

class Rva001DCBB0Filter : public PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);

	~Rva001DCBB0Filter()
	{
		m_vptr = 0x01083B5C;
	}

	Player *m_player;
	unsigned char m_match;
};

class PartitionFilterB00291F20 : public PartitionFilter
{
public:
	__forceinline PartitionFilterB00291F20(Object *object, int mode, bool match)
	{
		m_next = 0;
		*reinterpret_cast<unsigned int *>(this) = 0x01085DC0;
		m_object = object;
		m_mode = mode;
		m_match = match;
	}

	~PartitionFilterB00291F20()
	{
		m_vptr = 0x01083B5C;
	}

	Object *m_object;
	int m_mode;
	bool m_match;
};

class PartitionFilterBase00291F20
{
public:
	__forceinline PartitionFilterBase00291F20()
	{
		m_next = 0;
		m_vptr = 0x010BE58C;
	}

	~PartitionFilterBase00291F20()
	{
		m_vptr = 0x01083B5C;
	}

	volatile unsigned int m_vptr;
	PartitionFilter * volatile m_next;
};

class PartitionFilterRoot00291F20
{
public:
	__forceinline PartitionFilterRoot00291F20()
	{
		m_next = 0;
		m_vptr = 0x01083B80;
	}

	~PartitionFilterRoot00291F20()
	{
		m_vptr = 0x01083B5C;
	}

	volatile unsigned int m_vptr;
	PartitionFilter * volatile m_next;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, float maxDistance,
		int distanceCalculation, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

class Rva00291F20Base
{
public:
	bool Rva00013642();
	bool Rva00030891();

	void *m_vfptr;
	const Rva00291F20ModuleData *m_moduleData;
	Object *m_object;
	void *m_vfptr2;
};

class Rva00291F20Self
{
public:
	unsigned int Rva00291F20();

private:
	unsigned char m_pad00[0x14];
	unsigned int m_frame14;
	unsigned int m_frame18;
	bool m_flag1c;
	bool m_flag1d;
	bool m_flag1e;
	bool m_flag1f;
	bool m_flag20;
};

#define BASE ((Rva00291F20Base *)((char *)this - 0x10))

unsigned int Rva00291F20Self::Rva00291F20()
{
	const Rva00291F20ModuleData *md = BASE->m_moduleData;
	Object *obj = BASE->m_object;

	if (obj->m_flags344 & 1)
		return 0x3fffffff;

	bool ready = m_frame14 <= TheBfmeGameLogic->m_frame && (obj->m_status & 0x400) == 0;
	if (m_flag1d)
		ready = true;

	if (m_flag1c && ready)
	{
		if (m_flag20)
			m_flag1f = false;

		if (!m_flag1f)
		{
			obj->clearModelConditionState(0x35);
			((BfmeRvaBA00Object *)obj)->action(0x16);
			Rva00291F20Vt204 *hook = obj->m_slot204;
			if (hook != 0)
				hook->v127(0);
			m_frame14 = 0x3fffffff;
			m_frame18 = TheBfmeGameLogic->m_frame + md->m_delay10;
			m_flag1c = false;
			m_flag1e = false;
			if (md->m_fx2c != 0)
				bfmeLinkRelation(md->m_fx2c, obj, 0);
		}
	}

	if (m_flag1c)
		return 1;

	if (m_frame18 >= TheBfmeGameLogic->m_frame && !m_flag1f)
		return 1;

	bool ok = false;
	if (BASE->Rva00013642())
		ok = true;
	if (BASE->Rva00030891())
		ok = true;
	Rva00291F20Vt200 *opacity = BASE->m_object->m_slot200;
	if (opacity != 0 && opacity->w5() < 0.5)
		ok = true;

	if (m_flag1e)
	{
		if ((obj->m_flags118 & 0x2000) == 0)
			ok = true;
	}
	else if (obj->m_flags118 & 0x2000)
	{
		m_flag1e = true;
	}

	if (obj->m_status & 0x400)
		ok = false;
	if (m_flag1f)
		ok = true;

	if (m_flag1d)
		return 1;
	if (!ok)
		return 1;

	if ((obj->m_shroudRange & 0x8000) == 0 && !obj->testStatus(0xa))
	{
		((BfmeItemRY *)obj)->bfmeDoRY((void *)0x11a, (void *)md->m_delay20);
		obj->setDisabledUntil((DisabledType)4, TheBfmeGameLogic->m_frame + md->m_delay20);
		if (md->m_fx24 != 0)
			bfmeLinkRelation(md->m_fx24, obj, 0);
	}

	obj->setMode(0x35, 1);
	obj->clearCondition(0x16);
	Rva00291F20Vt204 *hook2 = obj->m_slot204;
	if (hook2 != 0)
		hook2->v127(8);
	m_flag1c = true;
	m_frame14 = TheBfmeGameLogic->m_frame + md->m_delay0c;
	if (md->m_fx28 != 0)
		bfmeLinkRelation(md->m_fx28, obj, 0);

	return 1;
}

bool Rva00291F20Base::Rva00013642()
{
	Object *object = m_object;
	const Rva00291F20ModuleData *moduleData = m_moduleData;
	Player *player = object->getControllingPlayer();
	PartitionFilterA00291F20 playerFilter(&moduleData->m_filter18, player, true);
	PartitionFilterB00291F20 relationshipFilter(object, 4, false);
	PartitionFilterBase00291F20 baseFilter;
	playerFilter.link(reinterpret_cast<PartitionFilter *>(&baseFilter));
	playerFilter.link(&relationshipFilter);
	return ThePartitionManager->getClosestObject(
		reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(object) + 0x38),
		moduleData->m_range14, 1, &playerFilter) != 0;
}

bool Rva00291F20Base::Rva00030891()
{
	Object *object = m_object;
	const Rva00291F20ModuleData *moduleData = m_moduleData;
	Rva001DCBB0Filter playerFilter(object, 0);
	Player *player = object->getControllingPlayer();
	PartitionFilterA00291F20 affiliationFilter(&moduleData->m_filter1c, player, true);
	PartitionFilterRoot00291F20 baseFilter;
	playerFilter.link(&affiliationFilter);
	playerFilter.link(reinterpret_cast<PartitionFilter *>(&baseFilter));
	return ThePartitionManager->getClosestObject(
		reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(object) + 0x38),
		moduleData->m_range14, 1, &playerFilter) != 0;
}
