// cl: /DNDEBUG /MD /EHsc
// Sixty 89-byte __thiscall destructors that differ ONLY in the two DIR32
// addresses they store into the object's vptr slot and in their own EH
// registration record.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame
//     mov [esi], <DERIVED VFTABLE>          ; derived vptr, dtor entry
//     eax = [esi+4]; ecx = [eax]
//     if (ecx) { edx=[ecx]; push 1; call [edx] }   ; virtual `delete`
//     eax = [esi+4]; [eax] = 0
//     mov [esi], <BASE VFTABLE>             ; inlined empty virtual ~Base
//
// WHAT THE BYTES SHOW.  Two vptr stores bracketing the body make this a
// DESTRUCTOR, not an ordinary member: the entry store publishes the derived
// vftable and the exit store publishes the base's, which is the whole of an
// inlined `virtual ~Base() {}` on a base whose only member is its vptr.  The
// derived vftables run at a FOUR-BYTE STRIDE across the sixty members, so each
// derived vftable holds exactly one slot -- the scalar deleting destructor --
// confirming the destructor is the only virtual function.  The base vftable is
// the SAME address in all sixty, so all sixty derive from one base.
//
// The call is `mov edx,[ecx] / push 1 / call [edx]`: slot 0 with flag 1 is the
// scalar deleting destructor, i.e. `delete` of a pointer to a class with a
// virtual destructor.  [esi+4] is reloaded after the call before the store of
// 0, so the source names it again rather than caching it -- two loads, one per
// mention.  The frame stores `this` at [esp+4] and sets the EH state to 0
// before the call, so an unwind funclet exists to run the base destructor if
// `delete` throws; that is what forces the SEH prolog and /EHsc.
//
// WHERE THE BYTES CANNOT DECIDE: `m_pp` is spelled as a pointer-to-pointer
// member.  A reference member (`Victim *&`) and a pointer to a struct whose
// first field is the victim pointer compile to the identical two loads; the
// pointer-to-pointer spelling asserts the least.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The two
// vftable addresses and the EH data address are DIR32 relocation sites, so the
// byte gate takes them from the target -- the shape, not the addresses, is what
// this file proves.

class BigOwnedVictim
{
public:
	virtual ~BigOwnedVictim();
};

class BigOwnedPtrBase
{
public:
	virtual ~BigOwnedPtrBase() {}
};

#define BFME_OWNED_POINTER_DTOR( NAME )                                   	class NAME : public BigOwnedPtrBase                                   	{                                                                     	public:                                                               		virtual ~NAME();                                                  		BigOwnedVictim **m_pp;                                            	};                                                                    	NAME::~NAME()                                                         	{                                                                     		if ( *m_pp )                                                      			delete *m_pp;                                                 		*m_pp = 0;                                                        	}

BFME_OWNED_POINTER_DTOR( Rva00070620 )

// SubsystemDeleter<T>.  The same shape as the macro above, instantiated per
// subsystem class.  The decorated names come from retail's incremental-link
// thunk table: ??1?$SubsystemDeleter@V<T>@@@@UAE@XZ, the paired scalar
// deleting destructor ??_G?$SubsystemDeleter@V<T>@@@@UAEPAXI@Z and the
// constructor ??0?$SubsystemDeleter@V<T>@@@@QAE@AAPAV<T>@@@Z fit 176 of 179
// ILT hash windows across 59 classes (expected false fits 0.23); see
// targets/game/reverse/identity_evidence/subsystem-deleter-ilt.md.  The
// constructor takes T *&, so m_pp holds the address of the subsystem's global
// pointer; it stays typed as BigOwnedVictim ** because only the template
// argument, not the member type, reaches the decorated name or the bytes.

template<class T>
class SubsystemDeleter : public BigOwnedPtrBase
{
public:
	virtual ~SubsystemDeleter();
	BigOwnedVictim **m_pp;
};

