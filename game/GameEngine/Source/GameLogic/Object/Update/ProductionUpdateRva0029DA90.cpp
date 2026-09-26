// cl: /O2 /DNDEBUG /MD /EHsc
typedef bool Bool;
typedef unsigned int UnsignedInt;

extern float g_bfmeScaleBC;

class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};

class Money
{
public:
	void deposit(UnsignedInt amount, Bool showMessage);
};

class Rva000F9730
{
public:
	Bool markKey(UnsignedInt key);
};

class Player
{
public:
	Money *money() { return (Money *)((char *)this + 0x48); }
	Rva000F9730 *keys() { return (Rva000F9730 *)((char *)this + 0x684); }
};

class ProductionEntry
{
public:
	virtual ~ProductionEntry();
	int m_type;                    // +0x04
	unsigned char m_pad08[8];    // +0x08
	UnsignedInt m_id;             // +0x10
	float m_progress;             // +0x14
	unsigned char m_pad18[0x10]; // +0x18
	UnsignedInt m_cost;           // +0x28
	unsigned char m_pad2c[0x10]; // +0x2c
	ProductionEntry *m_next;     // +0x3c
};

class Rva0029DA90ProductionFacet;
class ProductionUpdate
{
	friend class Rva0029DA90ProductionFacet;
protected:
	void removeFromProductionQueue(ProductionEntry *entry);
};

// Secondary interface at ProductionUpdate primary+0x20.  The retail body
// calls removeFromProductionQueue with (this-0x20), but no named caller proves
// this secondary interface's original method name.
class Rva0029DA90ProductionFacet
{
public:
	void process(UnsignedInt productionID);

private:
	Object *owner() const { return *(Object *const *)((const char *)this - 0x18); }
	ProductionEntry *head() const { return *(ProductionEntry *const *)((const char *)this + 8); }
	Bool flagD5() const { return *((const char *)this + 0xb5) != 0; }
	void *fieldD8() const { return *(void *const *)((const char *)this + 0xb8); }
	ProductionUpdate *primary() { return (ProductionUpdate *)((char *)this - 0x20); }
};

void Rva0029DA90ProductionFacet::process(UnsignedInt productionID)
{
	for (ProductionEntry *entry = head(); entry != 0; entry = entry->m_next)
	{
		Bool suppressRefund = entry->m_progress >= g_bfmeScaleBC && fieldD8() != 0;
		if (entry->m_id != productionID || (!flagD5() && suppressRefund))
			continue;

		Player *player = owner()->getControllingPlayer();
		if (!suppressRefund)
			player->money()->deposit(entry->m_cost, true);
		if (entry->m_type == 3)
			player->keys()->markKey(entry->m_id);
		primary()->removeFromProductionQueue(entry);
		delete entry;
		return;
	}
}
