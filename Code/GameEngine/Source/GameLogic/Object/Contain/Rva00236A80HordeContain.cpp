// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: address-derived HordeContain member scan, retail 0x00236A80.
// The body walks the OpenContain list at +0x38, checks each Object id against
// HordeContain's member index at +0x120, and reports missing entries through
// the eleventh interface at +0xE4.  AODHordeContain and HordeContain vtables
// both place this body at slot 31, but no direct caller names the method.

#define _STLP_USE_NEWALLOC 1
#include <list>
#include <map>

class Object
{
public:
	unsigned char m_pad[0x74];
	int m_id;
};

class __declspec(novtable) Rva00236A80OpenContain
{
public:
	virtual void slot00();

protected:
	unsigned char m_pad04[0x34];
	_STL::list<Object *> m_members;
	unsigned char m_pad3C[0xA8];
};

class __declspec(novtable) Rva00236A80HordeContainView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void reportMissingMember(Object *);
};

class Rva00236A80HordeContain
	: public Rva00236A80OpenContain,
	  public Rva00236A80HordeContainView
{
public:
	void rva00236A80();

private:
	unsigned char m_padE8[0x38];
	_STL::map<int, int> m_memberIndex;
};

// ?rva00236A80@Rva00236A80HordeContain@@QAEXXZ
void Rva00236A80HordeContain::rva00236A80()
{
	for (_STL::list<Object *>::iterator it = m_members.begin();
		it != m_members.end(); ++it)
	{
		Object *member = *it;
		int id = member->m_id;
		if (m_memberIndex.find(id) == m_memberIndex.end())
			((Rva00236A80HordeContainView *)this)->reportMissingMember(member);
	}
}
