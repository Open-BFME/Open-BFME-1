// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: GarrisonContain::redeployOccupants, retail 0x0021F850.
// Both the GarrisonContain and HordeGarrisonContain primary vtables route
// slot 17 here.  The Zero Hour vtable independently names the corresponding
// method, and the body preserves its 40-entry snapshot/redeploy/restore flow.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

class Rva0021F850Link
{
public:
	Rva0021F850Link *m_next;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
//
// Only the member this body calls is declared. The garrisoned state is
// reapplied through Object::notifyModelConditionChanged, reached via
// ILT 0x0002191D, so the notification belongs to the Object and the call stays
// a cast; no Object storage is spelled here, so none is needed.
class Object
{
public:
	void notifyModelConditionChanged(void);				// ILT 0x0002191D
};

template<Int NUMBITS>
class Rva0021F850BitFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

enum Rva0021F850ModelCondition
{
	RVA0021F850_GARRISONED = 10
};

class Rva0021F850OwnerObject
{
public:
	void setModelConditionState(Rva0021F850ModelCondition bit)
	{
		if (!m_conditionFlags.test(bit))
		{
			m_conditionFlags.set(bit);
			reinterpret_cast<Object *>(this)->notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_head[0x110];
	Rva0021F850BitFlags<288> m_conditionFlags;
};

struct Rva0021F850Entry
{
	void *m_key;
	Int m_04;
	Int m_08;
	Int m_0c;
	Int m_10;
};

class GarrisonContain
{
public:
	virtual void bfmeVt00(); virtual void bfmeVt01(); virtual void bfmeVt02(); virtual void bfmeVt03();
	virtual void bfmeVt04(); virtual void bfmeVt05(); virtual void bfmeVt06(); virtual void bfmeVt07();
	virtual void bfmeVt08(); virtual void bfmeVt09(); virtual void bfmeVt10(); virtual void bfmeVt11();
	virtual void bfmeVt12(); virtual void bfmeVt13(); virtual void bfmeVt14(); virtual void bfmeVt15();
	virtual void bfmeVt16();
protected:
	virtual void redeployOccupants();
public:
	virtual void bfmeVt18(); virtual void bfmeVt19();
	virtual void bfmeVt20(); virtual void bfmeVt21(); virtual void bfmeVt22(); virtual void bfmeVt23();
	virtual void bfmeVt24(); virtual void bfmeVt25();
	virtual Int bfmeMapEntry(void *key);

protected:
	void removeInvalidObjectsFromGarrisonPoints();
	void addValidObjectsToGarrisonPoints();

private:
	unsigned char m_head[4];
	Rva0021F850OwnerObject *m_owner;
	unsigned char m_gap1[0x2c];
	Rva0021F850Link *m_listHead;
	unsigned char m_gap2[0x9c];
	Rva0021F850Entry m_entries[40];
};

void GarrisonContain::redeployOccupants()
{
	Rva0021F850Link *containListHead = m_listHead;
	Rva0021F850Link *containedNode = containListHead->m_next;
	unsigned int containedCount = 0;

	if (containedNode != containListHead)
	{
		do
		{
			containedNode = containedNode->m_next;
			++containedCount;
		}
		while (containedNode != containListHead);

		if (containedCount > 0)
			m_owner->setModelConditionState(RVA0021F850_GARRISONED);
	}

	Rva0021F850Entry previousEntries[40];
	for (Int snapshotIndex = 0; snapshotIndex < 40; ++snapshotIndex)
		previousEntries[snapshotIndex] = m_entries[snapshotIndex];

	removeInvalidObjectsFromGarrisonPoints();
	addValidObjectsToGarrisonPoints();

	for (Int previousIndex = 0; previousIndex < 40; ++previousIndex)
	{
		if (previousEntries[previousIndex].m_key != 0)
		{
			Int currentIndex = bfmeMapEntry(previousEntries[previousIndex].m_key);
			if (currentIndex != -1)
				m_entries[currentIndex].m_08 = previousEntries[previousIndex].m_08;
		}
	}
}
