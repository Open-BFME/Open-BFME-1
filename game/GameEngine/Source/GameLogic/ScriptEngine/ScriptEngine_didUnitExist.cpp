// cl: /O2 /DNDEBUG /MD /EHsc
// ScriptEngine::didUnitExist, retail 0x0034CA90, 165 bytes.

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class AsciiString
{
public:
	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

	Bool operator==(const AsciiString &rhs) const { return compare(rhs) == 0; }

private:
	BfmeAsciiStringData *m_data;
};

struct NamedRequest
{
	AsciiString m_name;
	void *m_object;
};

struct NamedRequestVector
{
	NamedRequest *m_begin;
	NamedRequest *m_end;

	NamedRequest *begin(void) const { return m_begin; }
	NamedRequest *end(void) const { return m_end; }
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
	virtual Bool didUnitExist(const AsciiString &unitName);

private:
	char m_slice_pad[0x17098];
	NamedRequestVector m_namedObjects;
};

Bool ScriptEngine::didUnitExist(const AsciiString &unitName)
{
	NamedRequest *it = m_namedObjects.begin();
	NamedRequest *end = m_namedObjects.end();

	for (; it != end; ++it)
	{
		if (unitName == it->m_name)
			return it->m_object == 0;
	}

	return false;
}
