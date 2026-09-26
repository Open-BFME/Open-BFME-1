// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
// The cleanup at006286B0 calls node-pool deallocation0082E5F0;
// the existing BFME_STLP_NODE_ALLOC shim preserves that allocator.
#define ASCIISTRING_H
#include "ascii_string.h"
template <> inline const char *StringBase<char>::str() const {return m_data ? m_data->data : "";}
template <> inline int StringBase<char>::getLength() const {return m_data ? m_data->length : 0;}
template <> inline bool StringBase<char>::isEmpty() const {return m_data == 0 || m_data->length == 0;}
template <> inline char StringBase<char>::getCharAt(int n) const {return m_data ? m_data->data[n] : 0;}
#include <string.h>
#pragma intrinsic(strlen)
template <> inline int StringBase<char>::compare(const char *other) const {
 const int otherLength=other ? strlen(other):0;
 const int length=m_data ? m_data->length:0;
 const char *data=m_data ? m_data->data:"";
 int result=memcmp(data,other,length<otherLength?length:otherLength);
 if(result==0) result=length-otherLength;
 return result;
}
template <> inline void StringBase<char>::concat(char c) {concat(&c,1);}
// stlport
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
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// FILE: GSConfig.cpp
// Author: Matthew D. Campbell, Sept 2002
// Description: GameSpy online config
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////
#include "Common/GameType.h"
#include <algorithm>
#include <list>
#include <set>
// The independent 263-byte overflow body at6288F0 already has this scoped
// identity in vector_ushort_fill_insert.cpp. Preserve its existing pin.
#define _M_insert_overflow Rva006288F0InsertOverflow
#include <vector>
#undef _M_insert_overflow
#include <stdlib.h>
#include <time.h>
#define DEBUG_LOG(x)

// Call-only ABI view from Common/GameState.h; both path converters are
// independently matched at0010F280 and0010F550. The legacy include chain
// imports unrelated SNMP/MapCache declarations incompatible with canonical strings.
class GameState {public: AsciiString realMapPathToPortableMapPath(const AsciiString&) const; AsciiString portableMapPathToRealMapPath(const AsciiString&) const;};
extern GameState *TheGameState;
// Established MapCacheLookup.cpp signatures; this TU never accesses its data.
class MapMetaData;
class MapCache {public: AsciiString getMapDir()const;const MapMetaData *findMap(AsciiString);};
extern MapCache *TheMapCache;
#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/RankPointValue.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////

extern GameSpyConfigInterface *TheGameSpyConfig;

class GameSpyConfig : public GameSpyConfigInterface
{
public:
	GameSpyConfig( AsciiString config );
	~GameSpyConfig() {}

	// Pings
	std::list<AsciiString> getPingServers(void)	{ return m_pingServers; }
	Int getNumPingRepetitions(void)							{ return m_pingReps; }
	Int getPingTimeoutInMs(void)								{ return m_pingTimeout; }
	virtual Int getPingCutoffGood( void )				{	return m_pingCutoffGood; }
	virtual Int getPingCutoffBad( void )				{ return m_pingCutoffBad;	}

	// QM
	// ?getQMMaps@GameSpyConfig@@UAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@XZ present-unmatched
	// Retail505D10 is a string getter, not this list-return reference method.
	std::list<AsciiString> getQMMaps(void)			{ return m_qmMaps; }
	Int getQMBotID(void)												{ return m_qmBotID; }
	Int getQMChannel(void)											{ return m_qmChannel; }
	void setQMChannel(Int channel)							{ m_qmChannel = channel; }

	// Player Info
	Int getPointsForRank(Int rank);
	virtual Bool isPlayerVIP(Int id);
	
	virtual Bool getManglerLocation(Int index, AsciiString& host, UnsignedShort& port);

	// Ladder / Any other external parsing
	AsciiString getLeftoverConfig(void)					{ return m_leftoverConfig; }
	
	// NAT Timeouts
	virtual Int getTimeBetweenRetries() { return m_natRetryInterval; }
	virtual Int getMaxManglerRetries() { return m_natMaxManglerRetries; }
	virtual time_t getRetryInterval() { return m_natManglerRetryInterval; }
	virtual time_t getKeepaliveInterval() { return m_natKeepaliveInterval; }
	virtual time_t getPortTimeout() { return m_natPortTimeout; }
	virtual time_t getRoundTimeout() { return m_natRoundTimeout; }

