// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);

class AsciiString;

template <typename T>
class StringBase
{
public:
	struct Data
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &source);
	~StringBase() {}
	void trim();

private:
	friend class AsciiString;
	void releaseBuffer();

	public:
	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	~AsciiString() { releaseBuffer(); }

	void trim() { StringBase<char>::trim(); }
};

inline int compare(const AsciiString &left, const AsciiString &right)
{
	const StringBase<char> *self = (const StringBase<char> *)&left;
	const StringBase<char> *that = (const StringBase<char> *)&right;
	int thatLength = that->m_data ? that->m_data->m_length : 0;
	const char *thatText = that->m_data ? that->m_data->m_text : (const char *)0x0107388B;
	int selfLength = self->m_data ? self->m_data->m_length : 0;
	const char *selfText = self->m_data ? self->m_data->m_text : (const char *)0x0107388B;
	int count = selfLength < thatLength ? selfLength : thatLength;
	int result = _memicmp(selfText, thatText, count);
	if (result != 0)
		return result;
	return selfLength - thatLength;
}

struct Video;

class VideoPlayer
{
public:
	virtual const Video *getVideo(AsciiString movieTitle);
};

// BFME's video table records are 0x1c bytes: three AsciiStrings followed by
// the looping, volume, default, and trailing record fields witnessed in the
// INI parser and member-stride walkers.
struct BfmeVideoRecord
{
	AsciiString m_filename;
	AsciiString m_internalName;
	AsciiString m_commentForWB;
	unsigned char m_isLooping;
	float m_volume;
	unsigned char m_isDefault;
	unsigned char m_padding[3];
	int m_unknown;
};

extern BfmeVideoRecord *g_bfmeVideoTableBegin; // retail 0x0130B19C
extern BfmeVideoRecord *g_bfmeVideoTableEnd;   // retail 0x0130B1A0

// ?getVideo@VideoPlayer@@UAEPBUVideo@@VAsciiString@@@Z
const Video *VideoPlayer::getVideo(AsciiString movieTitle)
{
	AsciiString title(movieTitle);
	title.trim();

	BfmeVideoRecord *it = g_bfmeVideoTableBegin;
	for (; it != g_bfmeVideoTableEnd; ++it)
	{
		AsciiString name(it->m_internalName);
		name.trim();
		if (compare(name, title) == 0)
			return reinterpret_cast<const Video *>(it);
	}
	return 0;
}
