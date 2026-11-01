// ?method@Rva00228050OpenContain@@QAE_NPAVObject@@@Z
// partial score=0.9299 date=2026-11-01
// cl: /DNDEBUG /MD /EHsc
// stlport
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xC8 - 8];
	unsigned char m_kindOfAtC8[4];
	unsigned char m_kindOfAtCC;
};

class StealthUpdate
{
public:
	void markAsDetected(UnsignedInt numFrames, Bool flag);
};

class Module;
class Player;
class Object;

class AICommandInterface
{
public:
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	AICommandInterface *getCommandInterface() { return (AICommandInterface *)((char *)this + 0x20); }
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0x204 - 8];
	AIUpdateInterface *m_ai;					// +0x204

	Player *getControllingPlayer() const;
	AIUpdateInterface *getAI() { return m_ai; }

protected:
	Module *findModule(NameKeyType key) const;
	friend class Rva00228050OpenContain;
};

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

class ContainInterface00228050
{
public:
#define S(n) virtual void slot##n();
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11)
	S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23)
	S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32) S(33) S(34) S(35)
#undef S
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits);	// +0x90
};

class Rva00228050OpenContain
{
public:
	Bool method(Object *other);

private:
	Object *getObject() { return m_object; }

	unsigned char m_unreconstructed_000[8];
	Object *m_object;							// +0x08
	unsigned char m_unreconstructed_00c[0x20 - 0x0c];
	ContainInterface00228050 m_containInterface;		// +0x20
	unsigned char m_unreconstructed_024[0x38 - 0x24];
	ContainedItemsList m_containList;			// +0x38
};

Bool Rva00228050OpenContain::method(Object *other)
{
	ContainedItemNode *volatile next;
	for (ContainedItemNode *cur = m_containList.m_node->m_next; cur != m_containList.m_node; cur = next)
	{
		Object *rider = cur->m_item;
		next = cur->m_next;
		Player *riderPlayer = rider->getControllingPlayer();
		if (riderPlayer == other->getControllingPlayer())
			continue;
		ThingTemplate *thing = rider->m_template;
		if (thing != 0 && thing->m_nextOverride != 0)
			thing = (ThingTemplate *)thing->m_nextOverride->getFinalOverride();
		if ((thing->m_kindOfAtCC & 2) == 0)
			continue;

		if (rider->getAI())
		{
			static const NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
			StealthUpdate *stealth = (StealthUpdate *)rider->findModule(key_StealthUpdate);
			if (stealth != 0)
				stealth->markAsDetected(0, true);
			rider->getAI()->getCommandInterface()->aiExit(getObject(), CMD_FROM_AI);
		}
		else
		{
			m_containInterface.removeFromContain(rider, true);
		}
	}
	return true;
}

#undef NAMEKEY