	// Custom match
	virtual Bool restrictGamesToLobby() { return m_restrictGamesToLobby; }

protected:
	std::list<AsciiString> m_pingServers;
	Int m_pingReps;
	Int m_pingTimeout;
	Int m_pingCutoffGood;
	Int m_pingCutoffBad;

	Int m_natRetryInterval;
	Int m_natMaxManglerRetries;
	time_t m_natManglerRetryInterval;
	time_t m_natKeepaliveInterval;
	time_t m_natPortTimeout;
	time_t m_natRoundTimeout;

	std::vector<AsciiString> m_manglerHosts;
	std::vector<UnsignedShort> m_manglerPorts;

	std::list<AsciiString> m_qmMaps;
	Int m_qmBotID;
	Int m_qmChannel;

	Bool m_restrictGamesToLobby;

	std::set<Int> m_vip; // VIP people

	Int m_rankPoints[MAX_RANKS];

	AsciiString m_leftoverConfig;
};

///////////////////////////////////////////////////////////////////////////////////////

class SectionChecker
{
public:
	typedef std::list<const Bool *> SectionList;
	void addVar(const Bool *var) { m_bools.push_back(var); }
	Bool isInSection();
protected:
	 SectionList m_bools;
};
Bool SectionChecker::isInSection() {
	Bool ret = FALSE;
	for (SectionList::const_iterator it = m_bools.begin(); it != m_bools.end(); ++it)
	{
		ret = ret || **it;
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////

// Native 3751-byte BFME constructor; identity, layout and allocator evidence:
// targets/game/reverse/identity_evidence/00628ba0-gamespy-config.md.
GameSpyConfig::GameSpyConfig( AsciiString config ) :
m_natRetryInterval(1000),
m_natMaxManglerRetries(25),
m_natManglerRetryInterval(300),
m_natKeepaliveInterval(15000),
m_natPortTimeout(10000),
m_natRoundTimeout(10000),
m_pingReps(1),
m_pingTimeout(1000),
m_pingCutoffGood(300),
m_pingCutoffBad(600),
m_restrictGamesToLobby(FALSE),
m_qmBotID(0),
m_qmChannel(0)
{
	// BFME constructor stores these ten defaults at +64..+88.
	m_rankPoints[0] = 0;
	m_rankPoints[1] = 5;
	m_rankPoints[2] = 10;
	m_rankPoints[3] = 30;
	m_rankPoints[4] = 50;
	m_rankPoints[5] = 150;
	m_rankPoints[6] = 500;
	m_rankPoints[7] = 1000;
	m_rankPoints[8] = 2000;
	m_rankPoints[9] = 5000;

	AsciiString line;
	Bool inPingServers = FALSE;
	Bool inPingDuration = FALSE;
	Bool inQMMaps = FALSE;
	Bool inQMBot = FALSE;
	Bool inManglers = FALSE;
	Bool inVIP = FALSE;
	Bool inNAT = FALSE;
	Bool inCustom = FALSE;

	SectionChecker sections;
	sections.addVar(&inPingServers);
	sections.addVar(&inPingDuration);
	sections.addVar(&inQMMaps);
	sections.addVar(&inQMBot);
	sections.addVar(&inManglers);
	sections.addVar(&inVIP);
	sections.addVar(&inNAT);
	sections.addVar(&inCustom);

	while (config.nextToken(&line, "\n"))
	{
		if (line.getCharAt(line.getLength()-1) == '\r')
			line.removeLastChar();	// there is a trailing '\r'

		line.trim();

		if (line.isEmpty())
			continue;

		if (!sections.isInSection() && line.compare("<PingServers>") == 0)
		{
			inPingServers = TRUE;
		}
		else if (inPingServers && line.compare("</PingServers>") == 0)
		{
			inPingServers = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<PingDuration>") == 0)
		{
			inPingDuration = TRUE;
		}
		else if (inPingDuration && line.compare("</PingDuration>") == 0)
		{
			inPingDuration = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<QMMaps>") == 0)
		{
			inQMMaps = TRUE;
		}
		else if (inQMMaps && line.compare("</QMMaps>") == 0)
		{
			inQMMaps = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<Manglers>") == 0)
		{
			inManglers = TRUE;
		}
		else if (inManglers && line.compare("</Manglers>") == 0)
		{
			inManglers = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<QMBot>") == 0)
		{
			inQMBot = TRUE;
		}
		else if (inQMBot && line.compare("</QMBot>") == 0)
		{
			inQMBot = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<VIP>") == 0)
		{
			inVIP = TRUE;
		}
		else if (inVIP && line.compare("</VIP>") == 0)
		{
			inVIP = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<NAT>") == 0)
		{
			inNAT = TRUE;
		}
		else if (inNAT && line.compare("</NAT>") == 0)
		{
			inNAT = FALSE;
		}
		else if (!sections.isInSection() && line.compare("<Custom>") == 0)
		{
			inCustom = TRUE;
		}
		else if (inCustom && line.compare("</Custom>") == 0)
		{
			inCustom = FALSE;
		}
		else if (inVIP)
		{
			line.toLower();
			if (line.getLength())
			{
				Int val = atoi(line.str());
				if (val > 0)
					m_vip.insert(val);
			}
		}
		else if (inPingServers)
		{
			line.toLower();
			m_pingServers.push_back(line);
		}
		else if (inPingDuration)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " ="))
			{
				if (key.compare("reps") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingReps = atoi(val.str());
					}
				}
				else if (key.compare("timeout") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingTimeout = atoi(val.str());
					}
				}
				else if (key.compare("low") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingCutoffGood = atoi(val.str());
					}
				}
				else if (key.compare("med") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_pingCutoffBad = atoi(val.str());
					}
				}
			}
		}
		else if (inManglers)
		{
			line.trim();
			line.toLower();
			AsciiString hostStr;
			AsciiString portStr;
			line.nextToken(&hostStr, ":");
			line.nextToken(&portStr, ":\n\r");
			if (hostStr.isNotEmpty() && portStr.isNotEmpty())
			{
				m_manglerHosts.push_back(hostStr);
				m_manglerPorts.push_back(atoi(portStr.str()));
			}
		}
		else if (inQMMaps)
		{
			line.toLower();
			AsciiString mapName;
			mapName.format("%s\\%s\\%s.map", TheMapCache->getMapDir().str(), line.str(), line.str());
			mapName = TheGameState->portableMapPathToRealMapPath(TheGameState->realMapPathToPortableMapPath(mapName));
			mapName.toLower();

			const MapMetaData *md = TheMapCache->findMap(mapName);
			if (md)
			{
				m_qmMaps.push_back(mapName);
			}
		}
		else if (inQMBot)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " ="))
			{
				if (key.compare("id") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_qmBotID = atoi(val.str());
					}
				}
			}
		}
		else if (inNAT)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " ="))
			{
				if (key.compare("retryinterval") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natRetryInterval = atoi(val.str());
					}
				}
				else if (key.compare("manglerretries") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natMaxManglerRetries = atoi(val.str());
					}
				}
				else if (key.compare("manglerinterval") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natManglerRetryInterval = atoi(val.str());
					}
				}
				else if (key.compare("keepaliveinterval") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natKeepaliveInterval = atoi(val.str());
					}
				}
				else if (key.compare("porttimeout") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natPortTimeout = atoi(val.str());
					}
				}
				else if (key.compare("roundtimeout") == 0)
				{
					if (line.nextToken(&val, " ="))
					{
						m_natRoundTimeout = atoi(val.str());
					}
				}
				else
				{
					DEBUG_LOG(("Unknown key '%s' = '%s' in NAT block of GameSpy Config\n", key.str(), val.str()));
				}
			}
			else
			{
				DEBUG_LOG(("Key '%s' missing val in NAT block of GameSpy Config\n", key.str()));
			}
		}
		else if (inCustom)
		{
			line.toLower();
			AsciiString key, val;
			if (line.nextToken(&key, " =") && line.nextToken(&val, " ="))
			{
				if (key.compare("restricted") == 0)
				{
					m_restrictGamesToLobby = atoi(val.str());
				}
				else
				{
					DEBUG_LOG(("Unknown key '%s' = '%s' in Custom block of GameSpy Config\n", key.str(), val.str()));
				}
			}
			else
			{
				DEBUG_LOG(("Key '%s' missing val in Custom block of GameSpy Config\n", key.str()));
			}
		}
		else
		{
			m_leftoverConfig.concat(line);
			((StringBase<char>&)m_leftoverConfig).concat('\n');
		}
	}

}

