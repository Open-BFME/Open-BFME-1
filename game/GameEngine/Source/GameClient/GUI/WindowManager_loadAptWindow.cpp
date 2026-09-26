// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// WindowManager::loadAptWindow, vtable 0x010F72A8 slot 15: claims an APT window
// record, maps the movie file to it and loads the movie's .big archive.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

// The by-value strings use the same inline StringBase forwarders as the landed
// WindowManager callers.  The length-taking overloads are the two retail calls
// in this body, so keep them visible rather than expanding the implementation.
template <typename T>
class StringBase
{
public:
	bool endsWith(const T *text, int length) const;
	bool endsWith(const T *text) const;
	void concat(const T *text, int length);
	void concat(const T *text);

private:
	friend class AsciiString;
	StringBase();
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	bool endsWith(const char *text, int length) const
	{
		return ((const StringBase<char> *)this)->endsWith(text, length);
	}

	bool endsWith(const char *text) const
	{
		return ((const StringBase<char> *)this)->endsWith(text);
	}

	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void concat(const char *text)
	{
		((StringBase<char> *)this)->concat(text);
	}
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return *(const void * const *)&left == *(const void * const *)&right;
}

namespace rts
{
	template <class T>
	struct hash
	{
		unsigned int operator()(T value) const;
	};
}

enum Rva00469D20Mapped
{
	Rva00469D20MappedZero = 0
};

typedef _STL::hash_map<AsciiString, Rva00469D20Mapped,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00469D20Mapped> > >
	Rva00469D20Map;

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva004666C0
{
public:
	void set(int index, const Rva0036CA00Str &directory,
		const Rva0036CA00Str &file, int parameter);

	Rva0036CA00Str m_directory;
	Rva0036CA00Str m_file;
	int m_parameter;
	int m_index;
	unsigned char m_flags;
};

class ArchiveFileSystem
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual bool loadBigFilesFromDirectory(AsciiString directory,
		AsciiString file, bool overwrite) = 0;
};

extern ArchiveFileSystem *TheArchiveFileSystem;

class WindowManager
{
public:
	#define WINDOW_MANAGER_SLOT(n) virtual void windowManagerSlot##n() = 0
	WINDOW_MANAGER_SLOT(0); WINDOW_MANAGER_SLOT(1); WINDOW_MANAGER_SLOT(2);
	WINDOW_MANAGER_SLOT(3); WINDOW_MANAGER_SLOT(4); WINDOW_MANAGER_SLOT(5);
	WINDOW_MANAGER_SLOT(6); WINDOW_MANAGER_SLOT(7); WINDOW_MANAGER_SLOT(8);
	WINDOW_MANAGER_SLOT(9); WINDOW_MANAGER_SLOT(10); WINDOW_MANAGER_SLOT(11);
	WINDOW_MANAGER_SLOT(12); WINDOW_MANAGER_SLOT(13); WINDOW_MANAGER_SLOT(14);
	#undef WINDOW_MANAGER_SLOT
	virtual int loadAptWindow(AsciiString directory, AsciiString file,
		bool unknown1, int unknown2, int unknown3);

private:
	unsigned char m_beforeFileMap[0x54];
	Rva00469D20Map m_fileToWindow;
	// The other map views occupy the remaining bytes before the proven APT
	// records at +0xa8.
	unsigned char m_betweenMaps[0x3c];
	Rva004666C0 m_aptWindows[12];
	unsigned char m_betweenRecordsAndDirty[0x15];
	unsigned char m_aptWindowsDirty;
};

// ?loadAptWindow@WindowManager@@UAEHVAsciiString@@0_NHH@Z
int WindowManager::loadAptWindow(AsciiString directory, AsciiString file,
	bool unknown1, int unknown2, int unknown3)
{
	Rva00469D20Map *map = &m_fileToWindow;
	Rva00469D20Map::iterator found = map->find(file);
	if (found != map->end() &&
		(*found).second != (Rva00469D20Mapped)-1)
		return -1;

	int index = unknown3;
	if (index == -1)
	{
		index = 0;
		while (index < 12)
		{
			if (m_aptWindows[index].m_index == -1)
				goto free_slot;
			++index;
		}
		return -1;
	}
	else
	{
		if ((unsigned int)index >= 12)
			return 0;
		if (m_aptWindows[index].m_index != -1)
			return -1;
	}

	goto selected_slot;

free_slot:
	if (index == -1)
		return -1;

selected_slot:


	if (!directory.endsWith("\\", 1) &&
		!directory.endsWith("/"))
		directory.concat("\\");

	m_aptWindows[index].set(index,
		*(const Rva0036CA00Str *)&directory,
		*(const Rva0036CA00Str *)&file,
		unknown2);
	(*map)[file] = (Rva00469D20Mapped)index;

	if (unknown1)
	{
		m_aptWindowsDirty = 1;
		m_aptWindows[index].m_flags |= 1;
	}

	AsciiString aptFile = file;
	aptFile.concat(".big", 4);
	TheArchiveFileSystem->loadBigFilesFromDirectory(directory, aptFile, true);
	return index;
}
