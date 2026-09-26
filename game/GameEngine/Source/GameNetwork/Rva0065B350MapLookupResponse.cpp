// cl: /I. /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// 0x0065B350: look the key up in the pointer map at +0x5c; on success parse the
// trimmed text and queue a type-4 response through g_bfmeQueueEUG slot 0x18,
// then erase the key. The early return keeps the string at function scope,
// which gives the find result its own frame slot as retail does.
#define ASCIISTRING_H
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "PreRTS.h"
typedef struct in_addr IN_ADDR;
#include "Common/UserPreferences.h"
#include <map>
#include <string>
#include <stdlib.h>
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

// The response deque has a independently witnessed 1F0-byte stride. This
// BFME tail is not described by the smaller upstream PSResponse declaration.
struct Rva0065B350Response {
    int word0;
    PSPlayerStats player;
    char opaque1C8[0xC];
    int word1D4, word1D8;
    char opaque1DC[0x14];
};
typedef char VerifyStats[sizeof(PSPlayerStats) == 0x1C4 ? 1 : -1];
typedef char VerifyResponse[sizeof(Rva0065B350Response) == 0x1F0 ? 1 : -1];
class Rva0065B350QueueView {
public:
    virtual void slot0(); virtual void slot4(); virtual void slot8();
    virtual void slotC(); virtual void slot10(); virtual void slot14();
    virtual void slot18(const Rva0065B350Response &);
};
class BfmeQueueEUG;
extern BfmeQueueEUG *g_bfmeQueueEUG;
class Gen_00654130 { public: void bfmeErase(void *); };
struct Rva0065B350Payload { int word0, word4; };
class Rva0065B350 {
public:
    char opaque0[0x5C];
    _STL::map<void *, void *> values;
    int handle(void *, int, const char *, int, int);
};
int Rva0065B350::handle(void *key, int status, const char *text, int, int)
{
    _STL::map<void *, void *>::iterator found = values.find(key);
    if (status || found == values.end() || !found->second) {
        reinterpret_cast<Gen_00654130 *>(this)->bfmeErase(key);
        return 1;
    }
    AsciiString value(text);
    value.trim();
    int parsed = atoi(value.str());
    if (parsed != -2) {
        int type = static_cast<Rva0065B350Payload *>(found->second)->word4;
        if (type == 1 || type == 2) {
            Rva0065B350Response response;
            response.word0 = 4;
            response.word1D4 = parsed;
            response.word1D8 = type;
            if (g_bfmeQueueEUG)
                reinterpret_cast<Rva0065B350QueueView *>(g_bfmeQueueEUG)->slot18(response);
        }
    }
    reinterpret_cast<Gen_00654130 *>(this)->bfmeErase(key);
    return 1;
}
