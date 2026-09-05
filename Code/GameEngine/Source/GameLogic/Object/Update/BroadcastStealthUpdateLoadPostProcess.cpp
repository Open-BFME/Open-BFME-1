// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Object {};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class BfmeA987
{
public:
	void bfmeBase987();

protected:
	int m_base;
};

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern void __stdcall _CxxThrowException(void *, void *);

class BroadcastStealthUpdate : public BfmeA987
{
public:
	void loadPostProcess();

private:
	unsigned char m_pad[0x24];
	_STL::list<Object *> m_objects;
	int m_objectCount;
	_STL::list<int> m_ids;
};

// ?loadPostProcess@BroadcastStealthUpdate@@QAEXXZ
void BroadcastStealthUpdate::loadPostProcess()
{
	bfmeBase987();

	if (!m_objects.empty())
	{
		BfmeFormattedText error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
		__assume(0);
	}

	for (_STL::list<int>::iterator it = m_ids.begin(); it != m_ids.end(); ++it)
	{
		Object *object = TheGameLogic->findObjectByID(*it);
		if (object == 0)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, (void *)0x011DFE5C);
			__assume(0);
		}
		m_objects.push_back(object);
	}

	m_ids.clear();
}
