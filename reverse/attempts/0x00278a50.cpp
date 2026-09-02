// ?privateFollowPath@AIUpdateInterface@@MAEXPBV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@PAVObject@@W4CommandSourceType@@H@Z
// partial score=0.8 date=2026-09-02
// ?privateFollowPath@AIUpdateInterface@@MAEXPBV?@UCoord3D@@V?@UCoord3D@@@_STL@@@_STL@@PAVObject@@W4CommandSourceType@@H@Z
// partial score=0.8 date=2026-09-02
// ?bfmeFollowPath36@AIUpdateInterface@@MAEXPBV?@UCoord3D@@V?@UCoord3D@@@_STL@@@_STL@@PAVObject@@W4CommandSourceType@@H@Z
// partial score=0.8 date=2026-09-02
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

enum StateID
{
	BFME_AI_FOLLOW_PATH_36 = 0x36
};

struct Coord3D
{
	float x, y, z;
};

class Object
{
public:
	Bool isMobile() const;
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
	void setGoalPosition(const Coord3D *pos);
	void setGoalPath(const _STL::vector<Coord3D> *path);
};

class AIUpdateInterface
{
protected:
	virtual void bfmeFollowPath36(const _STL::vector<Coord3D> *path, Object *ignoreObject,
		CommandSourceType cmdSource, int extra);
	void playMoveVoiceResponse(const Coord3D *position);
	void ignoreObstacle(Object *obj);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	unsigned char m_unmodelled_4C[0x1A0 - 0x4C];
	int m_extra1A0;
};

void AIUpdateInterface::bfmeFollowPath36(const _STL::vector<Coord3D> *path, Object *ignoreObject,
	CommandSourceType cmdSource, int extra)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	if (path->size() > 0)
	{
		Coord3D goal = (*path)[path->size() - 1];
		m_stateMachine->setGoalPosition(&goal);
		if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI)
			playMoveVoiceResponse(&goal);
	}
	m_stateMachine->setGoalPath(path);
	m_lastCommandSource = cmdSource;
	ignoreObstacle(ignoreObject);
	m_extra1A0 = extra;
	m_stateMachine->setState(BFME_AI_FOLLOW_PATH_36);
}
