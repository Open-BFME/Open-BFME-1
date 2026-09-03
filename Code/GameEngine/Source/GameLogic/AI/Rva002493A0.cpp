// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>

class BfmeRva493A0Object;

class BfmeRva493A0Result
{
public:
	virtual void unused00(void) = 0;
	virtual void unused01(void) = 0;
	virtual void unused02(void) = 0;
	virtual void unused03(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused05(void) = 0;
	virtual bool accepts(BfmeRva493A0Object *object) = 0;
};

class BfmeRva493A0Contain
{
public:
	virtual void unused00(void) = 0;
	virtual void unused01(void) = 0;
	virtual void unused02(void) = 0;
	virtual void unused03(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused05(void) = 0;
	virtual void unused06(void) = 0;
	virtual void unused07(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused09(void) = 0;
	virtual void unused10(void) = 0;
	virtual void unused11(void) = 0;
	virtual void unused12(void) = 0;
	virtual void unused13(void) = 0;
	virtual void unused14(void) = 0;
	virtual void unused15(void) = 0;
	virtual void unused16(void) = 0;
	virtual void unused17(void) = 0;
	virtual void unused18(void) = 0;
	virtual void unused19(void) = 0;
	virtual void unused20(void) = 0;
	virtual void unused21(void) = 0;
	virtual void unused22(void) = 0;
	virtual void unused23(void) = 0;
	virtual void unused24(void) = 0;
	virtual void unused25(void) = 0;
	virtual BfmeRva493A0Result *getResult(void) = 0;
};

class BfmeRva493A0Object
{
public:
	char m_head[0x1fc];
	BfmeRva493A0Contain *m_contain;
};

struct BfmeRva493A0Node
{
	BfmeRva493A0Node *m_next;
	BfmeRva493A0Node *m_previous;
	void *m_value;
};

class Rva002493A0
{
public:
	BfmeRva493A0Result *find(BfmeRva493A0Object *object);
	BfmeRva493A0Result *find2(BfmeRva493A0Object *object);

private:
	char m_pad[0x38];
	_STL::list<BfmeRva493A0Object *> m_objects;
};

BfmeRva493A0Result *Rva002493A0::find(BfmeRva493A0Object *object)
{
	_STL::list<BfmeRva493A0Object *> objects(m_objects);
	for (_STL::list<BfmeRva493A0Object *>::iterator it = objects.begin();
		it != objects.end(); ++it)
	{
		if (*it != 0)
		{
			BfmeRva493A0Contain *contain = (*it)->m_contain;
			if (contain != 0)
			{
				BfmeRva493A0Result *result = contain->getResult();
				if (result != 0 && result->accepts(object) == true)
					return result;
			}
		}
	}
	return 0;
}

BfmeRva493A0Result *Rva002493A0::find2(BfmeRva493A0Object *object)
{
	_STL::list<BfmeRva493A0Object *> objects(m_objects);
	for (_STL::list<BfmeRva493A0Object *>::iterator it = objects.begin();
		it != objects.end(); ++it)
	{
		if (*it != 0)
		{
			BfmeRva493A0Contain *contain = (*it)->m_contain;
			if (contain != 0)
			{
				BfmeRva493A0Result *result = contain->getResult();
				if (result != 0 && result->accepts(object) == true)
					return result;
			}
		}
	}
	return 0;
}
