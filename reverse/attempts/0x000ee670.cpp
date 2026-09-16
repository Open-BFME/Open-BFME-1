// ?getNthInList@ObjectTypes@@QBE?AVAsciiString@@H@Z
// partial score=0.92 date=2026-09-04
// ?getNthInList@ObjectTypes@@QBE?AVAsciiString@@H@Z
// partial score=0.92 date=2026-09-04
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Gy /O2 /Ob1
// stlport
// ObjectTypes::getNthInList at 0x000EE670 (77B).

class AsciiString
{
public:
	AsciiString(const AsciiString &);

private:
	void *m_data;
};

extern AsciiString TheEmptyAsciiString;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AsciiStringVector
{
public:
	AsciiString *begin() const
	{
		return m_begin;
	}
	unsigned int size() const { return (unsigned int)(m_finish - m_begin); }

	AsciiString *m_begin;
	AsciiString *m_finish;
};

class ObjectTypes
{
public:
	unsigned int getListSize() const { return m_strings.size(); }
	AsciiString getNthInList(int index) const;

private:
	char m_pad[8];
	AsciiStringVector m_strings;
};

AsciiString ObjectTypes::getNthInList(int index) const
{
	volatile int dead = 0;
	if (index < getListSize())
	{
		_ReadWriteBarrier();
		return m_strings.begin()[index];
	}
	return *(const AsciiString *)&TheEmptyAsciiString;
}
