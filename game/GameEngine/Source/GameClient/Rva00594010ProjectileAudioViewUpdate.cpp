// cl: /DNDEBUG /MD
// Retail 0x00594010: scan the client drawable chain for a projectile object,
// queue its projectile-side MiscAudio event, and notify the tactical view.
// The owner name is address-derived: no matched caller or RTTI names this
// body.  The fields and virtual slots below are constrained by the retail
// instructions and by the existing BFME client/audio shims.

typedef unsigned int UnsignedInt;
typedef int ObjectID;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	void *m_vtable;
	BfmeOverridable *m_nextOverride;
};

class Rva00594010Template : public BfmeOverridable
{
public:
	unsigned char m_bfmePadding[0xC8];
	UnsignedInt m_kindOf;
};

class Rva00594010Object
{
public:
	void *m_vtable;
	Rva00594010Template *m_template;
	unsigned char m_bfmePadding[0x6C];
	ObjectID m_id;
};

class ClientNode4120
{
public:
	unsigned char m_bfmeHead[0xFC];
	Rva00594010Object *m_object;
	unsigned char m_bfmeBetweenLinks[4];
	ClientNode4120 *m_next;
	unsigned char m_bfmeToProjectileFlag[0x2A4];
	unsigned char m_projectileScanEnabled;
};

class ClientRoot4120
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
	virtual ClientNode4120 *getHead();
};

extern ClientRoot4120 *TheGameClient;

class ClientSubsystem
{
public:
#define CLIENT_SUBSYSTEM_SLOT(number) virtual void slot##number();
	CLIENT_SUBSYSTEM_SLOT(00) CLIENT_SUBSYSTEM_SLOT(01)
	CLIENT_SUBSYSTEM_SLOT(02) CLIENT_SUBSYSTEM_SLOT(03)
	CLIENT_SUBSYSTEM_SLOT(04) CLIENT_SUBSYSTEM_SLOT(05)
	CLIENT_SUBSYSTEM_SLOT(06) CLIENT_SUBSYSTEM_SLOT(07)
	CLIENT_SUBSYSTEM_SLOT(08) CLIENT_SUBSYSTEM_SLOT(09)
	CLIENT_SUBSYSTEM_SLOT(10) CLIENT_SUBSYSTEM_SLOT(11)
	CLIENT_SUBSYSTEM_SLOT(12) CLIENT_SUBSYSTEM_SLOT(13)
	CLIENT_SUBSYSTEM_SLOT(14) CLIENT_SUBSYSTEM_SLOT(15)
	CLIENT_SUBSYSTEM_SLOT(16)
	virtual void addAudioEvent(void *event);
	CLIENT_SUBSYSTEM_SLOT(18) CLIENT_SUBSYSTEM_SLOT(19)
	CLIENT_SUBSYSTEM_SLOT(20) CLIENT_SUBSYSTEM_SLOT(21)
	CLIENT_SUBSYSTEM_SLOT(22) CLIENT_SUBSYSTEM_SLOT(23)
	CLIENT_SUBSYSTEM_SLOT(24) CLIENT_SUBSYSTEM_SLOT(25)
	CLIENT_SUBSYSTEM_SLOT(26) CLIENT_SUBSYSTEM_SLOT(27)
	CLIENT_SUBSYSTEM_SLOT(28) CLIENT_SUBSYSTEM_SLOT(29)
	CLIENT_SUBSYSTEM_SLOT(30) CLIENT_SUBSYSTEM_SLOT(31)
	CLIENT_SUBSYSTEM_SLOT(32) CLIENT_SUBSYSTEM_SLOT(33)
	CLIENT_SUBSYSTEM_SLOT(34) CLIENT_SUBSYSTEM_SLOT(35)
	CLIENT_SUBSYSTEM_SLOT(36) CLIENT_SUBSYSTEM_SLOT(37)
	CLIENT_SUBSYSTEM_SLOT(38) CLIENT_SUBSYSTEM_SLOT(39)
	CLIENT_SUBSYSTEM_SLOT(40) CLIENT_SUBSYSTEM_SLOT(41)
	CLIENT_SUBSYSTEM_SLOT(42) CLIENT_SUBSYSTEM_SLOT(43)
	CLIENT_SUBSYSTEM_SLOT(44) CLIENT_SUBSYSTEM_SLOT(45)
	CLIENT_SUBSYSTEM_SLOT(46) CLIENT_SUBSYSTEM_SLOT(47)
	CLIENT_SUBSYSTEM_SLOT(48) CLIENT_SUBSYSTEM_SLOT(49)
	CLIENT_SUBSYSTEM_SLOT(50) CLIENT_SUBSYSTEM_SLOT(51)
	CLIENT_SUBSYSTEM_SLOT(52) CLIENT_SUBSYSTEM_SLOT(53)
	CLIENT_SUBSYSTEM_SLOT(54) CLIENT_SUBSYSTEM_SLOT(55)
	CLIENT_SUBSYSTEM_SLOT(56) CLIENT_SUBSYSTEM_SLOT(57)
	CLIENT_SUBSYSTEM_SLOT(58) CLIENT_SUBSYSTEM_SLOT(59)
	CLIENT_SUBSYSTEM_SLOT(60) CLIENT_SUBSYSTEM_SLOT(61)
	CLIENT_SUBSYSTEM_SLOT(62) CLIENT_SUBSYSTEM_SLOT(63)
	CLIENT_SUBSYSTEM_SLOT(64) CLIENT_SUBSYSTEM_SLOT(65)
	CLIENT_SUBSYSTEM_SLOT(66) CLIENT_SUBSYSTEM_SLOT(67)
	CLIENT_SUBSYSTEM_SLOT(68) CLIENT_SUBSYSTEM_SLOT(69)
	CLIENT_SUBSYSTEM_SLOT(70) CLIENT_SUBSYSTEM_SLOT(71)
	CLIENT_SUBSYSTEM_SLOT(72)
	virtual void *getMiscAudio();
#undef CLIENT_SUBSYSTEM_SLOT
};

