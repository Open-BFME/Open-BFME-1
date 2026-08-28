// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GenOwner::ready, retail 0x00215080, 77 bytes.
//
// A chain of four guards that all answer false, and one line of work at the end:
// take the id at this+0xE4, find the object, take its interface at +0x200, ask
// that interface for something through vtable slot 41 (+0xA4) and cache the
// answer at this+0xE0. Only when all four hold does the last line run -- the
// object id of this owner's own object, read through this+0x08 and Object+0x74,
// is stamped at +0xCC of whatever came back.

typedef bool Bool;
typedef int ObjectID;					// H in the decorated name the ledger pins

class BfmeReadyResult
{
public:
	unsigned char m_unmodelled_000[0xCC];
	ObjectID m_owner;					// +0xCC
};

class BfmeReadyInterface
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void unusedSlot17();
	virtual void unusedSlot18();
	virtual void unusedSlot19();
	virtual void unusedSlot20();
	virtual void unusedSlot21();
	virtual void unusedSlot22();
	virtual void unusedSlot23();
	virtual void unusedSlot24();
	virtual void unusedSlot25();
	virtual void unusedSlot26();
	virtual void unusedSlot27();
	virtual void unusedSlot28();
	virtual void unusedSlot29();
	virtual void unusedSlot30();
	virtual void unusedSlot31();
	virtual void unusedSlot32();
	virtual void unusedSlot33();
	virtual void unusedSlot34();
	virtual void unusedSlot35();
	virtual void unusedSlot36();
	virtual void unusedSlot37();
	virtual void unusedSlot38();
	virtual void unusedSlot39();
	virtual void unusedSlot40();
	virtual BfmeReadyResult *fetch(void);			// vtable +0xA4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }

	unsigned char m_unmodelled_000[0x74];
	ObjectID m_id;						// Object+0x74
	unsigned char m_unmodelled_078[0x200 - 0x78];
	BfmeReadyInterface *m_interface;			// Object+0x200
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);			// ILT 0x0001F253
};

extern GameLogic *TheGameLogic;

class GenOwner
{
public:
	Bool ready(void);

private:
	unsigned char m_unmodelled_000[8];
	Object *m_object;					// this+0x08
	unsigned char m_unmodelled_00c[0xE0 - 0x0C];
	BfmeReadyResult *m_cached;				// this+0xE0
	ObjectID m_id;						// this+0xE4
};

Bool GenOwner::ready(void)
{
	ObjectID id = m_id;
	if (id == 0)
		return false;

	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj == 0)
		return false;

	BfmeReadyInterface *iface = obj->m_interface;
	if (iface == 0)
		return false;

	m_cached = iface->fetch();
	if (m_cached == 0)
		return false;

	m_cached->m_owner = m_object->getID();
	return true;
}
