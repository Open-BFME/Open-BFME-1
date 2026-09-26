// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class File {};
class INI {};

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

namespace FXParticleSystem {

struct RandomVariableWriteView {
	unsigned int distribution;
	float minimum;
	float maximum;
};

void writeDefaultPhysicsHeader(const void *self, File *file, unsigned int *flags);
void writePhysicsScalar(INI *stream, void *flags, const void *name, const float *value);
void writePhysicsPair(void *stream, void *flags, const void *name, RandomVariableWriteView *value);
void writePhysicsVector(INI *stream, void *flags, const void *name, const float *value);
void writeINI_part2(File *file, unsigned int *flags);

template <int Category> class DefaultModuleTemplate {};
template <> class DefaultModuleTemplate<3> {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
private:
	unsigned char padding_[0x08];
	float driftVelocity_[3];
	float gravity_;
	RandomVariableWriteView velocityDamping_;
};

// ?writeINI@?$DefaultModuleTemplate@$02@FXParticleSystem@@UBEXAAVFile@@I@Z
void DefaultModuleTemplate<3>::writeINI(File &file, unsigned int flags) const
{
	writeDefaultPhysicsHeader(this, &file, &flags);
	OutputStream stream(0x10);

	if (gravity_ != BfmeZeroRange)
		writePhysicsScalar((INI *)&stream, (void *)flags, (const void *)0x0107b92c, &gravity_);

	RandomVariableWriteView *damping =
		(RandomVariableWriteView *)((unsigned char *)this + 0x1c);
	if (damping->minimum != BfmeZeroRange || damping->maximum != BfmeZeroRange)
		writePhysicsPair((void *)&stream, (void *)flags, (const void *)0x0111459c,
			damping);

	float *drift = (float *)((unsigned char *)this + 0x0c);
	if (drift[0] != BfmeZeroRange || drift[1] != BfmeZeroRange ||
		drift[2] != BfmeZeroRange)
		writePhysicsVector((INI *)&stream, (void *)flags, (const void *)0x0111458c,
			drift);

	writeStreamText(file, reinterpret_cast<StreamTextAccessor *>(&stream)->getText());
	writeINI_part2(&file, &flags);
}
}
