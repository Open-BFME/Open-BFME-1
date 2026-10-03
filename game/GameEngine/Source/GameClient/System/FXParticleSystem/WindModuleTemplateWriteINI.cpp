// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport

// Category-7 (wind) module template INI writer.  The primary table
// 0x0111101C is installed by the matched constructor
// ??0?$DefaultModuleTemplate@$06@FXParticleSystem@@QAE@XZ and its slot 3
// reaches this body through ILT 0x0003462B; the same slot of the concrete
// table 0x01111048 (ConcreteModuleTemplate<DefaultModuleTag<7>>) points here
// too.  Slot 3 is writeINI(File &, unsigned int) const in this family:
// 0x01110C50 -> 0x006000B0, 0x011108B8 -> 0x005EEF50 and 0x01110938 ->
// 0x005F3870, all matched rows.  Every key below is the literal retail
// pushes next to the field it guards, so the field names are read off the
// body itself.

namespace _STL
{
template <class T> class char_traits
{
};

template <class T> class allocator
{
};

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
class basic_string
{
public:
	~basic_string()
	{
		unsigned int bytes =
			(unsigned int)(m_storageEnd - m_start) * sizeof(CharT);
		if (m_start) {
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

template <class CharT, class Traits, class Alloc>
class basic_stringbuf : public basic_streambuf<CharT, Traits>
{
public:
	basic_stringbuf(int mode);
	virtual ~basic_stringbuf();

private:
	char padding_[0x68];
};

template <class CharT, class Traits, class Alloc>
class basic_ostringstream : public basic_ostream<CharT, Traits>
{
public:
	basic_ostringstream(int mode);
	virtual ~basic_ostringstream();

private:
	basic_stringbuf<CharT, Traits, Alloc> buf_;
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>,
	_STL::allocator<char> > StreamText;
typedef _STL::basic_ostringstream<char, _STL::char_traits<char>,
	_STL::allocator<char> > OutputStream;

class StreamTextAccessor
{
public:
	StreamText getText();
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

class File
{
};

class INI
{
};

__forceinline void writeStreamText(File &file, const StreamText &text)
{
	reinterpret_cast<FileWriteShim *>(&file)->write(
		text.m_start, (int)(text.m_finish - text.m_start));
}

// Retail's shared single-line key writer; it indents by `flags` spaces, then
// writes the key, the " = " separator and the value string.
void u1Call_005C7110(void *stream, void *flags, void *name, void **value);

// The category-7 header writer at 0x005FF160 and the shared INI tail at
// 0x005EE1D0; both are reached through their retail addresses and called cdecl.
void b_005ff160();
void Rva005EE1D0Finish(File *file, unsigned int *indent);

extern const float g_rva01075350;

namespace FXParticleSystem
{
// Exported retail table of wind-motion keywords, indexed by m_windMotion.
extern const char *const WindMotionNames[];

// The generic float writer, reached through ILT 0x0001FC8A.
void writePhysicsScalar(INI *stream, void *flags, const void *name,
	const float *value);

template <int Category> class DefaultModuleTemplate
{
};

template <> class DefaultModuleTemplate<7> {
public:
	virtual void writeINI(File &file, unsigned int flags) const;

private:
	// Three vptrs: this one, the module-class view the shared header writer
	// calls through (+4) and the module-info table (+8).  Offsets follow the
	// matched constructor, which stores its three tables at +0/+4/+8.
	void *m_moduleClassView;
	void *m_moduleInfoView;
	unsigned int m_windMotion;					// 0x0C, "WindMotion"
	float m_windStrength;						// 0x10
	float m_windFullStrengthDist;				// 0x14
	float m_windZeroStrengthDist;				// 0x18
	float m_pad1c[2];
	float m_windAngleChangeMin;					// 0x24
	float m_windAngleChangeMax;					// 0x28
	float m_pad2c;
	float m_windMotionStartAngleMin;			// 0x30
	float m_windMotionStartAngleMax;			// 0x34
	float m_pad38;
	float m_windMotionEndAngleMin;				// 0x3C
	float m_windMotionEndAngleMax;				// 0x40
	float m_pad44;
	float m_turbulenceAmplitude;				// 0x48
	float m_turbulenceFrequency;				// 0x4C
};

// ?writeINI@?$DefaultModuleTemplate@$06@FXParticleSystem@@UBEXAAVFile@@I@Z
void DefaultModuleTemplate<7>::writeINI(File &file, unsigned int flags) const
{
	typedef void (__cdecl *BaseWriteFunction)(const void *, File *,
		unsigned int *);
	typedef void (__cdecl *FinishWriteFunction)(File *, unsigned int *);
	// The category-7 header ("Wind" + the module class name) goes straight to
	// the file before the parameter block is buffered.
	reinterpret_cast<BaseWriteFunction>(::b_005ff160)(this, &file, &flags);
	OutputStream stream(0x10);

	// "WindMotion" = the WindMotionNames entry; nothing is written for the
	// not-used default.
	if (m_windMotion != 1)
		u1Call_005C7110(&stream, (void *)flags, (void *)"WindMotion",
			(void **)(WindMotionNames + m_windMotion));

	if (m_windStrength != 2.0f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindStrength", &m_windStrength);
	if (m_windFullStrengthDist != 75.0f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindFullStrengthDist", &m_windFullStrengthDist);
	if (m_windZeroStrengthDist != 200.0f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindZeroStrengthDist", &m_windZeroStrengthDist);
	if (m_windAngleChangeMin != 0.15f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindAngleChangeMin", &m_windAngleChangeMin);
	if (m_windAngleChangeMax != 0.45f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindAngleChangeMax", &m_windAngleChangeMax);
	if (m_windMotionStartAngleMin != g_rva01075350)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindPingPongStartAngleMin", &m_windMotionStartAngleMin);
	if (m_windMotionStartAngleMax != 0.7853982f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindPingPongStartAngleMax", &m_windMotionStartAngleMax);
	if (m_windMotionEndAngleMin != 5.4977875f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindPingPongEndAngleMin", &m_windMotionEndAngleMin);
	if (m_windMotionEndAngleMax != 6.2831855f)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"WindPingPongEndAngleMax", &m_windMotionEndAngleMax);
	if (m_turbulenceAmplitude != g_rva01075350)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"TurbulenceAmplitude", &m_turbulenceAmplitude);
	if (m_turbulenceFrequency != g_rva01075350)
		writePhysicsScalar((INI *)&stream, (void *)flags,
			"TurbulenceFrequency", &m_turbulenceFrequency);

	writeStreamText(file,
		reinterpret_cast<StreamTextAccessor *>(&stream)->getText());
	reinterpret_cast<FinishWriteFunction>(::Rva005EE1D0Finish)(&file, &flags);
}
}
