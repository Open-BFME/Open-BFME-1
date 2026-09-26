// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

namespace _STL
{
template <class T> class char_traits
{
};

template <class T> class allocator
{
};

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *, unsigned int);
};

template <class CharT, class Traits, class Allocator>
class basic_string
{
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
				__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}

	CharT *m_start;
	CharT *m_finish;
	CharT *m_storageEnd;
};

class ios_base
{
protected:
	ios_base();

public:
	virtual ~ios_base();
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	virtual ~basic_streambuf();
};

template <class CharT, class Traits>
class basic_ios : public ios_base
{
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
class basic_ostream : virtual public basic_ios<CharT, Traits>
{
public:
	basic_ostream(basic_streambuf<CharT, Traits> *streambuf);
	virtual ~basic_ostream();
};

template <class CharT, class Traits>
class basic_filebuf : public basic_streambuf<CharT, Traits>
{
public:
	basic_filebuf(int mode);
	virtual ~basic_filebuf();

private:
	char padding_[0x68];
};

template <class CharT, class Traits>
class basic_ofstream : public basic_ostream<CharT, Traits>
{
public:
	basic_ofstream(int mode);
	virtual ~basic_ofstream();

private:
	basic_filebuf<CharT, Traits> buf_;
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	StreamText;
typedef _STL::basic_ofstream<char, _STL::char_traits<char> > OutputStream;

class Rva005CB9F0StreamText
{
public:
	StreamText getText();
};

class StreamWriter
{
public:
	void indent(int character);
	void append(const char *text);
	void separate(int character);
};

class File
{
};

class FileWriteShim
{
public:
	virtual ~FileWriteShim();
	virtual void open();
	virtual void close();
	virtual void read();
	virtual int write(const void *buffer, int bytes);
};

struct ModuleClassEntry
{
	const char *key;
	const char *name;
};

class ModuleClassView
{
public:
	virtual ModuleClassEntry *getClass(void) const;
};

extern const char g_u4Separator[];

namespace FXParticleSystem
{
enum ModuleCategory
{
	MODULE_CATEGORY_WIND = 7
};

const char *GetKey(ModuleCategory category);
}

__forceinline void writeStreamText(File &file, const StreamText &text)
{
	reinterpret_cast<FileWriteShim *>(&file)->write(
		text.m_start, (int)(text.m_finish - text.m_start));
}

// The retail body writes the common header for category 7 wind modules.
void Rva005FF160WriteWindHeader(const void *self, File *file,
	unsigned int *flags)
{
	OutputStream stream(0x10);
	const char *name = ((ModuleClassView *)((unsigned char *)self + 4))
		->getClass()->name;
	for (unsigned int indent = *flags; indent > 0; --indent)
		reinterpret_cast<StreamWriter *>(&stream)->indent(' ');
	reinterpret_cast<StreamWriter *>(&stream)->append(
		FXParticleSystem::GetKey(FXParticleSystem::MODULE_CATEGORY_WIND));
	reinterpret_cast<StreamWriter *>(&stream)->append(g_u4Separator);
	reinterpret_cast<StreamWriter *>(&stream)->append(name);
	reinterpret_cast<StreamWriter *>(&stream)->separate('\n');
	writeStreamText(*file,
		reinterpret_cast<Rva005CB9F0StreamText *>(&stream)->getText());
	*flags += 2;
}
