// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: ThingTemplate::parsePerUnitFX's FieldParse callback, retail
// 0x00145C80, 206 bytes.  The body is the static free function
// parseArbitraryFXIntoMap of ThingTemplate.cpp (the FieldParse table at
// 0x01094960 pairs it with the key "" and ThingTemplate::parsePerUnitFX at
// 0x00145D90 is its only caller); the readable form is the copy in
// ThingTemplate.cpp and in the Zero Hour twin.
//
// The stand-in types below exist to hit the STLport instantiations retail
// calls: the mapped type names the four-byte value the _M_insert at 0x00142EE0
// allocates, and the pair constructor is reached through the ILT thunk at
// 0x000307D8 -- see the matching targets/game/reverse/symbols.csv pin.  Both
// emit byte-identical code whichever four-byte type fills them, so the layout
// is what the byte gate proves and the spelling is not.

#include <map>

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase();
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	static AsciiString TheEmptyString;

	int compare(const AsciiString &other) const;
};

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
};

class FXList;

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

extern FXListStore *TheFXListStore;

// The mapped type is the four-byte value the _M_insert at 0x00142EE0
// allocates, so the insert lands on the insert_unique already instantiated for
// it at 0x001446F0 (RvaTreeInsertUniquePlain.cpp).
struct Rva00142EE0Value
{
	Rva00142EE0Value(const FXList *list) : m_fxList(list) {}

	const FXList *m_fxList;
};

typedef std::map<AsciiString, Rva00142EE0Value> PerUnitFXMap;

// ?parseArbitraryFXIntoMap@@YAXPAVINI@@PAX1PBX@Z
void parseArbitraryFXIntoMap(INI *ini, void *instance, void *, const void *userData)
{
	PerUnitFXMap *mapFX = (PerUnitFXMap *)instance;
	const char *name = (const char *)userData;
	const char *token = ini->getNextToken();
	const FXList *fxl = TheFXListStore->findFXList(token);	// could be null!
	mapFX->insert(std::make_pair(AsciiString(name), fxl));
}
