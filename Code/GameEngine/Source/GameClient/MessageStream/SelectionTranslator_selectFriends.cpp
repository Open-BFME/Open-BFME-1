// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Exact BFME retail implementation of SelectionTranslator::selectFriends at 0x005B8230.
// stlport
#define UnicodeString ZHUnicodeString
#define SelectionTranslator BfmeSelectionTranslator
#define Matrix4x4 Matrix4
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"

#include "Common/MessageStream.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"
#include "GameClient/InGameUI.h"
#include "GameClient/SelectionXlat.h"
#undef UnicodeString

class BfmeSelectFriendsUnicodeBase
{
    friend class UnicodeString;
private:
    BfmeSelectFriendsUnicodeBase(const WideChar *text);
    BfmeSelectFriendsUnicodeBase(const BfmeSelectFriendsUnicodeBase &other);
    void releaseBuffer();
};

class UnicodeString
{
public:
    UnicodeString() : m_text(0) {}
    explicit UnicodeString(const WideChar *text)
    {
        ((BfmeSelectFriendsUnicodeBase *)this)->
            BfmeSelectFriendsUnicodeBase::BfmeSelectFriendsUnicodeBase(text);
    }
    UnicodeString(const UnicodeString &other)
    {
        ((BfmeSelectFriendsUnicodeBase *)this)->
            BfmeSelectFriendsUnicodeBase::BfmeSelectFriendsUnicodeBase(
                *(const BfmeSelectFriendsUnicodeBase *)&other);
    }
    ~UnicodeString()
    {
        ((BfmeSelectFriendsUnicodeBase *)this)->
            BfmeSelectFriendsUnicodeBase::releaseBuffer();
    }
    void format(UnicodeString format, ...);
private:
    WideChar *m_text;
};

// BFME adds virtuals to InGameUI that are absent from the Zero Hour reference
// header.  This local view preserves the retail slots used by this body.
class BfmeSelectFriendsInGameUI
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12();
    virtual void message(UnicodeString format, ...);
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
    virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
    virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
    virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
    virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
    virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
    virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
    virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
    virtual void slot54(); virtual void slot55();
    virtual void selectDrawable(Drawable *draw);
    virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual Int getSelectCount();
    virtual Int getMaxSelectCount();
};

extern Bool CanSelectDrawable(const Drawable *draw, Bool dragSelecting);
extern const WideChar BFMEEmptyUnicodeString;

class BfmeSelectFriendsUnicodeString
{
public:
    static const WideChar *str(const ZHUnicodeString &text)
    {
        char *data = *reinterpret_cast<char *const *>(&text);
        return data ? reinterpret_cast<const WideChar *>(data + 8)
                    : &BFMEEmptyUnicodeString;
    }
};

class BfmeSelectFriendsDrawable
{
private:
    void *m_vtable;
    const ThingTemplate *m_template;
    unsigned char m_opaque[0xFC - 8];
    Object *m_object;

public:
    const ThingTemplate *getTemplate() const
    {
        if (m_template == 0)
            return 0;
        return static_cast<const ThingTemplate *>(
            reinterpret_cast<const Overridable *>(m_template)->getFinalOverride());
    }

    Object *getObject() const { return m_object; }
};

Bool SelectionTranslator::selectFriends(Drawable *draw, GameMessage *createTeamMsg,
                                        Bool dragSelecting)
{
    if (CanSelectDrawable(draw, dragSelecting))
    {
        if (reinterpret_cast<BfmeSelectFriendsInGameUI *>(TheInGameUI)->getMaxSelectCount() > 0
            && reinterpret_cast<BfmeSelectFriendsInGameUI *>(TheInGameUI)->getSelectCount()
                >= reinterpret_cast<BfmeSelectFriendsInGameUI *>(TheInGameUI)->getMaxSelectCount())
        {
            if (!m_displayedMaxWarning)
            {
                m_displayedMaxWarning = TRUE;
                UnicodeString msg;
                msg.format(
                    UnicodeString(BfmeSelectFriendsUnicodeString::str(
                        TheGameText->fetch("GUI:MaxSelectionSize"))),
                    reinterpret_cast<BfmeSelectFriendsInGameUI *>(TheInGameUI)->getMaxSelectCount());
                reinterpret_cast<BfmeSelectFriendsInGameUI *>(TheInGameUI)->message(msg);
            }
            return FALSE;
        }

        const BfmeSelectFriendsDrawable *bfmeDraw =
            reinterpret_cast<const BfmeSelectFriendsDrawable *>(draw);
        m_selectCountMap[bfmeDraw->getTemplate()]++;

        if (bfmeDraw->getObject() && createTeamMsg)
            createTeamMsg->appendObjectIDArgument(bfmeDraw->getObject()->getID());

        reinterpret_cast<BfmeSelectFriendsInGameUI *>(TheInGameUI)->selectDrawable(draw);
        return TRUE;
    }

    return FALSE;
}
