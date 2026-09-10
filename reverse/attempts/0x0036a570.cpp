// ?applyAttributeModifier@AttributeModifierPoolUpdate@@QAE_NABVAsciiString@@H@Z
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// AttributeModifierPoolUpdate::applyAttributeModifier, retail RVA 0x0036A570.
// Object::applyAttributeModifier at 0x001C1DA0 is the named caller.  The pool
// stores 16-byte entries, and its definition store supplies the two ten-word
// model-condition masks used by Object::clearAndSetModelConditionFlags.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType {};

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<320> ModelConditionFlags;

template <class T>
class StringBase
{
public:
	StringBase(const StringBase<T> &source);
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	const char *str() const
	{
		const char *data = *(const char * const *)this;
		return data ? data + 8 : "";
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const char Rva006A16B0Empty[];

class Object
{
public:
	void clearAndSetModelConditionFlags(const BitFlags<320> &clear,
		const BitFlags<320> &set);
};

class UpdateModule
{
public:
	void setWakeFrame(Object *object, UnsignedInt frame);

private:
	unsigned char m_prefix[0x20];
};

struct AttributeModifierEntry
{
	Int m_index;
	Int m_unused04;
	UnsignedInt m_expirationFrame;
	Int m_unused0c;
};

class AttributeModifierDefinitionStore
{
public:
	Int indexOf(Int key) const;
	Int valueAt(Int index) const;
	void copyClearMask(Int index, ModelConditionFlags *out) const;
	void copySetMask(Int index, ModelConditionFlags *out) const;
};

extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;

class Rva00367E30Logic
{
private:
	unsigned char m_unreconstructed[0x3c];

public:
	UnsignedInt m_frame;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class AttributeModifierPoolUpdate : public UpdateModule
{
public:
	Bool applyAttributeModifier(const AsciiString &name, Int duration);

private:
	Object *m_object;
	unsigned char m_unreconstructed0c[0x14];
	std::vector<AttributeModifierEntry> m_modifiers;
	UnsignedInt m_nextExpiration;
};

Bool AttributeModifierPoolUpdate::applyAttributeModifier(
	const AsciiString &name, Int duration)
{
	const char *text = name.str();
	NameKeyType key = TheNameKeyGenerator->nameToKey(text);
	Int index = TheAttributeModifierDefinitionStore->indexOf((Int)key);
	if (index < 0)
		return false;

	UnsignedInt frame = TheBfmeGameLogic->m_frame;
	for (std::vector<AttributeModifierEntry>::iterator it = m_modifiers.begin();
		it != m_modifiers.end(); ++it)
	{
		if (it->m_index == index)
		{
			Int length = duration;
			if (length < 0)
				length = TheAttributeModifierDefinitionStore->valueAt(index);
			it->m_expirationFrame = frame + (UnsignedInt)length;
			return true;
		}
	}

	ModelConditionFlags clear = {};
	ModelConditionFlags set = {};
	TheAttributeModifierDefinitionStore->copyClearMask(index, &clear);
	TheAttributeModifierDefinitionStore->copySetMask(index, &set);
	if (m_object != 0)
		m_object->clearAndSetModelConditionFlags(clear, set);

	Int length = duration;
	if (length < 0)
		length = TheAttributeModifierDefinitionStore->valueAt(index);
	UnsignedInt expiration = frame + (UnsignedInt)length;

	AttributeModifierEntry entry;
	entry.m_index = index;
	entry.m_unused04 = 0;
	entry.m_expirationFrame = expiration;
	entry.m_unused0c = 0;
	m_modifiers.push_back(entry);

	if (expiration < m_nextExpiration)
	{
		m_nextExpiration = expiration;
		setWakeFrame(m_object, expiration);
	}
	return true;
}
