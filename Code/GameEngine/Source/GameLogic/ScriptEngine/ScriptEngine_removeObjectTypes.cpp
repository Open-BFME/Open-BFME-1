// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// The matched ScriptEngine::doObjectTypeListMaintenance body calls this
// function through retail ILT 0x000143AD.  The original Generals source has
// the same find/delete/erase implementation in ScriptEngine.cpp.
//
// BFME places m_allObjectTypeLists at this+0x17628.  Keeping the small layout
// shim TU-local avoids exposing an incomplete reconstruction in a shared
// header.  /MD is significant here: vector::erase reaches CRT memmove through
// the imported slot used by retail.

// stlport
#include <algorithm>
#include <vector>

class ObjectTypes
{
public:
	virtual ~ObjectTypes();

	void deleteInstance()
	{
		delete this;
	}
};

class ScriptEngine
{
protected:
	void removeObjectTypes(ObjectTypes *typesToRemove);

	unsigned char m_padding[0x17628];
	std::vector<ObjectTypes *> m_allObjectTypeLists;
};

// ?removeObjectTypes@ScriptEngine@@IAEXPAVObjectTypes@@@Z
void ScriptEngine::removeObjectTypes(ObjectTypes *typesToRemove)
{
	if (typesToRemove == 0)
		return;

	std::vector<ObjectTypes *>::iterator it = std::find(
		m_allObjectTypeLists.begin(), m_allObjectTypeLists.end(),
		typesToRemove);

	if (it == m_allObjectTypeLists.end())
		return;

	typesToRemove->deleteInstance();
	m_allObjectTypeLists.erase(it);
}
