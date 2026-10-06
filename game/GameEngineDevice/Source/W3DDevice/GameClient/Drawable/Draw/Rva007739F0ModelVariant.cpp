// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

void __cdecl operator delete(void *) throw();
#include <set>
#include <bitset>

// TU-local wide model of BFME's reference-counted narrow string: the copy
// constructor (0x00887B60), set (0x00887C90), concat (0x00887D60) and the
// private releaseBuffer (0x00887940) stay out of line; the destructor, str()
// and the one-character concat inline, as every retail call site shows.
template <typename T> struct Rva007739F0StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &src);
	void concat(const T *str, int len);

private:
	StringBase(const StringBase<T> &src);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	Rva007739F0StringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &that)
	{
		StringBase<char>::set(that);
		return *this;
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	void concat(char c) { StringBase<char>::concat(&c, 1); }
	void concat(const char *s, int len) { StringBase<char>::concat(s, len); }

	friend bool operator<(const AsciiString &left, const AsciiString &right);
};

class Debug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &operator<<(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
};

Debug &operator<<(Debug &debug, const StringBase<char> &text);

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug *slot6C(int first, int second);
};

extern void *g_Rva00F36E5C; // VA 01336E5C debug manager cell (data_rows.csv owner)
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))
extern void _bfme_debugRecordCallsite(int kind);
extern bool _bfme_debugReportingEnabled(void);

Bool Render_Obj_Exists(const char *name);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
};

// The template view this body reads: an AsciiString at +0x20 (unwitnessed).
struct Rva007739F0TemplateView
{
	unsigned char m_unmodelled00[0x20];
	AsciiString m_name20;
};

// Drawable: template at +0x04, status word at +0x110 (witnessed m_status).
class Drawable
{
public:
	const Rva007739F0TemplateView *getTemplate() const
	{
		if (!m_template)
			return 0;
		return (const Rva007739F0TemplateView *)m_template->getFinalOverride();
	}

	UnsignedInt getStatusBits() const { return m_status; }

private:
	void *m_vtable;
	const Overridable *m_template;
	unsigned char m_unmodelled008[0x108];
	UnsignedInt m_status;
};

class GameLODManager
{
public:
	Int getValue16C4() const { return m_value16C4; }

private:
	unsigned char m_unmodelled0000[0x16c4];
	Int m_value16C4;
};

extern GameLODManager *TheGameLODManager;

// 0x0075B4A0: the level-of-detail suffix kind for a drawable (2, 1 or 0);
// status bit 0x20 forces the low kind and reports it through forcedLow.
// Defined here, out of line, as in retail: the caller below keeps the
// drawable pointer in EDX across the call because this body leaves EDX alone.
// ?rva0075B4A0@@YAHPBVDrawable@@PA_N@Z
Int rva0075B4A0(const Drawable *drawable, Bool *forcedLow)
{
	Int level = TheGameLODManager->getValue16C4();
	if (level != 4 && drawable && (drawable->getStatusBits() & 0x20))
	{
		if (forcedLow)
			*forcedLow = true;
		level = 1;
	}

	switch (level)
	{
	case 0:
	case 1:
		return 2;
	case 2:
		return 1;
	case 3:
	case 4:
		return 0;
	}
	return 0;
}

// 0x00761D20: the model name with its level-of-detail suffix ("M" for kind
// 1, "L" for kind 2); a negative kind returns the name unchanged.
// ?rva00761D20@@YA?AVAsciiString@@ABV1@H@Z
AsciiString rva00761D20(const AsciiString &name, Int kind)
{
	if (kind < 0)
		return name;

	AsciiString result = name;
	switch (kind)
	{
	case 1:
		result.concat("M", 1);
		break;
	case 2:
		result.concat("L", 1);
		break;
	}
	return result;
}

// The module data flags this body reads (unwitnessed offsets).
struct Rva007739F0Data
{
	unsigned char m_unmodelled000[0x108];
	Bool m_flag108;
	Bool m_flag109;
	Bool m_flag10A;
	Bool m_flag10B;
};

// ZH ModelState.h ModelConditionFlagType, the bits this body tests.
enum
{
	MODELCONDITION_DAMAGED = 3,
	MODELCONDITION_REALLY_DAMAGED = 4,
	MODELCONDITION_RUBBLE = 5,
	MODELCONDITION_NIGHT = 7,
	MODELCONDITION_SNOW = 8
};

