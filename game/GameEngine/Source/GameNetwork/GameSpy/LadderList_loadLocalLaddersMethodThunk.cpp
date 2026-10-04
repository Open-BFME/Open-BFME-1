// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

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

// Retail spells this global `GlobalData *TheWritableGlobalData`; this TU only
// reads the user-data path through it, so it keeps the local view and casts at
// the use. Retail reaches that member through the ILT thunk ?j_000106ea@@YAXXZ,
// so the call goes through a member pointer initialised with the thunk.
class GlobalData;

class Rva006C9270GlobalData
{
public:
	typedef AsciiString (Rva006C9270GlobalData::*GetPathUserDataFn)() const;
};

extern GlobalData *TheWritableGlobalData;

// Same story for the file list: retail calls the shared free __stdcall body
// ?bfmeListAllEBC@@YGXABVBfmeStrEBC@@0PAXH@Z (see
// game/GameEngine/Source/Common/BfmeConv2019.cpp) from this site, so the
// thiscall member pointer is initialised with that routine's address.
class FileSystem
{
public:
	typedef void (FileSystem::*ListFilesFn)(const AsciiString &, const AsciiString &, FilenameList &, bool);
};

// Only forward declared: this TU never builds one, it only passes references.
class BfmeStrEBC;

extern void __stdcall bfmeListAllEBC(const BfmeStrEBC &, const BfmeStrEBC &, void *, int);

extern FileSystem *TheFileSystem;

// ?j_00028efc@@YAXXZ is the ILT thunk retail's checkLadder call goes through.
extern void j_000106ea();
extern void j_00028efc();

class LadderList
{
private:
	void loadLocalLadders();
	typedef void (LadderList::*CheckLadderFn)(AsciiString, int);
};

// Kept: the retail call is the implicit teardown of
// std::_Rb_tree<AsciiString, _Identity<AsciiString>, rts::less_than_nocase<...>,
// allocator<AsciiString>>::~_Rb_tree. Only STLport's own template instantiates
// that mangled name, and the set must stay a scope object with an implicit
// destructor for the unwind state byte and the .text$x cleanup thunks to come
// out identical, so it cannot be respelled or called through a member pointer.
#pragma comment(linker, "/alternatename:??1?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@3@@_STL@@QAE@XZ=?j_000124db@@YAXXZ")

// ?loadLocalLadders@LadderList@@AAEXXZ
void LadderList::loadLocalLadders()
{
	AsciiString dirname;
	union { void (*fn)(); Rva006C9270GlobalData::GetPathUserDataFn call; } path = { j_000106ea };
	dirname.format(AsciiString("%sLoTRB4MEOnline\\Ladders\\"),
		(((Rva006C9270GlobalData *)TheWritableGlobalData)->*path.call)().str());

	FilenameList filenameList;
	union { void (__stdcall *fn)(const BfmeStrEBC &, const BfmeStrEBC &, void *, int);
		FileSystem::ListFilesFn call; } list = { bfmeListAllEBC };
	(TheFileSystem->*list.call)(dirname, AsciiString("*.ini"), filenameList, true);

	int index = -1;
	FilenameList::iterator it = filenameList.begin();
	union { void (*fn)(); LadderList::CheckLadderFn call; } check = { j_00028efc };
	while (it != filenameList.end())
	{
		AsciiString filename = *it;
		filename.toLower();
		(this->*check.call)(filename, index--);
		++it;
	}
}
