// cl: /DNDEBUG /MD /EHsc
// PopulateReplayFileListbox (retail 0x004E1450, 1774 B), rewritten from the
// retail disassembly as a standalone TU on the BFME StringBase layout (word
// length at +4, text at +8, out-of-line set/concat/releaseBuffer) instead of
// the ZH ReplayMenu.cpp include set, whose AsciiString inlines an
// InterlockedDecrement release and cannot produce retail's calls. Identity:
// ReplayMenu callers (ReplayMenuInit, deleteReplay, PopupReplayInit,
// reallySaveReplay) and the GeneralsMD twin.
//
// BFME differences from the ZH body, all read off the retail bytes:
// lastReplayFName is built once before the loop; compareNoCase inlines
// _memicmp (IAT 0x01359310); the version test compares exeCRC with
// Rva0009B4B0(GlobalData+0xBD0, GlobalData+0xBD0); only two colours are used;
// GadgetListBoxAddEntryText takes a trailing Bool. The ReplayHeader trailing
// dword and the 0x58-byte GameInfo prefix are frame witnesses (the header
// ends at +0x60 where info starts, and the slot array sits at info+0x58).
// ZH's GameInfo lays out m_mapCRC at +0x3c, so that AsciiString keeps an
// offset name.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short WideChar;
typedef unsigned int size_t;

extern "C" size_t strlen(const char *);
#pragma intrinsic(strlen)
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, size_t);

extern char Rva006A16B0Empty[];				// 0x0107388B
extern const char g_bfmeEmptyUnicode[];		// 0x0107388C

template <typename T> struct StringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

class AsciiString;
class UnicodeString;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
public:
	void set(const StringBase<T> &other);
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringHeader<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	__forceinline ~AsciiString() { releaseBuffer(); }

	AsciiString &operator=(const AsciiString &other) { set(other); return *this; }

	Int getLength() const { return m_data ? m_data->m_length : 0; }
	const char *str() const { return m_data ? m_data->m_text : Rva006A16B0Empty; }

	void set(const AsciiString &other);
	void set(const char *text, Int length);
	void set(const char *text) { set(text, text ? (Int)strlen(text) : 0); }
	void concat(const char *text, Int length);
	void concat(const AsciiString &other) { Int length = other.getLength(); concat(other.str(), length); }

	const char *reverseFind(char c) const
	{
		const char *text = str();
		const char *p = text + getLength();
		while (p != text)
		{
			if (*--p == c)
				return p;
		}
		return 0;
	}

	__forceinline Int compareNoCase(const AsciiString &other) const
	{
		Int otherLength = other.getLength();
		const char *otherText = other.str();
		Int length = getLength();
		const char *text = str();
		Int result = _memicmp(text, otherText, length < otherLength ? length : otherLength);
		if (result != 0)
			return result;
		return length - otherLength;
	}

private:
	void releaseBuffer();
};

static __forceinline Int compareWide(const WideChar *text, const WideChar *otherText, Int count)
{
	while (count > 0)
	{
		if (*text != *otherText)
			return (Int)*text - (Int)*otherText;
		++text;
		++otherText;
		--count;
	}
	return 0;
}

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	__forceinline ~UnicodeString() { releaseBuffer(); }

	UnicodeString &operator=(const UnicodeString &other) { StringBase<WideChar>::set(other); return *this; }

	Int getLength() const { return m_data ? m_data->m_length : 0; }
	const WideChar *str() const { return m_data ? m_data->m_text : (const WideChar *)g_bfmeEmptyUnicode; }

	void translate(const AsciiString &src);
	void removeLastChar();

	__forceinline Int compare(const UnicodeString &other) const
	{
		Int otherLength = other.getLength();
		const WideChar *otherText = other.str();
		Int length = getLength();
		const WideChar *text = str();
		Int result = compareWide(text, otherText, length < otherLength ? length : otherLength);
		if (result != 0)
			return result;
		return length - otherLength;
	}

private:
	void releaseBuffer();
};

__forceinline Bool operator==(const UnicodeString &left, const UnicodeString &right)
{
	return left.compare(right) == 0;
}

