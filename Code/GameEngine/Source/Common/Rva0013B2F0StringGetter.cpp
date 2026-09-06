// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: retail 0x0013B2F0 (97 bytes) is the twin of Rva0013B370StringGetter.cpp returning
// the FIRST string of the row (field +0) instead of the second; same default fallback.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);

private:
	void *m_data;
};

struct Rva0013B2F0StringRow
{
	AsciiString m_field0;
	AsciiString m_field4;
	AsciiString m_field8;
	AsciiString m_fieldC;
	AsciiString m_field10;
};

extern AsciiString TheBfmeCrateNameDefault;

class Rva0013B2F0StringTable
{
public:
	AsciiString getField0(int index) const;

private:
	Rva0013B2F0StringRow *m_begin;
	Rva0013B2F0StringRow *m_end;
	Rva0013B2F0StringRow *m_capacity;
};

AsciiString Rva0013B2F0StringTable::getField0(int index) const
{
	volatile int compilerStackSlot = 0;
	if (index >= 0 && (unsigned int)index < (unsigned int)(m_end - m_begin))
		return m_begin[index].m_field0;

	return TheBfmeCrateNameDefault;
}
