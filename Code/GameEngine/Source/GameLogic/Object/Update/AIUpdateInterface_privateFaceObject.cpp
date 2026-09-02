// cl: /DNDEBUG /MD
//
// Retail 0x00279180: AIUpdateInterface::privateFaceObject.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

enum StateID
{
	BFME_AI_FACE_OBJECT = 0x1F
};

struct Coord3D
{
	float x, y, z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[0xC8 - 8];
	UnsignedInt m_kindof[3];
};

class Thing
{
public:
	virtual void slot00();
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Bool isMobile() const;
	Coord3D getPosition() const;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
};

class AIUpdateInterface
{
protected:
	virtual void privateFaceObject(Object *obj, CommandSourceType cmdSource);
	void playAttackVoiceResponse(const Coord3D *position);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[0x6C - 0x4C];
	Object *m_faceObject;
};

void AIUpdateInterface::privateFaceObject(Object *obj, CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	ThingTemplate *const volatile *templateSlot = &m_object->m_template;
	ThingTemplate *tmpl = *templateSlot;
	if (tmpl && tmpl->m_nextOverride)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if (tmpl->m_kindof[0] & 0x2000000)
		return;

	m_faceObject = obj;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_FACE_OBJECT);

	if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
	{
		Coord3D pos = obj->getPosition();
		playAttackVoiceResponse(&pos);
	}
}
