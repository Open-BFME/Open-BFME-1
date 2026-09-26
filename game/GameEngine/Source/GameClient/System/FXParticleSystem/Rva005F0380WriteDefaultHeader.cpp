// ?Rva005F0380WriteDefaultHeader@FXParticleSystem@@YAXPBXPAVFile@@PAI@Z
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class File {};

namespace _STL {
template <class T> class char_traits {};
template <class T> class allocator {};
template <bool threads, int instance> class __node_alloc {
public:
	static void _M_deallocate(void *, unsigned int);
};
template <class C, class T, class A> class basic_string {
public:
	~basic_string() {
		unsigned int bytes = (unsigned int)(m_storageEnd - m_start) * sizeof(C);
		if (m_start) {
			if (bytes > 128) ::operator delete(m_start);
			else __node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}
	C *m_start; C *m_finish; C *m_storageEnd;
};
class ios_base {
protected:
	ios_base();
public:
	virtual ~ios_base();
};
template <class C, class T> class basic_streambuf {
public:
	virtual ~basic_streambuf();
};
template <class C, class T> class basic_ios : public ios_base {
public:
	basic_ios();
	virtual ~basic_ios() {}
protected:
	void init(basic_streambuf<C, T> *);
private:
	char padding_[0x50]; C fill_; basic_streambuf<C, T> *streambuf_;
	basic_ios<C, T> *tie_;
};
template <class C, class T> class basic_ostream : virtual public basic_ios<C, T> {
public:
	basic_ostream(basic_streambuf<C, T> *);
	virtual ~basic_ostream();
};
template <class C, class T> class basic_filebuf : public basic_streambuf<C, T> {
public:
	basic_filebuf(int);
	virtual ~basic_filebuf();
private:
	char padding_[0x68];
};
template <class C, class T> class basic_ofstream : public basic_ostream<C, T> {
public:
	basic_ofstream(int);
	virtual ~basic_ofstream();
private:
	basic_filebuf<C, T> buf_;
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	StreamText;
typedef _STL::basic_ofstream<char, _STL::char_traits<char> > OutputStream;

class StreamTextAccessor { public: StreamText getText(); };
class StreamWriter {
public:
	void indent(int character);
	void append(const char *text);
	void separate(int character);
};
class FileWriteShim {
public:
	virtual ~FileWriteShim();
	virtual void open();
	virtual void close();
	virtual void read();
	virtual int write(const void *buffer, int bytes);
};

struct ModuleClassEntry {
	const char *key;
	const char *name;
};
class ModuleClassView {
public:
	virtual ModuleClassEntry *getClass(void) const;
};

__forceinline void writeStreamText(File &file, const StreamText &text)
{
	reinterpret_cast<FileWriteShim *>(&file)->write(
		text.m_start, (int)(text.m_finish - text.m_start));
}

namespace FXParticleSystem {

enum ModuleCategory { MODULE_CATEGORY_DRAW = 0 };
const char *GetKey(ModuleCategory category);

void Rva005F0380WriteDefaultHeader(const void *self, File *file,
	unsigned int *flags)
{
	OutputStream stream(0x10);
	const char *name = ((ModuleClassView *)((unsigned char *)self + 4))
		->getClass()->name;
	for (unsigned int indent = *flags; indent > 0; --indent)
		reinterpret_cast<StreamWriter *>(&stream)->indent(' ');
	reinterpret_cast<StreamWriter *>(&stream)->append(
		GetKey(MODULE_CATEGORY_DRAW));
	reinterpret_cast<StreamWriter *>(&stream)->append(" = ");
	reinterpret_cast<StreamWriter *>(&stream)->append(name);
	reinterpret_cast<StreamWriter *>(&stream)->separate('\n');
	writeStreamText(*file,
		reinterpret_cast<StreamTextAccessor *>(&stream)->getText());
	*flags += 2;
}

}
