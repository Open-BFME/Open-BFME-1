// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: SiegeEngineContain::removeFromContainList at retail 0x0022BE30.
// The constructor at 0x0022BC50 fixes the +0x04 module-data, +0x08 owner,
// and +0xE4 list layout. The primary vtable slot +0x2C and the neighboring
// isValidContainerFor body at 0x0022BF30 identify this SiegeEngineContain method.

class Player;

// Retail's incremental-link thunks for the calls below; each body is reached
// through its 5-byte ILT stub, so the calls name the thunk directly.
extern void j_00020824();
extern void j_0001da34();
extern void j_000122ab();
extern void j_0002191d();
extern void j_00031525();
extern void j_0003dee7();

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

class BfmeRvaA760Object
{
public:
	char m_head[0x128];
	union
	{
		unsigned char m_flagsByte;
		unsigned int m_flags;
	};
	unsigned int m_status;
	char m_gap[0x204 - 0x130];
	SiegeEngineMemberAI *m_ai;
};

class Object : public BfmeRvaA760Object
{
public:
};

class Rva2225E0Filter
{
public:
};

class SiegeEngineModuleData
{
public:
	char m_head[0x224];
	Rva2225E0Filter m_filter;
	int m_capacity;
};

class BfmeRvaA760Output
{
private:
	char m_pad[4];
};

class Rva223440PointerList
{
public:
};

class SiegeEngineContain
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
	virtual void slot10();
	virtual void removeFromContainList(Object *object);

	SiegeEngineModuleData *m_moduleData;
	Object *m_object;
	char m_gap[0xe4 - 0x0c];
	BfmeRvaA760Output m_list;
	int m_remaining;
};

void SiegeEngineContain::removeFromContainList(Object *object)
{
	Object *member = object;
	Object *owner = m_object;
	SiegeEngineModuleData *moduleData = m_moduleData;
	Player *player;
	{
		typedef Player *(Object::*GetControllingPlayer)(void) const;
		union { void (*fn)(); GetControllingPlayer call; } u = { j_00020824 };
		player = (owner->*u.call)();
	}
	bool accepted;
	{
		typedef bool (Rva2225E0Filter::*Accepts)(Object *, Player *);
		union { void (*fn)(); Accepts call; } u = { j_0001da34 };
		accepted = (moduleData->m_filter.*u.call)(member, player);
	}
	if (accepted)
	{
		if (moduleData->m_capacity > 0)
		{
			int output;
			{
				typedef void (BfmeRvaA760Output::*Fill)(int *);
				union { void (*fn)(); Fill call; } u = { j_00031525 };
				(m_list.*u.call)(&output);
			}
			--m_remaining;
			{
				typedef void (BfmeRvaA760Object::*Apply)(int);
				union { void (*fn)(); Apply call; } u = { j_000122ab };
				(member->*u.call)(0x14);
			}
			signed char status = (signed char)member->m_status;
			if ((status >> 7) != 0)
			{
				volatile unsigned int *statusPointer = (volatile unsigned int *)((char *)member + 0x12c);
				unsigned int statusWord = *statusPointer;
				statusWord &= 0xffffff7f;
				*statusPointer = statusWord;
				{
					typedef void (BfmeRvaA760Object::*Notify)(void);
					union { void (*fn)(); Notify call; } u = { j_0002191d };
					(member->*u.call)();
				}
			}
			if (!member->m_ai)
				goto finish;
			goto dispatch;
		}
	}

fallback:
	if ((member->m_flagsByte & 0x40) != 0)
	{
		member->m_flags &= 0xffffffbf;
		{
			typedef void (BfmeRvaA760Object::*Notify)(void);
			union { void (*fn)(); Notify call; } u = { j_0002191d };
			(member->*u.call)();
		}
	}
	{
		typedef void (Rva223440PointerList::*Remove)(void *);
		union { void (*fn)(); Remove call; } u = { j_0003dee7 };
		(((Rva223440PointerList *)this)->*u.call)(member);
	}

finish:
	return;

dispatch:
	return member->m_ai->invoke(0);
}
