// cl: /DNDEBUG /MD /EHsc

// Retail 0x004A0B20 (81 bytes, thiscall, two stack arguments, ret 8). It calls
// ControlBar::GetPurchaseScienceStatus (0x004A09D0, reached through ILT 0x0001CDB9)
// with the player, the button index and the addresses of three local booleans and one
// local button pointer. It returns true when the first two booleans are set and the
// third is clear. No matched caller names this body, so the name keeps the address.

typedef bool Bool;
typedef int Int;

class Player;
class CommandButton;

class ControlBar
{
public:
    void GetPurchaseScienceStatus(
        Player *player,
        Int buttonIndex,
        const CommandButton **buttonOut,
        Bool *found,
        Bool *successAtArg5,
        Bool *failureAtArg6);
    Bool Rva004A0B20(Player *player, Int buttonIndex);
};

Bool ControlBar::Rva004A0B20(Player *player, Int buttonIndex)
{
    const CommandButton *button;
    Bool found;
    Bool successAtArg5;
    Bool failureAtArg6;
    this->GetPurchaseScienceStatus(player, buttonIndex, &button, &found, &successAtArg5, &failureAtArg6);
    return found && successAtArg5 && !failureAtArg6;
}
