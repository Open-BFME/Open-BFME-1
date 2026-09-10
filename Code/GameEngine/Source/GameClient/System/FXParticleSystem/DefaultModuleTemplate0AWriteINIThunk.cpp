// ?writeINI@?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UBEXAAVFile@@I@Z
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// DefaultModuleTemplate<0> is the default-color module (MSVC mangles zero as
// @$0A@). Its layout follows ParticleSystemTemplate's eight RGB color keys
// and its random ColorScale value. The matched constructor at 0x005DD4C0
// installs vtable VA 0x011108F8; slot +0x0c routes through ILT 0x000355D5
// to this body. The final ret 8 at 0x005F07CF gives the full 674-byte boundary.
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
// The retail calls at 0x005F0562 and 0x005F060F enter these existing ILT
// thunks. Their concrete callees are not named; retain the address-backed
// aliases rather than assigning an unproven helper identity.
extern void j_0003ddfc();
extern void j_00047401();
__forceinline void writeStreamText(File &file, const StreamText &text)
{
	reinterpret_cast<FileWriteShim *>(&file)->write(
		text.m_start, (int)(text.m_finish - text.m_start));
}
StreamWriter *formatInteger(StreamWriter *stream, unsigned int value);
StreamWriter *formatReal(StreamWriter *stream, double value);
extern const float BfmeZeroRange;

namespace FXParticleSystem {
void writeINI_part2(File *file, unsigned int *flags);

struct ColorKeyWriteView {
	float red;
	float green;
	float blue;
	unsigned int frame;
};

struct RandomVariableWriteView {
	float getMinimumValue() const { return minimum; }
	float getMaximumValue() const { return maximum; }
	unsigned int distribution;
	float minimum;
	float maximum;
};

template <int Category> class DefaultModuleTemplate {};
template <> class DefaultModuleTemplate<0> {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
private:
	unsigned char padding_[0x08];
	ColorKeyWriteView colorKeys_[8];
	RandomVariableWriteView colorScale_;
};

// ?writeINI@?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UBEXAAVFile@@I@Z
void DefaultModuleTemplate<0>::writeINI(File &file, unsigned int flags) const
{
	typedef void (__cdecl *UnknownBaseWriter)(const void *self, File *file, unsigned int *flags);
	reinterpret_cast<UnknownBaseWriter>(j_0003ddfc)(this, &file, &flags);
	OutputStream stream(0x10);
	ColorKeyWriteView *key = (ColorKeyWriteView *)colorKeys_;
	for (unsigned int keyIndex = 0; keyIndex < 8; ++keyIndex, ++key) {
		if (key->red != BfmeZeroRange || key->green != BfmeZeroRange ||
			key->blue != BfmeZeroRange || key->frame != 0) {
			for (unsigned int indent = flags; indent > 0; --indent)
				reinterpret_cast<StreamWriter *>(&stream)->indent(' ');
			reinterpret_cast<StreamWriter *>(&stream)->append("Color");
			StreamWriter *writer = formatInteger(
				reinterpret_cast<StreamWriter *>(&stream), keyIndex + 1);
			writer->append(" = ");
			typedef StreamWriter *(__cdecl *UnknownColorWriter)(StreamWriter *, const float *);
			writer = reinterpret_cast<UnknownColorWriter>(j_00047401)(
				reinterpret_cast<StreamWriter *>(&stream), &key->red);
			writer->separate(' ');
			unsigned int frame = key->frame;
			writer = formatInteger(writer, frame);
			writer->separate('\n');
		}
	}
	RandomVariableWriteView *scale = (RandomVariableWriteView *)
		((unsigned char *)this + 0x8c);
	if (scale->getMinimumValue() != BfmeZeroRange ||
		scale->getMaximumValue() != BfmeZeroRange) {
		for (unsigned int indent = flags; indent > 0; --indent)
			reinterpret_cast<StreamWriter *>(&stream)->indent(' ');
		reinterpret_cast<StreamWriter *>(&stream)->append("ColorScale = ");
		StreamWriter *writer = reinterpret_cast<StreamWriter *>(&stream);
		float maximum = scale->getMaximumValue();
		writer = formatReal(writer, scale->getMinimumValue());
		writer->separate(' ');
		formatReal(writer, maximum);
		reinterpret_cast<StreamWriter *>(&stream)->separate('\n');
	}
	writeStreamText(file, reinterpret_cast<StreamTextAccessor *>(&stream)->getText());
	writeINI_part2(&file, &flags);
}
}
