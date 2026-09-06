// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
// Open-BFME5: the vector dispatcher at retail 0x001E4350.
//
// The owner list and its item interface are the same ones independently
// matched by BfmeThing404::notifyAll at 0x001E4040.  This body inlines that
// walk for each pointer in the owning vector.  The outer class is kept
// address-derived because the retail owner name is not recovered.

class Rva001E4350Item
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void notify(void);                 // slot +0x20
};

struct Rva001E4350Node
{
	Rva001E4350Node *m_next;
	Rva001E4350Node *m_prev;
	Rva001E4350Item *m_item;
};

class Rva001E4350Owner
{
public:
	char m_pad[0x538];
	Rva001E4350Node *m_listHead;
};

extern "C" void *g_bfmeOtherBN;

#include <vector>

class Rva001E4350
{
public:
	void notifyAll(void);

private:
	char m_pad[8];
	_STL::vector<Rva001E4350Owner *> m_owners;
};

// ?notifyAll@Rva001E4350@@QAEXXZ
void Rva001E4350::notifyAll(void)
{
	Rva001E4350Node *node;

	if (g_bfmeOtherBN)
	{
		for (int i = 0; i < m_owners.size(); ++i)
		{
			Rva001E4350Owner *owner = m_owners[i];

			if (owner && g_bfmeOtherBN)
			{
				for (node = owner->m_listHead->m_next;
					node != owner->m_listHead;
					node = node->m_next)
				{
					node->m_item->notify();
				}
			}
		}
	}
}
