// ?d_00225960@@YAXXZ
// partial score=0.78 date=2026-09-21
// ?rva00225960@Rva00225960Owner@@QAEXXZ [retail body 0x00225960, 249 bytes]
// Address-derived: an OpenContain-family method that asserts an empty
// "active" list (this+0x38, list<Object*>), then drains a "pending" list of
// object IDs (this+0x70, list<int>) via GameLogic::findObjectByID, pushing
// each resolved Object* onto the active list, notifying via vtable slot
// 0x5c when a flag bit is set, and setting the object's m_containedBy
// (this+0x214) field to this object's owner (this+8).  Both throw sites are
// the same bfmeFormatText(tag=5)+_CxxThrowException(assert-style) call.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Object;
typedef int ObjectID;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;

struct BfmeFormattedText225960
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText225960 *__cdecl bfmeFormatText(
	BfmeFormattedText225960 *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);
extern "C" char g_rva005c5100ThrowInfo;

class Gen_001ef410
{
public:
	void m();
};

class Rva00225960Owner
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void notify(Object *object, int a, int b);

	void rva00225960();

private:
	char m_pad00[4];
	void *m_owner;
	char m_pad0c[0x38 - 0xc];
	_STL::list<Object *> m_activeList;
	char m_pad3c[0x70 - 0x3c];
	_STL::list<ObjectID> m_pendingList;
};

void Rva00225960Owner::rva00225960()
{
	void *owner = m_owner;

	((Gen_001ef410 *)this)->m();

	if (!m_activeList.empty()) {
		BfmeFormattedText225960 buf;
		bfmeFormatText(&buf, 5, 0);
		_CxxThrowException(&buf, &g_rva005c5100ThrowInfo);
	}

	for (_STL::list<ObjectID>::iterator it = m_pendingList.begin();
		it != m_pendingList.end(); ++it) {
		Object *object = TheBfmeGameLogic->findObjectByID(*it);
		if (!object) {
			BfmeFormattedText225960 buf;
			bfmeFormatText(&buf, 5, 0);
			_CxxThrowException(&buf, &g_rva005c5100ThrowInfo);
		}

		m_activeList.push_back(object);

		if (*(unsigned int *)((char *)object + 0x94) & 0x10000000)
			notify(object, 0, 0);

		*(void **)((char *)object + 0x214) = owner;
	}

	m_pendingList.clear();
}
