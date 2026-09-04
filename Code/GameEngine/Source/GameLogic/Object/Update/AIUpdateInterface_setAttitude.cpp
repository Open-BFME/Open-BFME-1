// cl: /DNDEBUG /MD /EHs-c-
// AIUpdateSetAttitudeShim::setAttitude — retail 0x0027DEF0 / 128B.
// Dump sibling of BoneFXUpdate::initTimes in Code/gen_asm/d_0027db50.asm.
// Identity: ILT 0x00030553 -> this body; AIGroup::setAttitude (0x00150FE0)
// calls it on each member AI at Object+0x204.
// ZH setAttitude is a 13-byte store; BFME adds a -3 (clear) path that idles
// the command interface and notifies the looked-up object's AI.
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

enum AttitudeType
{
	ATTITUDE_BFME_CLEAR = -3
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;
class AINotify;
class Slot38Target;
class AICommandInterface;
class GameLogic;

class AIUpdateSetAttitudeShim
{
public:
	void setAttitude(AttitudeType tude);

	unsigned char m_beforeObject[8];
	Object *m_object;
	unsigned char m_beforeCommand[0x20 - 0x0C];
	unsigned char m_command[0x10];
	Slot38Target *m_slot38;
	unsigned char m_beforeId[0x40 - 0x34];
	int m_lookedUpId;
	unsigned char m_beforeAttitude[0x1F8 - 0x44];
	AttitudeType m_attitude;
};

class Object
{
public:
	unsigned char m_beforeId[0x74];
	int m_id;
	unsigned char m_beforeAI[0x204 - 0x78];
	AINotify *m_ai;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmd);
};

class Slot38Target
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void clear(int);
};

class AINotify
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
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
	virtual void notify(int objectId, int);
};

GameLogic *TheBfmeGameLogic;

void AIUpdateSetAttitudeShim::setAttitude(AttitudeType tude)
{
	m_attitude = tude;
	if (tude != ATTITUDE_BFME_CLEAR)
		return;

	if (m_lookedUpId)
	{
		Object *found = TheBfmeGameLogic->findObjectByID(m_lookedUpId);
		if (found)
		{
			m_slot38->clear(0);
			reinterpret_cast<AICommandInterface *>(m_command)->aiIdle(CMD_FROM_AI);
		}
	}

	if (m_lookedUpId)
	{
		Object *self = m_object;
		Object *found = TheBfmeGameLogic->findObjectByID(m_lookedUpId);
		if (self && found)
		{
			AINotify *ai = found->m_ai;
			if (ai)
				ai->notify(self->m_id, 0);
		}
	}

	m_lookedUpId = 0;
}
