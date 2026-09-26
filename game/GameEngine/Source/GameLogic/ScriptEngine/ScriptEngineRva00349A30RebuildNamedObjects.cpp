// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/sweep /Iinputs/reference/shims/ini /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "Common/AsciiString.h"

class Object;

typedef _STL::pair<AsciiString, Object *> NamedRequest;

typedef _STL::vector<NamedRequest> NamedRequestVector;

class Object
{
public:
	const AsciiString &getName(void) const { return m_name; }
	Object *getNextObject(void) const { return m_nextObject; }

private:
	unsigned char m_pad[0x84];
	AsciiString m_name;
	Object *m_nextObject;
};

struct Gen_00383090
{
	int m(void);
};

extern Gen_00383090 *TheGameLogic;

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	void createNamedCache(void);

private:
	unsigned char m_pad[0x17098];
	NamedRequestVector m_namedObjects;
};

// ?createNamedCache@ScriptEngine@@QAEXXZ
void ScriptEngine::createNamedCache(void)
{
	m_namedObjects.clear();

	if (TheGameLogic == 0)
		return;

	Object *object = (Object *)TheGameLogic->m();
	while (object != 0)
	{
		if (!object->getName().isEmpty())
		{
			NamedRequest request;
			request.first = object->getName();
			request.second = object;
			m_namedObjects.push_back(request);
		}
		object = object->getNextObject();
	}
}
