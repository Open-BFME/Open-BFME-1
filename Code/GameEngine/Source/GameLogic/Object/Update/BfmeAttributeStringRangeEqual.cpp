// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Int getLength() const { return m_data ? m_data->m_len : 0; }
	const char *str() const { return m_data ? (const char *)(m_data + 1) : ""; }

	Int compare(const AsciiString &other) const
	{
		Int otherLength = other.getLength();
		const char *otherData = other.str();
		Int thisLength = getLength();
		const char *thisData = str();
		Int shorter = thisLength < otherLength ? thisLength : otherLength;
		Int result = memcmp(thisData, otherData, shorter);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	Bool operator==(const AsciiString &other) const { return compare(other) == 0; }

private:
	BfmeAsciiStringData *m_data;
};

Bool bfmeAttributeStringRangeEqual(const AsciiString *first,
		const AsciiString *last, const AsciiString *other)
{
	for (; first != last; ++first, ++other) {
		if (!(*first == *other))
			return false;
	}
	return true;
}

struct BfmeAttributeStringVector
{
	AsciiString *m_begin;
	AsciiString *m_end;
};

Bool bfmeAttributeStringVectorsEqual(const BfmeAttributeStringVector *left,
		const BfmeAttributeStringVector *right)
{
	return left->m_end - left->m_begin == right->m_end - right->m_begin
		&& bfmeAttributeStringRangeEqual(left->m_begin, left->m_end, right->m_begin);
}
