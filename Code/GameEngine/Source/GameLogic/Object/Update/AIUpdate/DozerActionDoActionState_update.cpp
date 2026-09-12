// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME DozerActionDoActionState::update, 0x002B8FF0 / 1936B.
// Identity: ctor 0x002B73E0 names this state and installs vtable VA0x010C6E20;
// slot +0x18 routes through ILT0x0001C8B4 to this complete 1936-byte body.
// TU-local BFME layouts retain the retail interface slots. Object model flags
// are BitFlags<304> at +0x110; actively constructing is bit72 (word+0x118).
// This state drives construction and repair, sounds, bridge scaffolding,
// completion notifications, and the builder's Drawable voice-response list.
// All81 relocation sites and the eight-state EH map are independently checked.
// EH: FuncInfo VA0x01202B90; unwind map VA0x01202B50; handler VA0x01013530.
#include <list>
#include <bitset>
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
struct Coord3D { float x,y,z; };
template<int N> class BitFlags { _STL::bitset<N> bits; public: enum BogusInitType { INIT=0 }; BitFlags(BogusInitType,int,int,int); bool test(int i) const { return bits.test(i); } void set(int i) { bits.set(i); } };
typedef BitFlags<304> ModelConditionFlags;
enum ObjectStatusTypes { OBJECT_STATUS_UNDER_CONSTRUCTION=2, OBJECT_STATUS_RECONSTRUCTING=21 };
enum KindOfType { KINDOF_BRIDGE_TOWER=24 };
enum RadarEventType { RADAR_EVENT_CONSTRUCTION=1 };
class Object; class Player; class Drawable; class AIUpdateInterface; class DozerAIInterface;
class BodyModuleInterface; class AudioEventRTS; class PickAndPlayInfo;
template<typename T> class StringBase {
    friend class AsciiString; friend class UnicodeString;
    struct Data { int refs; unsigned short length,capacity; T text[1]; };
    Data *m_data;
    StringBase() : m_data(0) {}
    StringBase(const T *);
    StringBase(const StringBase &);
    ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
public: void set(const StringBase &);
};
class AsciiString : private StringBase<char> {
public:
    AsciiString(const char *s) : StringBase<char>(s) {}
    AsciiString(const AsciiString &s) : StringBase<char>(s) {}
    ~AsciiString() {}
    const char *str() const { return m_data ? m_data->text : ""; }
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString() {}
    UnicodeString(const unsigned short *s) : StringBase<unsigned short>(s) {}
    UnicodeString(const UnicodeString &s) : StringBase<unsigned short>(s) {}
    ~UnicodeString() {}
    UnicodeString &operator=(const UnicodeString &s) { set(s); return *this; }
    const unsigned short *str() const { return m_data ? m_data->text : (const unsigned short *)L""; }
    bool isEmpty() const;
    void format(UnicodeString, ...);
};
class ThingTemplate {
public:
    char pad00[0xc]; UnicodeString displayName;
    char pad10[0x10]; AsciiString name;
    int calcTimeToBuild(const Player *,int) const;
};
enum DozerTask { DOZER_TASK_BUILD,DOZER_TASK_REPAIR,DOZER_TASK_FORTIFY };
enum StateReturnType { STATE_FAILURE=-2,STATE_SUCCESS=-1,STATE_CONTINUE=0 };
enum CommandSourceType { CMD_FROM_AI=2 };
class AICommandInterface { public: void aiMoveToPosition(const Coord3D *,CommandSourceType); void aiFaceObject(Object *,CommandSourceType); void aiIdle(CommandSourceType); };
class Drawable {
public:
    virtual void slot00();
    const AudioEventRTS *getPerUnitSound(const AsciiString &) const;
    char getDisplayName(UnicodeString &) const;
};
class DozerAIInterface {
public:
    virtual void slot00();
    virtual float getRepairHealthPerSecond() const;
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual bool getIsRebuild() const;
    virtual void slot0C();
    virtual void cancelTask(DozerTask);
    virtual void internalTaskComplete(DozerTask);
    virtual void slot0F();
    virtual void slot10();
    virtual const Coord3D *getDockPoint(DozerTask,int);
    virtual void setBuildSubTask(int);
    virtual int getBuildSubTask() const;
    virtual void slot14();
    virtual void createBridgeScaffolding(Object *);
    virtual void slot16();
    virtual void startBuildingSound(const AudioEventRTS *,unsigned int);
    virtual void finishBuildingSound();

};
class AIUpdateInterface {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void slot0E();
    virtual void slot0F();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot1A();
    virtual void slot1B();
    virtual void slot1C();
    virtual void slot1D();
    virtual void slot1E();
    virtual void slot1F();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot2A();
    virtual void slot2B();
    virtual void slot2C();
    virtual void slot2D();
    virtual void slot2E();
    virtual void slot2F();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot3A();
    virtual void slot3B();
    virtual void slot3C();
    virtual void slot3D();
    virtual void slot3E();
    virtual void slot3F();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot4A();
    virtual void slot4B();
    virtual void slot4C();
    virtual void slot4D();
    virtual void slot4E();
    virtual DozerAIInterface *getDozerAIInterface();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot5A();
    virtual void slot5B();
    virtual void slot5C();
    virtual void slot5D();
    virtual void slot5E();
    virtual void slot5F();
    virtual bool isIdle() const;
    AICommandInterface *commands() { return (AICommandInterface *)((char *)this+0x20); }
};
class BodyModuleInterface {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual float getHealth() const;
    virtual void slot05();
    virtual float getMaxHealth() const;
    virtual void slot07();
    virtual int getDamageState() const;
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void slot0E();
    virtual void slot0F();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot1A();
    virtual void slot1B();
    virtual void slot1C();
    virtual void slot1D();
    virtual void slot1E();
    virtual void slot1F();
    virtual void internalChangeHealth(float,bool);
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void evaluateVisualCondition();

};
class CreateModuleInterface {
public:
    virtual void slot00();
    virtual void onBuildComplete();

};
class BehaviorInterfaces {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual CreateModuleInterface *getCreate();

};
class BehaviorModule { public: char pad[0xc]; BehaviorInterfaces interfaces; };
// Both Object and Drawable use Thing's primary vptr. Keeping this base
// polymorphic preserves the zero adjustment for the inherited query calls.
class Thing { public: virtual void slot00(); const ThingTemplate *getTemplate() const; bool isKindOf(KindOfType) const; };
class Object : public Thing {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual Drawable *getDrawable();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void slot0E();
    virtual void slot0F();
    virtual void slot10();
    virtual bool attemptHealingFromSoleBenefactor(float,Object *,int);
    char pad04[0x34]; Coord3D position;
    char pad44[0x30]; unsigned int id,producerID,builderID;
    char pad80[0x90]; ModelConditionFlags modelFlags;
    char padAfterFlags[0x6c]; unsigned int disabledFlags;
    char pad1A8[0x48]; BehaviorModule **behaviorModules;
    char pad1F4[0xc]; BodyModuleInterface *body; AIUpdateInterface *ai;
    char pad208[0x18]; float constructionPercent;
    char pad224[0x120]; unsigned int specialFlags;
    Player *getControllingPlayer() const;
    void setProducer(const Object *); void setBuilder(const Object *);
    void clearStatus(ObjectStatusTypes); void clearModelConditionFlags(const ModelConditionFlags &);
    bool isLocallyControlled() const;
    void notifyModelConditionChanged();
    __forceinline void setActivelyConstructing() {
        if (!modelFlags.test(72)) { modelFlags.set(72); notifyModelConditionChanged(); }
    }
    unsigned int getID() const { return id; }
    const Coord3D *getPosition() const { return &position; }
    BodyModuleInterface *getBodyModule() const { return body; }
    AIUpdateInterface *getAIUpdateInterface() const { return ai; }
    float getConstructionPercent() const { return constructionPercent; }
    void setConstructionPercent(float value) { constructionPercent=value; }
};
class StateMachine {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void setGoalObject(Object *);
    char pad04[0xc]; Object *owner;
    Object *getGoalObject();
};
class GameTextInterface {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual UnicodeString fetch(const char *,bool *);

};
class InGameUI {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void __cdecl message(UnicodeString,...);
    virtual void __cdecl message(AsciiString,...);

};
class BridgeTowerBehaviorInterface {
public:
    virtual void slot00();
    virtual unsigned int getBridgeID();

};
class BridgeBehaviorInterface {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual bool isScaffoldInMotion();

};

