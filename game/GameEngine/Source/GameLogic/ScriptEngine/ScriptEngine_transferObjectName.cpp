// cl: /DNDEBUG /MD /EHsc
// ScriptEngine::transferObjectName, retail 0x0034D550, 180 bytes.

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_length;
	UnsignedShort m_pad;
};

class AsciiString
{
public:
    Int getLength(void) const
    {
        return m_data ? m_data->m_length : 0;
    }

    Bool isNotEmpty(void) const
    {
        return m_data && m_data->m_length != 0;
    }

	Int compare(const AsciiString &other) const;
	AsciiString &operator=(const AsciiString &other);

private:
	BfmeAsciiStringData *m_data;
};

class AsciiStringCompareShim
{
public:
    Int compare(const AsciiString &other) const;
};

class Object
{
public:
	AsciiString &getName(void)
	{
		return *reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(this) + 0x84);
	}

	Bool hasCustomIndicatorColor(void) const
	{
		return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x244) != 0;
	}

	Int getIndicatorColor(void) const;
	void setCustomIndicatorColor(Int color);
	void removeCustomIndicatorColor(void);
};

struct NamedRequest
{
	AsciiString m_name;
	Object *m_object;
};

class NamedRequestVector
{
public:
	NamedRequest *begin(void) const { return m_begin; }
	NamedRequest *end(void) const { return m_end; }

private:
	NamedRequest *m_begin;
	NamedRequest *m_end;
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void removeObjectFromCache(Object *object) = 0;

	void transferObjectName(const AsciiString &unitName, Object *newObject);

private:
	char m_padding[0x17098];
	NamedRequestVector m_namedObjects;
};

// ?transferObjectName@ScriptEngine@@QAEXABVAsciiString@@PAVObject@@@Z
void ScriptEngine::transferObjectName(const AsciiString &unitName, Object *newObject)
{
        if (!newObject || !unitName.getLength())
            return;

    if (newObject->getName().isNotEmpty())
        removeObjectFromCache(newObject);

    newObject->getName() = unitName;

    NamedRequest *it = m_namedObjects.begin();
    NamedRequest *end = m_namedObjects.end();
    for (; it != end; ++it)
    {
        if (!reinterpret_cast<const AsciiStringCompareShim *>(&unitName)->compare(it->m_name))
        {
			Object *oldObject = it->m_object;
			if (oldObject)
			{
                if (oldObject->hasCustomIndicatorColor())
                    newObject->setCustomIndicatorColor(oldObject->getIndicatorColor());
                else
                    newObject->removeCustomIndicatorColor();
			}

			it->m_object = newObject;
			return;
		}
	}
}
