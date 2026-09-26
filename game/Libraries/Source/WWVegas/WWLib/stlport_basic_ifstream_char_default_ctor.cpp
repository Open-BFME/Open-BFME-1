// STLport 4.5 narrow basic_ifstream default constructor.
// The retail constructor uses the 0xBC virtual-base offset and the 0xB4
// basic_filebuf size represented by this minimal ABI layout.

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
class basic_ifstream : public basic_istream<CharT, Traits> {
public:
  basic_ifstream()
      : basic_ios<CharT, Traits>(), basic_istream<CharT, Traits>(0), buf_() {
    this->init(&buf_);
  }

private:
  basic_filebuf<CharT, Traits> buf_;
};

template class basic_ifstream<char, char_traits<char> >;

}
