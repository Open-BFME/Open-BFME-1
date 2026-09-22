// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ScriptEngine::getObjectTypes at 0x0034CE80 (169 bytes).
// Identity: matched doObjectTypeListMaintenance and objectTypesFromParam
// call virtual slot 20; ScriptEngine vtable VA0x010E7A30 slot20 points through
// ILT0x00046E9D to this body. The released ScriptEngine twin names the method.
// The matched maintenance/removal methods witness m_allObjectTypeLists+17628.
// ObjectTypes constructors witness m_listName+4. The sole retail callee is
// ILT0x0003EAE0 -> 0x001DB5B0, independently verified as getListName's four-byte
// lea eax,[ecx+4]; ret body (ICF-shared with a differently named accessor).
// Native AsciiString::compare and vector iteration reproduce the retail loop.

#include "ascii_string.h"
#include <vector>

class ObjectTypes
{
public:
	const AsciiString &getListName() const;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);

private:
	unsigned char m_padding[0x17624];
	std::vector<ObjectTypes *> m_allObjectTypeLists;
};

// ?getObjectTypes@ScriptEngine@@UAEPAVObjectTypes@@ABVAsciiString@@@Z
ObjectTypes *ScriptEngine::getObjectTypes(const AsciiString &objectTypeList)
{
	std::vector<ObjectTypes *>::iterator it;

	for (it = m_allObjectTypeLists.begin(); it != m_allObjectTypeLists.end(); ++it)
	{
		if ((*it) == 0)
			continue;

		if ((*it)->getListName().compare(objectTypeList) == 0)
			return *it;
	}

	return 0;
}
