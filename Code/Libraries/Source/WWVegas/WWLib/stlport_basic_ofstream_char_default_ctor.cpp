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
  basic_filebuf();
  virtual ~basic_filebuf();

private:
  char padding_[0xb0];
};

template <class CharT>
class char_traits {};

template <class CharT, class Traits>
class basic_ofstream : public basic_ostream<CharT, Traits> {
public:
  basic_ofstream()
      : basic_ios<CharT, Traits>(), basic_ostream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
  }

private:
  basic_filebuf<CharT, Traits> buf_;
};

template class basic_ofstream<char, char_traits<char> >;

}
