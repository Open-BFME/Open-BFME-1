typedef bool Bool;
typedef unsigned int UnsignedInt;

const Bool FALSE = 0;
const Bool TRUE = 1;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x;
    float y;
    float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
    int x;
    int y;
};

enum KindOfType
{
    KINDOF_SELECTABLE = 1,
    KINDOF_STRUCTURE = 7,
    KINDOF_DOZER = 14,
    KINDOF_ALWAYS_SELECTABLE = 57,
    KINDOF_FORCEATTACKABLE = 67,
    // Retail performs this additional BFME-only rejection after the
    // SELECTABLE/FORCEATTACKABLE pair. The enum name is intentionally
    // descriptive until the underlying KindOf name is independently proven.
    KINDOF_BFME_SELECTION_REJECTED = 0x85
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
private:
    void *m_vtable;
    const Overridable *m_nextOverride;

public:
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride != 0)
            return m_nextOverride->getFinalOverride();
        return this;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
private:
    unsigned char m_opaque[0x4CA - sizeof(Overridable)];
    Bool m_allowsSelectionWhenEffectivelyDead;

public:
    Bool allowsSelectionWhenEffectivelyDead() const
    {
        return m_allowsSelectionWhenEffectivelyDead;
    }
};

template <class T> class OverridePtr
{
private:
    const T *m_overridable;

public:
    operator const T *() const
    {
        if (m_overridable == 0)
            return 0;
        return static_cast<const T *>(m_overridable->getFinalOverride());
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
private:
    void *m_vtable;
    OverridePtr<ThingTemplate> m_template;

public:
    const ThingTemplate *getTemplate() const { return m_template; }
    Bool isKindOf(KindOfType kind) const;
    const Coord3D *getPosition() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
private:
    unsigned char m_opaque[0x344 - sizeof(Thing)];
    Bool m_effectivelyDead;
    Bool m_selectionSuppressed;

public:
    Bool isEffectivelyDead() const { return (m_effectivelyDead & 1) != 0; }
    Bool isSelectionSuppressed() const { return m_selectionSuppressed; }
    Bool isSelectable() const;
    Bool isLocallyControlled() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public Thing
{
private:
    unsigned char m_opaque[0xFC - sizeof(Thing)];
    Object *m_object;

public:
    const Object *getObject() const { return m_object; }
    Bool isDrawableEffectivelyHidden() const;
};

// The helpers below intentionally name only the behavior proved by the call
// sites. Their internal BFME layouts remain opaque in this translation unit
// rather than borrowing Zero Hour's incompatible Object and Drawable layouts.
class BFMESelectionDrawablePositionView
{
public:
    const Coord3D *getPosition() const;
};

class BFMESelectionObjectStatus
{
public:
    Bool testStatus(int status) const;
};

class BFMESelectionStatusBits
{
public:
    Bool test(UnsignedInt bit) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
    UnsignedInt winGetStatus();
    GameWindow *winGetParent();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
{
public:
    Bool worldToScreen(const Coord3D *world, ICoord2D *screen);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot0A() = 0;
    virtual void slot0B() = 0;
    virtual void slot0C() = 0;
    virtual void slot0D() = 0;
    virtual void slot0E() = 0;
    virtual void slot0F() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot1A() = 0;
    virtual void slot1B() = 0;
    virtual void slot1C() = 0;
    virtual void slot1D() = 0;
    virtual void slot1E() = 0;
    virtual void slot1F() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot2A() = 0;
    virtual void slot2B() = 0;
    virtual void slot2C() = 0;
    virtual void slot2D() = 0;
    virtual void slot2E() = 0;
    virtual void slot2F() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot3A() = 0;
    virtual void slot3B() = 0;
    virtual void slot3C() = 0;
    virtual void slot3D() = 0;
    virtual void slot3E() = 0;
    virtual void slot3F() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual GameWindow *getWindowUnderCursor(int x, int y, Bool ignoreHidden) = 0;
};

extern GameWindowManager *TheWindowManager;
extern View *TheTacticalView;

Bool CanSelectDrawable(const Drawable *draw, Bool dragSelecting)
{
    if (draw == 0 || draw->getObject() == 0)
        return FALSE;

    const Object *obj = draw->getObject();

    if (obj->isEffectivelyDead()
        && !obj->getTemplate()->allowsSelectionWhenEffectivelyDead()
        && !obj->isKindOf(KINDOF_ALWAYS_SELECTABLE))
        return FALSE;

    if (!obj->isKindOf(KINDOF_SELECTABLE) && obj->isKindOf(KINDOF_FORCEATTACKABLE))
        return FALSE;

    if (obj->isKindOf(KINDOF_BFME_SELECTION_REJECTED))
        return FALSE;

    if (draw->isDrawableEffectivelyHidden())
        return FALSE;

    GameWindow *window = 0;
    if (TheWindowManager != 0)
    {
        const Coord3D *position =
            reinterpret_cast<const BFMESelectionDrawablePositionView *>(draw)->getPosition();
        ICoord2D screen;
        TheTacticalView->worldToScreen(position, &screen);
        window = TheWindowManager->getWindowUnderCursor(screen.x, screen.y, FALSE);
    }

    while (window != 0)
    {
        if ((window->winGetStatus() & 0x10000) == 0)
            return FALSE;
        window = window->winGetParent();
    }

    if (dragSelecting
        && (obj->isKindOf(KINDOF_STRUCTURE)
            || (obj->isKindOf(KINDOF_DOZER)
                && reinterpret_cast<const BFMESelectionStatusBits *>(obj)->test(0x48))))
        return FALSE;

    if (reinterpret_cast<const BFMESelectionObjectStatus *>(obj)->testStatus(3))
        return FALSE;

    if (obj->isSelectionSuppressed())
        return FALSE;

    if (!obj->isSelectable())
        return FALSE;

    if (dragSelecting && !obj->isLocallyControlled())
        return FALSE;

    return TRUE;
}
