// ?newCampaign@CampaignManager@@QAEPAVCampaign@@VAsciiString@@@Z
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: convert d_005bcbf0 (dump Code/gen_asm/d_005b3e30.asm) to standalone C++.
//
// Identity: CampaignManager::newCampaign(AsciiString) (reference/CnC_Generals_Zero_Hour/
// GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h). The tracked
// CampaignManager.cpp already carries a plain-C++ (present-unmatched) definition of this
// function; left untouched per file policy. This is a fresh source beside it with its own
// minimal class layout (Campaign is 24 B: vtable + 4 AsciiString-sized members + one
// std::list-sized member, matching retail's `push 0x18` allocation size) so the compare,
// erase and construct sequence gets the retail register shape.

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
    void set(const AsciiString &s) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&s); }
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
    Campaign();
    virtual ~Campaign() {}
    void deleteInstance() { delete this; }

    AsciiString m_name;
    AsciiString m_firstMission;
    AsciiString m_campaignNameLabel;
    std::list<Mission *> m_missions;
    AsciiString m_finalMovieName;
};

class CampaignManager {
public:
    virtual ~CampaignManager() {}
    Campaign *newCampaign(AsciiString name);

private:
    std::list<Campaign *> m_campaignList;
    Campaign *m_currentCampaign;
    Mission *m_currentMission;
};

// ?newCampaign@CampaignManager@@QAEPAVCampaign@@VAsciiString@@@Z
Campaign *CampaignManager::newCampaign(AsciiString name)
{
    CampaignManager *self = this;
    std::list<Campaign *>::iterator it;
    it = self->m_campaignList.begin();
    name.toLower();
    while (it != self->m_campaignList.end())
    {
        Campaign *campaign = *it;
        if (campaign->m_name.compare(name) == 0)
        {
            self->m_campaignList.erase(it);
            campaign->deleteInstance();
            break;
        }
        else
            ++it;
    }
    Campaign *newCampaign = new Campaign();
    newCampaign->m_name.set(name);
    self->m_campaignList.push_back(newCampaign);
    return newCampaign;
}
