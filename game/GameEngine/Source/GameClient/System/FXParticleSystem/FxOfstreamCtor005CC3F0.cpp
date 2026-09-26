// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the basic_ofstream<char>(int mode) constructor (0x005CC3F0,
// 193 B, filebuf built from mode|out through the ILT at 0x0002B409)
// and the basic_ostream<char>(basic_streambuf*) constructor (0x005CC230, 141 B)
// that the FX particle system TU instantiated; the game-side filebuf is 0x6c
// bytes so the virtual base sits at +0x70, unlike the stlport library copies.
// STLport 4.5 narrow basic_ofstream default constructor.
// The retail constructor uses the 0xB8 virtual-base offset and the 0xB0
// basic_filebuf size represented by this minimal ABI layout. Near-twin of
// the narrow basic_ifstream default constructor (0x0084C240): basic_ostream
// has no int data member analogous to basic_istream's gcount_, so every
// this-relative offset from the streambuf pointer onward is 4 bytes lower
// and the "mov dword ptr [esi+4], ebx" gcount_-zeroing store is absent.

namespace _STL {

class ios_base {
protected:
  ios_base();

public:
  virtual ~ios_base();
};

template <class CharT, class Traits>
class basic_streambuf {
public:
  virtual ~basic_streambuf();
};

template <class CharT, class Traits>
class basic_ios : public ios_base {
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
class basic_ostream : virtual public basic_ios<CharT, Traits> {
public:
  basic_ostream(basic_streambuf<CharT, Traits> *streambuf)
      : basic_ios<CharT, Traits>() {
    this->init(streambuf);
  }
  virtual ~basic_ostream();
};

template <class CharT, class Traits>
class basic_filebuf : public basic_streambuf<CharT, Traits> {
public:
  basic_filebuf(int mode);
  virtual ~basic_filebuf();

private:
  char padding_[0x68];
};

template <class CharT>
class char_traits {};

template <class CharT, class Traits>
class basic_ofstream : public basic_ostream<CharT, Traits> {
public:
  basic_ofstream(int mode)
      : basic_ios<CharT, Traits>(), basic_ostream<CharT, Traits>(0), buf_(mode | 0x10) {
    this->init(&buf_);
  }

private:
  basic_filebuf<CharT, Traits> buf_;
};

template basic_ofstream<char, char_traits<char> >::basic_ofstream(int);
template basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *);

}
