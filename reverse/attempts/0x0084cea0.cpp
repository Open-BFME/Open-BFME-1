// ??0Rva0084CEA0Stream@@QAE@PBDHJ@Z
// partial score=0.94 date=2026-09-21
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Address-derived: retail RVA 0x0084CEA0, 249 bytes. Same construction
// sequence as basic_fstream<wchar_t>'s real pathname constructor at
// 0x0084D0A0 (StreamConstructorInstantiations.cpp) -- same vtables
// (0x112fcac/0x112fca4/0x112ebcc/0x112fc50), same ios_base/basic_iostream/
// basic_filebuf<wchar_t> construction order -- except this body always
// pushes the literal 0x80 to _M_open instead of forwarding its own third
// argument, the same hardcoded-protection quirk the narrow twin shows at
// 0x0084C6F0. Since 0x0084D0A0 already claims the real
// basic_fstream<wchar_t> mangled name, this can't be another instantiation
// of the same template specialization; it stays an address-derived wrapper
// class replicating the same STLport plumbing by composition.
#include <fstream>

class Rva0084CEA0Stream : public _STL::basic_iostream<wchar_t, _STL::char_traits<wchar_t> >
{
public:
	Rva0084CEA0Stream(const char *name, _STL::ios_base::openmode mode, long /*protection*/) :
		_STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >(),
		_STL::basic_iostream<wchar_t, _STL::char_traits<wchar_t> >(0),
		_M_buf()
	{
		this->init(&_M_buf);
		if (!_M_buf.open(name, mode, 0x80))
			this->setstate(_STL::ios_base::failbit);
	}

private:
	_STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> > _M_buf;
};

// force emission of the inline constructor above
void Rva0084CEA0Force(const char *name)
{
	Rva0084CEA0Stream s(name, _STL::ios_base::in, 0);
	(void)s;
}
