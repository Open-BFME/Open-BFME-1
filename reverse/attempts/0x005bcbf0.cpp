// ?d_005bcbf0@@YAXXZ
// partial score=0.8 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// CampaignManager::newCampaign from the WWDownload campaign manager source.

#include <list>
#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}

	~AsciiString();

	void toLower()
	{
		((StringBase<char> *)this)->toLower();
	}

	void set(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
	}

	int compare(const AsciiString &that) const
	{
		const StringBase<char> *self = (const StringBase<char> *)this;
		const StringBase<char> *other = (const StringBase<char> *)&that;
		int otherLength = other->m_data ? other->m_data->length : 0;
		const char *otherData = other->m_data
			? &other->m_data->data[0] : (const char *)"";
		int selfLength = self->m_data ? self->m_data->length : 0;
		const char *selfData = self->m_data
			? &self->m_data->data[0] : (const char *)"";
		int length = selfLength < otherLength ? selfLength : otherLength;
		int result = memcmp(selfData, otherData, length);
		if (result != 0)
			return result;
		return selfLength - otherLength;
	}

private:
	char *m_text;
};

class Mission;

class Campaign
{
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

class CampaignManager
{
public:
	virtual ~CampaignManager() {}
	Campaign *newCampaign(AsciiString name);

private:
	std::list<Campaign *> m_campaignList;
	Campaign *m_currentCampaign;
	Mission *m_currentMission;
};

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
