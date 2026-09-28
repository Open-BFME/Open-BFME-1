// ?parseModuleName@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Oy- /Igame/Libraries/Source/WWVegas/WWLib
// BFME ThingTemplate::parseModuleName at retail RVA 0x001458A0.
//
// The callback is registered by ThingTemplate's Behavior/Body/Draw/
// ClientUpdate field tables.  BFME's ThingTemplate has four 12-byte
// ModuleInfo subobjects at +0x294, +0x2a0, +0x2ac and +0x2b8, rather than the
// three ZH members in the vendored header.  This TU keeps that ABI view local.
//
// Retail facts this body now reproduces (0x001458A0..0x00145BA3, 772 B):
//  * tokenStr lives in the DEAD userData argument slot [ebp+0x14] and is built
//    by an out-of-line BFMERetailAsciiString(const char*) ctor call.
//  * the second getNextToken AND the inline strlen AND the set(text,len) call
//    all sit inside the try: EH state 2 covers +0x46..+0x6c and state 1 is
//    stored at +0x7d, after the set returns.  Keeping the strlen+set out of
//    the try moves the state store 0x2b bytes early and was the single largest
//    win of this session.
//  * BFME's INI has a FOURTH load type: getLoadType() == 4 also skips the four
//    clearCopiedFromDefaultEntries calls, so the control flow is
//    `if (loadType == 2) {...throw if mode != ADD_REMOVE_REPLACE...}
//     else if (loadType != 4) { four clears }` -- NOT a plain if/else.  The one
//    cached `Int loadType` feeds both compares (retail keeps it in eax across
//    the call-free span between +0xf0 and +0x128); a second getLoadType()
//    expression gets rematerialised and diverges.
//  * addModuleInfo is called with SEVEN arguments; the 7th is
//    `ini->getLoadType() == 4`, re-read from memory at +0x270, not the
//    loadType local.
//  * the loadType==4 bool is stored to the dead `instance` argument slot
//    [ebp+0xc] (sete byte ptr) and `inheritable` to the dead `store` slot
//    [ebp+0x10], both matching the landed addModuleInfo parameter names.
//
// THE MODE-BYTE LEVER (this session's whole win, 345 -> 29 diffs):
// retail materialises m_moduleParsingMode into bl at +0x15a and re-tests
// `cmp bl,1` at +0x1dd, i.e. the two flat `if (mode == ADD_REMOVE_REPLACE)`
// statements test a value the compiler holds in a callee-saved register.  A
// local alone does NOT produce that: MSVC 7.1 folds the local back into the
// member load (char, unsigned char and a volatile read of the member all
// compile to `cmp byte ptr [esi+0x498],1` and then DELETE the second test, via
// the same condition propagation that fires for the member expression -- the
// second test is reachable only from the first if's true edge).  What works is
// to break the propagation by making the two tests read DIFFERENT expressions:
// the FIRST `if` tests the member expression, the SECOND tests an
// `unsigned char` local holding the same read.  Then the loads are not one
// shared value, the local has to live in a register (mov bl at +0x15a, the
// re-test at +0x1dd), and the whole register cascade follows for free: EBX
// takes the mode byte, EDI takes &m_moduleBeingReplacedName, `ini` is reloaded
// from [ebp+8] at +0x1e0, and the second throw's str() sites change shape.
// Verified by probe: 345 -> 29 non-reloc diffs, 5 -> 3 structural differences,
// and the main body is now exactly 772 bytes (the extra 10 bytes the object
// reports are the trailing catch funclet, which retail has as its own 9-byte
// row at 0x00145BA4).
//
// Still open: ONE difference, 29 bytes, all inside the second INIException's
// three str() temporaries.  Retail puts the first-computed one (getName().str())
// in a fresh register (`mov eax,[esi+0x20]; test; lea ecx,[eax+8]`) and folds
// the other two in place; ours folds the first in place (add eax,8) and gives
// the fresh register (edx) to the second, which shifts the third to ecx.  It is
// a single fold decision in a varargs ternary, and it is NOT reachable from the
// source.  rotation_sweep.py's 40 toggles all leave the byte count unchanged, and
// nine spellings of str() (if-form, two named temporaries, Header::data member
// access, __forceinline, empty string via a const local or a static array,
// explicit != 0, cast placement) all compile to the identical instruction
// sequence.  The str() offsets +4/+8 do match the vendored StringBase<char>
// Header (int ref_count; unsigned short length; unsigned short capacity;
// T data[1]), so modelling m_data as that struct is faithful but changes
// nothing here.
//
// WHAT IS PROVEN NOT TO MOVE IT (2026-09-28 session, ~50 more spellings):
//  * The retail pattern is NOT reachable by reordering or restructuring the
//    three temporaries.  Three named temps in reverse source order, two named
//    temps, hoisting only getName().str(), hoisting only mbrName.str(), a
//    direct m_nameString instead of the getName() accessor, casts on the three
//    args, and a `const char *` format global all compile to the IDENTICAL
//    instruction sequence (29 diffs, shape 0.967, byte for byte).
//  * An __forceinline helper taking the three `const char *` in source order
//    (W1), the three AsciiString& in either order (W3/W4) also compile to the
//    identical sequence: the front end re-normalises the argument list, so the
//    helper boundary is invisible.  Passing them in the WRONG order (W2/W6)
//    changes the byte order and gets worse (240).
//  * The empty string spelled as a static array, a static pointer, a class-level
//    `const char *const`, or a forced-inline getter compiles identically.  A
//    static array only changes the masked relocation bytes (29 -> 25) with no
//    change in the instruction shape, so it is NOT an improvement.
//  * It is not a rotation-phase residue either.  Inserting one or two further
//    rotation steps immediately before the block (an extra materialised local
//    plus a comparison that throws) leaves the block's internal assignment
//    byte-identical: eax folds, edx is fresh, ecx folds.  So the block does not
//    read the incoming EAX/ECX/EDX pointer state, and rotation_sweep --pairs
//    (809 toggles, singles and pairs, all +0 diffs) is exhausted.
//  * eh_levers (6 choices, 128 combinations, 9 trials) has no usable choice:
//    throw() per callee and /EHsc- both delete the EH frame retail keeps.
//    shape_family_levers over all ten families generates only two alternatives
//    on this body (an interfaceMask commutativity rewrite), neither useful.
//  * Moving the throw into a helper that builds the three pointers as named
//    locals (W6) is worse (240), and wrapping either ReplaceModule check in an
//    __forceinline helper is worse (338).  `!compare()`, `0 == compare()` and
//    `!(compare() != 0)` are all identical.
//  * The mode-byte lever above is load-bearing: re-testing the member in BOTH
//    `if`s collapses back to 350 differing bytes, and testing the local in both
//    drops to 345.  Keep one of each.
//  * AsciiString must keep exactly one scalar member: adding a second member
//    costs 72 differing bytes.
// Header note: this TU's AsciiString has exactly one scalar member, so
// tools/adopt_header.py will classify it as an adoption candidate and the
// commit hook will refuse it; landing needs a distinct type name or a
// documented shim exception.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include <string.h>

