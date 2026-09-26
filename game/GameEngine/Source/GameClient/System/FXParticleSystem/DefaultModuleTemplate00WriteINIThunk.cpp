// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// DefaultModuleTemplate<1> is the default-alpha module (MSVC mangles 1 as
// @$00). Its info subobject starts at +8; each key stores distribution,
// minimum, maximum, and frame, so the values written here begin at +0x10.
class File {};

namespace _STL {
template <class T> class char_traits {};
template <class T> class allocator {};
template <bool threads, int instance> class __node_alloc {
public: static void _M_deallocate(void *, unsigned int);
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
protected: ios_base();
public: virtual ~ios_base();
};
template <class C, class T> class basic_streambuf {
public: virtual ~basic_streambuf();
};
template <class C, class T> class basic_ios : public ios_base {
public: basic_ios(); virtual ~basic_ios() {}
protected: void init(basic_streambuf<C, T> *);
private: char padding_[0x50]; C fill_; basic_streambuf<C, T> *streambuf_; basic_ios<C, T> *tie_;
};
template <class C, class T> class basic_ostream : virtual public basic_ios<C, T> {
public: basic_ostream(basic_streambuf<C, T> *); virtual ~basic_ostream() {}
};
template <class C, class T> class basic_filebuf : public basic_streambuf<C, T> {
public: basic_filebuf(int); virtual ~basic_filebuf();
private: char padding_[0x68];
};
template <class C, class T> class basic_ofstream : public basic_ostream<C, T> {
public: basic_ofstream(int); virtual ~basic_ofstream() {}
private: basic_filebuf<C, T> buf_;
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > StreamText;
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
	virtual ~FileWriteShim(); virtual void open(); virtual void close(); virtual void read();
	virtual int write(const void *buffer, int bytes);
};
__forceinline void writeStreamText(File &file, const StreamText &text)
{
	reinterpret_cast<FileWriteShim *>(&file)->write(
		text.m_start, (int)(text.m_finish - text.m_start));
}
StreamWriter *formatInteger(StreamWriter *stream, unsigned int value);
StreamWriter *formatReal(StreamWriter *stream, double value);
extern const float BfmeZeroRange;

namespace FXParticleSystem {
void writeDefaultAlphaHeader(const void *self, File *file, unsigned int *flags);
void writeINI_part2(File *file, unsigned int *flags);

struct AlphaKeyWriteView {
	float minimum;
	float maximum;
	unsigned int frame;
	unsigned int nextDistribution;
};

template <int Category> class DefaultModuleTemplate {};
template <> class DefaultModuleTemplate<1> {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
private:
	unsigned char padding_[0x0c];
	AlphaKeyWriteView alphaKeys_[8];
};

// ?writeINI@?$DefaultModuleTemplate@$00@FXParticleSystem@@UBEXAAVFile@@I@Z
void DefaultModuleTemplate<1>::writeINI(File &file, unsigned int flags) const
{
	writeDefaultAlphaHeader(this, &file, &flags);
	OutputStream stream(0x10);
	for (unsigned int keyIndex = 0; keyIndex < 8; ++keyIndex) {
		const AlphaKeyWriteView &key = alphaKeys_[keyIndex];
		if (key.minimum != BfmeZeroRange || key.maximum != BfmeZeroRange || key.frame != 0) {
			for (unsigned int indent = flags; indent > 0; --indent)
				reinterpret_cast<StreamWriter *>(&stream)->indent(' ');
			reinterpret_cast<StreamWriter *>(&stream)->append("Alpha");
			StreamWriter *writer = formatInteger(reinterpret_cast<StreamWriter *>(&stream), keyIndex + 1);
			writer->append(" = ");
			float maximum = key.maximum;
			writer = formatReal(reinterpret_cast<StreamWriter *>(&stream), key.minimum);
			writer->separate(' ');
			formatReal(writer, maximum);
			reinterpret_cast<StreamWriter *>(&stream)->separate(' ');
			unsigned int frame = key.frame;
			writer = formatInteger(reinterpret_cast<StreamWriter *>(&stream), frame);
			writer->separate('\n');
		}
	}
	writeStreamText(file, reinterpret_cast<StreamTextAccessor *>(&stream)->getText());
	writeINI_part2(&file, &flags);
}
}
