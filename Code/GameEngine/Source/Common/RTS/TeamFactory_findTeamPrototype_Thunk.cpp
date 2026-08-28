// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
//
// TeamFactory::findTeamPrototype -- sibling TU of TeamFactoryList.cpp.
//
// The pinned name is ?findTeamPrototype@TeamFactory@@QAEPAVTeamPrototype@@ABVAsciiString@@0@Z:
// BFME's overload takes TWO AsciiStrings (team name and owner name) where ZH
// takes one, and looks the pair up in the same pair<NameKeyType,NameKeyType>
// keyed m_prototypes map that removeTeamPrototypeFromList already proved --
// retail reaches it at this+0x0c and calls the very same _M_find body at
// 0x000EE500 through ILT 0x00011CB6. Team.h cannot declare the two-argument
// overload without a shared-header edit, so TeamFactory is spelled locally with
// the layout retail shows: two base vptrs (SubsystemInterface, Snapshot), one
// BFME word at +0x08, and the map at +0x0c.
//
// MSVC evaluates the pair constructor arguments right to left, which is why
// retail keys the OWNER name (second parameter) first and the team name second,
// then stores them as first=name, second=owner.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>		// STLport node_alloc, as in TeamFactoryList.cpp

class TeamPrototype;

enum NameKeyType { NAMEKEY_INVALID = 0 };

// Spelled locally so that str() is the inlined m_data ? m_data->peek() : ""
// retail emits, and so that no header pulls in the one-argument overload.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	///< ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;	///< retail [0x012ED600]

typedef std::pair<NameKeyType, NameKeyType> BfmeTeamPrototypeKey;
typedef std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > BfmeTeamPrototypeMap;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString& name, const AsciiString& ownerName);

private:
	void *m_subsystemInterfaceVptr;		// +0x00
	void *m_snapshotVptr;				// +0x04
	int m_unreconstructed08;			// +0x08
	BfmeTeamPrototypeMap m_prototypes;	// +0x0c
};

// ?findTeamPrototype@TeamFactory@@QAEPAVTeamPrototype@@ABVAsciiString@@0@Z
TeamPrototype *TeamFactory::findTeamPrototype(const AsciiString& name, const AsciiString& ownerName)
{
	BfmeTeamPrototypeKey nk(TheNameKeyGenerator->nameToKey(name.str()),
		TheNameKeyGenerator->nameToKey(ownerName.str()));

	BfmeTeamPrototypeMap::iterator it = m_prototypes.find(nk);
	if (it != m_prototypes.end())
		return it->second;

	return 0;
}
