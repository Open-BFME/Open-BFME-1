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

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
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
			reinterpret_cast<BfmeOwnerVNI *>(this)->bfmeApply1VNI();
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
	Rva0021F850Link *head = m_listHead;
	Rva0021F850Link *p = head->m_next;
	unsigned int n = 0;

	if (p != head)
	{
		do
		{
			p = p->m_next;
			++n;
		}
		while (p != head);

		if (n > 0)
			m_owner->setModelConditionState(RVA0021F850_GARRISONED);
	}

	Rva0021F850Entry tmp[40];
	for (Int i = 0; i < 40; ++i)
		tmp[i] = m_entries[i];

	removeInvalidObjectsFromGarrisonPoints();
	addValidObjectsToGarrisonPoints();

	for (Int j = 0; j < 40; ++j)
	{
		if (tmp[j].m_key != 0)
		{
			Int k = bfmeMapEntry(tmp[j].m_key);
			if (k != -1)
				m_entries[k].m_08 = tmp[j].m_08;
		}
	}
}