#include "string_base.h"

struct FieldParse;

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const char *text, Int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}
	Int compare(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compare(
			*(const StringBase<char> *)&other);
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388b;
	}

	Bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)((const char *)m_data + 4) != 0;
	}

	Bool operator!=(const AsciiString &other) const
	{
		return compare(other) != 0;
	}

private:
	char *m_data;
};

class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_message;
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);

	Int getLoadType() const
	{
		return *(const Int *)((const char *)this + 8);
	}
};

enum ModuleType
{
	MODULETYPE_BEHAVIOR = 0,
	MODULETYPE_DRAW = 1,
	MODULETYPE_CLIENT_UPDATE = 2
};

enum ModuleInterfaceType
{
	MODULEINTERFACE_BODY = 0x20
};

enum ModuleParseMode
{
	MODULEPARSE_NORMAL,
	MODULEPARSE_ADD_REMOVE_REPLACE,
	MODULEPARSE_INHERITABLE,
	MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND
};

class ThingTemplate;

class BfmeModuleData
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot04();
	virtual void bfmeSlot08();
	virtual void bfmeSlot0c();
	virtual Bool isAiModuleData() const;
	virtual Bool hasAiModuleData() const;
};

class BfmeModuleInfo
{
public:
	Bool clearCopiedFromDefaultEntries(Int interfaceMask);
	Bool clearAiModuleInfo();
	Bool clearModuleInfo();
	void addModuleInfo(ThingTemplate *thingTemplate,
		const AsciiString &name, const AsciiString &moduleTag,
		const BfmeModuleData *data, Int interfaceMask, Bool inheritable,
		Bool overrideableByLikeKind);

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class BfmeModuleFactory
{
public:
	Int findModuleInterfaceMask(const AsciiString &name, ModuleType type);
	BfmeModuleData *newModuleDataFromINI(INI *ini, const AsciiString &name,
		ModuleType type, const AsciiString &moduleTag);
};

#define TheModuleFactory (*((BfmeModuleFactory **)0x012ef198))

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }

protected:
	static void __cdecl parseModuleName(INI *ini, void *instance, void *store,
		const void *userData);

private:
	char m_unreconstructed00[0x20];
	AsciiString m_nameString;
	char m_unreconstructed24[0x50 - 0x24];
	AsciiString m_moduleBeingReplacedName;
	AsciiString m_moduleBeingReplacedTag;
	char m_unreconstructed58[0x294 - 0x58];
	BfmeModuleInfo m_behaviorModuleInfo;
	BfmeModuleInfo m_drawModuleInfo;
	BfmeModuleInfo m_clientUpdateModuleInfo;
	BfmeModuleInfo m_clientBehaviorModuleInfo;
	char m_unreconstructed2c4[0x498 - 0x2c4];
	char m_moduleParsingMode;
};

// ?parseModuleName@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parseModuleName(INI *ini, void *instance,
	void *store, const void *userData)
{
	Int type = (Int)(UnsignedInt)userData;
	ThingTemplate *self = (ThingTemplate *)instance;
	BfmeModuleInfo *mi = (BfmeModuleInfo *)store;
	const char *token = ini->getNextToken();
	AsciiString tokenString = token;
	AsciiString moduleTagString;

	try
	{
		const char *moduleTag = ini->getNextToken();
		moduleTagString.set(moduleTag, moduleTag != 0 ? (Int)strlen(moduleTag) : 0);
	}
	catch (...)
	{
		throw;
	}

	Int interfaceMask;
	if (type == 999)
	{
		type = MODULETYPE_BEHAVIOR;
		interfaceMask = TheModuleFactory->findModuleInterfaceMask(tokenString,
			(ModuleType)type);
		if ((interfaceMask & MODULEINTERFACE_BODY) == 0)
		{
			throw INIException(3, "Only Body allowed here");
		}
	}
	else
	{
		interfaceMask = TheModuleFactory->findModuleInterfaceMask(tokenString,
			(ModuleType)type);
		if ((interfaceMask & MODULEINTERFACE_BODY) != 0)
		{
			throw INIException(3, "No Body allowed here");
		}
	}

	Int loadType = ini->getLoadType();
	if (loadType == 2)
	{
		if (self->m_moduleParsingMode != MODULEPARSE_ADD_REMOVE_REPLACE)
		{
			throw INIException(3, "You must use AddModule to add modules in override INI files.");
		}
	}
	else if (loadType != 4)
	{
		self->m_behaviorModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
		self->m_drawModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
		self->m_clientUpdateModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
		self->m_clientBehaviorModuleInfo.clearCopiedFromDefaultEntries(interfaceMask);
	}

	// The first ReplaceModule check reads the member directly and the second
	// reads this local, on purpose: retail keeps the mode byte in bl across the
	// first throw and re-tests it, which only happens when the two conditions
	// are not one shared value.  See the header note.
	unsigned char parsingMode = self->m_moduleParsingMode;

	if (self->m_moduleParsingMode == MODULEPARSE_ADD_REMOVE_REPLACE
			&& self->m_moduleBeingReplacedName.isNotEmpty()
			&& self->m_moduleBeingReplacedName != tokenString)
	{
		throw INIException(3,
			"ReplaceModule must replace modules with another module of the same type, but you are attempting to replace a %s with a %s for object %s.",
			self->m_moduleBeingReplacedName.str(), tokenString.str(), self->getName().str());
	}

	if (parsingMode == MODULEPARSE_ADD_REMOVE_REPLACE
			&& self->m_moduleBeingReplacedTag.isNotEmpty()
			&& self->m_moduleBeingReplacedTag.compare(moduleTagString) == 0)
	{
		throw INIException(3,
			"ReplaceModule must specify a new, unique tag for the replaced module, but you are not doing so for %s (%s) for object %s.",
			moduleTagString.str(), self->m_moduleBeingReplacedName.str(), self->getName().str());
	}

	BfmeModuleData *data = TheModuleFactory->newModuleDataFromINI(
		ini, tokenString, (ModuleType)type, moduleTagString);
	Bool overrideableByLikeKind = ini->getLoadType() == 4;
	if (data->isAiModuleData())
	{
		mi->clearAiModuleInfo();
		if (data->hasAiModuleData() && overrideableByLikeKind)
		{
			mi->clearModuleInfo();
		}
	}

	Bool inheritable = self->m_moduleParsingMode == MODULEPARSE_INHERITABLE;
	mi->addModuleInfo(self, tokenString, moduleTagString, data, interfaceMask,
		inheritable, overrideableByLikeKind);
}
