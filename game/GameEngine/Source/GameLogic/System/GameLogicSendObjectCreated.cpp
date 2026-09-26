// cl: /DNDEBUG /MD /EHsc
// GameLogic::sendObjectCreated, retail RVA 0x0038B1B0, 207 bytes.
// Object initialization calls ILT 0x3DC99 at 0x1C688A with TheGameLogic and
// the new Object. The corresponding Object::initObject source names this
// notification. Retail creates the drawable, binds both sides, then dispatches
// Lua event 12 through the already recovered 0x2E7650 wrapper.

class BfmeDelayedLuaEvent {
public:
    BfmeDelayedLuaEvent();
    ~BfmeDelayedLuaEvent();
    char data[0x18];
};

// Constructor EDBB0 constructs three 24-byte events at +4. Destructor EDC40
// destroys them and restores base vtable 01073744. It does not install the
// derived vtable on entry. This destructor view preserves that behavior and
// its base cleanup state when inlined; the base's original name is unknown.
class BfmeDelayedLuaEventListBase {
public:
    virtual ~BfmeDelayedLuaEventListBase() {}
};
class __declspec(novtable) DelayedLuaEventList : public BfmeDelayedLuaEventListBase {
public:
    DelayedLuaEventList();
    __forceinline ~DelayedLuaEventList() {}
    BfmeDelayedLuaEvent events[3];
};

class ThingTemplate {
public:
    ThingTemplate *getFinalOverride();
    char pad0[4];
    ThingTemplate *overrideTemplate;
};
class Object {
public:
    ThingTemplate *getTemplate() const {
        ThingTemplate *t = thingTemplate;
        if (t && t->overrideTemplate)
            t = t->overrideTemplate->getFinalOverride();
        return t;
    }
    char pad0[4];
    ThingTemplate *thingTemplate;
    char pad8[0x8C];
    unsigned status;
};
class Drawable;
enum DrawableStatus { DRAWABLE_STATUS_NONE = 0, DRAWABLE_STATUS_UNK20 = 0x20 };
class BFMEThingFactory {
public:
    Drawable *newDrawable(const ThingTemplate *, DrawableStatus, int);
};
extern void *g_global12EF1D8;
class BfmeOwnerBR {
public:
    void bfmeGo939B(int, Object *, DelayedLuaEventList *);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
int GetGameLogicRandomValue(int, int, const char *, int);
class GameLogic {
public:
    void sendObjectCreated(Object *);
    void bindObjectAndDrawable(Object *, Drawable *);
};

void GameLogic::sendObjectCreated(Object *obj)
{
    int randomValue = GetGameLogicRandomValue(1, 999,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\System\\GameLogic.cpp", 0x1697);
    DrawableStatus status = DRAWABLE_STATUS_NONE;
    if (obj->status & 0x400000)
        status = DRAWABLE_STATUS_UNK20;
    Drawable *draw = static_cast<BFMEThingFactory *>(g_global12EF1D8)->newDrawable(
        obj->getTemplate(), status, randomValue);
    bindObjectAndDrawable(obj, draw);
    DelayedLuaEventList events;
    reinterpret_cast<BfmeOwnerBR *>(TheLuaScriptEngine)->bfmeGo939B(12, obj, &events);
}
