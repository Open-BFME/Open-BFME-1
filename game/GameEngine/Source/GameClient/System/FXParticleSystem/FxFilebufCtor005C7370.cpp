// cl: /DNDEBUG /MD /EHsc
// STLport 4.5 narrow basic_filebuf(int) constructor used by the FX particle
// system's basic_ofstream(int) constructor at 0x005CC3F0.  The stream buffer
// keeps its get and put areas inline, then stores the open mode and file name.

namespace _STL {

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class locale {
public:
  locale();
};

template <class CharT>
class char_traits {};

template <class CharT>
class allocator {};

template <class CharT, class Traits, class Allocator>
class basic_string {
public:
  basic_string();
};

template <class CharT, class Traits>
class basic_streambuf {
  struct FileArea {
    CharT *m_ptr;
    int m_count;
    CharT *m_base;
    char m_padding[0x14];
  };

public:
  basic_streambuf()
      : m_get(&m_get_area), m_put(&m_put_area), m_locale() {
    m_state = 0;
    _ReadWriteBarrier();
    FileArea *get = m_get;
    get->m_base = 0;
    get->m_ptr = 0;
    get->m_count = 0;
    FileArea *put = m_put;
    put->m_base = 0;
    put->m_ptr = 0;
    put->m_count = 0;
  }
  virtual ~basic_streambuf();

private:
  FileArea *m_get;
  FileArea *m_put;
  FileArea m_get_area;
  FileArea m_put_area;
  locale m_locale;
  volatile int m_state;
};

template <class CharT, class Traits>
class basic_filebuf : public basic_streambuf<CharT, Traits> {
public:
  basic_filebuf(int mode);
  virtual ~basic_filebuf();

private:
  int m_mode;
  basic_string<CharT, Traits, allocator<CharT> > m_name;
};

template <class CharT, class Traits>
basic_filebuf<CharT, Traits>::basic_filebuf(int mode)
    : basic_streambuf<CharT, Traits>(), m_mode(mode), m_name() {}

template basic_filebuf<char, char_traits<char> >::basic_filebuf(int);

}
