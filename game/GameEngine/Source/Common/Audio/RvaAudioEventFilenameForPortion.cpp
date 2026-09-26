// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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
	~AsciiString();
	static const AsciiString TheEmptyString;

private:
	const char *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AsciiString getAttackFilename();
	AsciiString getFilename();
	AsciiString getDecayFilename();
};

class RvaAudioEventFilenameForPortion
{
public:
	AsciiString getFilenameForPlayPortion();

private:
	unsigned char m_pad00[0x60];
	int m_portionToPlay;
};

AsciiString RvaAudioEventFilenameForPortion::getFilenameForPlayPortion()
{
	switch (m_portionToPlay)
	{
	case 0:
		return ((AudioEventRTS *)this)->getAttackFilename();
	case 1:
		return ((AudioEventRTS *)this)->getFilename();
	case 2:
		return ((AudioEventRTS *)this)->getDecayFilename();
	default:
		return AsciiString::TheEmptyString;
	}
}
