// ?newOverride@AI@@IAEXXZ
// partial score=0.94 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// readable body of ?newOverride@AI@@IAEXXZ:
// Code/GameEngine/Source/GameLogic/AI/ai.cpp
//
// Retail 0x0014E2B0, 571 bytes. BFME copies TAiData then clones three lists
// (AISideInfo, AISideBuildList, and a 0x14-byte named-list node) and links
// m_next at +0xF8. m_aiData lives at AI+0x14.

#include "StringInline.h"

void *operator new(unsigned int size);
void operator delete(void *ptr);

class Xfer;
class BuildListInfo
{
public:
	BuildListInfo *duplicate(void);
};

class TAiData;
class AISideInfo;
class AISideBuildList;
class AINamedListNode;

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class TAiData : public Snapshot
{
public:
	TAiData();
	TAiData &operator=(const TAiData &that);
	void addFactionBuildList(AISideBuildList *buildList);

	unsigned char m_body[0xEC - 4];
	AISideInfo *m_sideInfo;
	AISideBuildList *m_sideBuildLists;
	AINamedListNode *m_namedLists;
	TAiData *m_next;
};

class AISideInfo
{
public:
	AISideInfo();
	AISideInfo &operator=(const AISideInfo &that);

	unsigned char m_body[0x1BC];
	AISideInfo *m_next;
};

class AISideBuildList
{
public:
	virtual ~AISideBuildList();
	AISideBuildList(AsciiString side) :
		m_side(side),
		m_buildList(0),
		m_next(0)
	{
	}

	AsciiString m_side;
	BuildListInfo *m_buildList;
	AISideBuildList *m_next;
};

class AINamedListNode
{
public:
	AINamedListNode(AsciiString name);
	void copyTail(const void *src);

	void *m_vtable;
	AsciiString m_name;
	unsigned int m_value;
	unsigned char m_tail[4];
	AINamedListNode *m_next;
};

class AI
{
protected:
	void newOverride(void);

	unsigned char m_pad[0x14];
	TAiData *m_aiData;
};

// ?newOverride@AI@@IAEXXZ
void AI::newOverride(void)
{
	TAiData *cur = m_aiData;
	m_aiData = new TAiData;
	*m_aiData = *cur;

	m_aiData->m_sideInfo = 0;
	AISideInfo *info = cur->m_sideInfo;
	while (info)
	{
		AISideInfo *newInfo = new AISideInfo;
		*newInfo = *info;
		newInfo->m_next = 0;
		newInfo->m_next = m_aiData->m_sideInfo;
		m_aiData->m_sideInfo = newInfo;
		info = info->m_next;
	}

	m_aiData->m_sideBuildLists = 0;
	AISideBuildList *build = cur->m_sideBuildLists;
	while (build)
	{
		AISideBuildList *newbuild = new AISideBuildList(build->m_side);
		newbuild->m_next = 0;
		if (build->m_buildList)
			newbuild->m_buildList = build->m_buildList->duplicate();
		m_aiData->addFactionBuildList(newbuild);
		build = build->m_next;
	}

	m_aiData->m_namedLists = 0;
	AINamedListNode *named = cur->m_namedLists;
	while (named)
	{
		AINamedListNode *node = new AINamedListNode(named->m_name);
		node->copyTail(&named->m_tail);
		node->m_value = named->m_value;
		node->m_next = m_aiData->m_namedLists;
		m_aiData->m_namedLists = node;
		named = named->m_next;
	}

	m_aiData->m_next = cur;
}
