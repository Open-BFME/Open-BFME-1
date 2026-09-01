// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);

private:
	void *m_data;
};

struct Rva0013B370StringRow
{
	AsciiString m_field0;
	AsciiString m_field4;
	AsciiString m_field8;
	AsciiString m_fieldC;
	AsciiString m_field10;
};

extern AsciiString TheBfmeCrateNameDefault;

class Rva0013B370StringTable
{
public:
	AsciiString getField4(int index) const;

private:
	Rva0013B370StringRow *m_begin;
	Rva0013B370StringRow *m_end;
	Rva0013B370StringRow *m_capacity;
};

AsciiString Rva0013B370StringTable::getField4(int index) const
{
	volatile int compilerStackSlot = 0;
	if (index >= 0 && (unsigned int)index < (unsigned int)(m_end - m_begin))
		return m_begin[index].m_field4;

	return TheBfmeCrateNameDefault;
}
