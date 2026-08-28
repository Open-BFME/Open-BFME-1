#pragma once
#include "ascii_string.h"

class Xfer;
enum INILoadType { INI_LOAD_INVALID = 0, INI_LOAD_OVERWRITE = 1, INI_LOAD_CREATE_OVERRIDES = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI {
public:
	INI();
	~INI();
	// BFME's load takes four arguments where ZH's takes three; the subsystem
	// loader at 0x000BB310 calls it as load(file, 1, 0, xfer).
	void load(AsciiString filename, int loadType, int reload, void* xfer);
	// The three-argument entry point the legend path uses (0x00853A20). Provisional
	// name: it is NOT INI::load, which is the 1037-byte body at 0x00853610 already
	// carried as a MASM dump — 0x00853A20 is a separate, smaller function that
	// takes (AsciiString, INILoadType, Xfer*). Rename it if its real name turns up.
	void loadFile(AsciiString filename, INILoadType loadType, Xfer* xfer);
	// BFME's loadDirectory takes a fifth argument ZH's does not; the legend path
	// calls it as loadDirectory(dir, TRUE, INI_LOAD_OVERWRITE, xfer, 0).
	void loadDirectory(AsciiString dirpath, bool recursive, INILoadType loadType, Xfer* xfer, int extra);
	static bool loadSubsystemFiles(const char* subsystem, void* xfer);
	const char* getNextToken(const char* seps = 0);
	void initFromINI(void* what, const struct FieldParse* parseTable);
	const char* getNextTokenOrNull(const char* seps = 0);
	static float scanReal(const char* token);
	static int scanInt(const char* token);
	static int scanBool(const char* token);
	static int scanIndexList(const char* token, const char* const* names);

	// INI field-parse procs referenced by FieldParse tables.
	static void parseAsciiString(INI* ini, void* instance, void* store, const void* userData);
	static void parseAsciiStringVectorAppend(INI* ini, void* instance, void* store, const void* userData);
	static void parseLookupList(INI* ini, void* instance, void* store, const void* userData);

private:
	// Not ported. The padding keeps sizeof(INI) at retail's 0x848 so callers that
	// stack-allocate one get retail's frame; INI::INI() at 0x00851230 writes as
	// far as [this+0x834].
	char m_unported[0x848];
};
// INI::scanLookupList (0x00850A70) walks these in 8-byte strides, matching the
// name at +0 and taking the value at +4.
struct LookupListRec { const char* name; int value; };

typedef void (*INIFieldParseProc)(INI*, void*, void*, const void*);
struct FieldParse { const char* token; INIFieldParseProc parse; const void* userData; int offset; };
