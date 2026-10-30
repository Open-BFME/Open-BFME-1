// ?Rva006077C0ParseSoundState@@YAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// INI field callback at retail 0x006077C0, reached only through ILT 0x0001D55C
// from the "SoundState" FieldParse entry at VA 0x01115860. It parses one
// 0x1F0-byte sound-state element (a model-condition BitFlags at +0, then the
// voice fields at +0x28 and the table below) and appends it to the vector at
// instance+8. The element's constructor, BitFlags parser, copy constructor and
// destructor are the address-named bodies behind the ILTs called here; their
// placeholder spellings disagree on the element type, so the calls go to the
// ILT thunks' own names.
#include <new>
#include <vector>

class INI;
class AsciiString;
struct FieldParse;

class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		m_count = 0;
		for (int i = 0; i < 16; ++i)
		{
			m_offsets[i] = 0;
			m_fields[i] = 0;
		}
	}

	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *m_fields[16];
	unsigned int m_offsets[16];
	unsigned int m_count;
};

class INI
{
public:
	void initFromINIMulti(void *, const MultiIniFieldParse &);
};

extern const FieldParse *getVoiceFieldParse();
extern const FieldParse g_01115814[3];

extern void j_00043504();
extern void j_00033433();
extern void j_00010aaa();

// ??1Gen000075EF@@QAE@XZ is the element destructor's ILT pin.
class Gen000075EF
{
public:
	Gen000075EF()
	{
		typedef void (Gen000075EF::*Fn)();
		union { void (*fn)(); Fn call; } u = { j_00043504 };
		(this->*u.call)();
	}
	~Gen000075EF();

	void parseFlags(INI *ini)
	{
		typedef void (Gen000075EF::*Fn)(INI *, AsciiString *);
		union { void (*fn)(); Fn call; } u = { j_00033433 };
		(this->*u.call)(ini, 0);
	}

private:
	char m_body[0x1F0];
};

struct Rva00607770Element
{
	Rva00607770Element(const Rva00607770Element &other)
	{
		typedef void (Rva00607770Element::*Fn)(const Rva00607770Element &);
		union { void (*fn)(); Fn call; } u = { j_00010aaa };
		(this->*u.call)(other);
	}

	char m_body[0x1F0];
};

namespace _STL
{
	template <> class vector<Rva00607770Element, allocator<Rva00607770Element> >;
}

typedef _STL::vector<Rva00607770Element, _STL::allocator<Rva00607770Element> > Rva006077C0SoundStates;

static void pushSoundState(Rva006077C0SoundStates *, const Rva00607770Element &);

namespace _STL
{
	template <> class vector<Rva00607770Element, allocator<Rva00607770Element> >
	{
		friend void ::pushSoundState(Rva006077C0SoundStates *, const Rva00607770Element &);

	protected:
		void _M_insert_overflow(Rva00607770Element *, const Rva00607770Element &,
			const __false_type &, unsigned int, bool);

	private:
		Rva00607770Element *_M_start;
		Rva00607770Element *_M_finish;
		Rva00607770Element *_M_end_of_storage;
	};
}

// STLport vector::push_back, inlined.
static __forceinline void pushSoundState(Rva006077C0SoundStates *v, const Rva00607770Element &x)
{
	if (v->_M_finish != v->_M_end_of_storage)
	{
		Rva00607770Element *p = v->_M_finish;
		new (p) Rva00607770Element(x);
		++v->_M_finish;
	}
	else
	{
		_STL::__false_type tag;
		v->_M_insert_overflow(v->_M_finish, x, tag, 1, true);
	}
}

void Rva006077C0ParseSoundState(INI *ini, void *instance, void *, const void *)
{
	if (instance == 0)
		return;

	Gen000075EF state;
	state.parseFlags(ini);

	MultiIniFieldParse fields;
	fields.add(g_01115814);
	fields.add(getVoiceFieldParse(), 0x28);
	ini->initFromINIMulti(&state, fields);

	Rva006077C0SoundStates *states = reinterpret_cast<Rva006077C0SoundStates *>(
		static_cast<char *>(instance) + 8);
	pushSoundState(states, reinterpret_cast<const Rva00607770Element &>(state));
}

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

extern "C" void __identifier("?parsePerUnitSounds@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?u4IniFlag00606890@@YAXPAVINI@@PAX1PBX@Z")(INI *, void *, void *, const void *);

extern "C" const FieldParse __identifier("?g_01115814@@3QBUFieldParse@@B")[3] =
{
	{ "UnitSpecificSounds", __identifier("?parsePerUnitSounds@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z"), 0, 0x1dc },
	{ "VoicePriority", __identifier("?u4IniFlag00606890@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1e8 },
	{ 0, 0, 0, 0 }
};
