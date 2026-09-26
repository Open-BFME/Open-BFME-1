// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
//
// TeamFactory::removeTeamPrototypeFromList — sibling TU (LocomotorAccessors
// pattern). Retail body @ 0x000EFD50 (149B) keys m_prototypes by
// pair<NameKeyType,NameKeyType> from TeamPrototype AsciiStrings at +0x10/+0x14
// (single-vptr layout; owner-name beside m_name), erases a 0x1C-byte node, and
// calls STLport erase helpers via direct e8. Team.cpp keeps the ZH single-key
// typedef so its other matched symbols stay green; /D_STLP_USE_STATIC_LIB is
// file-local so dllimport-dependent Team.cpp rows are undisturbed.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)
#include "PreRTS.h"
#include "Common/Team.h"
#include "Common/NameKeyGenerator.h"

// ?removeTeamPrototypeFromList@TeamFactory@@QAEXPAVTeamPrototype@@@Z
void TeamFactory::removeTeamPrototypeFromList(TeamPrototype* team)
{
	struct BfmeAsciiString {
		char *m_text;
		const char *str() const { return m_text ? m_text + 8 : ""; }
	};
	struct BfmeTeamPrototypeView {
		void *vftable;
		void *m_factory;
		void *m_owningPlayer;
		UnsignedInt m_id;
		BfmeAsciiString m_name;       // +0x10
		BfmeAsciiString m_ownerName;  // +0x14
	};
	typedef std::pair<NameKeyType, NameKeyType> BfmeTeamPrototypeKey;
	typedef std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > BfmeTeamPrototypeMap;

	BfmeTeamPrototypeView *tp = reinterpret_cast<BfmeTeamPrototypeView *>(team);
	// MSVC evaluates pair ctor args RTL: owner-name key first (+0x14), then name (+0x10).
	BfmeTeamPrototypeKey nk(NAMEKEY(tp->m_name.str()), NAMEKEY(tp->m_ownerName.str()));
	BfmeTeamPrototypeMap *map = reinterpret_cast<BfmeTeamPrototypeMap *>(&m_prototypes);
	BfmeTeamPrototypeMap::iterator it = map->find(nk);
	if (it != map->end())
		map->erase(it);
}
