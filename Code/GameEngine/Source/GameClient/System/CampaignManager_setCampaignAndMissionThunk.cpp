// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: convert d_005bc9a0 (dump Code/gen_asm/d_005b3e30.asm) to standalone C++.
//
// Identity: CampaignManager::setCampaignAndMission(AsciiString, AsciiString)
// (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h).
// Evidence: the mission.isEmpty() early-out calls thunk 0x00013b0b, which resolves
// to FUN_009bc5d0 == retail 0x005BC5D0 == the already-matched CampaignManager::setCampaign
// (Code/GameEngine/Source/GameClient/System/CampaignManager.cpp). The match-found path
// calls thunk 0x0000770c -> retail 0x005BC110 (Campaign::getMission, present-unmatched)
// after storing the result at this+0xc (m_currentMission) and the found Campaign* at
// this+8 (m_currentCampaign), exactly matching setCampaignAndMission's body. The tracked
// CampaignManager.cpp already carries a plain-C++ (present-unmatched) definition of this
// function; it is left untouched per file policy, and this is a fresh source beside it
// because that definition's `mission.isEmpty()` forwards through StringBase<char>::isEmpty()
// (out-of-line, cross-TU, not inlined) while retail inlines the m_data/length check --
// the same shape AsciiString::compare(const AsciiString&) already gets right by hand.

#include <list>
#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString {
public:
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
    }
    ~AsciiString();
    void toLower() { ((StringBase<char> *)this)->toLower(); }
    bool isEmpty() const
    {
        const StringBase<char> *self = (const StringBase<char> *)this;
        return !self->m_data || self->m_data->length == 0;
    }
    int compare(const AsciiString &s) const
    {
        const StringBase<char> *self = (const StringBase<char> *)this;
        const StringBase<char> *that = (const StringBase<char> *)&s;
        int thatLen = that->m_data ? that->m_data->length : 0;
        const char *thatData = that->m_data ? &that->m_data->data[0] : (const char *)"";
        int thisLen = self->m_data ? self->m_data->length : 0;
        const char *thisData = self->m_data ? &self->m_data->data[0] : (const char *)"";
        int n = thisLen < thatLen ? thisLen : thatLen;
        int c = memcmp(thisData, thatData, n);
        if (c != 0)
            return c;
        return thisLen - thatLen;
    }

private:
    char *m_text;
};

class Mission;

class Campaign {
public:
    virtual ~Campaign() {}
    AsciiString m_name;
    Mission *getMission(AsciiString missionName);
};

class CampaignManager {
public:
    virtual ~CampaignManager() {}
    void setCampaign(AsciiString campaign);
    void setCampaignAndMission(AsciiString campaign, AsciiString mission);

private:
    std::list<Campaign *> m_campaignList;
    Campaign *m_currentCampaign;
    Mission *m_currentMission;
};

// ?setCampaignAndMission@CampaignManager@@QAEXVAsciiString@@0@Z
void CampaignManager::setCampaignAndMission(AsciiString campaign, AsciiString mission)
{
    if (mission.isEmpty())
    {
        setCampaign(campaign);
        return;
    }
    std::list<Campaign *>::iterator it;
    it = m_campaignList.begin();
    campaign.toLower();
    while (it != m_campaignList.end())
    {
        Campaign *camp = *it;
        if (camp->m_name.compare(campaign) == 0)
        {
            m_currentCampaign = camp;
            m_currentMission = camp->getMission(mission);
            return;
        }
        ++it;
    }
}