extern ClientSubsystem *TheAudioClientUpdate;

class View
{
public:
#define VIEW_SLOT(number) virtual void slot##number();
	VIEW_SLOT(000) VIEW_SLOT(001) VIEW_SLOT(002) VIEW_SLOT(003)
	VIEW_SLOT(004) VIEW_SLOT(005) VIEW_SLOT(006) VIEW_SLOT(007)
	VIEW_SLOT(008) VIEW_SLOT(009) VIEW_SLOT(010) VIEW_SLOT(011)
	VIEW_SLOT(012) VIEW_SLOT(013) VIEW_SLOT(014) VIEW_SLOT(015)
	VIEW_SLOT(016) VIEW_SLOT(017) VIEW_SLOT(018) VIEW_SLOT(019)
	VIEW_SLOT(020) VIEW_SLOT(021) VIEW_SLOT(022) VIEW_SLOT(023)
	VIEW_SLOT(024) VIEW_SLOT(025) VIEW_SLOT(026) VIEW_SLOT(027)
	VIEW_SLOT(028) VIEW_SLOT(029) VIEW_SLOT(030) VIEW_SLOT(031)
	VIEW_SLOT(032) VIEW_SLOT(033) VIEW_SLOT(034) VIEW_SLOT(035)
	VIEW_SLOT(036) VIEW_SLOT(037) VIEW_SLOT(038) VIEW_SLOT(039)
	VIEW_SLOT(040) VIEW_SLOT(041) VIEW_SLOT(042) VIEW_SLOT(043)
	VIEW_SLOT(044) VIEW_SLOT(045) VIEW_SLOT(046) VIEW_SLOT(047)
	VIEW_SLOT(048) VIEW_SLOT(049) VIEW_SLOT(050) VIEW_SLOT(051)
	VIEW_SLOT(052) VIEW_SLOT(053) VIEW_SLOT(054) VIEW_SLOT(055)
	VIEW_SLOT(056) VIEW_SLOT(057) VIEW_SLOT(058) VIEW_SLOT(059)
	VIEW_SLOT(060) VIEW_SLOT(061) VIEW_SLOT(062) VIEW_SLOT(063)
	VIEW_SLOT(064) VIEW_SLOT(065) VIEW_SLOT(066) VIEW_SLOT(067)
	VIEW_SLOT(068) VIEW_SLOT(069) VIEW_SLOT(070) VIEW_SLOT(071)
	VIEW_SLOT(072) VIEW_SLOT(073) VIEW_SLOT(074) VIEW_SLOT(075)
	VIEW_SLOT(076) VIEW_SLOT(077) VIEW_SLOT(078) VIEW_SLOT(079)
	VIEW_SLOT(080) VIEW_SLOT(081) VIEW_SLOT(082) VIEW_SLOT(083)
	VIEW_SLOT(084) VIEW_SLOT(085) VIEW_SLOT(086) VIEW_SLOT(087)
	VIEW_SLOT(088) VIEW_SLOT(089) VIEW_SLOT(090) VIEW_SLOT(091)
	VIEW_SLOT(092) VIEW_SLOT(093) VIEW_SLOT(094) VIEW_SLOT(095)
	virtual void notifyProjectile(ObjectID id);
	VIEW_SLOT(097) VIEW_SLOT(098) VIEW_SLOT(099) VIEW_SLOT(100)
	VIEW_SLOT(101) VIEW_SLOT(102) VIEW_SLOT(103) VIEW_SLOT(104)
	VIEW_SLOT(105) VIEW_SLOT(106) VIEW_SLOT(107) VIEW_SLOT(108)
	VIEW_SLOT(109) VIEW_SLOT(110) VIEW_SLOT(111) VIEW_SLOT(112)
	VIEW_SLOT(113) VIEW_SLOT(114)
	virtual void notifyProjectileState(int first, ObjectID id, int third, int fourth);
#undef VIEW_SLOT
};

extern View *TheTacticalView;

class Rva00594010
{
public:
	void update();

private:
	unsigned char m_bfmePadding[0x48];
	unsigned char m_updateComplete;
};

// ?update@Rva00594010@@QAEXXZ
void Rva00594010::update()
{
	ObjectID objectID = 0;
	ClientNode4120 *drawable = TheGameClient->getHead();
	if (drawable != 0)
	{
		do
		{
			if (drawable->m_projectileScanEnabled != 0)
			{
				Rva00594010Object *object = drawable->m_object;
				if (object != 0)
				{
					Rva00594010Template *thingTemplate = object->m_template;
					if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
						thingTemplate = (Rva00594010Template *)
							thingTemplate->m_nextOverride->friend_getFinalOverride();
					if ((thingTemplate->m_kindOf & 0x02000000) != 0)
					{
						objectID = object->m_id;
						if (objectID != 0 && TheAudioClientUpdate != 0 &&
							TheAudioClientUpdate->getMiscAudio() != 0)
						{
							TheAudioClientUpdate->addAudioEvent(
								reinterpret_cast<char *>(TheAudioClientUpdate->getMiscAudio()) + 0xB60);
						}
						break;
					}
				}
			}
			drawable = drawable->m_next;
		} while (drawable != 0);
	}

	TheTacticalView->notifyProjectile(objectID);
	TheTacticalView->notifyProjectileState(0, objectID, 1, 1);
	m_updateComplete = 1;
}
