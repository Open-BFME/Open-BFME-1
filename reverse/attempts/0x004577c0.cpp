// ?loadUserMaps@MapCache@@AAE_NXZ
// partial score=0.55 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oy- /D_STLP_USE_STATIC_LIB
// stlport

#include <string.h>
#include <map>
#include <set>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#define FALSE false
#define TRUE true

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	void toLower();
	void removeLastChar();
	bool startsWithNoCase(const T *text, int length) const;
	bool endsWithNoCase(const T *text, int length) const;
	void set(const StringBase<T> &other);

	struct Data
	{
		Int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
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

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	void __cdecl format(AsciiString fmt, ...);
	void toLower() { StringBase<char>::toLower(); }
	void removeLastChar() { StringBase<char>::removeLastChar(); }

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	Int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const char *reverseFind(char c) const
	{
		const char *start = str();
		const char *p = start + getLength();
		while (p != start)
		{
			--p;
			if (*p == c)
				return p;
		}
		return 0;
	}

	bool endsWithNoCase(const char *text) const
	{
		return StringBase<char>::endsWithNoCase(text, 0);
	}

	bool operator<(const AsciiString &other) const;
	int compareNoCase(const AsciiString &other) const;
};

namespace rts
{
template <typename T>
struct less_than_nocase
{
	bool operator()(const T &left, const T &right) const
	{
		return left.compareNoCase(right) < 0;
	}
};
}

struct MapMetaData
{
	char opaque[252];
};

struct FileInfo
{
	Int sizeHigh;
	Int sizeLow;
	Int timestampHigh;
	Int timestampLow;
};

class File
{
public:
	virtual void unknown00();
	virtual void unknown04();
	virtual void close();
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access);
	Bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
	void getFileListInDirectory(const AsciiString &directory,
		const AsciiString &searchName, void *filenameList,
		Bool searchSubdirectories) const;
};

extern FileSystem *TheFileSystem;

class GlobalData
{
public:
	char m_prefix[0xb7d];
	bool m_buildMapCache;
};

extern GlobalData *TheWritableGlobalData;

class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, Int loadType, Int reload, void *xfer);

private:
	char m_storage[0x844];
};

class BfmeStrEBC
{
public:
	void *m_bfmeDataEBC;
};

extern void __stdcall bfmeListAllEBC(const BfmeStrEBC &a,
	const BfmeStrEBC &b, void *out, Int flag);

typedef std::set<AsciiString, rts::less_than_nocase<AsciiString> > FilenameList;
typedef FilenameList::iterator FilenameListIter;

class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	AsciiString getMapDir() const;
	AsciiString getUserMapDir() const;
	AsciiString getMapExtension() const;

private:
	Bool loadUserMaps();
	Bool clearUnseenMaps(AsciiString dirName);
	Bool addMap(AsciiString dirName, AsciiString fname,
		FileInfo *fileInfo, Bool isOfficial);

	static const char * const m_mapCacheName;
	std::map<AsciiString, Bool> m_seen;
	std::set<AsciiString> m_allowedMaps;
};

const char * const MapCache::m_mapCacheName = "MapCache.ini";
static char *mapExtension = ".map";

Bool MapCache::loadUserMaps()
{
	AsciiString mapDir;
	if (TheWritableGlobalData->m_buildMapCache)
	{
		mapDir = getMapDir();
	}
	else
	{
		mapDir = getUserMapDir();

		INI ini;
		AsciiString fname;
		fname.format(AsciiString("%s\\%s"), mapDir.str(), m_mapCacheName);
		File *fp = TheFileSystem->openFile(fname.str(), 1);
		if (fp)
		{
			fp->close();
			try
			{
				ini.load(fname, 1, 0, (void *)0x004312EB);
			}
			catch (...)
			{
			}
		}
	}

	m_seen.clear();
	MapCache::iterator it = begin();
	while (it != end())
	{
		m_seen[it->first] = FALSE;
		++it;
	}

	FilenameList filenameList;
	FilenameListIter iter;
	AsciiString toplevelPattern;
	toplevelPattern.format(AsciiString("%s\\"), mapDir.str());
	Bool parsedAMap = FALSE;
	AsciiString filenamepattern;
	filenamepattern.format(AsciiString("*.%s"), getMapExtension().str());

	TheFileSystem->getFileListInDirectory(toplevelPattern, filenamepattern,
		&filenameList, TRUE);

	iter = filenameList.begin();
	while (iter != filenameList.end())
	{
		FileInfo fileInfo;
		AsciiString tempfilename;
		tempfilename = (*iter);
		tempfilename.toLower();

		const char *s = tempfilename.reverseFind('\\');
		if (!s)
		{
		}
		else
		{
			AsciiString endingStr;
			AsciiString fname = s + 1;
			for (Int i = 0; i < strlen(mapExtension); ++i)
				fname.removeLastChar();

			endingStr.format(AsciiString("%s\\%s%s"), fname.str(),
				fname.str(), mapExtension);

			Bool skipMap = FALSE;
			if (TheWritableGlobalData->m_buildMapCache)
			{
				std::set<AsciiString>::const_iterator sit = m_allowedMaps.find(fname);
				if (m_allowedMaps.size() != 0 && sit == m_allowedMaps.end())
				{
					skipMap = TRUE;
				}
			}

			if (!skipMap)
			{
				if (!tempfilename.endsWithNoCase(endingStr.str()))
				{
				}
				else
				{
					if (TheFileSystem->getFileInfo(tempfilename, &fileInfo))
					{
						char funk[260];
						strcpy(funk, tempfilename.str());
						char *filenameptr = funk;
						char *tempchar = funk;
						while (*tempchar != 0)
						{
							if ((*tempchar == '\\') || (*tempchar == '/'))
							{
								filenameptr = tempchar + 1;
							}
							++tempchar;
						}

						m_seen[tempfilename] = TRUE;
						parsedAMap |= addMap(mapDir, *iter, &fileInfo,
							TheWritableGlobalData->m_buildMapCache);
					}
				}
			}
		}
		iter++;
	}

	if (clearUnseenMaps(mapDir))
		return TRUE;

	return parsedAMap;
}
