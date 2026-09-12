// Near-twin of ?bfmeMakePairEL@@YA?AUBfmePairEL@@ABVBfmeWordEL@@0@Z
// (Code/GameEngine/Source/Common/Bfme5TwoWordPairFactory.cpp): same
// EH-protected two-member-construct shape, but the second member's copy
// constructor call targets 0x00047B27 (the AudioEventRTS copy-ctor ILT)
// instead of the shared 0x00887B60 copy ctor both of the twin's members
// use. Both fields still occupy just 4 bytes each in the returned record
// (second field starts at +4), so the real element types are not
// recovered here -- names are borrowed from the two already-pinned call
// targets, not asserted as the true field types.

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
	~AsciiString(void);

private:
	int m_data;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &other);
	~AudioEventRTS(void);

private:
	int m_value;
};

struct Rva0013F8B0Pair
{
	Rva0013F8B0Pair(const AsciiString &firstValue, const AudioEventRTS &secondValue)
		: first(firstValue), second(secondValue)
	{
	}

	AsciiString first;
	AudioEventRTS second;
};

// ?rva0013f8b0@@YA?AURva0013F8B0Pair@@ABVAsciiString@@ABVAudioEventRTS@@@Z
Rva0013F8B0Pair __cdecl rva0013f8b0(
	const AsciiString &first,
	const AudioEventRTS &second)
{
	return Rva0013F8B0Pair(first, second);
}
