// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	AsciiString();
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}

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
