// cl: /DNDEBUG /MD /EHsc
// Open-BFME: OpenContain::markAllPassengersDetected, retail 0x00226CF0.
// The BFME body walks the contain list directly, checks the stealth-garrison
// kind bit after resolving the template override, then removes the passenger's
// stealth grant with the BFME two-argument receiveGrant call.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum NameKeyType { NAMEKEY_INVALID = 0 };

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
	Overridable *getFinalOverride();

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
	void receiveGrant(Bool active, UnsignedInt frames);
};

class Object
{
public:
	StealthUpdate *findUpdateModule(NameKeyType key);

	void *m_vtable;
	ThingTemplate *m_template;
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

class OpenContain
{
public:
	void markAllPassengersDetected();

private:
	unsigned char m_unreconstructed_000[0x18];
	ContainedItemsList m_containList;
};

// ?markAllPassengersDetected@OpenContain@@QAEXXZ
void OpenContain::markAllPassengersDetected()
{
	ContainedItemNode *node = m_containList.m_node->m_next;
	if (node != m_containList.m_node)
	{
		do
		{
			Object *rider = node->m_item;
			node = node->m_next;
			ThingTemplate *thing = rider->m_template;
			if (thing != 0 && thing->m_nextOverride != 0)
				thing = (ThingTemplate *)thing->m_nextOverride->getFinalOverride();
			if ((thing->m_kindOfAtCC & 2) == 0)
				continue;

			static const NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
			StealthUpdate *stealth = rider->findUpdateModule(key_StealthUpdate);
			if (stealth != 0)
				stealth->receiveGrant(false, 1);
		}
		while (node != m_containList.m_node);
	}
}

#undef NAMEKEY
