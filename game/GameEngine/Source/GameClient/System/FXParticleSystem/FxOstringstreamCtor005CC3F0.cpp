// cl: /DNDEBUG /MD /EHsc
// The basic_ostringstream<char>(openmode) constructor (0x005CC3F0, 193 B) and
// the basic_ostream<char>(basic_streambuf*) constructor (0x005CC230, 141 B)
// that the FX particle system TU instantiated for its writeINI streams.
// STLport's ostringstream(openmode): basic_ostream(0), then the member
// basic_stringbuf built from mode|out (0x005C7370, through the ILT at
// 0x0002B409), then init(&buf). The 0x6c-byte stringbuf puts the basic_ios
// virtual base at +0x70. Compiled from the real STLport headers, MSVC inlines
// calls retail makes out of line (297 B against 193), hence this ABI model.

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

template <class CharT>
class char_traits {};

template <class T>
class allocator {};

template <class CharT, class Traits, class Alloc>
class basic_stringbuf : public basic_streambuf<CharT, Traits> {
public:
  basic_stringbuf(int mode);
  virtual ~basic_stringbuf();

private:
  char padding_[0x68];
};

template <class CharT, class Traits, class Alloc>
class basic_ostringstream : public basic_ostream<CharT, Traits> {
public:
  basic_ostringstream(int mode)
      : basic_ios<CharT, Traits>(), basic_ostream<CharT, Traits>(0), buf_(mode | 0x10) {
    this->init(&buf_);
  }

private:
  basic_stringbuf<CharT, Traits, Alloc> buf_;
};

template basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int);
template basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *);

}
