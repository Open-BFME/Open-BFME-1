// cl: /DNDEBUG /MD /EHsc

// BFME's ProductionUpdate::removeFromProductionQueue keeps the Zero Hour queue
// logic, but reads the constructing condition directly from the owning Object.
// The compact declarations below retain the retail layouts without pulling the
// full game headers into this focused translation unit.

#include <string.h>

class ExitInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void unreserveDoorForExit(int door) = 0;
};

class Object
{
public:
	ExitInterface *getObjectExitInterface() const;

	unsigned char m_bfmePad[0x110];
	unsigned int m_modelConditions[10];
};

class ProductionEntry
{
public:
	void *m_vtable;                         // +0x00
	int m_type;                             // +0x04
	unsigned char m_bfmePad08[0x2c - 0x08];
	int m_exitDoor;                         // +0x2c
	unsigned char m_bfmePad30[0x3c - 0x30];
	ProductionEntry *m_next;                // +0x3c
	ProductionEntry *m_prev;                // +0x40
};

template <int WordCount>
class BfmeConditionFlags
{
public:
	void set(unsigned int mask, bool value)
	{
		if (value)
			m_words[0] |= mask;
		else
			m_words[0] &= ~mask;
	}

private:
	unsigned int m_words[WordCount];
};

class ProductionUpdate
{
protected:
	void removeFromProductionQueue(ProductionEntry *production);

private:
	unsigned char m_bfmePad00[0x08];
	Object *m_object;                       // +0x08
	unsigned char m_bfmePad0c[0x28 - 0x0c];
	ProductionEntry *m_productionQueue;     // +0x28
	ProductionEntry *m_productionQueueTail; // +0x2c
	unsigned char m_bfmePad30[0x34 - 0x30];
	int m_productionCount;                  // +0x34
	unsigned char m_bfmePad38[0x84 - 0x38];
	BfmeConditionFlags<10> m_clearFlags;    // +0x84
	BfmeConditionFlags<8> m_setFlags;       // +0xac
	unsigned char m_flagsDirty;             // +0xcc
};

void ProductionUpdate::removeFromProductionQueue(ProductionEntry *production)
{
	if (production->m_type == 1 && production->m_exitDoor != -1)
	{
		ExitInterface *exit = m_object->getObjectExitInterface();
		if (exit)
			exit->unreserveDoorForExit(production->m_exitDoor);
	}

	if (production->m_prev)
		production->m_prev->m_next = production->m_next;
	else
		m_productionQueue = production->m_next;

	if (production->m_next)
		production->m_next->m_prev = production->m_prev;
	else
		m_productionQueueTail = production->m_prev;

	unsigned char *self = reinterpret_cast<unsigned char *>(this);
	int &productionCount = *reinterpret_cast<int *>(self + 0x34);
	--productionCount;

	Object *object = *reinterpret_cast<Object **>(self + 0x08);
	unsigned int conditions[10];
	memcpy(conditions, object->m_modelConditions, sizeof(conditions));
	if (productionCount == 0 && (conditions[2] & 0x100) != 0)
	{
		m_clearFlags.set(0x100, true);
		m_setFlags.set(0x100, false);
		m_flagsDirty = 1;
	}
}
