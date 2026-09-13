// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#include <set>

extern const char g_bfmeEmptyAscii[];

template <typename T>
class StringBase
{
	friend class AsciiString;

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &source);

public:
	void toLower();

private:
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void __cdecl format(AsciiString format, ...);

	void toLower()
	{
		((StringBase<char> *)this)->toLower();
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}
};

namespace rts
{
	template <typename T>
	struct less_than_nocase
	{
		bool operator()(const T &, const T &) const;
	};
}

typedef std::set<AsciiString, rts::less_than_nocase<AsciiString> > FilenameList;

class Rva006C9270GlobalData
{
public:
	AsciiString getPath_UserData() const;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class FileSystem
{
public:
	void getFileListInDirectory(const AsciiString &, const AsciiString &, FilenameList &, bool) const;
};

extern FileSystem *TheFileSystem;

class LadderList
{
private:
	void loadLocalLadders();
	void checkLadder(AsciiString, int);
};

#pragma comment(linker, "/alternatename:?getPath_UserData@Rva006C9270GlobalData@@QBE?AVAsciiString@@XZ=?j_000106ea@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFileListInDirectory@FileSystem@@QBEXABVAsciiString@@0AAV?$set@VAsciiString@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z=?bfmeListAllEBC@@YGXABVBfmeStrEBC@@0PAXH@Z")
#pragma comment(linker, "/alternatename:?checkLadder@LadderList@@AAEXVAsciiString@@H@Z=?j_00028efc@@YAXXZ")
#pragma comment(linker, "/alternatename:??1?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@3@@_STL@@QAE@XZ=?j_000124db@@YAXXZ")

// ?loadLocalLadders@LadderList@@AAEXXZ
void LadderList::loadLocalLadders()
{
	AsciiString dirname;
	dirname.format(AsciiString("%sLoTRB4MEOnline\\Ladders\\"), TheWritableGlobalData->getPath_UserData().str());

	FilenameList filenameList;
	TheFileSystem->getFileListInDirectory(dirname, AsciiString("*.ini"), filenameList, true);

	int index = -1;
	FilenameList::iterator it = filenameList.begin();
	while (it != filenameList.end())
	{
		AsciiString filename = *it;
		filename.toLower();
		checkLadder(filename, index--);
		++it;
	}
}
