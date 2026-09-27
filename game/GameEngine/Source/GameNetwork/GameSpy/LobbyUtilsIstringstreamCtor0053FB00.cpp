// The basic_istringstream<char>(const string&, openmode) constructor that
// LobbyUtils.cpp instantiated at 0x0053FB00 (201 B), and the
// basic_istream<char>(basic_streambuf*) constructor beside it (0x0053FA20).
// STLport's istringstream: basic_istream(0), then the member basic_stringbuf
// built from the string and mode|in (0x0053C660, through the ILT at
// 0x0004A958), then init(&buf). The 0x6c-byte stringbuf after the vbptr and
// gcount puts the basic_ios virtual base at +0x74.

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
class basic_istream : virtual public basic_ios<CharT, Traits> {
public:
  basic_istream(basic_streambuf<CharT, Traits> *streambuf)
      : basic_ios<CharT, Traits>(), gcount_(0) {
    this->init(streambuf);
  }
  virtual ~basic_istream();

private:
  int gcount_;
};

template <class CharT>
class char_traits {};

template <class T>
class allocator {};

template <class CharT, class Traits, class Alloc>
class basic_string;

template <class CharT, class Traits, class Alloc>
class basic_stringbuf : public basic_streambuf<CharT, Traits> {
public:
  basic_stringbuf(const basic_string<CharT, Traits, Alloc> &str, int mode);
  virtual ~basic_stringbuf();

private:
  char padding_[0x68];
};

template <class CharT, class Traits, class Alloc>
class basic_istringstream : public basic_istream<CharT, Traits> {
public:
  basic_istringstream(const basic_string<CharT, Traits, Alloc> &str, int mode)
      : basic_ios<CharT, Traits>(), basic_istream<CharT, Traits>(0), buf_(str, mode | 8) {
    this->init(&buf_);
  }

private:
  basic_stringbuf<CharT, Traits, Alloc> buf_;
};

template basic_istringstream<char, char_traits<char>, allocator<char> >::basic_istringstream(
    const basic_string<char, char_traits<char>, allocator<char> > &, int);
template basic_istream<char, char_traits<char> >::basic_istream(basic_streambuf<char, char_traits<char> > *);

}
