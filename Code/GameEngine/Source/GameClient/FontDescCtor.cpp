// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME FontDesc default constructor from GlobalLanguage.cpp.

typedef bool Bool;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void set(const char *text, int length);

private:
	void *m_data;
};

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
