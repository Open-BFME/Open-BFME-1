// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class File {};

namespace _STL {
template <class T> class char_traits {};
template <class T> class allocator {};
template <bool threads, int instance> class __node_alloc { public: static void _M_deallocate(void *, unsigned int); };
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
class ios_base { protected: ios_base(); public: virtual ~ios_base(); };
template <class C, class T> class basic_streambuf { public: virtual ~basic_streambuf(); };
template <class C, class T> class basic_ios : public ios_base {
public: basic_ios(); virtual ~basic_ios() {}
protected: void init(basic_streambuf<C, T> *);
private: char padding_[0x50]; C fill_; basic_streambuf<C, T> *streambuf_; basic_ios<C, T> *tie_;
};
template <class C, class T> class basic_ostream : virtual public basic_ios<C, T> {
public: basic_ostream(basic_streambuf<C, T> *); virtual ~basic_ostream();
};
template <class C, class T> class basic_filebuf : public basic_streambuf<C, T> {
public: basic_filebuf(int); virtual ~basic_filebuf();
private: char padding_[0x68];
};
template <class C, class T> class basic_ofstream : public basic_ostream<C, T> {
public: basic_ofstream(int); virtual ~basic_ofstream();
private: basic_filebuf<C, T> buf_;
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > StreamText;
typedef _STL::basic_ofstream<char, _STL::char_traits<char> > OutputStream;
class StreamTextAccessor { public: StreamText getText(); };
class FileWriteShim {
public:
	virtual ~FileWriteShim(); virtual void open(); virtual void close(); virtual void read();
	virtual int write(const void *buffer, int bytes);
};
__forceinline void writeStreamText(File &file, const StreamText &text)
{
	reinterpret_cast<FileWriteShim *>(&file)->write(text.m_start, (int)(text.m_finish - text.m_start));
}

extern const float BfmeZeroRange;

class U1Pair { public: unsigned char padding[4]; float minimum; float maximum; };
void b_005fff00();
void b_005ee1d0();
void u1Do_005C9030(void *stream, void *flags, void *name, U1Pair *value);
void u1Call_005C7110(void *stream, void *flags, void *name, void **value);

namespace FXParticleSystem {

template <int Category> class DefaultModuleTemplate {};
template <> class DefaultModuleTemplate<2> { public: virtual void writeINI(File &file, unsigned int flags) const; };

// ?writeINI@?$DefaultModuleTemplate@$01@FXParticleSystem@@UBEXAAVFile@@I@Z
void DefaultModuleTemplate<2>::writeINI(File &file, unsigned int flags) const
{
	typedef void (__cdecl *BaseWriteFunction)(const void *, File *, unsigned int *);
	typedef void (__cdecl *FinishWriteFunction)(File *, unsigned int *);
	reinterpret_cast<BaseWriteFunction>(::b_005fff00)(this, &file, &flags);
	OutputStream stream(0x10);

	U1Pair *value0 = (U1Pair *)((unsigned char *)this + 0x0c);
	if (value0->minimum != BfmeZeroRange || value0->maximum != BfmeZeroRange)
		u1Do_005C9030(&stream, (void *)flags, (void *)0x0111494c, value0);
	U1Pair *value1 = (U1Pair *)((unsigned char *)this + 0x18);
	if (value1->minimum != BfmeZeroRange || value1->maximum != BfmeZeroRange)
		u1Do_005C9030(&stream, (void *)flags, (void *)0x01114938, value1);
	U1Pair *value2 = (U1Pair *)((unsigned char *)this + 0x24);
	if (value2->minimum != BfmeZeroRange || value2->maximum != BfmeZeroRange)
		u1Do_005C9030(&stream, (void *)flags, (void *)0x01114930, value2);
	U1Pair *value3 = (U1Pair *)((unsigned char *)this + 0x30);
	if (value3->minimum != BfmeZeroRange || value3->maximum != BfmeZeroRange)
		u1Do_005C9030(&stream, (void *)flags, (void *)0x01114920, value3);
	U1Pair *value4 = (U1Pair *)((unsigned char *)this + 0x3c);
	if (value4->minimum != BfmeZeroRange || value4->maximum != BfmeZeroRange)
		u1Do_005C9030(&stream, (void *)flags, (void *)0x0111490c, value4);

	unsigned int value5 = *(const unsigned int *)((const unsigned char *)this + 0x48);
	if (value5 != 1)
		u1Call_005C7110(&stream, (void *)flags, (void *)0x01114900,
			(void **)(0x01110258 + value5 * 4));

	writeStreamText(file, reinterpret_cast<StreamTextAccessor *>(&stream)->getText());
	reinterpret_cast<FinishWriteFunction>(::b_005ee1d0)(&file, &flags);
}
}
