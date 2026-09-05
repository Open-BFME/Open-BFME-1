// Near-twin of ?bfmeMakePairEL@@YA?AUBfmePairEL@@ABVBfmeWordEL@@0@Z
// (Code/GameEngine/Source/Common/Bfme5TwoWordPairFactory.cpp): same
// EH-protected two-member-construct shape, but the second member's copy
// constructor call targets 0x00047B27 (the AudioEventRTS copy-ctor ILT)
// instead of the shared 0x00887B60 copy ctor both of the twin's members
// use. Both fields still occupy just 4 bytes each in the returned record
// (second field starts at +4), so the real element types are not
// recovered here -- names are borrowed from the two already-pinned call
// targets, not asserted as the true field types.

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString(void);

private:
	int m_value;
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