namespace _STL
{
	struct _Rb_tree_node_base
	{
		char _M_color;
		_Rb_tree_node_base *_M_parent;
		_Rb_tree_node_base *_M_left;
		_Rb_tree_node_base *_M_right;
	};

	class __new_alloc
	{
	public:
		static void *allocate(size_t n);
	};

	template <class Dummy> struct _Rb_global
	{
		static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
	};
}

struct FilenameNode : public _STL::_Rb_tree_node_base
{
	AsciiString m_value;			// +0x10
};

namespace rts
{
	template <class T> struct less_than_nocase {};
}

namespace _STL
{
	template <class T> class allocator {};
	template <class T> struct _Identity {};

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc> class _Rb_tree
	{
	public:
		_Rb_tree() : _M_header(0)
		{
			_M_header = (_Rb_tree_node_base *)__new_alloc::allocate(0x14);
			_M_node_count = 0;
			_M_header->_M_color = 0;
			_M_header->_M_parent = 0;
			_M_header->_M_left = _M_header;
			_M_header->_M_right = _M_header;
		}
		~_Rb_tree();					// 0x00197AE0 via ILT 0x000124DB

		_Rb_tree_node_base *_M_header;
		size_t _M_node_count;
		Compare _M_key_compare;
	};

	template <class Key, class Compare, class Alloc> class set
	{
	public:
		_Rb_tree<Key, Key, _Identity<Key>, Compare, Alloc> _M_t;
	};
}

typedef _STL::set<AsciiString, rts::less_than_nocase<AsciiString>, _STL::allocator<AsciiString> > FilenameList;

class GameWindow;

void GadgetListBoxReset(GameWindow *listbox);
void GadgetListBoxSetSelected(GameWindow *listbox, Int row);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Int color, Int row, Int column, Bool overwrite);

struct _SYSTEMTIME
{
	unsigned short wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
};
UnicodeString getUnicodeTimeBuffer(_SYSTEMTIME timeVal);

class RecorderClass
{
public:
	struct ReplayHeader
	{
		~ReplayHeader();					// ILT 0x00011E9B

		Int startTime;
		Int endTime;
		UnsignedInt frameDuration;
		Int networkCRCInterval;
		Int originalGameMode;
		Bool quitEarly;
		Bool playerDiscons[8];
		AsciiString gameOptions;			// +0x20
		Int localPlayerIndex;				// +0x24
		AsciiString filename;				// +0x28
		Bool forPlayback;					// +0x2c
		UnicodeString replayName;			// +0x30
		_SYSTEMTIME timeVal;				// +0x34
		UnicodeString versionString;		// +0x44
		UnicodeString versionTimeString;	// +0x48
		UnsignedInt versionNumber;			// +0x4c
		UnsignedInt exeCRC;					// +0x50
		UnsignedInt iniCRC;					// +0x54
		Bool desyncGame;					// +0x58
		Int m_bfme5C;						// +0x5c (frame witness: info at header+0x60)
	};

	Bool readReplayHeader(ReplayHeader &header);
	AsciiString getLastReplayFileName();
	static AsciiString getReplayExtention();
	static AsciiString getReplayDir();
};
extern RecorderClass *TheRecorder;

class GameSlot
{
public:
	~GameSlot();							// ILT 0x0000B988
private:
	unsigned char m_data[0x44];
};

class GameInfo
{
public:
	void *m_vtbl;
	AsciiString getMap() const;
	__forceinline ~GameInfo() {}
protected:
	unsigned char m_bfmeFields04[0x38];
	AsciiString m_string3C;					// +0x3c (destroyed inline after the slots)
	unsigned char m_bfmeFields40[0x18];
};

class ReplayGameInfo : public GameInfo
{
public:
	ReplayGameInfo();
	__forceinline ~ReplayGameInfo() {}
private:
	GameSlot m_slots[8];					// +0x58
};

Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, Bool includeSlots);

class MapMetaData
{
public:
	UnicodeString m_displayName;			// +0x00
};

class MapCache
{
public:
	void updateCache();
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

class FileSystem
{
public:
	void getFileListInDirectory(const AsciiString &directory, const AsciiString &searchName,
		FilenameList &filenameList, Bool searchSubdirectories) const;
};
extern FileSystem *TheFileSystem;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};
extern GameTextInterface *TheGameText;

