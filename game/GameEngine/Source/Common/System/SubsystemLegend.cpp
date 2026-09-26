// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// SubsystemLegend — a BFME-only engine subsystem with no ZH counterpart, so it is
// built against the BFME-native headers (ascii_string.h / subsystem_interface.h)
// rather than the ZH reference tree. That is load-bearing, not cosmetic: the ZH
// AsciiString header inlines its release path, while retail (and the ported
// StringBase<char>) keeps it out of line, and it is exactly that inlining which
// used to blow this file's register allocation.
//
// Layout recovered from retail, every offset proven by a body below:
//   +0x00  SubsystemInterface base (vptr; AsciiString m_name at +0x04 — the base
//          ctor 0x009A1A30 writes exactly those two words)
//   +0x08  std::list<SubsystemLegendEntry> m_entries
// The element is 0x30 bytes (list node 0x38, the size the ctor and dtor
// allocate/free). Its dtor (0x00078210) destroys, in reverse declaration order,
// +0x2c, +0x1c, +0x10, +0x04, +0x00, which pins the field layout; the copy ctor
// (0x009A12B0) confirms it independently, copying +0x28 as a plain dword between
// two StringBase copy-ctor calls. Field names come from the INI FieldParse table
// — see subsystem_legend.h.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)
#include <vector>
#include "PreRTS.h"
#include "subsystem_legend.h"
#include <stddef.h>
#include "Common/INI/INI.h"

// The "Loader" field's lookup table (retail 0x012D7758). Only two names exist.
// Note the retail bytes are ptr("INI"), ptr("STR"), 0, 0 — read as the 8-byte
// LookupListRec that INI::scanLookupList walks, that is one usable record whose
// value happens to be the address of "STR". Reproduced as-is rather than guessed.
static const LookupListRec TheSubsystemLegendLoaderNames[] =
{
	{ "INI", 0 },
	{ NULL,  0 }
};

// The FieldParse table retail keeps at 0x011415C0 and parseLoadSubsystem hands to
// INI::initFromINI. This is the INI schema of a "LoadSubsystem" block, and it is
// what names the entry fields. Data, not code — build.sh byte-verifies functions,
// so this table is not gate-checked; it is transcribed from the retail bytes.
const FieldParse TheSubsystemLegendFieldParse[] =
{
	{ "InitFile",         INI::parseAsciiStringVectorAppend, NULL,                            offsetof(SubsystemLegendEntry, m_initFile)      },
	{ "InitPath",         INI::parseAsciiStringVectorAppend, NULL,                            offsetof(SubsystemLegendEntry, m_initPath)      },
	{ "Extension",        INI::parseAsciiStringVectorAppend, NULL,                            offsetof(SubsystemLegendEntry, m_extension)     },
	{ "Loader",           INI::parseLookupList,              TheSubsystemLegendLoaderNames,   offsetof(SubsystemLegendEntry, m_loader)        },
	{ "InitFileDebug",    INI::parseAsciiString,             NULL,                            offsetof(SubsystemLegendEntry, m_initFileDebug) },
	{ "ExcludePathDebug", INI::parseAsciiString,             NULL,                            offsetof(SubsystemLegendEntry, m_initFileDebug) },
	{ NULL,               NULL,                              NULL,                            0                                               }
};

// ??0SubsystemLegendEntry@@QAE@XZ
SubsystemLegendEntry::SubsystemLegendEntry()
{
	m_name.clear();
	m_initFile.clear();
	m_initPath.clear();
	m_extension.clear();
	m_loader = 0;
	m_initFileDebug.clear();
}

// ??0SubsystemLegend@@QAE@XZ
SubsystemLegend::SubsystemLegend()
{
}

// ??1SubsystemLegend@@UAE@XZ
SubsystemLegend::~SubsystemLegend()
{
	m_entries.clear();
}

// ?init@SubsystemLegend@@UAEXXZ
void SubsystemLegend::init()
{
	m_entries.clear();
}

// ?reset@SubsystemLegend@@UAEXXZ
void SubsystemLegend::reset()
{
	m_entries.clear();
}

// ?update@SubsystemLegend@@UAEXXZ
void SubsystemLegend::update()
{
}

// ?getEntryCount@SubsystemLegend@@QBEHXZ
Int SubsystemLegend::getEntryCount() const
{
	return m_entries.size();
}

// ?findEntry@SubsystemLegend@@QAEPAUSubsystemLegendEntry@@VAsciiString@@@Z
// The lookup the whole legend exists for: SubsystemInterface::loadIniFilesFromLegend
// calls this with the subsystem's own name. It is also the only body in the TU
// that instantiates _List_iterator<Entry>::operator* and operator->.
SubsystemLegendEntry *SubsystemLegend::findEntry(AsciiString name)
{
	std::list<SubsystemLegendEntry>::iterator it;
	for (it = m_entries.begin(); it != m_entries.end(); ++it)
	{
		AsciiString entryName = it->m_name;
		if (entryName.compare(name) == 0)
			return &(*it);
	}
	return NULL;
}

// ?addEntry@SubsystemLegend@@QAEXABUSubsystemLegendEntry@@@Z
void SubsystemLegend::addEntry(const SubsystemLegendEntry &entry)
{
	m_entries.push_back(entry);
}

// ?parseLoadSubsystem@SubsystemLegend@@QAEXPAVINI@@@Z
void SubsystemLegend::parseLoadSubsystem(INI *ini)
{
	AsciiString name(ini->getNextToken(NULL));
	SubsystemLegendEntry entry;
	entry.m_name = name;
	ini->initFromINI(&entry, TheSubsystemLegendFieldParse);
	if (TheSubsystemLegend)
		TheSubsystemLegend->m_entries.push_back(entry);
}

// The INI block table registers this under the keyword "LoadSubsystem".
// ?parseSubsystemLegendDefinition@@YAXPAVINI@@@Z
void parseSubsystemLegendDefinition(INI *ini)
{
	if (TheSubsystemLegend)
		TheSubsystemLegend->parseLoadSubsystem(ini);
}
