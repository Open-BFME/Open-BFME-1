// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/buddythread /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
// Retail 0x006315E0 queues a BuddyRequest::BUDDYREQUEST_ADDBUDDY request.
// The GUI:BuddyAddReq string xref, the adjacent GameSpyInfo methods, and the
// matching request layout identify this helper. The stdcall return matches the
// retail ret 4 boundary.

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

// ?Rva006315E0RequestBuddyAdd@@YGXH@Z
void __stdcall Rva006315E0RequestBuddyAdd(Int profileID)
{
	BuddyRequest request;
	request.buddyRequestType = BuddyRequest::BUDDYREQUEST_ADDBUDDY;
	request.arg.addbuddy.id = profileID;
	UnicodeString text;
	bfmeUnicodeStringSet(text, TheGameText->fetch("GUI:BuddyAddReq"));
	wcsncpy(request.arg.addbuddy.text, bfmeUnicodeStringText(text), MAX_BUDDY_CHAT_LEN);
	request.arg.addbuddy.text[MAX_BUDDY_CHAT_LEN - 1] = 0;
	TheGameSpyBuddyMessageQueue->addRequest(request);
}
