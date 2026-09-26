// ?bfmeSetNeedsGateOpenRaw@Team@@QAEXHH@Z
// partial score=0.5 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// BFME Team::bfmeSetNeedsGateOpenRaw, retail RVA 0x000F1950.
// The Team keeps one object-ID set for gates that this team asks to stay open.
// A change in membership adjusts the matching GateOpenAndCloseBehavior request.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/NameKeyGenerator.h"
#include <set>

typedef int Int;

typedef _STL::set<NameKeyType> BfmeGateRequestSet;

extern NameKeyGenerator *TheNameKeyGenerator;

class Object
{
public:
	int getID() const;
	class Module *findModule(NameKeyType key);
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheBfmeGameLogic;

class Module
{
public:
	virtual ~Module();
};

class GateOpenAndCloseBehaviorBase
{
public:
	virtual void slot00() = 0;
};

class GateOpenAndCloseBehavior : public GateOpenAndCloseBehaviorBase, public Module
{
public:
	void adjustTeamGateRequest(Int delta);
};

class Team
{
private:
	unsigned char m_padding[0x104];
	BfmeGateRequestSet m_gateRequests;

public:
	void bfmeSetNeedsGateOpenRaw(Int gateID, Int needsOpen);
};

void Team::bfmeSetNeedsGateOpenRaw(Int gateID, Int needsOpen)
{
	BfmeGateRequestSet::const_iterator it = m_gateRequests.find((NameKeyType)gateID);
	const unsigned char needsOpenByte = *(const unsigned char *)&needsOpen;
	if ((it != m_gateRequests.end()) == needsOpenByte)
		return;

	if (needsOpenByte)
		m_gateRequests.insert((NameKeyType)gateID);
	else
		m_gateRequests.erase(it);

	Object *gate = TheBfmeGameLogic->findObjectByID(gateID);
	if (gate == 0)
		return;

	static NameKeyType gateBehaviorKey =
		TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	GateOpenAndCloseBehavior *behavior =
		static_cast<GateOpenAndCloseBehavior *>(gate->findModule(gateBehaviorKey));
	if (behavior != 0)
		behavior->adjustTeamGateRequest(needsOpenByte ? 1 : -1);
}
