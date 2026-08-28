// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
// readable body of ?AddPatternEntry@Debug@@AAEXI_NPBD@Z: Code/Libraries/Source/WWVegas/WWDebug/debug_debug.cpp
// Lift the Debug::AddPatternEntry naked dump to clean C++.
//
// Zero Hour's debug_debug.cpp body with one BFME addition: after copying the
// pattern retail runs it through _strlwr, so BFME matches patterns
// case-insensitively by folding them on the way in. The import directory names
// that slot, which is the only way to tell it from any other one-argument CRT
// call on a char*.
//
// strlen and strcpy are intrinsics here rather than calls -- retail inlines
// both as byte loops -- so they must be declared without dllimport or MSVC
// routes them through the IAT instead.
//
// The __ASSERT(pattern) is a no-op in release and retail has no trace of it.
//
// Retail pins the layout: firstPatternEntry at this+0x9E00 and lastPatternEntry
// at this+0x9E04, with the entry itself sixteen bytes -- next at +0x00,
// frameTypes at +0x04, isActive at +0x08 and pattern at +0x0C.

extern "C" unsigned int __cdecl strlen(const char *);
extern "C" char *__cdecl strcpy(char *, const char *);
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *);

void *DebugAllocMemory(unsigned int size);				///< ILT thunk at 0x0088EB30

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
private:
	struct PatternListEntry
	{
		/// next entry
		PatternListEntry *next;							///< retail this+0x00

		/// frame type(s)
		unsigned frameTypes;							///< retail this+0x04

		/// active (true) or inactive (false)?
		bool isActive;									///< retail this+0x08

		/// pattern itself (dynamic allocated memory)
		char *pattern;									///< retail this+0x0C
	};

	void AddPatternEntry(unsigned types, bool isActive, const char *pattern);

	unsigned char m_unreconstructed_00[0x9E00];
	PatternListEntry *firstPatternEntry;				///< retail this+0x9E00
	PatternListEntry *lastPatternEntry;					///< retail this+0x9E04
};

// ?AddPatternEntry@Debug@@AAEXI_NPBD@Z
void Debug::AddPatternEntry(unsigned types, bool isActive, const char *pattern)
{
	// alloc new pattern entry
	PatternListEntry *cur = (PatternListEntry *)
			DebugAllocMemory(sizeof(PatternListEntry));

	// init
	cur->next = 0;
	cur->frameTypes = types;
	cur->isActive = isActive;
	cur->pattern = (char *)DebugAllocMemory(strlen(pattern) + 1);
	strcpy(cur->pattern, pattern);
	_strlwr(cur->pattern);

	// add to list
	if (lastPatternEntry)
		lastPatternEntry->next = cur;
	else
		firstPatternEntry = cur;
	lastPatternEntry = cur;
}
