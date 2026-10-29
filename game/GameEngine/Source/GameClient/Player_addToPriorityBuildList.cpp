// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?addToPriorityBuildList@Player@@QAEXABVAsciiString@@PAVCoord3D@@M@Z: game/GameEngine/Source/Common/RTS/Player.cpp
// ZH Player::addToPriorityBuildList; layout from the matched addToBuildList
// sibling (Player_addToBuildList.cpp). BFME takes the template name by
// reference (ILT oracle CONFIRMED) and Coord3D is class-keyed. The by-value
// setTemplateName copy lands in the dead reference slot, as in retail.

// This unit's BuildListInfo view defines setNumRebuilds inline at another offset than
// retail's 0x0016A630 (+0x2C) and emits that COMDAT copy; rename it so only
// retail-equal copies carry the name. Inlined calls are unchanged.
#define setNumRebuilds setNumRebuilds_LocalView
#include "ascii_string.h"

// class-gate: allow Coord3D BFME decorations key Coord3D as a class (ILT oracle CONFIRMED); canonical Lib header declares a struct
class Coord3D
{
public:
	float x, y, z;
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
};

class BuildListInfo
{
public:
	BuildListInfo();

	void setTemplateName(AsciiString name) { m_templateName = name; }
	void setLocation(Coord3D loc) { m_location = loc; }
	void setAngle(float angle) { m_angle = angle; }
	void markPriorityBuild() { m_priorityBuild = true; }
	void setNumRebuilds(unsigned int n) { m_numRebuilds = n; }
	void setNextBuildList(BuildListInfo *next) { m_nextBuildList = next; }

private:
	void *m_vftable;
	AsciiString m_buildingName;
	AsciiString m_templateName;
	Coord3D m_location;
	float m_rallyX;
	float m_rallyY;
	float m_angle;
	bool m_isInitiallyBuilt;
 unsigned char m_pad25[3];
	unsigned int m_numRebuilds;
	BuildListInfo *m_nextBuildList;
	unsigned char m_pad30[0x18];
	unsigned int m_objectID;
	unsigned char m_tail4C[0x3C];
	bool m_priorityBuild;
	unsigned char m_pad89[3];
};

class Player
{
public:
	void addToPriorityBuildList(const AsciiString &templateName, Coord3D *pos, float angle);

private:
	unsigned char m_pad[0x1C0];
	BuildListInfo *m_pBuildList;
};

void Player::addToPriorityBuildList(const AsciiString &templateName, Coord3D *pos, float angle)
{
	BuildListInfo *newInfo = new BuildListInfo;
	newInfo->setTemplateName(templateName);
	newInfo->setLocation(*pos);
	newInfo->setAngle(angle);
	newInfo->markPriorityBuild();
	newInfo->setNumRebuilds(1);
	newInfo->setNextBuildList(m_pBuildList);
	m_pBuildList = newInfo;
}
