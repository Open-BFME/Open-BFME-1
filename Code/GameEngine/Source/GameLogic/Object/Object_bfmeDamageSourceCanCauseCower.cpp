// cl: /DNDEBUG /MD /EHsc

// Open-BFME: retail 0x001C5D00. AICowerState::update passes the recent damage
// source ObjectID here. AI vtable slot 131 defaults true, while GiantBirdAI
// overrides it false, which identifies this as the source-can-cause-cower test.

typedef int Int;
typedef bool Bool;
typedef Int ObjectID;

class AIUpdateInterface
{
public:
#define BFME_SLOT(n) virtual Int bfmeSlot##n() = 0
	BFME_SLOT(000); BFME_SLOT(001); BFME_SLOT(002); BFME_SLOT(003);
	BFME_SLOT(004); BFME_SLOT(005); BFME_SLOT(006); BFME_SLOT(007);
	BFME_SLOT(008); BFME_SLOT(009); BFME_SLOT(010); BFME_SLOT(011);
	BFME_SLOT(012); BFME_SLOT(013); BFME_SLOT(014); BFME_SLOT(015);
	BFME_SLOT(016); BFME_SLOT(017); BFME_SLOT(018); BFME_SLOT(019);
	BFME_SLOT(020); BFME_SLOT(021); BFME_SLOT(022); BFME_SLOT(023);
	BFME_SLOT(024); BFME_SLOT(025); BFME_SLOT(026); BFME_SLOT(027);
	BFME_SLOT(028); BFME_SLOT(029); BFME_SLOT(030); BFME_SLOT(031);
	BFME_SLOT(032); BFME_SLOT(033); BFME_SLOT(034); BFME_SLOT(035);
	BFME_SLOT(036); BFME_SLOT(037); BFME_SLOT(038); BFME_SLOT(039);
	BFME_SLOT(040); BFME_SLOT(041); BFME_SLOT(042); BFME_SLOT(043);
	BFME_SLOT(044); BFME_SLOT(045); BFME_SLOT(046); BFME_SLOT(047);
	BFME_SLOT(048); BFME_SLOT(049); BFME_SLOT(050); BFME_SLOT(051);
	BFME_SLOT(052); BFME_SLOT(053); BFME_SLOT(054); BFME_SLOT(055);
	BFME_SLOT(056); BFME_SLOT(057); BFME_SLOT(058); BFME_SLOT(059);
	BFME_SLOT(060); BFME_SLOT(061); BFME_SLOT(062); BFME_SLOT(063);
	BFME_SLOT(064); BFME_SLOT(065); BFME_SLOT(066); BFME_SLOT(067);
	BFME_SLOT(068); BFME_SLOT(069); BFME_SLOT(070); BFME_SLOT(071);
	BFME_SLOT(072); BFME_SLOT(073); BFME_SLOT(074); BFME_SLOT(075);
	BFME_SLOT(076); BFME_SLOT(077); BFME_SLOT(078); BFME_SLOT(079);
	BFME_SLOT(080); BFME_SLOT(081); BFME_SLOT(082); BFME_SLOT(083);
	BFME_SLOT(084); BFME_SLOT(085); BFME_SLOT(086); BFME_SLOT(087);
	BFME_SLOT(088); BFME_SLOT(089); BFME_SLOT(090); BFME_SLOT(091);
	BFME_SLOT(092); BFME_SLOT(093); BFME_SLOT(094); BFME_SLOT(095);
	BFME_SLOT(096); BFME_SLOT(097); BFME_SLOT(098); BFME_SLOT(099);
	BFME_SLOT(100); BFME_SLOT(101); BFME_SLOT(102); BFME_SLOT(103);
	BFME_SLOT(104); BFME_SLOT(105); BFME_SLOT(106); BFME_SLOT(107);
	BFME_SLOT(108); BFME_SLOT(109); BFME_SLOT(110); BFME_SLOT(111);
	BFME_SLOT(112); BFME_SLOT(113); BFME_SLOT(114); BFME_SLOT(115);
	BFME_SLOT(116); BFME_SLOT(117); BFME_SLOT(118); BFME_SLOT(119);
	BFME_SLOT(120); BFME_SLOT(121); BFME_SLOT(122); BFME_SLOT(123);
	BFME_SLOT(124); BFME_SLOT(125); BFME_SLOT(126); BFME_SLOT(127);
	BFME_SLOT(128); BFME_SLOT(129); BFME_SLOT(130);
#undef BFME_SLOT
	virtual Bool bfmeCanCauseCower() const = 0;
};

class Object
{
private:
	unsigned char m_unreconstructed[0x204];
	AIUpdateInterface *m_ai;

public:
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Bool bfmeDamageSourceCanCauseCower(ObjectID sourceID) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

Bool Object::bfmeDamageSourceCanCauseCower(ObjectID sourceID) const
{
	Object *source = TheGameLogic->findObjectByID(sourceID);
	if (source == 0)
		return false;
	AIUpdateInterface *ai = source->getAIUpdateInterface();
	if (ai == 0)
		return false;
	return ai->bfmeCanCauseCower();
}
