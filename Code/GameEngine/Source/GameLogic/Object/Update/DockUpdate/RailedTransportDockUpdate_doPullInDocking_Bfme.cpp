// cl: /O2 /Ob2 /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-

typedef float Real;
typedef unsigned int ObjectID;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void normalize();
};

class Thing
{
public:
	void setPosition(const Coord3D *position);
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class AIUpdatePrimary
{
public:
	virtual void slot00();

private:
	unsigned char m_beforeCommandInterface[0x1c];
};

class AIUpdateInterface : public AIUpdatePrimary, public AICommandInterface
{
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *reinterpret_cast<AIUpdateInterface *const *>(
			reinterpret_cast<const char *>(this) + 0x204);
	}

	void notifyModelConditionChanged();

	void setModelConditionState()
	{
		const unsigned int condition = 0x10000000;
		unsigned int flags = *reinterpret_cast<const unsigned int *>(
			reinterpret_cast<const char *>(this) + 0x114);
		if ((flags & condition) == 0)
		{
			*reinterpret_cast<unsigned int *>(
				reinterpret_cast<char *>(this) + 0x114) = flags | condition;
			notifyModelConditionChanged();
		}
	}

	void clearModelConditionState()
	{
		const unsigned int condition = 0x10000000;
		unsigned int flags = *reinterpret_cast<const unsigned int *>(
			reinterpret_cast<const char *>(this) + 0x114);
		if ((flags & condition) != 0)
		{
			*reinterpret_cast<unsigned int *>(
				reinterpret_cast<char *>(this) + 0x114) = flags & ~condition;
			notifyModelConditionChanged();
		}
	}

	class ContainModuleInterface *getContain() const
	{
		return *reinterpret_cast<class ContainModuleInterface *const *>(
			reinterpret_cast<const char *>(this) + 0x1fc);
	}
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class DockUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void cancelDock(Object *docker);
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void addToContain(Object *object);
};

class Rva002CE900RailedTransportDockUpdate
{
protected:
	void doPullInDocking();

private:
	unsigned char m_prefix[4];
	void *m_moduleData;
	Object *m_object;
	unsigned char m_beforeDockInterface[0x14];
	DockUpdateInterface m_dockInterface;
	unsigned char m_beforeDockingID[0x68];
	ObjectID m_dockingObjectID;
	Real m_pullInsideDistancePerFrame;
};

extern GameLogic *TheGameLogic;

// ?doPullInDocking@RailedTransportDockUpdate@@IAEXXZ
void Rva002CE900RailedTransportDockUpdate::doPullInDocking()
{
	if (m_dockingObjectID)
	{
		Object *us = m_object;
		Object *docker = TheGameLogic->findObjectByID(m_dockingObjectID);
		if (docker == 0)
			m_dockingObjectID = 0;
		if (docker)
		{
			const Coord3D *dockerPos = docker->getPosition();
			const Coord3D *dockPos = us->getPosition();

			Coord3D v;
			v.x = dockPos->x - dockerPos->x;
			v.y = dockPos->y - dockerPos->y;
			v.z = dockPos->z - dockerPos->z;
			v.normalize();

			v.x *= m_pullInsideDistancePerFrame;
			v.y *= m_pullInsideDistancePerFrame;
			v.x += dockerPos->x;
			v.y += dockerPos->y;
			v.z = dockerPos->z;

			docker->setPosition(&v);
			docker->setModelConditionState();

			Real dx = dockerPos->x - dockPos->x;
			Real dy = dockerPos->y - dockPos->y;
			Real distSq = dx * dx + dy * dy;
			if (distSq <= *(const Real *)0x010CAE24)
			{
				docker->clearModelConditionState();
				m_dockInterface.cancelDock(docker);

				AIUpdateInterface *dockerAI = docker->getAIUpdateInterface();
				if (dockerAI)
					dockerAI->aiIdle(CMD_FROM_AI);

				ContainModuleInterface *contain = us->getContain();
				if (contain)
				{
					contain->addToContain(docker);
				}
				m_dockingObjectID = 0;
			}
		}
	}
}
