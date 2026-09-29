// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// BFME parseLadder, 0x0062AD50; see identity_evidence/0062ad50-ladder-parser.md.
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

#include "Common/GameType.h"
#include <algorithm>
#include <list>
#include <string>
#include <stdlib.h>
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#define DEBUG_LOG(x)
#define NEW new
static const int MAX_SLOTS=8;
std::wstring MultiByteToWideCharSingleLine(const char*);
class PlayerTemplateStore {public:void getAllSideStrings(std::list<AsciiString>*);};
extern PlayerTemplateStore *ThePlayerTemplateStore;
class GameState {public: AsciiString realMapPathToPortableMapPath(const AsciiString&)const;AsciiString portableMapPathToRealMapPath(const AsciiString&)const;};
extern GameState *TheGameState;
class MapMetaData {public:char rvaFields00[0x20];int m_numPlayers;};
class MapCache {public:AsciiString getMapDir()const;const MapMetaData *findMap(AsciiString);};
extern MapCache *TheMapCache;
template <> inline bool StringBase<char>::isEmpty()const {return !m_data||m_data->length==0;}
template <> inline char StringBase<char>::getCharAt(int n)const {return m_data?m_data->data[n]:0;}
inline UnicodeString& UnicodeString::operator=(const wchar_t *s) {
 ((StringBase<unsigned short>*)this)->set((const unsigned short*)s,s?wcslen(s):0);return *this;
}
#include <string.h>
#pragma intrinsic(strlen)
template <> inline bool StringBase<char>::startsWith(const char *s)const {return startsWith(s,s?strlen(s):0);}
template <> inline void StringBase<char>::set(const char *s) {set(s,s?strlen(s):0);}
inline AsciiString& AsciiString::operator=(const char *s) {StringBase<char>::set(s);return *this;}
// These address-derived views avoid old ASCII template pins that route to a
// UTF-16 search. Both complete helpers are independently byte-verified: the
// 130-byte search uses the canonical 8-byte string header and byte comparison;
// its 46-byte wrapper preserves STLport's iterator return and tag ABI.
namespace _STL {
template<class Iter,class T>
inline Iter Rva00080110Find(Iter first,Iter last,const T&value,const input_iterator_tag&) {
 while(first!=last && !((*first).compare(value)==0)) ++first;
 return first;
}
template<class Iter,class T>
inline Iter Rva00080590Find(Iter first,Iter last,const T&value) {
 return Rva00080110Find(first,last,value,_STLP_ITERATOR_CATEGORY(first,Iter));
}
}

