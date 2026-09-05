// ?d_005217a0@@YAXXZ
// partial score=0.93 date=2026-09-05
// Open-BFME5: map-name and preview-state update for the BfmeCfgVSH object.
// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) const char *__cdecl strrchr(const char *, int);

extern const char g_bfmeEmptyAscii[];

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void toLower();
	void set(const StringBase<T> &other);

    struct Data
    {
        int m_refCount;
        unsigned short m_length;
        unsigned short m_allocated;
        T m_text[1];
    };

    Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(reinterpret_cast<const StringBase<char> &>(other)) {}
	~AsciiString() {}
	void toLower() { StringBase<char>::toLower(); }
	void set(const AsciiString &other)
	{
		StringBase<char>::set(reinterpret_cast<const StringBase<char> &>(other));
	}
	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : g_bfmeEmptyAscii;
	}
	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

class BfmeStrVSH
{
public:
	void bfmeSetVSH(const char *text, int length);
	void bfmeAssignVSH(const BfmeStrVSH &other);

	char *m_bfme00;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	void translate(const AsciiString &source);

	void set(const UnicodeString &source)
	{
		StringBase<unsigned short>::set(reinterpret_cast<const StringBase<unsigned short> &>(source));
	}
};

class BfmeSrcVSH
{
	public:
	UnicodeString m_title;
	unsigned char m_bfmePad04[0x1c];
	int m_hasMap;
	unsigned char m_bfmePad24[0x2c];
	AsciiString m_bfme50;
	unsigned char m_bfmePad54[0xa0];
	UnicodeString m_description;
};

class GameWindow;
void GadgetListBoxReset(GameWindow *listBox);

struct MapCacheNode
{
public:
	unsigned char m_treeLinks[0x14];
	BfmeSrcVSH second;
};

class MapCache
{
public:
	MapCacheNode *bfmeFind(const AsciiString &mapName);

	MapCacheNode *m_head;
};

extern MapCache *TheMapCache;

class BfmeCfgVSH
{
public:
	void bfmeSetMapVSH(const AsciiString &mapName);
	void bfmeApplyVSH(BfmeSrcVSH *src);
	void bfmeStep1VSH(BfmeSrcVSH *src);
	void bfmeStep2VSH(BfmeSrcVSH *src);
	void bfmeStep3VSH(BfmeSrcVSH *src);
	void bfmeStep5VSH(BfmeSrcVSH *src);

	BfmeStrVSH m_bfme00;
	unsigned char m_bfmePad04[0x0c];
	GameWindow *m_bfme10;
	unsigned char m_bfmePad14[0x28];
	BfmeSrcVSH *m_bfme3c;
};

// ?bfmeSetMapVSH@BfmeCfgVSH@@QAEXABVAsciiString@@@Z
void BfmeCfgVSH::bfmeSetMapVSH(const AsciiString &mapName)
{
	register bool state = false;
	if (mapName.isEmpty())
	{
		m_bfme00.bfmeSetVSH("", state);
		bfmeStep1VSH(reinterpret_cast<BfmeSrcVSH *>(state));
		bfmeStep2VSH(reinterpret_cast<BfmeSrcVSH *>(state));
		bfmeStep3VSH(reinterpret_cast<BfmeSrcVSH *>(state));

		if (m_bfme10 != reinterpret_cast<GameWindow *>(state))
		{
			GadgetListBoxReset(m_bfme10);
		}

		bfmeStep5VSH(reinterpret_cast<BfmeSrcVSH *>(state));
		return;
	}

	AsciiString lowerMap(mapName);
	lowerMap.toLower();
	MapCache *cache = TheMapCache;
	MapCacheNode *it = cache->bfmeFind(lowerMap);
	if (it != cache->m_head)
	{
		bfmeApplyVSH(&it->second);
	}
	else
	{
		const char *mapPath = mapName.str();
		AsciiString mapTitle(strrchr(mapPath, '\\') + 1);
		UnicodeString translated;
		translated.translate(mapTitle);
		state = 1;
		m_bfme3c->m_hasMap = state;
		m_bfme3c->m_title.set(translated);
		m_bfme3c->m_description.set(translated);
		m_bfme3c->m_bfme50.set(mapName);
		bfmeApplyVSH(m_bfme3c);
	}
}
