// d_00290520
// partial score=0.25 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5 WIP candidate for retail 0x00290520 (426 B), dump d_00280010.asm.
// This is an INI field-parse callback for EmotionTrackerUpdateModuleData: it
// reads one or two tokens, resolves an EmotionNugget by name via
// EmotionSystem::findNugget, builds an EmotionTrackerUpdateEntry (same class
// whose destructor is EmotionTrackerUpdateEntryDestructor.cpp -- three
// AsciiStrings at +0x00/+0x3C/+0xF4, sizeof 0xF8, matching this body's
// operator new(0xF8)) and appends it to the ModuleData's
// std::vector<EmotionTrackerUpdateEntry*> m_entries at +0x30 (the same
// vector/offset EmotionTrackerUpdateCtor.cpp iterates).
//
// NOT YET BYTE EXACT. Open questions (see re_attempts.log / banked notes):
//   - g_lookup (0x0135933C) semantics: called as (token, 0x10be338) and only
//     used as a bool; probably a keyword/table validity check before falling
//     back to a second getNextToken.
//   - the setter call at retail +0x10c (thunk j_0002a57c, gen_small stub,
//     real signature unresolved) that hands the found EmotionNugget* to the
//     new entry.
//   - the conditional call at +0x14b (thunk j_0000452a) gated on whether the
//     second-token branch was taken (bl flag).
//   - which of +0x00/+0x3C/+0xF4 the name token vs the translated
//     UnicodeString text land in.
// Banked as a partial candidate; not landed.

#include <new>

typedef unsigned int UnsignedInt;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *str);				// retail 0x00888BC0 (char)
	void releaseBuffer();					// retail 0x00887940 (char)

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text) : m_string(text) {}
	~AsciiString() { m_string.releaseBuffer(); }

	StringBase<char> m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(int, const char *, ...);
	INIException(const INIException &);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);		// retail 0x00850970
};

// Forward only -- never dereferenced here, only reinterpret_cast'd through so
// the EmotionSystem::findNugget mangling matches the existing symbols.csv pin.
class BfmeEmotionName;

class EmotionNugget
{
public:
	EmotionNugget();							// pinned ??0EmotionNugget@@QAE@XZ, retail 0x0001193C
};

class EmotionSystem
{
public:
	EmotionNugget *findNugget(const BfmeEmotionName &name);	// pinned, retail 0x0000C202
};

// address-derived: VA 0x012F0878, loaded right before findNugget's ecx
extern EmotionSystem *g_bfmeEmotionSystem0878;

// address-derived: VA 0x0135933C, generic (void*, void*) -> void* lookup used
// as a boolean gate here
extern "C" void *(__cdecl *g_lookup)(void *, void *);

class EmotionTrackerUpdateEntry
{
public:
	unsigned char m_unknown00[0xF8];
};

class EmotionTrackerUpdateModuleData
{
public:
	unsigned char m_unknown00[0x30];
	// std::vector<EmotionTrackerUpdateEntry *> at +0x30, matching
	// EmotionTrackerUpdateCtor.cpp's m_entries
	EmotionTrackerUpdateEntry **m_entriesFirst;
	EmotionTrackerUpdateEntry **m_entriesLast;
	EmotionTrackerUpdateEntry **m_entriesEnd;
};

static void bfmeAppendEmotionEntry(EmotionTrackerUpdateModuleData *data, EmotionTrackerUpdateEntry *entry)
{
	if (data->m_entriesLast != data->m_entriesEnd)
	{
		if (data->m_entriesFirst != 0)
			*data->m_entriesLast = entry;
		data->m_entriesLast++;
	}
	else
	{
		// retail grow path (vector<T*> _Insert_n / grow), not reproduced here
	}
}

// address-derived name; real ZH twin unknown -- BFME-only EmotionTrackerUpdate
// has no Zero Hour counterpart under reference/CnC_Generals_Zero_Hour.
void bfmeParseEmotionTrackerEntry_00290520(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	const char *token = ini->getNextToken();
	bool tookSecondToken = false;

	if (token != 0)
	{
		if (!g_lookup((void *)token, (void *)0x10be338))
		{
			tookSecondToken = true;
			token = ini->getNextToken();
		}
	}

	if (token == 0)
		throw INIException(3, "Expected additional data");

	EmotionNugget *nugget;
	{
		AsciiString name(token);
		nugget = g_bfmeEmotionSystem0878->findNugget(*(const BfmeEmotionName *)&name);
	}

	if (nugget == 0)
		throw INIException(3, "Emotion nugget not found");

	void *raw = ::operator new(0xF8);
	EmotionTrackerUpdateEntry *entry = 0;
	if (raw != 0)
	{
		new (raw) EmotionNugget();
		entry = (EmotionTrackerUpdateEntry *)raw;
	}

	(void)tookSecondToken;

	bfmeAppendEmotionEntry((EmotionTrackerUpdateModuleData *)instance, entry);
}
