// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/buddythread /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// The retail body at RVA 0x004EF980 accepts a pending buddy request.
// The reference WOLBuddyOverlay code proves the request values and text key.
// Its C++ owner remains unknown, so this source keeps an address-derived name.

#define __PLACEMENT_VEC_NEW_INLINE

#include <map>

#include "PreRTS.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/BuddyThread.h"

template <typename T> class StringBase
{
public:
    void set(const StringBase<T> &source);
private:
    void *m_data;
};

static __forceinline void bfmeUnicodeStringSet(UnicodeString &dest, const UnicodeString &source)
{
    ((StringBase<unsigned short> *)&dest)->set(*(const StringBase<unsigned short> *)&source);
}

static __forceinline const unsigned short *bfmeUnicodeStringText(const UnicodeString &text)
{
    void *data = *(void *const *)&text;
    return data ? (const unsigned short *)((const char *)data + 8)
                : (const unsigned short *)0x0107388C;
}

struct Gen_t_004ee060_p12cd
{
    int a[3];
};

typedef std::map<Int, Gen_t_004ee060_p12cd> BuddyRequestMap;

class BfmeGameSpyInfoView
{
public:
    virtual ~BfmeGameSpyInfoView() {}
    virtual void s00() = 0;
    virtual void s01() = 0;
    virtual void s02() = 0;
    virtual void s03() = 0;
    virtual void s04() = 0;
    virtual void s05() = 0;
    virtual void s06() = 0;
    virtual void s07() = 0;
    virtual void s08() = 0;
    virtual void s09() = 0;
    virtual void s10() = 0;
    virtual void s11() = 0;
    virtual void s12() = 0;
    virtual void s13() = 0;
    virtual void s14() = 0;
    virtual void s15() = 0;
    virtual void s16() = 0;
    virtual void s17() = 0;
    virtual void s18() = 0;
    virtual void s19() = 0;
    virtual void s20() = 0;
    virtual BuddyRequestMap *getBuddyRequestMap() = 0;
};

// ?Rva004EF980AcceptBuddyRequest@@YAXH@Z
void Rva004EF980AcceptBuddyRequest(Int profileID)
{
    BuddyRequest request;
    request.buddyRequestType = BuddyRequest::BUDDYREQUEST_OKADD;
    request.arg.profile.id = profileID;
    TheGameSpyBuddyMessageQueue->addRequest(request);

    BuddyRequestMap *requests = ((BfmeGameSpyInfoView *)TheGameSpyInfo)->getBuddyRequestMap();
    requests->erase(profileID);

    BuddyRequest addRequest;
    addRequest.buddyRequestType = BuddyRequest::BUDDYREQUEST_ADDBUDDY;
    addRequest.arg.addbuddy.id = profileID;
    UnicodeString text;
    bfmeUnicodeStringSet(text, TheGameText->fetch("GUI:BuddyAddReq"));
    wcsncpy(addRequest.arg.addbuddy.text, bfmeUnicodeStringText(text), MAX_BUDDY_CHAT_LEN);
    addRequest.arg.addbuddy.text[MAX_BUDDY_CHAT_LEN - 1] = 0;
    TheGameSpyBuddyMessageQueue->addRequest(addRequest);
}
