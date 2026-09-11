// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

namespace _STL {

template <class T> class char_traits {};
template <class T> class allocator {};
template <bool threads, int instance>
class __node_alloc {
public:
    static void _M_deallocate(void *, unsigned int);
};

template <class CharT, class Traits, class Allocator>
class basic_string {
public:
    ~basic_string() {
        unsigned int bytes =
            (unsigned int)(m_storageEnd - m_start) * sizeof(CharT);
        if (m_start) {
            if (bytes > 128)
                ::operator delete(m_start);
            else
                __node_alloc<true, 0>::_M_deallocate(m_start, bytes);
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

template <class CharT, class Traits>
class basic_filebuf : public basic_streambuf<CharT, Traits> {
public:
    basic_filebuf(int mode);
    virtual ~basic_filebuf();

private:
    char padding_[0x68];
};

template <class CharT, class Traits>
class basic_ofstream : public basic_ostream<CharT, Traits> {
public:
    basic_ofstream(int);
    virtual ~basic_ofstream();

private:
    basic_filebuf<CharT, Traits> buf_;
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>,
    _STL::allocator<char> > Rva005EE070StreamText;

class Rva005CB9F0StreamText {
public:
    Rva005EE070StreamText getText();
};

class StreamWriter {
public:
    void indent(int character);
    void append(const char *text);
    void separate(int character);
};

class File {};

class FileWriteShim {
public:
    virtual ~FileWriteShim();
    virtual void open();
    virtual void close();
    virtual void read();
    virtual int write(const void *buffer, int size);
};

__forceinline void writeStreamText(File &file,
    const Rva005EE070StreamText &text) {
    reinterpret_cast<FileWriteShim *>(&file)->write(
        text.m_start, (int)(text.m_finish - text.m_start));
}

// ?Rva005EE070WriteIndentedLine@@YAXPBDPAVFile@@PAI@Z
void Rva005EE070WriteIndentedLine(const char *text, File *file, unsigned int *indent) {
    _STL::basic_ofstream<char, _STL::char_traits<char> > stream(0x10);

    for (unsigned int i = *indent; i > 0; --i)
        reinterpret_cast<StreamWriter *>(&stream)->indent(0x20);

    reinterpret_cast<StreamWriter *>(&stream)->append(text);
    reinterpret_cast<StreamWriter *>(&stream)->separate(0x0a);

    writeStreamText(*file,
        reinterpret_cast<Rva005CB9F0StreamText *>(&stream)->getText());
    *indent += 2;
}
