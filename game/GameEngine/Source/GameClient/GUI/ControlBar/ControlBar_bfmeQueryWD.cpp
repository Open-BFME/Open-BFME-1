// Open-BFME5: clean C++ reconstruction of the purchase-science query helper.
// The Player and PlayerTemplate offsets used here are BFME witnesses from
// tools/bfme_layout.py --grep Player --grep PlayerTemplate and the retail
// caller at ControlBar::populatePurchaseScience.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

enum ScienceType
{
    SCIENCE_INVALID = -1
};

class GameLogicPortraitShim
{
public:
    Bool isInMultiplayerOrSkirmishGame();
};

class AsciiString
{
public:
    void *m_data;

    Bool isEmpty() const
    {
        return m_data == 0 || *(unsigned short *)((char *)m_data + 4) == 0;
    }
};

class PlayerTemplate
{
public:
    char m_beforePurchaseScienceRank1[0xA4];
    AsciiString m_purchaseScienceRank1;
    AsciiString m_purchaseScienceRank3;

    const AsciiString &getPurchaseScienceCommandSetRank1() const
    {
        return m_purchaseScienceRank1;
    }

    const AsciiString &getPurchaseScienceCommandSetRank3() const
    {
        return m_purchaseScienceRank3;
    }
};

class Player
{
private:
    char m_beforePlayerTemplate[4];
    PlayerTemplate *m_playerTemplate;
    char m_beforeSciencePurchasePoints[0x264 - 8];
    Int m_sciencePurchasePoints;

public:
    PlayerTemplate *getPlayerTemplate() const
    {
        return m_playerTemplate;
    }

    Bool hasScience(ScienceType) const;

    Int getSciencePurchasePoints() const
    {
        return m_sciencePurchasePoints;
    }
};

struct ScienceVec
{
    ScienceType *m_begin;
    ScienceType *m_end;

    Bool empty() const
    {
        return m_begin == m_end;
    }

    ScienceType operator[](Int index) const
    {
        return m_begin[index];
    }
};

class CommandButton
{
public:
    char m_beforeScience[0x84];
    ScienceVec m_science;

    const ScienceVec &getScienceVec() const
    {
        return m_science;
    }

};

class CommandSet
{
public:
    const CommandButton *getCommandButton(Int index) const;
};

class ControlBar
{
public:
    void bfmeQueryWD(
        Player *player,
        Int buttonIndex,
        const CommandButton **buttonOut,
        Bool *found,
        Bool *successAtArg5,
        Bool *failureAtArg6);
    const CommandSet *findCommandSet(const AsciiString &name);
};

class ScienceStore
{
public:
    Bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
    Bool playerHasPrereqsForScience(const Player *player, ScienceType science) const;
    Int getSciencePurchaseCost(ScienceType science) const;
};

#define TheBfmeGameLogic (*(GameLogicPortraitShim **)0x012F0898)
#define TheControlBar (*(ControlBar **)0x012F33F8)
#define TheScienceStore (*(ScienceStore **)0x012ED7AC)

// ?bfmeQueryWD@ControlBar@@QAEXPAVPlayer@@HPAPBVCommandButton@@PA_N11@Z
void ControlBar::bfmeQueryWD(
    Player *player,
    Int buttonIndex,
    const CommandButton **buttonOut,
    Bool *found,
    Bool *canPurchaseAtArg5,
    Bool *hasScienceAtArg6)
{
    *(volatile Bool *)found = false;
    *(volatile Bool *)canPurchaseAtArg5 = false;
    *(volatile Bool *)hasScienceAtArg6 = false;

    const AsciiString *commandSetName = 0;
    if (TheBfmeGameLogic->isInMultiplayerOrSkirmishGame())
    {
        if (player == 0)
            goto failure;

        const PlayerTemplate *playerTemplate = player->getPlayerTemplate();
        if (playerTemplate == 0)
            goto failure;

        const AsciiString &rank3Name = playerTemplate->getPurchaseScienceCommandSetRank3();
        if (rank3Name.isEmpty())
            goto failure;
        commandSetName = &rank3Name;
    }
    else
    {
        if (player == 0)
            goto failure;

        const PlayerTemplate *playerTemplate = player->getPlayerTemplate();
        if (playerTemplate == 0)
            goto failure;

        const AsciiString &rank1Name = playerTemplate->getPurchaseScienceCommandSetRank1();
        if (rank1Name.isEmpty())
            goto failure;
        commandSetName = &rank1Name;
    }

    const CommandSet *commandSet = TheControlBar->findCommandSet(*commandSetName);
    if (commandSet == 0)
        goto failure;

    const CommandButton *commandButton = commandSet->getCommandButton(buttonIndex);
    *buttonOut = commandButton;
    if (commandButton == 0)
        goto failure;

    *found = true;

    const CommandButton *button = *buttonOut;
    if (button->getScienceVec().empty())
        goto failure;

    ScienceType science = button->getScienceVec()[0];
    if (!TheScienceStore->playerHasRootPrereqsForScience(player, science))
        goto failure;
    if (!player->hasScience(science))
    {
        if (TheScienceStore->playerHasPrereqsForScience(player, science))
        {
            Int purchasePoints = player->getSciencePurchasePoints();
            if (TheScienceStore->getSciencePurchaseCost(science) <= purchasePoints)
                *(volatile Bool *)canPurchaseAtArg5 = true;
        }
    }
    else
    {
        *(volatile Bool *)hasScienceAtArg6 = true;
    }

failure:
    return;
}
