// cl: /DNDEBUG /MD /EHsc
// readable body of ?privateIdle@ChinookAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/ChinookAIUpdate.cpp
// BFME's Chinook idle path is the Zero Hour privateIdle behavior expressed
// against the retail layouts: the rider list accessor is virtual at +0x104,
// the owning Object is at adjusted-this-0x18, and Object keeps its AI at +0x204.

enum CommandSourceType
{
	CMD_SOURCE_NONE = 0
};

class Object;

struct ContainedItemNode
{
	ContainedItemNode *m_next;
	ContainedItemNode *m_prev;
	Object *m_item;
};

struct ContainedItemsList
{
	ContainedItemNode *m_node;
};

class BfmeInnerRQ
{
public:
	void bfmeSetRQ(int object, int commandSource);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unreconstructed_000[0x204];
	void *m_ai;
};

#define CHINOOK_SLOT(n) virtual void unused##n();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ChinookAIUpdate.h
class ChinookAIUpdate
{
public:
	CHINOOK_SLOT(00) CHINOOK_SLOT(01) CHINOOK_SLOT(02) CHINOOK_SLOT(03)
	CHINOOK_SLOT(04) CHINOOK_SLOT(05) CHINOOK_SLOT(06) CHINOOK_SLOT(07)
	CHINOOK_SLOT(08) CHINOOK_SLOT(09) CHINOOK_SLOT(10) CHINOOK_SLOT(11)
	CHINOOK_SLOT(12) CHINOOK_SLOT(13) CHINOOK_SLOT(14) CHINOOK_SLOT(15)
	CHINOOK_SLOT(16) CHINOOK_SLOT(17) CHINOOK_SLOT(18) CHINOOK_SLOT(19)
	CHINOOK_SLOT(20) CHINOOK_SLOT(21) CHINOOK_SLOT(22) CHINOOK_SLOT(23)
	CHINOOK_SLOT(24) CHINOOK_SLOT(25) CHINOOK_SLOT(26) CHINOOK_SLOT(27)
	CHINOOK_SLOT(28) CHINOOK_SLOT(29) CHINOOK_SLOT(30) CHINOOK_SLOT(31)
	CHINOOK_SLOT(32) CHINOOK_SLOT(33) CHINOOK_SLOT(34) CHINOOK_SLOT(35)
	CHINOOK_SLOT(36) CHINOOK_SLOT(37) CHINOOK_SLOT(38) CHINOOK_SLOT(39)
	CHINOOK_SLOT(40) CHINOOK_SLOT(41) CHINOOK_SLOT(42) CHINOOK_SLOT(43)
	CHINOOK_SLOT(44) CHINOOK_SLOT(45) CHINOOK_SLOT(46) CHINOOK_SLOT(47)
	CHINOOK_SLOT(48) CHINOOK_SLOT(49) CHINOOK_SLOT(50) CHINOOK_SLOT(51)
	CHINOOK_SLOT(52) CHINOOK_SLOT(53) CHINOOK_SLOT(54) CHINOOK_SLOT(55)
	CHINOOK_SLOT(56) CHINOOK_SLOT(57) CHINOOK_SLOT(58) CHINOOK_SLOT(59)
	CHINOOK_SLOT(60) CHINOOK_SLOT(61) CHINOOK_SLOT(62) CHINOOK_SLOT(63)
	CHINOOK_SLOT(64)
	virtual const ContainedItemsList *getContainedItemsList() const;

protected:
	virtual void privateIdle(CommandSourceType commandSource);

private:
	Object *getOwningObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x18);
	}
};

#undef CHINOOK_SLOT

// ?privateIdle@ChinookAIUpdate@@MAEXW4CommandSourceType@@@Z
void ChinookAIUpdate::privateIdle(CommandSourceType commandSource)
{
	const ContainedItemsList *items = getContainedItemsList();
	ContainedItemNode *node = items->m_node->m_next;
	if (node != getContainedItemsList()->m_node)
	{
		Object *rider = node->m_item;
		if (rider->m_ai != 0)
		{
			BfmeInnerRQ *aiCommand = reinterpret_cast<BfmeInnerRQ *>(
				reinterpret_cast<unsigned char *>(rider->m_ai) + 0x20);
			aiCommand->bfmeSetRQ(reinterpret_cast<int>(getOwningObject()), commandSource);
		}
	}
}
