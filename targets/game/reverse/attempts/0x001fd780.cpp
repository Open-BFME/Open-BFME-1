// ?d_001fd780@@YAXXZ
// partial score=0.98 date=2026-09-27
// This source reconstructs retail RVA 0x001FD780 across 381 bytes.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// Vtable slot 1 at 0x010A40C4 and constructor 0x001FC580 identify
// GateOpenAndCloseBehavior::onObjectCreated. The body adjusts Module pointers
// back by four bytes to reach GateOpenAndCloseBehavior.
// This source uses the canonical AsciiString and StringBase definitions.
// The local candidateName starts empty. StringBase::set at 0x00887C90 copies
// the candidate object name, and scope cleanup releases its buffer through
// StringBase::releaseBuffer at 0x00887940.
// The body does not call the AsciiString copy constructor. The compare
// specializations below copy the implementation from StringBase.cpp.

#include "ascii_string.h"

// The ascii_string.h header defines an empty AsciiString destructor. The
// compiler calls StringBase<char>::~StringBase during scope cleanup.
// These compare specializations follow the definitions in StringBase.cpp.
// Inline definitions let this source call them without another AsciiString
// comparison implementation.
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
