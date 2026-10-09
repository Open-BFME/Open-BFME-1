// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// NetCommandMsg debug description, RVA0x006747C0, complete298B.
// Matched constructor0x006735D0 installs vtableVA0x0111A20C; slot+0x0C
// points through ILT0x0002D204 to this body. Derived frame/ACK descriptions
// call this base explicitly and append their payload fields. The debug method
// name follows EA GeneralsMD NetCommandMsg.h and its override family.
// BFME adds the base frame/player/ID text instead of returning an empty string.
// The command-type helper is GetAsciiNetCommandType, not a packet decoder.
#include "ascii_string.h"

enum NetCommandType { NETCOMMANDTYPE_FRAMEINFO = 3 };
int DoesCommandRequireACommandID(NetCommandType);
AsciiString GetAsciiNetCommandType(NetCommandType);
class NetCommandMsg {
public:
    virtual ~NetCommandMsg();
    virtual int getSortNumber();
    virtual bool unknownSlot08();
    virtual AsciiString getContentsAsAsciiString();
    unsigned timestamp;
    unsigned frame;
    unsigned player;
    unsigned short id;
    NetCommandType type;
    int references;
};
// NetCommandMsg vtable 0x0111A20C slot 2 reaches the 3-byte retail body at 0x006627A0.
bool NetCommandMsg::unknownSlot08()
{
    return false;
}

AsciiString NetCommandMsg::getContentsAsAsciiString()
{
    AsciiString result;
    if ((unsigned char)DoesCommandRequireACommandID(type))
        result.format("%s, frame=%d, player=%d, id=%d", GetAsciiNetCommandType(type).str(), frame, player, id);
    else
        result.format("%s, frame=%d, player=%d", GetAsciiNetCommandType(type).str(), frame, player);
    return result;
}
