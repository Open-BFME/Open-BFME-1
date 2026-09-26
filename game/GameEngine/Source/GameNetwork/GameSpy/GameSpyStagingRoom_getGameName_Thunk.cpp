// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: GameSpyStagingRoom::getGameName, retail 0x004CE820.
//
// The one-line accessor. It returns UnicodeString by value, so the body is
// mostly the return-slot protocol: reserve four bytes, take &m_gameName as
// this+0x3a0, clear the unwind state slot, and copy-construct into the hidden
// return pointer.
//
// The offset is the only thing here that is not boilerplate: m_gameName sits
// at this+0x3a0.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
// Retail's UnicodeString derives from StringBase<unsigned short> and holds
// nothing of its own, so its copy ctor is a forwarder retail inlines: the
// call site encodes the base body at 0x00888400
// (??0?$StringBase@G@@AAE@ABV0@@Z). The delegation has to be visible here
// for this TU to encode the same call.
#include "string_base.h"

class UnicodeString
{
public:
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}
	~UnicodeString();

private:
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom
{
public:
	UnicodeString getGameName(void) const;

private:
	char m_unreconstructed_00[0x3a0];
	UnicodeString m_gameName;						///< retail this+0x3a0
};

// ?getGameName@GameSpyStagingRoom@@QBE?AVUnicodeString@@XZ
UnicodeString GameSpyStagingRoom::getGameName(void) const
{
	return m_gameName;
}
