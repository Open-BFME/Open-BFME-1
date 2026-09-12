// cl: /ICode/GameEngine/Include/Precompiled /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME ThingTemplate::calcTimeToBuild, RVA0x00144AB0 /619 bytes.
// DozerActionDoActionState::update passes the controlling Player and -1 override
// through ILT0x0004B01F. Retail consumes both arguments and ends with ret8.
// BFME uses integer build-time stages, a 36-byte prerequisite vector, and
// player-count scaling in multiplayer/skirmish before the final floor(*5).
// The existing PreRTS fast_float2long_round helper implements the final x87
// conversion used by retail; no assembly is introduced by this conversion.
// Gen_00083240 and PlayerList::unidentified_000df510 deliberately retain the
// existing address-derived names: their complete semantic identities are unknown.
#include "PreRTS.h"
#include <vector>
class Player; class ThingTemplate;
class AsciiString { public: void *data; };
class Overridable {
public:
    void *vptr;
    const Overridable *next;
    const Overridable *friend_getFinalOverride() const {
        if (next) return next->friend_getFinalOverride();
        return this;
    }
};
class Handicap { public: enum HandicapType { BUILDTIME=1 }; float getHandicap(HandicapType,const ThingTemplate *) const; };
class Energy { public: float getEnergySupplyRatio() const; };
class Player {
public:
    char pad00[0xc]; Handicap handicap; char pad0D[0x97]; Energy energy;
    const Handicap *getHandicap() const { return &handicap; }
    const Energy *getEnergy() const { return &energy; }
    float getProductionTimeChangePercent(const AsciiString &) const;
    void countObjectsByThingTemplate(int,const ThingTemplate *const *,bool,int *,bool) const;
};
class ProductionPrerequisite {
    char data[36];
public: const ThingTemplate *getExistingBuildFacilityTemplate(const Player *) const;
};
class Gen_00083240 { public: float bfmeGet180(int) const; float bfmeGet200(int) const; };
class GlobalData {
public:
    // Runtime GlobalData fields; these are loaded values, not fixed defaults.
    char pad00[0xb3c]; float minLowEnergyProductionSpeed,maxLowEnergyProductionSpeed,lowEnergyPenaltyModifier,multipleFactory;
    char padB4C[0x394]; Gen_00083240 populationModifiers; //+0xEE0
};
class GameLogic { public: bool _bfme_isInMultiplayerOrSkirmishGame(); };
class PlayerList { public: int unidentified_000df510(bool); };
extern GlobalData *TheGlobalData;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
template<class T> inline const T &min(const T&a,const T&b) { return a<b?a:b; }
template<class T> inline const T &max(const T&a,const T&b) { return a>b?a:b; }
class ThingTemplate : public Overridable {
public:
    char pad08[0x18]; AsciiString name;
    char pad24[0xa4]; unsigned int kindOfWord0;
    char padCC[0x1f8]; _STL::vector<ProductionPrerequisite> prerequisites;
    char pad2D0[0xec]; float buildTime;
    char pad3C0[0xd3]; char buildCompletion;
    float getBuildTime() const {
        const ThingTemplate *t=next ? (const ThingTemplate*)next->friend_getFinalOverride() : this;
        return (t?t:this)->buildTime;
    }
    const ThingTemplate *getBuildFacilityTemplate(const Player *player) const {
        if ((int)prerequisites.size()>0) return prerequisites[0].getExistingBuildFacilityTemplate(player);
        return 0;
    }
    int calcTimeToBuild(const Player *,int) const;
};
int ThingTemplate::calcTimeToBuild(const Player *player,int overrideTime) const
{
    float rawBuildTime;
    if (overrideTime==-1) rawBuildTime=getBuildTime();
    else rawBuildTime=(float)overrideTime;
    // Keep the per-stage integer truncations; combining these float products
    // changes gameplay and does not reproduce the retail compiler output.
    int buildTime=rawBuildTime;
    buildTime*=player->getHandicap()->getHandicap(Handicap::BUILDTIME,this);
    float factionModifier=1+player->getProductionTimeChangePercent(name);
    buildTime*=factionModifier;
    float energyPercent=player->getEnergy()->getEnergySupplyRatio();
    if(energyPercent>1.0f) energyPercent=1.0f;
    float energyShort=1.0f-energyPercent;
    energyShort*=TheGlobalData->lowEnergyPenaltyModifier;
    float penaltyRate=1.0f-energyShort;
    penaltyRate=max(penaltyRate,TheGlobalData->minLowEnergyProductionSpeed);
    if(energyPercent<1.0f) penaltyRate=min(penaltyRate,TheGlobalData->maxLowEnergyProductionSpeed);
    if(penaltyRate<=0.0f) penaltyRate=0.01f;
    buildTime/=penaltyRate;
    if(buildCompletion==1) {
        const ThingTemplate *facility=getBuildFacilityTemplate(player);
        int count=0;
        if(facility) {
            player->countObjectsByThingTemplate(1,&facility,false,&count,true);
            float mult=TheGlobalData->multipleFactory;
            if(mult>0.0f) {
                for(int i=0;i<count-1;++i) buildTime*=mult;
            }
        }
    }
    if(TheGameLogic->_bfme_isInMultiplayerOrSkirmishGame()) {
        int players=ThePlayerList->unidentified_000df510(false);
        float modifier;
        if(kindOfWord0&0x80) modifier=TheGlobalData->populationModifiers.bfmeGet200(players);
        else modifier=TheGlobalData->populationModifiers.bfmeGet180(players);
        buildTime*=modifier;
    }
    return fast_float2long_round((float)floor((double)(buildTime*5)));
}
