// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// TEAM_MOVE_TO_NEAREST_OBJECT_OF_KINDOF_OWNED_BY_PLAYER (action template 392).
// Retail RVA 0x002FCA30 walks the player mask from a Parameter, finds each
// player's nearest object with the kind bit and moves the team to the closest.

extern "C" double sqrt(double value);

#include <bitset>

typedef bool Bool;
typedef float Real;
typedef unsigned short PlayerMaskType;

#include "ascii_string.h"

class BfmeAsciiStringArg : public AsciiString
{
public:
	BfmeAsciiStringArg(const AsciiString &that) : AsciiString(that) {}
	~BfmeAsciiStringArg();
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void sub(const Coord3D *other)
	{
		x -= other->x;
		y -= other->y;
		z -= other->z;
	}

	Real length(void) const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}
};

template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}
};

typedef BitFlags<192> KindOfMaskType;

class Object
{
public:
	char m_beforePosition[0x38];
	Coord3D m_position;
};

class Player
{
public:
	Object *findClosestByKindOf(const Coord3D *position,
		KindOfMaskType setMask, KindOfMaskType clearMask);
};

class Parameter;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class AIGroup
{
};

struct Rva0015A190Packet
{
	void *m_first;
	unsigned char m_flag;
	void *m_objA;
	void *m_objB;
};

class Rva0015A190Owner
{
public:
	void applyPacket(Rva0015A190Packet *packet, int command);
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *position) const;
	void getTeamAsAIGroup(AIGroup *group);
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

extern const KindOfMaskType KINDOFMASK_NONE;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamMoveToNearestObjectOfKindOfOwnedByPlayer(
		const AsciiString &teamName, int kindofBit, Parameter *playerParameter);
};

void ScriptActions::doTeamMoveToNearestObjectOfKindOfOwnedByPlayer(
	const AsciiString &teamName, int kindofBit, Parameter *playerParameter)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	Coord3D position;
	theTeam->getEstimateTeamPosition_000EDCD0(&position);
	Object *closestObject = 0;
	Real closestDistance = 99999.0f;
	PlayerMaskType playerMask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	if (!playerMask)
		return;

	while (playerMask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		KindOfMaskType kindofMask(KindOfMaskType::kInit, kindofBit);
		Object *object = player->findClosestByKindOf(&position,
			kindofMask, KINDOFMASK_NONE);
		if (object)
		{
			Coord3D distance;
			distance.x = object->m_position.x;
			distance.y = object->m_position.y;
			distance.z = object->m_position.z;
			distance.sub(&position);
			Real objectDistance = distance.length();
			if (!closestObject || objectDistance < closestDistance)
			{
				closestObject = object;
				closestDistance = objectDistance;
			}
		}
	}

	if (closestObject)
	{
		AIGroup *theGroup = TheAI->createGroup();
		if (theGroup)
		{
			theTeam->getTeamAsAIGroup(theGroup);
			Rva0015A190Packet packet;
			packet.m_first = (void *)&closestObject->m_position;
			packet.m_flag = 0;
			packet.m_objA = 0;
			packet.m_objB = 0;
			((Rva0015A190Owner *)theGroup)->applyPacket(&packet, 1);
		}
	}
}
