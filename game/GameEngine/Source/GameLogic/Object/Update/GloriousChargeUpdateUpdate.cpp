// Retail [0x0025EC70,0x0025ED1B), 171 bytes, RET 0.
// Constructor 0x0025E890+0x3F installs vtable VA0x010B5530 at primary+0x10;
// its first entry is ILT0x0001C224 -> this update body. This class view is
// the UpdateInterface subobject, not the primary object layout.
// cl: /DNDEBUG /MD /EHsc
enum UpdateSleepTime {
    UPDATE_SLEEP_INVALID=0, UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff
};
class BfmeThingYY { public: void bfmeClearYY(unsigned int); };
class Rva0025EC70Conditions {
public:
    void reset(int bit) { words[bit>>5] &= ~(1U<<(bit&31)); }
    unsigned int words[10];
};
class Object {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual BfmeThingYY *slot28();
    void notifyModelConditionChanged();
    unsigned char prefix004[0x10c];
    Rva0025EC70Conditions conditions;
};
static __forceinline void clearCondition(Object *o,int bit) {
    if(o->conditions.words[bit>>5] & (1U<<(bit&31))) {
        o->conditions.reset(bit);
        o->notifyModelConditionChanged();
    }
}
class GameLogic {
public:
    unsigned char prefix[0x3c];
    unsigned int frame;
};
extern GameLogic *TheGameLogic;
struct Rva0025EC70Data {
    unsigned char prefix[0x258];
    unsigned int duration;
    UpdateSleepTime sleep;
};
class Rva0025EB90Owner {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot0a(); virtual void slot0b();
    virtual void slot0c(); virtual void slot34(); virtual void slot38();
    virtual void slot3c();
    Rva0025EC70Data *data;
    Object *object;
    // ILT0x0004315D -> full179B body at0x0025EB90, primary receiver, RET0.
    void clearAffected();
};
class GloriousChargeUpdate {
public:
    virtual UpdateSleepTime update();
    Object *getObject() const { return *(Object **)((char *)this-8); }
    Rva0025EC70Data *getData() const { return *(Rva0025EC70Data **)((char *)this-0xc); }
    unsigned char prefix004[0xd8];
    unsigned int deadline;
    bool active;
};
UpdateSleepTime GloriousChargeUpdate::update()
{
    Rva0025EB90Owner *owner=(Rva0025EB90Owner *)((char *)this-0x10);
    owner->clearAffected();
    if (!active) {
        if (!(getObject()->conditions.words[6] & 0x800))
            goto sleep;
        owner->slot34();
        deadline=getData()->duration+TheGameLogic->frame;
        active=true;
    }
    if(TheGameLogic->frame>=deadline) {
        active=false;
        clearCondition(getObject(),196);
        BfmeThingYY *result=getObject()->slot28();
        if(result) result->bfmeClearYY(0x10);
        return UPDATE_SLEEP_FOREVER;
    }
    owner->slot3c();
// Both the inactive path and active tick return the configured sleep value.
sleep:
    return getData()->sleep;
}
