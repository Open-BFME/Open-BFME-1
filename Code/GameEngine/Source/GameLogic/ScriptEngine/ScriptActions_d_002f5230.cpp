// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
//
// Convert of gen-dump ?d_002f5230@@YAXXZ at 0x002F5230 (91 bytes).
// ScriptEngine vslot 27 by-value name then walk the pointer list at +0x1F0
// until a +0xC object returns non-null from vslot 15 and receives the
// second argument on vslot 0.

#include "StringInline.h"

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual struct Object *lookupByValue(AsciiString name);
};

class Apply0
{
public:
	virtual void apply(void *arg);
};

class Query15
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual Apply0 *query();
};

struct ListItem
{
	unsigned char m_beforeInner[0xC];
	Query15 m_inner;
};

struct Object
{
	unsigned char m_beforeList[0x1F0];
	ListItem **m_list;
};

extern ScriptEngine *TheScriptEngine;

void __stdcall d_002f5230(const AsciiString &name, void *arg)
{
	Object *object = (Object *)TheScriptEngine->lookupByValue(name);
	if (object)
	{
		ListItem **it = object->m_list;
		ListItem *cur = *it;
		if (cur)
		{
			do
			{
				Apply0 *found = cur->m_inner.query();
				if (found)
				{
					found->apply(arg);
					return;
				}
				cur = *++it;
			} while (cur);
		}
	}
}
