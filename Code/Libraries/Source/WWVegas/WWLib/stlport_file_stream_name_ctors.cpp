// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: STLport 4.5 narrow file-stream constructors taking a file name:
// basic_ifstream<char>(int fd, int), (const char*, int [, long]) and basic_ofstream<char>(...)
// from the static library (0x0084C410 / 0x0084C300 / 0x0084C520 and
// 0x0084B980 / 0x0084BB90). Same shell as the default constructors landed in
// stlport_basic_ifstream_char_default_ctor.cpp, then the filebuf is opened
// through _Filebuf_base::_M_open (the two- or three-argument overload) and a
// failed open sets failbit inline: iostate |= failbit, badbit if there is no
// streambuf, then the exception mask check.
namespace _STL {
class ios_base {
protected:
  ios_base();
  void _M_throw_failure();
public:
  virtual ~ios_base();
  enum { badbit = 1, failbit = 4, in = 8, out = 0x10 };
  int _M_pad4;
  int _M_iostate;
  int _M_pad0c;
  int _M_pad10;
  int _M_exception_mask;
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
  void setstate(int state) { clear(_M_iostate | state); }
  void clear(int state) {
    _M_clear_nothrow(streambuf_ != 0 ? state : (state | badbit));
    _M_check_exception_mask();
  }
  void _M_clear_nothrow(int state) { _M_iostate = state; }
  void _M_check_exception_mask() {
    if (_M_iostate & _M_exception_mask)
      _M_throw_failure();
  }
protected:
  void init(basic_streambuf<CharT, Traits> *streambuf);
private:
  char padding_[0x3c];
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
template <class CharT, class Traits>
class basic_ostream : virtual public basic_ios<CharT, Traits> {
public:
  basic_ostream(basic_streambuf<CharT, Traits> *streambuf)
      : basic_ios<CharT, Traits>() {
    this->init(streambuf);
  }
  virtual ~basic_ostream();
};
class _Filebuf_base {
public:
  bool _M_open(int fd, int mode);
  bool _M_open(const char *name, int mode, long protection);
};
template <class CharT, class Traits>
class basic_filebuf : public basic_streambuf<CharT, Traits> {
public:
  basic_filebuf();
  virtual ~basic_filebuf();
  basic_filebuf *open(int fd, int mode) { return _M_base._M_open(fd, mode) ? this : 0; }
  basic_filebuf *open(const char *name, int mode, long protection = 0x80) {
    return _M_base._M_open(name, mode, protection) ? this : 0;
  }
private:
  char padding_[0x50];
  _Filebuf_base _M_base;
  char padding2_[0x5c];
};
template <class CharT>
class char_traits {};
template <class CharT, class Traits>
class basic_ifstream : public basic_istream<CharT, Traits> {
public:
  basic_ifstream(int fd, int mode)
      : basic_ios<CharT, Traits>(), basic_istream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
    if (!buf_.open(fd, mode | ios_base::in))
      this->setstate(ios_base::failbit);
  }
  basic_ifstream(const char *name, int mode)
      : basic_ios<CharT, Traits>(), basic_istream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
    if (!buf_.open(name, mode | ios_base::in))
      this->setstate(ios_base::failbit);
  }
  basic_ifstream(const char *name, int mode, long protection)
      : basic_ios<CharT, Traits>(), basic_istream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
    if (!buf_.open(name, mode | ios_base::in, protection))
      this->setstate(ios_base::failbit);
  }
private:
  basic_filebuf<CharT, Traits> buf_;
};
template <class CharT, class Traits>
class basic_ofstream : public basic_ostream<CharT, Traits> {
public:
  basic_ofstream(const char *name, int mode)
      : basic_ios<CharT, Traits>(), basic_ostream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
    if (!buf_.open(name, mode | ios_base::out))
      this->setstate(ios_base::failbit);
  }
  basic_ofstream(const char *name, int mode, long protection)
      : basic_ios<CharT, Traits>(), basic_ostream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
    if (!buf_.open(name, mode | ios_base::out, protection))
      this->setstate(ios_base::failbit);
  }
private:
  basic_filebuf<CharT, Traits> buf_;
};
template basic_ifstream<char, char_traits<char> >::basic_ifstream(int, int);
template basic_ifstream<char, char_traits<char> >::basic_ifstream(const char *, int);
template basic_ifstream<char, char_traits<char> >::basic_ifstream(const char *, int, long);
template basic_ofstream<char, char_traits<char> >::basic_ofstream(const char *, int);
template basic_ofstream<char, char_traits<char> >::basic_ofstream(const char *, int, long);
}