class BridgeTowerBehavior { public: static BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterfaceFromObject(Object *); };
class BridgeBehavior { public: static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *); };
class GameLogic { public: Object *findObjectByID(int); };
class Player { public: void onStructureConstructionComplete(Object *,Object *,bool); };
class Radar { public: void createEvent(const Coord3D *,RadarEventType,float); };
class GameMessage { public: enum Type { MSG_CONSTRUCTION_COMPLETE=0x7de }; };
typedef _STL::list<Drawable *> DrawableList;
void pickAndPlayUnitVoiceResponse(const DrawableList *,GameMessage::Type,PickAndPlayInfo *);
extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;
extern GameLogic *TheGameLogic;
extern Radar *TheRadar;
class DozerActionDoActionState {
public:
    virtual StateReturnType update();
    char pad04[0x18]; StateMachine *machine; unsigned int unknown20; DozerTask task;
    Object *getMachineGoalObject() { return machine->getGoalObject(); }
    Object *getMachineOwner() { return machine->owner; }
};
StateReturnType DozerActionDoActionState::update()
{
    Object *goalObject = getMachineGoalObject();
    Object *dozer = getMachineOwner();
    AIUpdateInterface *ai = dozer->getAIUpdateInterface();
    if (!ai) return STATE_FAILURE;
    DozerAIInterface *dozerAI = ai->getDozerAIInterface();
    if (!dozerAI) return STATE_FAILURE;
    if (!goalObject) return STATE_FAILURE;
    Drawable *drawable = goalObject->getDrawable();
    unsigned int disabled = dozer->disabledFlags;
    // Preserve the complete disabled-mask read before testing UNMANNED. This
    // MSVC intrinsic emits no instruction; the retail body materializes EAX.
    _WriteBarrier();
    if (disabled & 0x20) return STATE_FAILURE;
    bool complete = false;
    switch (task) {
    case DOZER_TASK_BUILD: {
        if (dozer->getControllingPlayer() != goalObject->getControllingPlayer())
            return STATE_FAILURE;
        if (dozerAI->getBuildSubTask() == 0) {
            const Coord3D *dockLocation = dozerAI->getDockPoint(task,1);
            if (dockLocation) ai->commands()->aiMoveToPosition(dockLocation,CMD_FROM_AI);
            dozerAI->setBuildSubTask(1);
        }
        if (dozerAI->getBuildSubTask() == 1 && ai->isIdle()) {
            dozerAI->setBuildSubTask(2);
            ai->commands()->aiFaceObject(goalObject,CMD_FROM_AI);
        }
        if (dozerAI->getBuildSubTask() == 2 && ai->isIdle()) {
            dozerAI->setBuildSubTask(3);
            if (drawable)
                dozerAI->startBuildingSound(drawable->getPerUnitSound("UnderConstruction"),goalObject->getID());
        }
        if (dozerAI->getBuildSubTask() == 3) {
            dozer->setActivelyConstructing();
            if (goalObject->specialFlags & 1) {
                dozerAI->cancelTask(DOZER_TASK_BUILD);
                ai->commands()->aiIdle(CMD_FROM_AI);
                break;
            }
            if (goalObject->getConstructionPercent() == -1.0f) { complete=true; break; }
            int framesToBuild=goalObject->getTemplate()->calcTimeToBuild(dozer->getControllingPlayer(),-1);
            float percentProgressThisFrame = 100.0f / framesToBuild;
            goalObject->setConstructionPercent(goalObject->getConstructionPercent()+percentProgressThisFrame);
            BodyModuleInterface *body=goalObject->getBodyModule();
            body->internalChangeHealth(body->getMaxHealth() / (float)framesToBuild,false);
            if (!goalObject->producerID) goalObject->setProducer(dozer);
            if (!goalObject->builderID) goalObject->setBuilder(dozer);
            if (goalObject->getConstructionPercent() >= 100.0f) {
                goalObject->clearStatus(OBJECT_STATUS_UNDER_CONSTRUCTION);
                goalObject->clearStatus(OBJECT_STATUS_RECONSTRUCTING);
                dozerAI->finishBuildingSound();
                goalObject->clearModelConditionFlags(ModelConditionFlags(ModelConditionFlags::INIT,66,67,68));
                goalObject->setConstructionPercent(-1.0f);
                body->evaluateVisualCondition();
                Player *player=goalObject->getControllingPlayer();
                if (player) {
                    player->onStructureConstructionComplete(dozer,goalObject,dozerAI->getIsRebuild());
                    for (BehaviorModule **m=goalObject->behaviorModules; *m; ++m) {
                        CreateModuleInterface *create=(*m)->interfaces.getCreate();
                        if (create) create->onBuildComplete();
                    }
                }
                if (dozer->isLocallyControlled()) {
                    UnicodeString format=TheGameText->fetch("DOZER:ConstructionComplete",0);
                    UnicodeString objectName;
                    Drawable *draw=goalObject->getDrawable();
                    objectName = (draw && draw->getDisplayName(objectName)) ? objectName : goalObject->getTemplate()->displayName;
                    if (objectName.isEmpty()) {
                        UnicodeString format=TheGameText->fetch("INI:MissingDisplayName",0);
                        objectName.format(format,goalObject->getTemplate()->name.str());
                    }
                    UnicodeString msg;
                    msg.format(format.str(),objectName.str());
                    TheInGameUI->message(msg);
                    DrawableList list;
                    list.push_back(dozer->getDrawable());
                    pickAndPlayUnitVoiceResponse(&list,GameMessage::MSG_CONSTRUCTION_COMPLETE,0);
                    TheRadar->createEvent(goalObject->getPosition(),RADAR_EVENT_CONSTRUCTION,4.0f);
                }
                complete=true;
            }
        }
        break;
    }
    case DOZER_TASK_REPAIR: {
        BodyModuleInterface *body=goalObject->getBodyModule();
        if (dozerAI->getBuildSubTask() == 0) {
            const Coord3D *dockLocation=dozerAI->getDockPoint(task,1);
            if (dockLocation) ai->commands()->aiMoveToPosition(dockLocation,CMD_FROM_AI);
            dozerAI->setBuildSubTask(1);
        }
        if (dozerAI->getBuildSubTask() == 1 && ai->isIdle()) {
            dozerAI->setBuildSubTask(2);
            ai->commands()->aiFaceObject(goalObject,CMD_FROM_AI);
        }
        if (dozerAI->getBuildSubTask() == 2 && ai->isIdle()) {
            dozerAI->setBuildSubTask(3);
            if (drawable) {
                if (body->getDamageState() == 3)
                    dozerAI->startBuildingSound(drawable->getPerUnitSound("UnderRepairFromRubble"),goalObject->getID());
                else
                    dozerAI->startBuildingSound(drawable->getPerUnitSound("UnderRepairFromDamage"),goalObject->getID());
            }
        }
        if (dozerAI->getBuildSubTask() == 3) {
            if (body->getHealth() == body->getMaxHealth()) {
                TheInGameUI->message("DOZER:RepairComplete");
                dozerAI->finishBuildingSound();
                complete=true;
            } else {
                bool canHeal=true;
                if (goalObject->isKindOf(KINDOF_BRIDGE_TOWER)) dozerAI->createBridgeScaffolding(goalObject);
                dozer->setActivelyConstructing();
                if (goalObject->isKindOf(KINDOF_BRIDGE_TOWER)) {
                    BridgeTowerBehaviorInterface *tower=BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(goalObject);
                    Object *bridge=TheGameLogic->findObjectByID(tower->getBridgeID());
                    BridgeBehaviorInterface *bridgeBehavior=BridgeBehavior::getBridgeBehaviorInterfaceFromObject(bridge);
                    if (bridgeBehavior->isScaffoldInMotion() == true) canHeal=false;
                }
                if (canHeal) {
                    float health=body->getMaxHealth()*dozerAI->getRepairHealthPerSecond()*0.2f;
                    if (!goalObject->attemptHealingFromSoleBenefactor(health,dozer,2)) {
                        dozerAI->internalTaskComplete(task);
                        machine->setGoalObject(0);
                        return STATE_FAILURE;
                    }
                }
            }
        }
        break;
    }
    case DOZER_TASK_FORTIFY: break;
    default: return STATE_FAILURE;
    }
    if (complete == true) {
        dozerAI->internalTaskComplete(task);
        machine->setGoalObject(0);
        return STATE_SUCCESS;
    }
    return STATE_CONTINUE;
}