// ModelConditionFlags as ZH's BitFlags wrapper over a bitset: test() is an
// inline bit read.
template <size_t NUMBITS> class BitFlags
{
public:
	Bool test(Int i) const { return m_bits.test(i); }

private:
	_STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<304> Rva007739F0ConditionFlags;

// The draw module that owns the resolver: module data at +0x04 and the
// drawable at +0x08 (the ZH DrawableModule layout), a suffix kind at +0xA0
// and 304-bit model condition flags at +0x148. Its class is not proven, so
// it keeps the address.
class Rva007739F0Owner
{
public:
	AsciiString resolveModelVariant007739F0(const AsciiString &modelName);

private:
	void *m_vtable;
	const Rva007739F0Data *m_data;
	const Drawable *m_drawable;
	unsigned char m_unmodelled00C[0x94];
	Int m_kindA0;
	unsigned char m_unmodelled0A4[0xa4];
	Rva007739F0ConditionFlags m_conditions148;
};

// Retail 0x007739F0 (1310 B), called through ILTs from 0x00778590 and
// 0x00755F70. It resolves the render-object name a draw module should load:
// the model name with its level-of-detail suffix (reporting once per name a
// model that has to fall back to low detail, and once per name a missing low
// detail model, which falls back to the plain name), then, when the module
// data asks for it, the first existing "_[n][d|e|r][s]" variant for the
// current model conditions (NIGHT, DAMAGED / REALLY_DAMAGED / RUBBLE, SNOW;
// the bit numbers are ZH's ModelConditionFlagType order). The flags must be a
// real bitset behind BitFlags::test: a plain word, bitfields or a hand-written
// test let MSVC fold adjacent bit tests into one mask.
// ?resolveModelVariant007739F0@Rva007739F0Owner@@QAE?AVAsciiString@@ABV2@@Z
AsciiString Rva007739F0Owner::resolveModelVariant007739F0(const AsciiString &modelName)
{
	AsciiString name = modelName;
	const Rva007739F0Data *data = m_data;
	Bool forcedLow = false;
	Int kind = rva0075B4A0(m_drawable, &forcedLow);

	if (data->m_flag109 || forcedLow)
		name = rva00761D20(modelName, kind);
	else if (data->m_flag108)
		name = rva00761D20(modelName,
			(m_drawable && (m_drawable->getStatusBits() & 0x20)) ? 2 : m_kindA0);

	if (!data->m_flag109 && forcedLow)
	{
		static _STL::set<AsciiString> s_reportedStaticLOD;
		_STL::set<AsciiString>::iterator found = s_reportedStaticLOD.find(name);
			if (found == s_reportedStaticLOD.end())
		{
			s_reportedStaticLOD.insert(name);
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				(*TheBfmeAwakenDebug->slot6C(0, 0) << name
					<< " INI setting required: Model "
					<< m_drawable->getTemplate()->m_name20
					<< " does not have StaticModelLODMode = Yes entry... Please correct this. Still attempting low detail use.")
					.slot4C(2);
			}
		}
	}

	if (!Render_Obj_Exists(name.str()))
	{
		if (forcedLow)
		{
			static _STL::set<AsciiString> s_reportedMissing;
			_STL::set<AsciiString>::iterator found = s_reportedMissing.find(name);
			if (found == s_reportedMissing.end())
			{
				s_reportedMissing.insert(name);
				if (_bfme_debugReportingEnabled())
				{
					_bfme_debugRecordCallsite(1);
					TheBfmeAwakenDebug->slot60();
					(*TheBfmeAwakenDebug->slot6C(0, 0) << name
						<< " MISSING: Model " << m_drawable->getTemplate()->m_name20
						<< " requires low detail model " << name
						<< " but doesn't exist, so using regular model " << modelName
						<< ". Please add this model for horde performance reasons.")
						.slot4C(2);
				}
			}
		}
		name = modelName;
	}

	if (data->m_flag10B)
	{
		Bool snow = m_conditions148.test(MODELCONDITION_SNOW);
		Bool night = m_conditions148.test(MODELCONDITION_NIGHT);
		if (!m_conditions148.test(MODELCONDITION_RUBBLE)
			&& !m_conditions148.test(MODELCONDITION_REALLY_DAMAGED)
			&& !m_conditions148.test(MODELCONDITION_DAMAGED)
			&& !night && !snow)
			return name;

		for (Int damage = 3; damage >= 0; --damage)
		{
			switch (damage)
			{
			case 3:
				if (!m_conditions148.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			case 2:
				if (!m_conditions148.test(MODELCONDITION_REALLY_DAMAGED)
					&& !m_conditions148.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			case 1:
				if (!m_conditions148.test(MODELCONDITION_REALLY_DAMAGED)
					&& !m_conditions148.test(MODELCONDITION_DAMAGED)
					&& !m_conditions148.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			}

			for (Int n = 1; n >= 0; --n)
			{
				if (n && !night)
					continue;
				for (Int s = 1; s >= 0; --s)
				{
					if (s && !snow)
						continue;

					AsciiString candidate = name;
					candidate.concat('_');
					if (n)
						candidate.concat('n');
					switch (damage)
					{
					case 1:
						candidate.concat('d');
						break;
					case 2:
						candidate.concat('e');
						break;
					case 3:
						candidate.concat('r');
						break;
					}
					if (s)
						candidate.concat('s');
					if (Render_Obj_Exists(candidate.str()))
						return candidate;
				}
			}
		}
	}
	return name;
}
