// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x00487870 is WindowLayoutInfo::load, with a 234-byte body.
// The caller at 0x004889A0 constructs WindowLayoutInfo through 0x004888A0, then uses this body to choose the .apt or window-script loader.

typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(
	const char *left, const char *right);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class WindowLayoutInfo;

public:
	StringBase() {}

	struct Data
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	Data *m_data;

	private:
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
		return *this;
	}

	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

class WindowLayoutInfo;
class GameWindow;

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual GameWindow *winCreateFromScript(
		StringBase<char> filename, WindowLayoutInfo *info, void *extra);
};

class BfmeAptManager
{
public:
	void *loadLayout(AsciiString *filename, WindowLayoutInfo *info);
};

#pragma comment(linker, "/alternatename:?loadLayout@BfmeAptManager@@QAEPAXPAVAsciiString@@PAVWindowLayoutInfo@@@Z=?j_000429a6@@YAXXZ")

#define TheAptManager (*(BfmeAptManager **)0x012F19E8)
extern GameWindowManager *TheWindowManager;

class WindowLayoutInfo
{
public:
	Bool load(AsciiString filename);

	unsigned char m_prefix[0x24];
	AsciiString m_filename;
};

Bool WindowLayoutInfo::load(AsciiString filename)
{
	if (filename.isEmpty())
		return false;

	const unsigned short length = filename.m_data->m_length;
	const char *extension = filename.m_data->m_text;
	const char *begin = extension;
	const char *end = begin + length;
	void *result;
	while (extension != end)
	{
		if (*extension == '.')
		{
			if (_strcmpi(extension, ".apt") == 0)
				result = TheAptManager->loadLayout(&filename, this);
			else
				result = TheWindowManager->winCreateFromScript(
					*(StringBase<char> *)&filename, this, 0);
			goto checked;
		}
		++extension;
	}
	result = TheWindowManager->winCreateFromScript(
		*(StringBase<char> *)&filename, this, 0);

checked:
	if (result == 0)
		return false;

	m_filename = filename;
	return true;
}