// 0x000AED00 is the twin of ZH Version::getUnicodeVersion (called on
// TheVersion, fetches its format from the text table); its ledger row still
// carries the placeholder spelling, so the call is declared against it.
class UnicodeStringAL : public UnicodeString
{
};

class BfmeVersionAL
{
public:
	UnicodeStringAL bfmeVersionTextAL();
};

class Version : public BfmeVersionAL
{
public:
	UnsignedInt getVersionNumber();
};
extern Version *TheVersion;

struct GlobalData0BC8
{
	unsigned char m_pad[0xbc8];
	UnsignedInt m_crcBC8;					// +0xbc8 (compared with header.iniCRC)
	unsigned char m_padBCC[4];
	Int m_valueBD0;							// +0xbd0
};
extern GlobalData0BC8 *TheWritableGlobalData;

Int Rva0009B4B0(Int a, Int b);

void PopulateReplayFileListbox(GameWindow *listbox)
{
	if (!TheMapCache)
		return;

	GadgetListBoxReset(listbox);

	AsciiString asciistr;
	AsciiString asciisearch;
	asciisearch.set("*");
	asciisearch.concat(RecorderClass::getReplayExtention());

	FilenameList replayFilenames;
	TheFileSystem->getFileListInDirectory(RecorderClass::getReplayDir(), asciisearch, replayFilenames, true);

	TheMapCache->updateCache();

	AsciiString lastReplayFName = TheRecorder->getLastReplayFileName();
	lastReplayFName.concat(RecorderClass::getReplayExtention());

	for (_STL::_Rb_tree_node_base *it = replayFilenames._M_t._M_header->_M_left; it != replayFilenames._M_t._M_header;
		it = _STL::_Rb_global<bool>::_M_increment(it))
	{
		asciistr.set(((FilenameNode *)it)->m_value.reverseFind('\\') + 1);

		RecorderClass::ReplayHeader header;
		header.forPlayback = false;
		header.filename = asciistr;
		if (TheRecorder && TheMapCache && TheRecorder->readReplayHeader(header))
		{
			ReplayGameInfo info;
			if (ParseAsciiStringToGameInfo(&info, header.gameOptions, true))
			{
				header.replayName.translate(asciistr);
				for (Int tmp = 0; tmp < RecorderClass::getReplayExtention().getLength(); ++tmp)
					header.replayName.removeLastChar();

				UnicodeString replayNameToShow = header.replayName;
				if (lastReplayFName.compareNoCase(asciistr) == 0)
					replayNameToShow = TheGameText->fetch("GUI:LastReplay");

				UnicodeString displayTimeBuffer = getUnicodeTimeBuffer(header.timeVal);

				UnicodeString mapStr;
				const MapMetaData *md = TheMapCache->findMap(info.getMap());
				if (!md)
					mapStr.translate(info.getMap());
				else
					mapStr = md->m_displayName;

				Bool goodVersion = header.versionString == TheVersion->bfmeVersionTextAL()
					&& header.versionNumber == TheVersion->getVersionNumber()
					&& header.exeCRC == (UnsignedInt)Rva0009B4B0(TheWritableGlobalData->m_valueBD0, TheWritableGlobalData->m_valueBD0)
					&& header.iniCRC == TheWritableGlobalData->m_crcBC8;
				Int color;
				if (goodVersion)
				{
					if (header.localPlayerIndex >= 0)
						color = 0xffffffff;
					else
						color = 0xffffffff;
				}
				else
				{
					if (header.localPlayerIndex >= 0)
						color = 0xff808080;
					else
						color = 0xff808080;
				}

				Int insertionIndex = GadgetListBoxAddEntryText(listbox, replayNameToShow, color, -1, 0, true);
				GadgetListBoxAddEntryText(listbox, displayTimeBuffer, color, insertionIndex, 1, true);
				GadgetListBoxAddEntryText(listbox, header.versionString, color, insertionIndex, 2, true);
				GadgetListBoxAddEntryText(listbox, mapStr, color, insertionIndex, 3, true);
			}
		}
	}

	GadgetListBoxSetSelected(listbox, 0);
}
