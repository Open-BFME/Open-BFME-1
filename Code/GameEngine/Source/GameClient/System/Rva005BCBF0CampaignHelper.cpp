/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//
//  (c) 2001-2003 Electronic Arts Inc.
//
////////////////////////////////////////////////////////////////////////////////

// FILE: Rva005BCBF0CampaignHelper.cpp
//
// This is an address-derived neutral carrier for the complete retail body at
// 0x005BCBF0.  The original owner/method name is not proven.  Raw disassembly
// proves a thiscall ECX owner, a four-byte by-value AsciiString argument, a
// Campaign* result, and ret 4; the sole direct caller is the campaign parser
// at 0x005BCF98.  The control flow follows the canonical EA CampaignManager
// campaign-list helper, but this source intentionally makes no
// CampaignManager::newCampaign identity claim.
//
// Canonical donor: reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/
// Source/GameClient/System/CampaignManager.cpp, CampaignManager::newCampaign.

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include <list>

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

// Retail AsciiString is a single pointer to a ref-counted buffer.  The retail
// compare body reads the ushort length at +4 and bytes at +8 of that buffer.
struct Rva005BCBF0StringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();
	void toLower();
	void set(const AsciiString &that);

	int compare(const AsciiString &that) const
	{
		int otherLength = that.m_data ? that.m_data->length : 0;
		const char *otherData = that.m_data
			? &that.m_data->data[0] : (const char *)"";
		int selfLength = m_data ? m_data->length : 0;
		const char *selfData = m_data ? &m_data->data[0] : (const char *)"";
		int length = selfLength < otherLength ? selfLength : otherLength;
		int result = memcmp(selfData, otherData, length);
		if (result != 0)
			return result;
		return selfLength - otherLength;
	}

private:
	Rva005BCBF0StringData *m_data;
};

class Mission;

class Campaign
{
public:
	Campaign();
	virtual ~Campaign();
	void deleteInstance() { delete this; }

	AsciiString m_name;
	AsciiString m_firstMission;
	AsciiString m_campaignNameLabel;
	std::list<Mission *> m_missions;
	AsciiString m_finalMovieName;
};

class Rva005BCBF0CampaignHelper
{
public:
	Campaign *rva005BCBF0(AsciiString name);

private:
	unsigned char m_unmodelledHead[4];
	std::list<Campaign *> m_campaignList;
	Campaign *m_currentCampaign;
	Mission *m_currentMission;
};

Campaign *Rva005BCBF0CampaignHelper::rva005BCBF0(AsciiString name)
{
	Rva005BCBF0CampaignHelper *self = this;
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
