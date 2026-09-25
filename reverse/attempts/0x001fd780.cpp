// ?d_001fd780@@YAXXZ
// partial score=0.98 date=2026-09-25
// Partial reconstruction for retail RVA 0x001FD780 (381 bytes).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib
// Vtable 0x010A40C4 slot 1, constructor 0x001FC580, and the
// GateProxyBehavior lookup prove GateOpenAndCloseBehavior::onObjectCreated.
// The prior draft models the adjustment for the secondary base before
// update(bool).
//
// This TU deliberately uses the canonical WWLib AsciiString/StringBase view.
// The target's local is default-constructed, filled by StringBase::set at
// 0x00887C90, and released at scope exit through releaseBuffer 0x00887940.
// No physical copy-constructor call occurs in this body; the canonical copy
// constructor remains available for real by-value callers but is not invented
// here.

#include "ascii_string.h"

// The canonical header declares this destructor out of line.  Retail's local
// cleanup is the native StringBase<char>::releaseBuffer body, not an unknown
// AsciiString helper, so expose that exact inherited operation here.
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

// Native definitions from Code/Libraries/Source/string/StringBase.cpp.  The
// real source keeps these in the same TU as the StringBase implementation;
// forcing the two narrow overloads inline here lets this scratch caller use
// that implementation without hand-copying a second compare into AsciiString.
template <>
__forceinline int StringBase<char>::compare(const StringBase<char> &str) const
{
	const int len = str.m_data ? str.m_data->length : 0;
	const char *data = str.m_data ? &str.m_data->data[0] : "";
	return compare(data, len);
}

template <>
__forceinline int StringBase<char>::compare(const char *str, int len) const
{
	const int myLen = m_data ? m_data->length : 0;
	const char *data = m_data ? &m_data->data[0] : "";
	int byteOrder = memcmp(data, str, myLen < len ? myLen : len);
	if (byteOrder != 0)
		return byteOrder;
	return myLen - len;
}

typedef int ObjectID;
typedef int NameKeyType;

class ModuleData;

class Module
{
public:
	virtual void slot();
};

class Object
{
public:
	unsigned char m_pad00[0x74];
	ObjectID m_id_at_74;
	unsigned char m_pad78[0x0c];
	AsciiString m_name;
	Object *m_next;
	unsigned char m_pad8c[0x2b8];
	unsigned char m_privateStatus;

	Module *findModule(NameKeyType key) const;
};

class GameLogic
{
public:
	Object *getFirstObject();
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GateOpenAndCloseBehaviorModuleData
{
public:
	unsigned char m_pad00[0x14];
	AsciiString m_name;
};

class BehaviorModule
{
public:
	virtual void baseSlot();
	void loadPostProcess();
};

class GateOpenAndCloseBehavior : public BehaviorModule
{
public:
	virtual void onObjectCreated();
	void update(bool enabled);

	GateOpenAndCloseBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad10[0x18];
	ObjectID m_linkedObjectId;
};

extern GameLogic *TheBfmeGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;

void GateOpenAndCloseBehavior::onObjectCreated()
{
	GateOpenAndCloseBehavior *self = this;
	BehaviorModule::loadPostProcess();

	if (self->m_object == 0)
		return;

	if ((self->m_object->m_privateStatus & 1) != 0)
		((GateOpenAndCloseBehavior *)((unsigned char *)self - 4))->update(true);

	GateOpenAndCloseBehaviorModuleData *data = self->m_moduleData;
	if (*(char **)(void *)&data->m_name == 0)
		return;
	if (*(unsigned short *)(*(char **)(void *)&data->m_name + 4) == 0)
		return;

	Object *candidate = TheBfmeGameLogic->getFirstObject();
	AsciiString candidateName;
	while (candidate != 0)
	{
		candidateName.set(candidate->m_name);
		if (((const StringBase<char> *)&candidateName)->compare(
			*(const StringBase<char> *)&data->m_name) == 0)
		{
			static NameKeyType gateKey =
				TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
			Module *module = candidate->findModule(gateKey);
			if (module != 0)
			{
				if (((GateOpenAndCloseBehavior *)((unsigned char *)module - 4)) != 0)
				{
					((GateOpenAndCloseBehavior *)((unsigned char *)module - 4))
						->m_linkedObjectId = self->m_object->m_id_at_74;
					((GateOpenAndCloseBehavior *)((unsigned char *)this - 4))
						->m_linkedObjectId = candidate->m_id_at_74;
				}
			}
			break;
		}
		candidate = candidate->m_next;
	}
}
