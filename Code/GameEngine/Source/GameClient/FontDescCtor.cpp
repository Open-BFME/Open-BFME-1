// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ??0FontDesc@@: Code/GameEngine/Source/GameClient/GlobalLanguage.cpp
// BFME FontDesc default constructor from GlobalLanguage.cpp.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void set(const char *text, int length);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FontDesc.h
struct FontDesc
{
	FontDesc();
	AsciiString name;
	int size;
	Bool bold;
};

FontDesc::FontDesc()
{
	name.set("Arial Unicode MS", 16);
	size = 12;
	bold = false;
}