LadderInfo *parseLadder(AsciiString raw)
{
	DEBUG_LOG(("Looking at ladder:\n%s\n", raw.str()));
	LadderInfo *lad = NULL;
	AsciiString line;
	while (raw.nextToken(&line, "\n"))
	{
		if (line.getCharAt(line.getLength()-1) == '\r')
			line.removeLastChar();	// there is a trailing '\r'

		line.trim();

		if (line.isEmpty())
			continue;

		// woohoo!  got a line!
		line.trim();
		if ( !lad && ((const StringBase<char>&)line).startsWith("<Ladder ") )
		{
			// start of a ladder def
			lad = NEW LadderInfo;

			// fill in some info
			AsciiString tokenName, tokenAddr, tokenPort, tokenHomepage;
			line.removeLastChar(); // the '>'
			line = line.str() + 7; // the "<Ladder "
			line.nextToken(&tokenAddr, "\" ");
			line.nextToken(&tokenPort, " ");
			line.nextToken(&tokenHomepage, " ");

			lad->name = MultiByteToWideCharSingleLine(tokenName.str()).c_str();
			while (lad->name.getLength() > 20)
				((StringBase<unsigned short>*)&lad->name)->removeLastChar(); // Per Harvard's request, ladder names are limited to 20 chars
			lad->address = tokenAddr;
			lad->port = atoi(tokenPort.str());
			lad->homepageURL = tokenHomepage;
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("Name ") )
		{
			lad->name = MultiByteToWideCharSingleLine(line.str() + 5).c_str();
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("Desc ") )
		{
			lad->description = MultiByteToWideCharSingleLine(line.str() + 5).c_str();
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("Loc ") )
		{
			lad->location = MultiByteToWideCharSingleLine(line.str() + 4).c_str();
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("TeamSize ") )
		{
			lad->playersPerTeam = atoi(line.str() + 9);
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("RandomMaps ") )
		{
			lad->randomMaps = atoi(line.str() + 11);
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("RandomFactions ") )
		{
			lad->randomFactions = atoi(line.str() + 15);
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("Faction ") )
		{
			AsciiString faction = line.str() + 8;
			AsciiStringList outStringList;
			ThePlayerTemplateStore->getAllSideStrings(&outStringList);

			AsciiStringList::iterator aIt = std::Rva00080590Find(outStringList.begin(), outStringList.end(), faction);
			if (aIt != outStringList.end())
			{
				// valid faction - now check for dupes
				aIt = std::Rva00080590Find(lad->validFactions.begin(), lad->validFactions.end(), faction);
				if (aIt == lad->validFactions.end())
				{
					lad->validFactions.push_back(faction);
				}
			}
		}
		/*
		else if ( lad && ((const StringBase<char>&)line).startsWith("QM ") )
		{
			lad->validQM = atoi(line.str() + 3);
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("Custom ") )
		{
			lad->validCustom = atoi(line.str() + 7);
		}
		*/
		else if ( lad && ((const StringBase<char>&)line).startsWith("MinWins ") )
		{
			lad->minWins = atoi(line.str() + 8);
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("MaxWins ") )
		{
			lad->maxWins = atoi(line.str() + 8);
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("CryptedPass ") )
		{
			lad->cryptedPassword = line.str() + 12;
		}
		else if ( lad && line.compare("</Ladder>") == 0 )
		{
			DEBUG_LOG(("Saw a ladder: name=%ls, addr=%s:%d, players=%dv%d, pass=%s, replay=%d, homepage=%s\n",
				lad->name.str(), lad->address.str(), lad->port, lad->playersPerTeam, lad->playersPerTeam, lad->cryptedPassword.str(),
				lad->submitReplay, lad->homepageURL.str()));
			// end of a ladder
			if (lad->playersPerTeam >= 1 && lad->playersPerTeam <= MAX_SLOTS/2)
			{
				if (lad->validFactions.size() == 0)
				{
					DEBUG_LOG(("No factions specified.  Using all.\n"));
					lad->validFactions.push_back("America");
					lad->validFactions.push_back("China");
					lad->validFactions.push_back("GLA");

				}
				else
				{
					AsciiStringList validFactions = lad->validFactions;
					for (AsciiStringListIterator it = validFactions.begin(); it != validFactions.end(); ++it)
					{
						AsciiString faction = *it;
						AsciiString marker;
						marker.format("INI:Faction%s", faction.str());
						DEBUG_LOG(("Faction %s has marker %s corresponding to str %ls\n", faction.str(), marker.str(), TheGameText->fetch(marker).str()));
					}
				}

				if (lad->validMaps.size() == 0)
				{
					DEBUG_LOG(("No maps specified.  Using all.\n"));
					std::list<AsciiString> qmMaps = TheGameSpyConfig->getQMMaps();
					for (std::list<AsciiString>::const_iterator it = qmMaps.begin(); it != qmMaps.end(); ++it)
					{
						AsciiString mapName = *it;

						// check sizes on the maps before allowing them
						const MapMetaData *md = TheMapCache->findMap(mapName);
						if (md && md->m_numPlayers >= lad->playersPerTeam*2)
						{
							lad->validMaps.push_back(mapName);
						}
					}
				}
				return lad;
			}
			else
			{
				// no maps?  don't play on it!
				delete lad;
				lad = NULL;
				return NULL;
			}
		}
		else if ( lad && ((const StringBase<char>&)line).startsWith("Map ") )
		{
			// valid map
			AsciiString mapName = line.str() + 4;
			mapName.trim();
			if (mapName.isNotEmpty())
			{
				mapName.format("%s\\%s\\%s.map", TheMapCache->getMapDir().str(), mapName.str(), mapName.str());
				mapName = TheGameState->portableMapPathToRealMapPath(TheGameState->realMapPathToPortableMapPath(mapName));
				mapName.toLower();
				std::list<AsciiString> qmMaps = TheGameSpyConfig->getQMMaps();
				if (std::Rva00080590Find(qmMaps.begin(), qmMaps.end(), mapName) != qmMaps.end())
				{
					// check sizes on the maps before allowing them
					const MapMetaData *md = TheMapCache->findMap(mapName);
					if (md && md->m_numPlayers >= lad->playersPerTeam*2)
						lad->validMaps.push_back(mapName);
				}
			}
		}
		else
		{
			// bad ladder - kill it
			delete lad;
			lad = NULL;
		}
	}

	if (lad)
	{
		delete lad;
		lad = NULL;
	}
	return NULL;
}

