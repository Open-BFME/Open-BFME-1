// ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ
// partial score=0.45 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ present-unmatched
// Retail 0x00451460, 318 bytes.

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	struct Data
	{
		int m_refCount;
		int m_length;
		T m_text[1];
	};
	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void __cdecl format(AsciiString fmt, ...);
	void set(const char *text, int len);
	void concat(const char *text, int len);
	const char *str() const { return m_data ? m_data->m_text : ""; }
	int getLength() const { return m_data ? m_data->m_length : 0; }
};

typedef bool Bool;

class GlobalData
{
public:
	AsciiString getPath_UserData() const;
};

extern GlobalData *TheGlobalData;

Bool bfmeLocalUserMapsReady(void);

class MapCache
{
public:
	AsciiString getUserMapDir() const;
	AsciiString getMapDir() const;
};

// ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ
AsciiString MapCache::getUserMapDir() const
{
	MapCache *self = (MapCache *)this;
	AsciiString tmp;
	if (bfmeLocalUserMapsReady())
	{
		tmp.format(AsciiString("%s"), "UserData\\Maps");
	}
	else
	{
		{
			AsciiString extra = TheGlobalData->getPath_UserData();
			tmp.set(extra.str(), extra.getLength());
		}
		{
			AsciiString extra = self->getMapDir();
			tmp.concat(extra.str(), extra.getLength());
		}
	}
	return tmp;
}
