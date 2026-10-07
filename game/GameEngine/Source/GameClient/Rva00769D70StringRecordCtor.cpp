// cl: /DNDEBUG /MD /EHsc
// Constructor of an unidentified record, RVA 0x00769D70, 15 bytes:
//   push esi; mov esi,ecx; lea ecx,[esi+4]; call ILT 0x0004048A; mov eax,esi;
//   pop esi; ret
// ILT 0x0004048A reaches 0x004D4F40, the matched STLport std::string default
// constructor, so the record holds a std::string at +4 behind a field the
// constructor leaves alone. Its ?dup_ row used to borrow PopupPlayerInfo.cpp's
// PSResponse constructor, which builds a PSPlayerStats there instead. It sits
// among the ModelConditionInfo bodies (0x00769D00..0x00769DD0). Identity not
// recovered: the class is named for its address.
//
// std::string is spelled with just the declarations the body needs: retail
// calls the STLport constructor out of line, which the real header inlines.

namespace _STL
{

template <class Char>
class char_traits {};

template <class Type>
class allocator {};

template <class Char, class Traits, class Allocator>
class basic_string
{
public:
	basic_string();
	~basic_string();

private:
	Char *m_start;
	Char *m_finish;
	Char *m_endOfStorage;
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Rva00769D70String;

class Rva00769D70Record
{
public:
	Rva00769D70Record();

private:
	int m_field00;							// +0x00, untouched here
	Rva00769D70String m_text;				// +0x04
};

Rva00769D70Record::Rva00769D70Record()
{
}
