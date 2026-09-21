// cl: /DNDEBUG /MD /EHsc
// Open-BFME: STLport 4.5 narrow output file-stream constructor taking an
// already-open file descriptor: basic_ofstream<char>(int fd, int mode),
// retail 0x0084BA90. Same shell as the name-taking ofstream constructors
// landed in stlport_file_stream_name_ctors.cpp (0x0084B980 / 0x0084BB90,
// immediate neighbours of this body) and the fd-taking ifstream constructor
// instantiated there (basic_ifstream(int, int)); this is the missing
// ofstream counterpart of that same fd overload, opened through
// _Filebuf_base::_M_open(int, int) (retail pin ?_M_open@_Filebuf_base@_STL@@QAE_NHH@Z).
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
private:
  char padding_[0x50];
  _Filebuf_base _M_base;
  char padding2_[0x5c];
};
template <class CharT>
class char_traits {};
template <class CharT, class Traits>
class basic_ofstream : public basic_ostream<CharT, Traits> {
public:
  basic_ofstream(int fd, int mode)
      : basic_ios<CharT, Traits>(), basic_ostream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
    if (!buf_.open(fd, mode | ios_base::out))
      this->setstate(ios_base::failbit);
  }
private:
  basic_filebuf<CharT, Traits> buf_;
};
template basic_ofstream<char, char_traits<char> >::basic_ofstream(int, int);
}
