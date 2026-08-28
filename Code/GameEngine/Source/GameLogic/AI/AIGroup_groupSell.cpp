// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupSell, retail 0x00150E90, 45 bytes.
//
// The reference's body unchanged, including the reason it looks the way it
// does: selling can remove the member from the list, so the iterator is
// advanced BEFORE the call -- which is why retail reads the next node into the
// walk register between fetching the object and pushing it.
//
// TheBuildAssistant's sellObject is vtable slot 18 (+0x48).
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

enum CommandSourceType { CMD_FROM_PLAYER = 0 };

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class BuildAssistant
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void unusedSlot17();
	virtual void sellObject(Object *obj);			// vtable +0x48
};

extern BuildAssistant *TheBuildAssistant;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupSell(CommandSourceType cmdSource);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

void AIGroup::groupSell( CommandSourceType cmdSource )
{
	_STL::list<Object *>::iterator i, thisIterator;
	Object *obj;

	for( i = m_memberList.begin(); i != m_memberList.end(); /*empty*/ )
	{

		// work off of 'thisIterator' as we may change the contents of this list
		thisIterator = i;
		++i;

		// get object
		obj = *thisIterator;

		// try to sell object
		TheBuildAssistant->sellObject( obj );

	}  // end for, i

}
