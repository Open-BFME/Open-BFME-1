// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

namespace _STL {

template <class T> class char_traits {};
template <class T> class allocator {};
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

template <class CharT, class Traits, class Allocator>
class basic_string {
public:
    ~basic_string()
    {
        unsigned int bytes =
            (unsigned int)(m_storageEnd - m_start) * sizeof(CharT);
        if (m_start)
        {
            if (bytes > 128)
                ::operator delete(m_start);
            else
                _STL::nodePoolDeallocate(m_start, bytes);
        }
    }

    CharT *m_start;
    CharT *m_finish;
    CharT *m_storageEnd;
};

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
    basic_ios();
    virtual ~basic_ios() {}

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
    basic_ostream(basic_streambuf<CharT, Traits> *streambuf);
    virtual ~basic_ostream();
};

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
    basic_ostringstream(int);
    virtual ~basic_ostringstream();

private:
    basic_stringbuf<CharT, Traits, Alloc> buf_;
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>,
    _STL::allocator<char> > StreamText;
typedef _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > OutputStream;

class File {};

class StreamTextAccessor {
public:
    StreamText getText();
};

class StreamWriter {
public:
    void indent(int character);
    void append(const char *text);
};

class FileWriteShim {
public:
    virtual ~FileWriteShim();
    virtual void open();
    virtual void close();
    virtual void read();
    virtual int write(const void *buffer, int size);
};

__forceinline void writeStreamText(File &file, const StreamText &text)
{
    reinterpret_cast<FileWriteShim *>(&file)->write(
        text.m_start, (int)(text.m_finish - text.m_start));
}

// ?Rva005EE1D0Finish@@YAXPAVFile@@PAI@Z
void Rva005EE1D0Finish(File *file, unsigned int *indent)
{
    *indent -= 2;
    OutputStream stream(0x10);

    for (unsigned int i = *indent; i > 0; --i)
        reinterpret_cast<StreamWriter *>(&stream)->indent(0x20);

    reinterpret_cast<StreamWriter *>(&stream)->append("End\n");
    writeStreamText(*file,
        reinterpret_cast<StreamTextAccessor *>(&stream)->getText());
}
