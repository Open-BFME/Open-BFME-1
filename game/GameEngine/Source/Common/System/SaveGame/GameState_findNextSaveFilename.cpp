// cl: /DNDEBUG /MD /EHsc
// Real-C++ reconstruction of GameState::findNextSaveFilename at 0x00110010.
// The retail body is the BFME lowest-number save-file search: its hidden
// AsciiString result and by-value UnicodeString account for ret 8.

typedef int Int;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase();
	void set(const StringBase<T> &other);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	static AsciiString TheEmptyString;

	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void format(AsciiString format, ...);

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	const char *str() const
	{
		return m_data ? &m_data->data[0] : (const char *)0x0107388B;
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

extern "C" __declspec(dllimport) int __cdecl _access(const char *path, int mode);

class GameState
{
public:
	AsciiString getFilePathInSaveDirectory(const AsciiString &leaf) const;

private:
	AsciiString findNextSaveFilename(UnicodeString desc);
};

static const char *SAVE_GAME_EXTENSION = ".sav";
static const Int MAX_SAVE_FILE_NUMBER = 99999999;

// ?findNextSaveFilename@GameState@@AAE?AVAsciiString@@VUnicodeString@@@Z
AsciiString GameState::findNextSaveFilename(UnicodeString desc)
{
	// This unreachable string lifetime models the upstream alternative search
	// mode. MSVC 7.1 retains its unwind-state number: deleting this scope
	// changes live states 4/5 to 3/4 and breaks the 281-byte retail match.
	// This branch is never selectable; BFME only executes the numbered search.
	if (false)
	{
		AsciiString filename;
		return AsciiString::TheEmptyString;
	}
	else
	{
		AsciiString filename;
		AsciiString fullPath;
		Int i = 1;

		while (true)
		{
			filename.format("%08d%s", i, SAVE_GAME_EXTENSION);
			fullPath = getFilePathInSaveDirectory(filename);

			if (_access(fullPath.str(), 0) == -1)
				return filename;

			++i;
			if (i > MAX_SAVE_FILE_NUMBER)
				return AsciiString::TheEmptyString;
		}
	}
}
