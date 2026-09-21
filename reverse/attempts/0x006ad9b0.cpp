// ?Rva006AD9B0GetAllowAudioReinitialize@@YA_NXZ
// partial score=0.95 date=2026-09-21
//
// Free-standing helper: builds a fresh OptionPreferences (which loads
// Options.ini in its own constructor), looks up the AllowAudioReinitialize
// key, and returns false only when the stored value case-insensitively
// equals "false" or "no"; a missing key, or any other value, returns true.
// No `this` pointer is read anywhere in the retail body -- it is not an
// OptionPreferences member, it constructs and destroys its own local
// OptionPreferences before returning.
//
// callers (still unnamed dumps, no name evidence): ?d_006b86d0@@YAXXZ
// @ carved.csv; ?d_006b9c90@@YAXXZ @ d_006b9500.asm
//
// callees, in body order:
//   OptionPreferences::OptionPreferences(void) via ILT 0x0003713C -> 0x000904E0 (matched)
//   AsciiString(const char *) 0x00888BC0 (retail calls the StringBase base ctor
//     directly, alias ??0BFMERetailAsciiString@@QAE@PBD@Z; SEE CAVEAT below)
//   PreferenceMap::find via ILT 0x0000AEAC -> 0x00080600 (STLport _M_find<AsciiString>, matched)
//   AsciiString::releaseBuffer()/~AsciiString() 0x00887940 (matched, key destructor)
//   AsciiString(const AsciiString &) 0x00887B60 (retail calls the StringBase base
//     copy ctor directly, alias ??0GameSpyGroupRoom@@QAE@ABV0@@Z; SEE CAVEAT below)
//   AsciiString::compareNoCase(const char *) via ILT 0x000405E8 -> 0x00075E00,
//     pinned as ?compareNoCase@AsciiString@@QBEHPBD@Z; returns 0 on a
//     case-insensitive match, and retail's two `test eax,eax; je fail`
//     sequences fire on that zero, so retail returns false exactly when the
//     stored value equals "false" or "no" and true for anything else
//     (including a missing key)
//   AsciiString::releaseBuffer()/~AsciiString() 0x00887940 (matched, value destructor)
//   OptionPreferences::~OptionPreferences() via ILT 0x00001307 -> 0x00090450 (matched)
//
// string literals verified against the retail image: key = 0x0111C2A8
// "AllowAudioReinitialize", compares = 0x0111C2A0 "false", 0x010EBA88 "no"
//
// PROBE STATE: 234/234 bytes, 11 non-reloc byte(s) differ (score ~0.953).
// Every remaining diff is the SAME 4-byte esp offset shift (our locals start
// at esp+8, retail's at esp+0xc) plus one downstream `lea [esi+0x14]; push`
// vs `add esi,0x14; push esi` register-reuse choice at +0x57 that seems to
// follow from it. Sizing OptionPreferences (4 + PreferenceMap{m_end+pad})
// larger/smaller only grows/shrinks the TAIL of the frame -- it never moves
// this base offset, so the missing 4 bytes belong to something in the
// [[esp, esp+0xc) region below `key`/`prefs`, not to PreferenceMap/
// OptionPreferences's own size. Tried and did NOT move the offset: `it`
// declared before/after `prefs`, an unused int local, `(void)&it`, and a
// `PreferenceNode * volatile it` (which also drops the esi caching entirely
// and makes things much worse -- revert that idea).
//
// LINKAGE CAVEAT for the next worker: this file declares its own local
// `AsciiString` with an undefined `AsciiString(const char *)` and
// `AsciiString(const AsciiString &)`. The REAL `AsciiString` class
// (Code/Libraries/Source/WWVegas/WWLib/ascii_string.h) already has ITS OWN
// matched constructors at DIFFERENT addresses (??0AsciiString@@QAE@PBD@Z ->
// 0x0005EE70 via ILT 0x00012C42; ??0AsciiString@@QAE@ABV0@@Z -> 0x0005EE50
// via ILT 0x000416AF) -- NOT the 0x00888BC0/0x00887B60 StringBase base
// constructors this retail body actually calls. probe.py cannot see this
// (it masks relocation operands) but add_match.py's full byte gate will.
// The fix is almost certainly: construct through `BFMERetailAsciiString`
// (ctor matched at 0x00888BC0) and `GameSpyGroupRoom` (copy ctor matched at
// 0x00887B60) instead of `AsciiString`, while STILL getting an automatic,
// EH-tracked destructor call -- a `key.releaseBuffer()`/`value.releaseBuffer()`
// MANUAL call compiles WITHOUT the `mov byte/dword ptr [esp+0x28], 0/-1`
// EH-state-clear store retail has right before +0x91/+0xc2 (tried this,
// verified the instruction is simply missing), so the local must stay a true
// scope-exit-destroyed object, not a manually released one. `AsciiString`
// keeps the correct `~AsciiString()`/`compareNoCase` addresses (0x00887940 and
// 0x00075E00 via ILT 0x000405E8 are both already pinned under that class
// name) -- only the two constructors need to come from elsewhere. A
// placement-new through `BFMERetailAsciiString`/`GameSpyGroupRoom` into
// storage typed/aliased as `AsciiString`, still relying on `AsciiString`'s
// own scope-exit destructor call, is the next thing to try; a bare
// `(AsciiString*)&raw` cast without placement-new does NOT invoke the right
// constructor at all so is not sufficient by itself.

class AsciiString
{
public:
	AsciiString(const char *s);
	AsciiString(const AsciiString &that);
	~AsciiString();

	int compareNoCase(const char *s) const throw();

	char *m_text;
};

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();
	PreferenceNode *end(void) const { return m_end; }

	PreferenceNode *m_end;								///< retail this+0x00
	unsigned char m_unreconstructed_04[0x10];
};

class OptionPreferences
{
public:
	OptionPreferences(void);
	~OptionPreferences();

	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

bool Rva006AD9B0GetAllowAudioReinitialize(void)
{
	PreferenceNode *it;
	OptionPreferences prefs;

	{
		AsciiString key("AllowAudioReinitialize");
		it = prefs.m_prefs.find(key);
	}

	if (it != prefs.m_prefs.end())
	{
		AsciiString value(it->m_value);
		if (value.compareNoCase("false") == 0 || value.compareNoCase("no") == 0)
			return false;
	}

	return true;
}
