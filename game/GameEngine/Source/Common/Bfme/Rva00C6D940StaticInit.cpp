// cl: /DNDEBUG /MD /EHsc
// Retail 0x00C6D940 initializes the address-derived object at 0x0130BE08 as
// STLport's basic_ostream<char> and registers its virtual-base cleanup.
namespace _STL {

class ios_base
{
protected:
    ios_base();

public:
    virtual ~ios_base();
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
    virtual ~basic_streambuf();
};

template <class CharT, class Traits>
class basic_ios : public ios_base
{
public:
    basic_ios() : ios_base(), streambuf_(0), tie_(0), fill_(0) {}
    virtual ~basic_ios();

protected:
    void init(basic_streambuf<CharT, Traits> *streambuf);

private:
    char padding_[0x50];
    CharT fill_;
    basic_streambuf<CharT, Traits> *streambuf_;
    basic_ios<CharT, Traits> *tie_;
};

template <class CharT, class Traits>
class basic_ostream : virtual public basic_ios<CharT, Traits>
{
public:
    basic_ostream(basic_streambuf<CharT, Traits> *streambuf);
    virtual ~basic_ostream() {}
};

template <class CharT>
class char_traits {};

}

#pragma comment(linker, "/alternatename:??0?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@QAE@PAV?$basic_streambuf@DV?$char_traits@D@_STL@@@1@@Z=?j_00041e5c@@YAXXZ")
#pragma comment(linker, "/alternatename:??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ=?j_000414bb@@YAXXZ")

_STL::basic_ostream<char, _STL::char_traits<char> > g_rva0130BE08Object(0);
