// cl: /DNDEBUG /MD /EHsc
// readable body of ?orderAllPassengersToIdle@OpenContain@@: Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp
// Zero Hour OpenContain::orderAllPassengersToIdle expressed against BFME's
// adjusted contain interface and Object AI layout.

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

#define OPEN_SLOT(n) virtual void unused##n();

class OpenContain
{
public:
	OPEN_SLOT(00) OPEN_SLOT(01) OPEN_SLOT(02) OPEN_SLOT(03)
	OPEN_SLOT(04) OPEN_SLOT(05) OPEN_SLOT(06) OPEN_SLOT(07)
	OPEN_SLOT(08) OPEN_SLOT(09) OPEN_SLOT(10) OPEN_SLOT(11)
	OPEN_SLOT(12) OPEN_SLOT(13) OPEN_SLOT(14) OPEN_SLOT(15)
	OPEN_SLOT(16) OPEN_SLOT(17) OPEN_SLOT(18) OPEN_SLOT(19)
	OPEN_SLOT(20) OPEN_SLOT(21) OPEN_SLOT(22) OPEN_SLOT(23)
	OPEN_SLOT(24) OPEN_SLOT(25) OPEN_SLOT(26) OPEN_SLOT(27)
	OPEN_SLOT(28) OPEN_SLOT(29) OPEN_SLOT(30) OPEN_SLOT(31)
	OPEN_SLOT(32) OPEN_SLOT(33) OPEN_SLOT(34) OPEN_SLOT(35)
	OPEN_SLOT(36) OPEN_SLOT(37) OPEN_SLOT(38) OPEN_SLOT(39)
	OPEN_SLOT(40) OPEN_SLOT(41) OPEN_SLOT(42) OPEN_SLOT(43)
	OPEN_SLOT(44) OPEN_SLOT(45) OPEN_SLOT(46) OPEN_SLOT(47)
	OPEN_SLOT(48) OPEN_SLOT(49) OPEN_SLOT(50) OPEN_SLOT(51)
	OPEN_SLOT(52) OPEN_SLOT(53) OPEN_SLOT(54) OPEN_SLOT(55)
	OPEN_SLOT(56) OPEN_SLOT(57) OPEN_SLOT(58) OPEN_SLOT(59)
	OPEN_SLOT(60) OPEN_SLOT(61) OPEN_SLOT(62) OPEN_SLOT(63)
	OPEN_SLOT(64)
	virtual const ContainedItemsList *getContainedItemsList() const;
	virtual void orderAllPassengersToIdle(CommandSourceType commandSource);

private:
	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x18);
	}
};

#undef OPEN_SLOT

// ?orderAllPassengersToIdle@OpenContain@@UAEXW4CommandSourceType@@@Z
void OpenContain::orderAllPassengersToIdle(CommandSourceType commandSource)
{
	ContainedItemNode *node = getContainedItemsList()->m_node->m_next;
	if (node != getContainedItemsList()->m_node)
	{
		bool morePassengers;
		do
		{
			Object *rider = node->m_item;
			node = node->m_next;
			morePassengers = node != getContainedItemsList()->m_node;
			if (rider->m_ai != 0)
			{
				BfmeInnerRQ *aiCommand = reinterpret_cast<BfmeInnerRQ *>(
					reinterpret_cast<unsigned char *>(rider->m_ai) + 0x20);
				aiCommand->bfmeSetRQ(reinterpret_cast<int>(getObject()), commandSource);
			}
		} while (morePassengers);
	}
}
