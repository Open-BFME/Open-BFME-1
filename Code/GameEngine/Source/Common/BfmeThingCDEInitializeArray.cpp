// cl: /EHsc

// ?initializeArray@BfmeThingCDE@@QAEXH@Z
//
// Called by the owner allocator's BfmeOwnerCDE::rva008fa850 at 0x008FA850
// (Code/GameEngine/Source/Common/BfmeOwnerCDECreate.cpp) right after the node
// is constructed.

void *operator new[](unsigned int size);

class Element
{
public:
	Element() {}
	~Element() {}

	int m_00;
	void *m_04;
	int m_08;
	int m_0c;
};

class BfmeThingCDE
{
public:
	void initializeArray(int count);

	unsigned char m_pad00[0x1c];
	void *m_1c;
	int m_20;
};

void BfmeThingCDE::initializeArray(int count)
{
	m_20 = count;
	Element *array = new Element[count];
	m_1c = array;
	for (Element *p = array, *end = array + m_20; p != end; ++p)
	{
		p->m_00 = 0;
		p->m_04 = this;
	}
}
