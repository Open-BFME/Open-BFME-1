// Retail 0x004BE120, 66 bytes. The callback table at 0x00D051F0
// identifies this input route, but no owner name is established.
// GWM_IME_CHAR is filtered through the landed character policy; all other
// messages and accepted characters forward through ILT 0x00003DF0.
typedef unsigned short WideChar;

class Rva004BE120Input
{
public:
    int input(unsigned int msg, unsigned int data1, unsigned int data2);

private:
    char m_unreconstructed00[12];
    int m_characterFlags;
};

extern bool __cdecl GadgetTextEntryValidateCharacter(
    WideChar character, signed char flags);
extern void j_00003df0();

int Rva004BE120Input::input(unsigned int msg, unsigned int data1,
                           unsigned int data2)
{
    // The caller passes the full +0x0C dword. The policy consumes its low
    // byte, so retain the retail stack argument without narrowing it here.
    typedef bool (__cdecl *RawCharacterPolicy)(WideChar, int);
    RawCharacterPolicy policy = reinterpret_cast<RawCharacterPolicy>(
        &GadgetTextEntryValidateCharacter);
    if (msg == 0x19 && !policy((WideChar)data1, m_characterFlags))
        return 1;

    // The thunk tails through a virtual slot; that callee removes all three
    // arguments. The member-pointer view preserves the witnessed thiscall.
    typedef int (Rva004BE120Input::*Fallback)(
        unsigned int, unsigned int, unsigned int);
    union { void (*raw)(); Fallback member; } route;
    route.raw = ::j_00003df0;
    return (this->*route.member)(msg, data1, data2);
}
