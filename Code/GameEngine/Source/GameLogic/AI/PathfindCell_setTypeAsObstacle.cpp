// ?setTypeAsObstacle@PathfindCell@@QAE_NPAVObject@@_NABUICoord2D@@@Z present-unmatched
// BFME compact PathfindCell layout, retail 0x003F73D0.
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindCell;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModule
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void v5(void);
	virtual void v6(void);
	virtual void v7(void);
	virtual Int getDamageState(void);
};

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride(void);

	char m_pad00[4];
	LocomotorOverridable *m_override;
	char m_pad08[0xd0 - 8];
	unsigned int m_kindOf;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_pad00[4];
	LocomotorOverridable *m_template;
	char m_pad08[0x74 - 8];
	unsigned int m_id;
	char m_pad78[0x200 - 0x78];
	BodyModule *m_bodyModule;
};

class Rva003F7380State
{
public:
	void finishReset(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	static void allocateCellInfos(void);

	char m_pad00[0xc];
	unsigned int m_next;
	char m_pad10[0x10];
	unsigned int m_obstacleID;
	unsigned int m_flags;
};

extern PathfindCellInfo *g_bfmePathfindFreeList;

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeList, PathfindCell *cell, const ICoord2D *pos);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	void setTypeAsObstacle(Object *obstacle, Bool isFence, const ICoord2D &pos);

private:
	PathfindCellInfo *m_info;
	char m_pad04[8];
	unsigned int m_packed;
};

void PathfindCell::setTypeAsObstacle(Object *obstacle, Bool isFence,
	const ICoord2D &pos)
{
	unsigned int type = m_packed & 7;
	if (type != 0 && type != 5)
		return;

		BodyModule *body = obstacle->m_bodyModule;
		if (body != 0)
		{
			Int damageState = body->getDamageState();
			if (damageState == 3)
			{
				m_packed = (m_packed & ~4u) | damageState;
				if (m_info != 0)
				{
					m_info->m_obstacleID = 0;
					((Rva003F7380State *)this)->finishReset();
				}
				return;
			}
		}

		m_packed = (m_packed & ~3u) | 4u;
		if (m_info == 0)
		{
			if (g_bfmePathfindFreeList == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList, this, &pos);
		}
		else
			m_info->m_next = 0;

		m_info->m_obstacleID = obstacle->m_id;
		unsigned int fence = (unsigned char)isFence;
		m_info->m_flags = m_info->m_flags ^
			((m_info->m_flags ^ (fence << 1)) & 2u);
		LocomotorOverridable *templ = obstacle->m_template;
		if (templ != 0 && templ->m_override != 0)
			templ = templ->m_override->friend_getFinalOverride();
		unsigned char transparentBit = (unsigned char)(templ->m_kindOf >> 9);
		unsigned int transparent = (unsigned int)transparentBit << 2;
		m_info->m_flags = m_info->m_flags ^
			((m_info->m_flags ^ transparent) & 4u);
}
