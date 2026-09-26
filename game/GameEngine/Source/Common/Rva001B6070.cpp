// Open-BFME5: clean C++ conversion of the override-resolved string accessor.

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
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_pad00[4];
	const Overridable *m_nextOverride;
	char m_pad08[4];
	AsciiString m_value;
};

class Rva001B6070Owner
{
public:
	AsciiString getResolvedValue() const;

private:
	char m_pad00[4];
	const Overridable *m_value;
};

AsciiString Rva001B6070Owner::getResolvedValue() const
{
	const Overridable * volatile unused = 0;
	const Overridable *value = m_value;
	if (value != 0 && value->m_nextOverride != 0)
		value = value->m_nextOverride->getFinalOverride();

	return value->m_value;
}