template<class T>
SubsystemDeleter<T>::~SubsystemDeleter()
{
	if ( *m_pp )
		delete *m_pp;
	*m_pp = 0;
}
class AI;
template SubsystemDeleter<AI>::~SubsystemDeleter();
class ActionManager;
template SubsystemDeleter<ActionManager>::~SubsystemDeleter();
class AerialPathfinder;
template SubsystemDeleter<AerialPathfinder>::~SubsystemDeleter();
class AptPlayer;
template SubsystemDeleter<AptPlayer>::~SubsystemDeleter();
class ArmorStore;
template SubsystemDeleter<ArmorStore>::~SubsystemDeleter();
class AttributeModifierStore;
template SubsystemDeleter<AttributeModifierStore>::~SubsystemDeleter();
class AudioManager;
template SubsystemDeleter<AudioManager>::~SubsystemDeleter();
class BuildAssistant;
template SubsystemDeleter<BuildAssistant>::~SubsystemDeleter();
class CDManagerInterface;
template SubsystemDeleter<CDManagerInterface>::~SubsystemDeleter();
class CaveSystem;
template SubsystemDeleter<CaveSystem>::~SubsystemDeleter();
class CrateSystem;
template SubsystemDeleter<CrateSystem>::~SubsystemDeleter();
class DamageFXStore;
template SubsystemDeleter<DamageFXStore>::~SubsystemDeleter();
class EmotionSystem;
template SubsystemDeleter<EmotionSystem>::~SubsystemDeleter();
class Eva;
template SubsystemDeleter<Eva>::~SubsystemDeleter();
class ExperienceLevelSystem;
template SubsystemDeleter<ExperienceLevelSystem>::~SubsystemDeleter();
class FXListStore;
template SubsystemDeleter<FXListStore>::~SubsystemDeleter();
class FunctionLexicon;
template SubsystemDeleter<FunctionLexicon>::~SubsystemDeleter();
class GameClient;
template SubsystemDeleter<GameClient>::~SubsystemDeleter();
class GameLogic;
template SubsystemDeleter<GameLogic>::~SubsystemDeleter();
class GameResultsInterface;
template SubsystemDeleter<GameResultsInterface>::~SubsystemDeleter();
class GameState;
template SubsystemDeleter<GameState>::~SubsystemDeleter();
class GameStateMap;
template SubsystemDeleter<GameStateMap>::~SubsystemDeleter();
class GameTextInterface;
template SubsystemDeleter<GameTextInterface>::~SubsystemDeleter();
class GlobalData;
template SubsystemDeleter<GlobalData>::~SubsystemDeleter();
class GlobalLanguage;
template SubsystemDeleter<GlobalLanguage>::~SubsystemDeleter();
class GlobalWeatherSystem;
template SubsystemDeleter<GlobalWeatherSystem>::~SubsystemDeleter();
class HouseColorSystem;
template SubsystemDeleter<HouseColorSystem>::~SubsystemDeleter();
class LightPointSystem;
template SubsystemDeleter<LightPointSystem>::~SubsystemDeleter();
class LivingWorldCampaignManager;
template SubsystemDeleter<LivingWorldCampaignManager>::~SubsystemDeleter();
class LivingWorldLogic;
template SubsystemDeleter<LivingWorldLogic>::~SubsystemDeleter();
class LivingWorldManager;
template SubsystemDeleter<LivingWorldManager>::~SubsystemDeleter();
class LocomotorStore;
template SubsystemDeleter<LocomotorStore>::~SubsystemDeleter();
class LuaScriptEngine;
template SubsystemDeleter<LuaScriptEngine>::~SubsystemDeleter();
class MessageStream;
template SubsystemDeleter<MessageStream>::~SubsystemDeleter();
class MetaMap;
template SubsystemDeleter<MetaMap>::~SubsystemDeleter();
class ModuleFactory;
template SubsystemDeleter<ModuleFactory>::~SubsystemDeleter();
class MultiplayerSettings;
template SubsystemDeleter<MultiplayerSettings>::~SubsystemDeleter();
class ObjectCreationListStore;
template SubsystemDeleter<ObjectCreationListStore>::~SubsystemDeleter();
class PlayerAITypeSet;
template SubsystemDeleter<PlayerAITypeSet>::~SubsystemDeleter();
class PlayerList;
template SubsystemDeleter<PlayerList>::~SubsystemDeleter();
class PlayerTemplateStore;
template SubsystemDeleter<PlayerTemplateStore>::~SubsystemDeleter();
class Radar;
template SubsystemDeleter<Radar>::~SubsystemDeleter();
class RankInfoStore;
template SubsystemDeleter<RankInfoStore>::~SubsystemDeleter();
class RecorderClass;
template SubsystemDeleter<RecorderClass>::~SubsystemDeleter();
class ScienceStore;
template SubsystemDeleter<ScienceStore>::~SubsystemDeleter();
class ScriptEngine;
template SubsystemDeleter<ScriptEngine>::~SubsystemDeleter();
class SidesList;
template SubsystemDeleter<SidesList>::~SubsystemDeleter();
class SpecialPowerStore;
template SubsystemDeleter<SpecialPowerStore>::~SubsystemDeleter();
class SplineService;
template SubsystemDeleter<SplineService>::~SubsystemDeleter();
class SubsystemLegend;
template SubsystemDeleter<SubsystemLegend>::~SubsystemDeleter();
class TaintManager;
template SubsystemDeleter<TaintManager>::~SubsystemDeleter();
class TeamFactory;
template SubsystemDeleter<TeamFactory>::~SubsystemDeleter();
class TerrainRoadCollection;
template SubsystemDeleter<TerrainRoadCollection>::~SubsystemDeleter();
class TerrainTypeCollection;
template SubsystemDeleter<TerrainTypeCollection>::~SubsystemDeleter();
class ThingFactory;
template SubsystemDeleter<ThingFactory>::~SubsystemDeleter();
class UpgradeCenter;
template SubsystemDeleter<UpgradeCenter>::~SubsystemDeleter();
class VictoryConditionsInterface;
template SubsystemDeleter<VictoryConditionsInterface>::~SubsystemDeleter();
class VictorySystem;
template SubsystemDeleter<VictorySystem>::~SubsystemDeleter();
class WeaponStore;
template SubsystemDeleter<WeaponStore>::~SubsystemDeleter();
