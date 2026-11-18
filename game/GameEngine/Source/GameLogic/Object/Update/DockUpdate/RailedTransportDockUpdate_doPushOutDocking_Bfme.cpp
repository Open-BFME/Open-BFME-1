// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-

// RailedTransportDockUpdate::doPushOutDocking (retail 0x002CEA90, 446 B).
// BFME's RailedTransportDockUpdate is four bytes narrower than the Zero Hour
// class at the dock interface boundary, so this TU keeps a local ABI view of
// the class, like its sibling doPullInDocking at 0x002CE900.
//
// The body is Zero Hour's: the *=/+= spelling of the push step inside the
// block that Zero Hour opens with "if( unloader )".  VC7.1 keeps both
// products on the x87 stack and stores v.z between them only while v lives
// in that inner block; with v in the outer scope it spills v.x and v.y after
// each product (460 B).  The redundant test itself is not in retail, so the
// block stands without it.

#include "../../../../../Include/Common/ScalarTypes.h"
typedef unsigned int ObjectID;

enum DisabledType
{
	DISABLED_HELD = 3
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNSELECTABLE = 3
};

#include "../../../command_source_type.h"




enum ModelConditionFlagType
{
	MODELCONDITION_MOVING = 60
};

// class-gate: allow Coord3D the canonical header is the bare 12-byte layout; this body calls Coord3D::normalize (ILT 0x2BD82 -> 0x000FB930), a member it omits (446/446, 0 non-reloc diffs).
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void normalize();
};

class Matrix3D;

class BFMEDrawableBoneQuery
{
public:
	// BFME's six-argument form has a default final argument at this call site.
	int getPristineBonePositions(const char *boneNamePrefix, int startIndex,
		Coord3D *positions, Matrix3D *transforms, int maxBones,
		int extra = 0) const;
};

class Thing
{
public:
	virtual void slot00();
	void setPosition(const Coord3D *position);

	const Coord3D *getPosition() const
	{
		return &m_cachedPos;
	}

private:
	unsigned char m_beforePosition[0x34];
	Coord3D m_cachedPos;
};

class ModelConditionFlags
{
public:
	unsigned int m_bits() const
	{
		return m_bitsValue[1];
	}

	void set(unsigned int condition)
	{
		m_bitsValue[1] |= condition;
	}

	void clear(unsigned int condition)
	{
		m_bitsValue[1] &= ~condition;
	}

private:
	unsigned int m_bitsValue[10];
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
	void aiMoveToPosition(const Coord3D *position, CommandSourceType source);
};

// The BFME AIUpdate object carries the command-interface subobject at +0x20.
// The leading storage is deliberately explicit so the compiler performs the
// same secondary-base adjustment on both direct calls below.
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
	virtual BFMEDrawableBoneQuery *getDrawable() const;

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return m_ai;
	}

	void notifyModelConditionChanged();
	bool clearDisabled(DisabledType type);
	void clearStatus(ObjectStatusTypes status);

	void setModelConditionState()
	{
		unsigned int condition = 0x10000000;
		unsigned int flags = m_modelConditionFlags.m_bits();
		if ((condition & flags) == 0)
		{
			m_modelConditionFlags.set(condition);
			notifyModelConditionChanged();
		}
	}

	void clearModelConditionState()
	{
		unsigned int condition = 0x10000000;
		unsigned int flags = m_modelConditionFlags.m_bits();
		if ((condition & flags) != 0)
		{
			m_modelConditionFlags.clear(condition);
			notifyModelConditionChanged();
		}
	}

	void convertBonePosToWorldPos(const Coord3D *position,
		const Matrix3D *transform, Coord3D *worldPosition,
		Matrix3D *worldTransform) const;

	unsigned char m_beforeID[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_beforeModelConditions[0x110 - 0x78];

public:
	ModelConditionFlags m_modelConditionFlags;

private:
	unsigned char m_beforeAI[0x204 - 0x138];
	AIUpdateInterface *m_ai;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class DockUpdateInterfaceSlots0To6
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
};

class DockUpdateInterface : public DockUpdateInterfaceSlots0To6
{
public:
	virtual void getExitPosition(Object *docker, Coord3D *position);
};

class RailedTransportDockUpdate
{
protected:
	void doPushOutDocking();
	void unloadNext();
public:

	Object *getObject() const
	{
		return m_object;
	}

private:
	unsigned char m_prefix[4];
	void *m_moduleData;
	Object *m_object;
	unsigned char m_beforeDockInterface[0x14];
	DockUpdateInterface m_dockInterface;
	unsigned char m_beforeUnloadingID[0x70];
	ObjectID m_unloadingObjectID;
	Real m_pushOutsideDistancePerFrame;
};

extern GameLogic *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;

#define sqr(value) ((value) * (value))

// ?doPushOutDocking@RailedTransportDockUpdate@@IAEXXZ
void RailedTransportDockUpdate::doPushOutDocking()
{
	if (m_unloadingObjectID)
	{
		Object *unloader = TheGameLogic->findObjectByID(m_unloadingObjectID);
		if (unloader == 0)
		{
			unloadNext();
			return;
		}

		{
			const Coord3D *unloaderPos = unloader->getPosition();

			Coord3D destPos;
			m_dockInterface.getExitPosition(unloader, &destPos);
			destPos.z = TheTerrainLogic->getGroundHeight(destPos.x, destPos.y);

			Coord3D v;
			v.x = destPos.x - unloaderPos->x;
			v.y = destPos.y - unloaderPos->y;
			v.z = destPos.z - unloaderPos->z;
			v.normalize();

			v.x *= m_pushOutsideDistancePerFrame;
			v.y *= m_pushOutsideDistancePerFrame;
			v.x += unloaderPos->x;
			v.y += unloaderPos->y;
			v.z = destPos.z;

			unloader->setPosition(&v);

			unloader->setModelConditionState();

			Real dx = destPos.x - v.x;
			Real dy = destPos.y - v.y;
			Real dz = destPos.z - v.z;
			Real distSq = sqr(dx) + sqr(dy) + sqr(dz);
			Real closeEnoughDistance = 3.0f;
			if (distSq <= sqr(closeEnoughDistance))
			{
				Object *us = getObject();

				unloader->clearModelConditionState();

				AIUpdateInterface *unloaderAI = unloader->getAIUpdateInterface();
				if (unloaderAI)
					unloaderAI->aiIdle(CMD_FROM_AI);

				unloader->clearDisabled(DISABLED_HELD);
				unloader->clearStatus(OBJECT_STATUS_UNSELECTABLE);

				BFMEDrawableBoneQuery *draw = us->getDrawable();
				if (unloaderAI && draw)
				{
					Coord3D finalPos;
					draw->getPristineBonePositions("DOCKWAITING07", 0,
						&finalPos, 0, 1);
					us->convertBonePosToWorldPos(&finalPos, 0, &finalPos, 0);
					unloaderAI->aiMoveToPosition(&finalPos, CMD_FROM_AI);
				}

				unloadNext();
			}
		}
	}
}
