// cl: /I. /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// RVA 0065B500: identity and ABI witnessed by bfmeCbXK at 0065BD00.
// Complete retail response parser; BFME response tail is independently 1F0 bytes.
// find at +005C uses the same map and erase contract as matched handle (0065B350).
// String labels identify the four allocations. Stores at +0542..+0557 place
// gondor/rohan/isengard/mordor at response +1DC/+1E0/+1E4/+1E8.
// Counter meanings remain opaque: retail stores the second and third numeric
// lines in arrays at +00 and +10, indexed today/yesterday/all time/last week.
#define ASCIISTRING_H
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "PreRTS.h"
typedef struct in_addr IN_ADDR;
#include "Common/UserPreferences.h"
#include <map>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#pragma intrinsic(strlen)
#undef isdigit
template <> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
template <> inline char StringBase<char>::getCharAt(int n) const { return m_data ? m_data->data[n] : 0; }
template <> inline void StringBase<char>::set(const char *s) { set(s, s ? strlen(s) : 0); }
inline AsciiString &AsciiString::operator=(const char *s) { StringBase<char>::set(s); return *this; }

// Retail allocation is 20 bytes hex, split into two arrays of four counters.
struct FactionCounters0065B500 {
    int words00[4], words10[4];
    FactionCounters0065B500() {
        for (int i=0; i<4; ++i) words00[i] = words10[i] = 0;
    }
};
struct Response0065B500 {
    int word0;
    PSPlayerStats player;
    char opaque1C8[0x14];
    FactionCounters0065B500 *gondor, *rohan, *isengard, *mordor;
    int opaque1EC;
};
typedef char VerifyResponse[sizeof(Response0065B500)==0x1F0 ? 1 : -1];
class Queue0065B500 {
public:
    virtual void slot0(); virtual void slot4(); virtual void slot8();
    virtual void slotC(); virtual void slot10(); virtual void slot14();
    virtual void slot18(const Response0065B500 &);
};
class GameSpyPSMessageQueueInterface;
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
class Gen_00654130 { public: void bfmeErase(void *); };
class Rva0065B350 {
public:
    char opaque0[0x5C];
    _STL::map<void *, void *> values;
    int handleXKResponse(void *, int, const char *, int, int);
};
int Rva0065B350::handleXKResponse(void *key, int status, const char *text, int, int)
{
    _STL::map<void *, void *>::iterator found = values.find(key);
    if (!status && found != values.end() && found->second) {
        FactionCounters0065B500 *rohan = new FactionCounters0065B500;
        FactionCounters0065B500 *gondor = new FactionCounters0065B500;
        FactionCounters0065B500 *isengard = new FactionCounters0065B500;
        FactionCounters0065B500 *mordor = new FactionCounters0065B500;
        AsciiString input(text);
        int period = 4;
        AsciiString line;
        FactionCounters0065B500 *current = 0;
        while (input.nextToken(&line, "\n")) {
            line.trim();
            line.toLower();
            if (strstr(line.str(), "today")) period = 0;
            else if (strstr(line.str(), "yesterday")) period = 1;
            else if (strstr(line.str(), "all time")) period = 2;
            else if (strstr(line.str(), "last week")) period = 3;
            else if (period != 4) {
                if (strstr(line.str(), "rohan")) current = rohan;
                else if (strstr(line.str(), "gondor")) current = gondor;
                else if (strstr(line.str(), "isengard")) current = isengard;
                else if (strstr(line.str(), "mordor")) current = mordor;
            }
            if (current) {
                AsciiString first, second, third;
                input.nextToken(&first, "\n");
                input.nextToken(&second, "\n");
                input.nextToken(&third, "\n");
                while (!first.isEmpty() && !isdigit(first.getCharAt(0))) first = first.str()+1;
                while (!second.isEmpty() && !isdigit(second.getCharAt(0))) second = second.str()+1;
                while (!third.isEmpty() && !isdigit(third.getCharAt(0))) third = third.str()+1;
                if (!first.isEmpty() && !second.isEmpty() && !third.isEmpty()) {
                    current->words00[period] = atoi(second.str());
                    current->words10[period] = atoi(third.str());
                }
                current = 0;
            }
        }
        Response0065B500 response;
        response.word0 = 5;
        response.gondor = gondor;
        response.rohan = rohan;
        response.isengard = isengard;
        response.mordor = mordor;
        if (TheGameSpyPSMessageQueue) reinterpret_cast<Queue0065B500 *>(TheGameSpyPSMessageQueue)->slot18(response);
        else {
            delete rohan;
            delete gondor;
            delete isengard;
            delete mordor;
        }
        reinterpret_cast<Gen_00654130 *>(this)->bfmeErase(key);
    } else {
        reinterpret_cast<Gen_00654130 *>(this)->bfmeErase(key);
    }
    return 1;
}
