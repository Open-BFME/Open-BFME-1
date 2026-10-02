// Retail 0x0022BFF0: restores the pointer list at +0xE4 from IDs at +0xFC.
// Identity is address-derived; offsets and slot +0x5C witnessed in retail.
// Base call follows ILT 0x1727E -> 0x22CDB0 -> 0x225960.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Object;
typedef int ObjectID;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct BfmeFormattedText225960
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText225960 *__cdecl bfmeFormatText(
	BfmeFormattedText225960 *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);
extern "C" char g_rva005c5100ThrowInfo;

class Rva00225960Owner
{
public:
	void rva00225960();
};

class ContainListRestore0022BFF0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void notify(Object *object, int a, int b);

	void restore();

private:
	char m_at04[4];
	void *m_at08;
	char m_beforeE4[0xe4 - 0xc];
	_STL::list<Object *> m_atE4;
	char m_beforeFC[0xfc - 0xe8];
	_STL::list<ObjectID> m_atFC;
};

void ContainListRestore0022BFF0::restore()
{
	void *owner = m_at08;

	((Rva00225960Owner *)this)->rva00225960();

	if (!m_atE4.empty()) {
		BfmeFormattedText225960 buf;
		bfmeFormatText(&buf, 5, 0);
		_CxxThrowException(&buf, &g_rva005c5100ThrowInfo);
	}

	for (_STL::list<ObjectID>::iterator it = m_atFC.begin();
		it != m_atFC.end(); ++it) {
		Object *object = TheGameLogic->findObjectByID(*it);
		if (!object) {
			BfmeFormattedText225960 buf;
			bfmeFormatText(&buf, 5, 0);
			_CxxThrowException(&buf, &g_rva005c5100ThrowInfo);
		}

		m_atE4.push_back(object);

		if (*(unsigned int *)((char *)object + 0x94) & 0x10000000)
			notify(object, 0, 0);

		*(void **)((char *)object + 0x214) = owner;
	}

	m_atFC.clear();
}


