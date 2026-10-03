// updateCache and getDefaultMap call the ILT thunk at 0x00028FF1, which routes
// to this body at 0x004577C0.
// MapUtil.h supplies MapCache. Address-named views model its retail GlobalData
// flag and File vtable slot. The BFME INI view matches the 0x848-byte local and
// four-argument load call.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#include <string.h>
#include <map>
#include <set>
#define _OPERATOR_NEW_DEFINED_
#define __INI_H_
#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/AsciiString.h"
#include "GameClient/MapUtil.h"
#include "Common/FileSystem.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva004577C0StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class Rva004577C0StringView
{
public:
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

	Rva004577C0StringData *m_data;
};

inline bool rvaAsciiStringEndsWithNoCase(const AsciiString &value,
	const char *text)
{
	return ((const StringBase<char> &)value).endsWithNoCase(text,
		text ? (Int)strlen(text) : 0);
}

struct Rva004577C0GlobalData
{
	char m_prefix[0xb7d];
	Bool m_buildMapCache;
};

class Rva004577C0FileView
{
public:
	virtual void unknown00();
	virtual void unknown04();
	virtual void close();
};

class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, Int loadType, Int reload, void *xfer);

private:
	char m_storage[0x848];
};

// The existing byte-valued map operator[] retains its char ABI. Its
// mapped value is one byte at node+0x14; this caller stores only zero/one.
typedef std::map<AsciiString, char> Rva004545A0SeenMap;
struct Rva004577C0SeenView
{
    _STL::_Rb_tree_node_base *m_header;
    unsigned int m_count;
    unsigned int m_padding;
};
extern void j_0000db2a();
extern void j_000312eb(); // INI load callback through retail ILT, target RVA 0x000C1E50.
template <class F> inline F rva004577C0Call(void (*raw)())
{
    union { void (*p)(); F f; } u;
    u.p = raw;
    return u.f;
}

static const char * const mapCacheIniName = "MapCache.ini";
static const char * const mapExtension = ".map";

Bool MapCache::loadUserMaps()
{
	AsciiString mapDir;
	if (((Rva004577C0GlobalData *)TheWritableGlobalData)->m_buildMapCache)
	{
		mapDir = getMapDir();
	}
	else
	{
		mapDir = getUserMapDir();

		INI ini;
		AsciiString fname;
		fname.format(AsciiString("%s\\%s"), ((const Rva004577C0StringView &)mapDir).str(), mapCacheIniName);
		Rva004577C0FileView *fp = (Rva004577C0FileView *)TheFileSystem->openFile(
			((const Rva004577C0StringView &)fname).str(), 1);
		if (fp)
		{
			fp->close();
			try
			{
				ini.load(fname, 1, 0, (void *)j_000312eb);
			}
			catch (...)
			{
			}
		}
	}

	Rva004577C0SeenView &seen = (Rva004577C0SeenView &)m_seen;
	if (seen.m_count != 0)
	{
		typedef void (Rva004577C0SeenView::*Erase)(_STL::_Rb_tree_node_base *);
		(seen.*rva004577C0Call<Erase>(j_0000db2a))(seen.m_header->_M_parent);
		seen.m_header->_M_left = seen.m_header;
		seen.m_header->_M_parent = 0;
		seen.m_header->_M_right = seen.m_header;
		seen.m_count = 0;
	}
	MapCache::iterator it = begin();
	while (it != end())
	{
		((Rva004545A0SeenMap &)m_seen)[it->first] = FALSE;
		++it;
	}

	FilenameListIter iter;
	FilenameList filenameList;
	AsciiString toplevelPattern;
	toplevelPattern.format(AsciiString("%s\\"), ((const Rva004577C0StringView &)mapDir).str());
	Bool parsedAMap = FALSE;
	AsciiString filenamepattern;
	filenamepattern.format(AsciiString("*.%s"), ((const Rva004577C0StringView &)getMapExtension()).str());

	TheFileSystem->getFileListInDirectory(toplevelPattern, filenamepattern,
		filenameList, TRUE);

	iter = filenameList.begin();
	while (iter != filenameList.end())
	{
		FileInfo fileInfo;
		AsciiString tempfilename;
		tempfilename = (*iter);
		tempfilename.toLower();

		const char *s = ((const Rva004577C0StringView &)tempfilename).reverseFind('\\');
		if (!s)
		{
		}
		else
		{
			AsciiString endingStr;
			AsciiString fname = s + 1;
			for (Int i = 0; i < 4; ++i)
				fname.removeLastChar();

			endingStr.format(AsciiString("%s\\%s%s"), ((const Rva004577C0StringView &)fname).str(),
				((const Rva004577C0StringView &)fname).str(), mapExtension);

			Bool skipMap = FALSE;
			if (((Rva004577C0GlobalData *)TheWritableGlobalData)->m_buildMapCache)
			{
				std::set<AsciiString>::const_iterator sit = m_allowedMaps.find(fname);
				if (m_allowedMaps.size() != 0 && sit == m_allowedMaps.end())
				{
					skipMap = TRUE;
				}
			}

			if (!skipMap)
			{
				if (!rvaAsciiStringEndsWithNoCase(tempfilename,
					((const Rva004577C0StringView &)endingStr).str()))
				{
				}
				else
				{
					if (TheFileSystem->getFileInfo(tempfilename, &fileInfo))
					{
						char funk[260];
						strcpy(funk, ((const Rva004577C0StringView &)tempfilename).str());
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

						if (strlen(filenameptr) < 0x50)
						{
							((Rva004545A0SeenMap &)m_seen)[tempfilename] = TRUE;
							parsedAMap |= addMap(mapDir, *iter, &fileInfo,
								((Rva004577C0GlobalData *)TheWritableGlobalData)->m_buildMapCache);
						}
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
