// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/science /Ireference/shims/asciistring8 /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// FILE: Science.cpp /////////////////////////////////////////////////////////
// Created:   Steven Johnson, October 2001
// Desc:      @todo
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "Common/Player.h"
#include "Common/Science.h"

ScienceStore* TheScienceStore = NULL;

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
void ScienceStore::init()
{
	DEBUG_ASSERTCRASH(m_sciences.empty(), ("Hmm"));
	m_sciences.clear();
}

//-----------------------------------------------------------------------------
ScienceStore::~ScienceStore()
{
	// nope.
	//m_sciences.clear();

	// go through all sciences and delete any overrides
	for (ScienceInfoVec::iterator it = m_sciences.begin(); it != m_sciences.end(); /*++it*/)
	{
		ScienceInfo* si = *it;
		++it;
		if (si) {
			delete si;
		}
	}

	m_sciences.clear();
}

//-----------------------------------------------------------------------------
// ?reset@ScienceStore@@ present-unmatched
void ScienceStore::reset()
{
	// nope.
	//m_sciences.clear();

	// go through all sciences and delete any overrides
	for (ScienceInfoVec::iterator it = m_sciences.begin(); it != m_sciences.end(); /*++it*/)
	{
		ScienceInfo* si = *it;
		Overridable* temp = si->deleteOverrides();
		if (!temp)
		{
			it = m_sciences.erase(it);
		}
		else
		{
			++it;
		}
	}
}

//-----------------------------------------------------------------------------
ScienceType ScienceStore::getScienceFromInternalName(const AsciiString& name) const
{
	if (name.isEmpty())
		return SCIENCE_INVALID;
	NameKeyType nkt = TheNameKeyGenerator->nameToKey(name);
	ScienceType st = (ScienceType)nkt;
	return st;
}

//-----------------------------------------------------------------------------
__declspec(naked) AsciiString ScienceStore::getInternalNameForScience(ScienceType science) const
{
	__asm {
		__emit 0x51;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x83;
		__emit 0xf8;
		__emit 0xff;
		__emit 0x56;
		__emit 0x8b;
		__emit 0x74;
		__emit 0x24;
		__emit 0x0c;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x75;
		__emit 0x13;
		__emit 0x68;
		__emit 0x50;
		__emit 0x6e;
		__emit 0x33;
		__emit 0x01;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x4d;
		__emit 0x09;
		__emit 0x7a;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xc6;
		__emit 0x5e;
		__emit 0x59;
		__emit 0xc2;
		__emit 0x08;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0x56;
		__emit 0xe8;
		__emit 0x53;
		__emit 0x7a;
		__emit 0xf5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xc6;
		__emit 0x5e;
		__emit 0x59;
		__emit 0xc2;
		__emit 0x08;
		__emit 0x00;
	}
}

//-----------------------------------------------------------------------------
// return a vector of all the currently-known science names
// NOTE: this is really only for use by WorldBuilder! Please
// do not use it in RTS!
std::vector<AsciiString> ScienceStore::friend_getScienceNames() const
{
	std::vector<AsciiString> v;
	for (ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it)
	{
		const ScienceInfo* si = (const ScienceInfo*)(*it)->getFinalOverride();
		NameKeyType nk = (NameKeyType)(si->m_science);
		v.push_back(TheNameKeyGenerator->keyToName(nk));
	}
	return v;
}

//-----------------------------------------------------------------------------
// ?addRootSciences@ScienceInfo@@ present-unmatched
// Still here, unlike its Zero Hour caller: friend_parseScienceDefinition does
// not call this in BFME, but the TU still instantiates std::find over a
// ScienceVec, which is where the matched __find/find at 0x0018B470/0x0018B590
// come from. Nothing else in this file emits them.
void ScienceInfo::addRootSciences(ScienceVec& v) const
{
	if (m_prereqSciences.empty())
	{
		// we're a root. add ourselves.
		if (std::find(v.begin(), v.end(), m_science) == v.end())
			v.push_back(m_science);
	}
	else
	{
		// we're not a root. add the roots of all our prereqs.
		for (ScienceVec::const_iterator it = m_prereqSciences.begin(); it != m_prereqSciences.end(); ++it)
		{
			const ScienceInfo* si = TheScienceStore->findScienceInfo(*it);
			if (si)
				si->addRootSciences(v);
		}
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
const ScienceInfo* ScienceStore::findScienceInfo(ScienceType st) const
{
	for (ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it)
	{
		const ScienceInfo* si = (const ScienceInfo*)(*it)->getFinalOverride();
		if (si->m_science == st)
		{
			return si;
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
/*static*/ void ScienceStore::friend_parseScienceDefinition( INI* ini )
{
	const char* c = ini->getNextToken();
	NameKeyType nkt = NAMEKEY(c);
	ScienceType st = (ScienceType)nkt;

	if (TheScienceStore)
	{

		static const FieldParse myFieldParse[] =
		{
			{ "PrerequisiteSciences", INI::parseScienceVector, NULL, offsetof( ScienceInfo, m_prereqSciences ) },
			{ "SciencePurchasePointCost", INI::parseInt, NULL, offsetof( ScienceInfo, m_sciencePurchasePointCost ) },
			{ "SciencePurchasePointCostMP", INI::parseInt, NULL, offsetof( ScienceInfo, m_sciencePurchasePointCostMP ) },
			{ "IsGrantable", INI::parseBool, NULL, offsetof( ScienceInfo, m_grantable ) },
			{ "DisplayName", INI::parseAndTranslateLabel, NULL, offsetof( ScienceInfo, m_name) },
			{ "Description", INI::parseAndTranslateLabel, NULL, offsetof( ScienceInfo, m_description) },
			{ 0, 0, 0, 0 }
		};

		ScienceInfo* info = NULL;

		// see if the science already exists. (can't use findScienceInfo() since it is const and should remain so.)
		for (ScienceInfoVec::iterator it = TheScienceStore->m_sciences.begin(); it != TheScienceStore->m_sciences.end(); ++it)
		{
			// note that we don't use getFinalOverride here. this is correct and as-desired.
			if ((*it)->m_science == st)
			{
				info = *it;
				break;
			}
		}

		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) 
		{
			ScienceInfo* newInfo = newInstance(ScienceInfo);
			
			if (info == NULL)
			{
				// only add if it's not overriding an existing one.
				info = newInfo;
				info->markAsOverride();	// yep, so we will get cleared on reset()
				TheScienceStore->m_sciences.push_back(info);
			}
			else
			{
				// copy data from final override to 'newInfo' as a set of initial default values
				info = (ScienceInfo*)(info->friend_getFinalOverride());

				*newInfo = *info;
				info->setNextOverride(newInfo);
				newInfo->markAsOverride();	// must do AFTER the copy

				// use the newly created override for us to set values with etc
				info = newInfo;
				//TheScienceStore->m_sciences.push_back(info);	// NO, BAD, WRONG -- don't add in this case.
			}
		} 
		else
		{
			if (info != NULL)
			{
				// Zero Hour logs this with DEBUG_CRASH and then throws the bare
				// INI_INVALID_DATA; BFME carries the message into the exception,
				// so it survives into a release build.
				throw INIException(3, "duplicate science %s!\n", c);
			}
			info = newInstance(ScienceInfo);
			TheScienceStore->m_sciences.push_back(info);
		}

		ini->initFromINI(info, myFieldParse);
		info->m_science = st;
		// no addRootSciences here: BFME has no m_rootSciences (see Science.h)
	}
}

//-----------------------------------------------------------------------------
// BFME-only global reads, proven byte-identical against the already-matched
// GameLogic.cpp (TheGameLogic->m_gameMode lives at +0x10c there too, see
// GameLogic::isInSinglePlayerGame) and against retail bytes at 0x49F8B0
// (ControlBar::setControlBarSchemeByPlayer, matched) which reference the same
// TheGameLogic global address 0x12F0898. TheRecorder lives at 0x12ED62C
// (proven the same way against GameLogic::isInSinglePlayerGame's retail
// bytes). Declared locally rather than pulling in the real GameLogic.h /
// Recorder.h (heavy, unrelated dependencies) -- only the mangled names need
// to match.
class GameLogic;
extern GameLogic* TheGameLogic;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	Bool isMultiplayer(void);
};
extern RecorderClass* TheRecorder;

Int ScienceStore::getSciencePurchaseCost(ScienceType st) const
{
	const ScienceInfo* si = findScienceInfo(st);
	if (si)
	{
		// ZH GameLogic.h unnamed enum: GAME_SINGLE_PLAYER=0, GAME_LAN=1,
		// GAME_SKIRMISH=2, GAME_REPLAY=3, GAME_SHELL=4, GAME_INTERNET=5,
		// GAME_NONE=6. Online modes (and a multiplayer replay of one) use the
		// BFME-added alt cost field; everything else uses the normal cost.
		const Int mode = *reinterpret_cast<const Int*>(reinterpret_cast<const char*>(TheGameLogic) + 0x10c);
		if (mode == 1 /*GAME_LAN*/ || mode == 5 /*GAME_INTERNET*/ || mode == 2 /*GAME_SKIRMISH*/ ||
			(mode == 3 /*GAME_REPLAY*/ && TheRecorder && TheRecorder->isMultiplayer()))
		{
			return si->m_sciencePurchasePointCostMP;
		}
		return si->m_sciencePurchasePointCost;
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
Bool ScienceStore::isScienceGrantable(ScienceType st) const
{
	const ScienceInfo* si = findScienceInfo(st);
	if (si)
	{
		return si->m_grantable;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
Bool ScienceStore::getNameAndDescription(ScienceType st, UnicodeString& name, UnicodeString& description) const
{
	const ScienceInfo* si = findScienceInfo(st);
	if (si)
	{
		name = si->m_name;
		description = si->m_description;
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
// BFME layout drift (see Science.h): m_prereqSciences is not ZH's flat
// ScienceVec here -- retail stores an OR-of-AND group structure at the same
// [this+0x18]/[this+0x1c] begin/end slot: an outer std::vector<ScienceVec>
// (0xc-byte/group stride) of inner std::vector<ScienceType> groups (4-byte/
// item stride). A player qualifies if ANY one group is fully satisfied.
// Reinterpreted in place rather than reshaping ScienceInfo's declared
// (ZH-flat) field type, which other still-unmatched accessors still rely on.
Bool ScienceStore::playerHasPrereqsForScience(const Player* player, ScienceType st) const
{
	const ScienceInfo* si = findScienceInfo(st);
	if (si)
	{
		struct RawGroup { ScienceType *begin, *end, *capEnd; };
		typedef const RawGroup* GroupIter;
		const char* base = reinterpret_cast<const char*>(si);
		GroupIter group = *reinterpret_cast<GroupIter const*>(base + 0x18);
		// The group-end pointer is re-read from [si+0x1c] at each test (not
		// hoisted into a local) to match retail's loop-rotated codegen, which
		// re-loads it both at loop entry and at the do-while back-edge.
		if (group != *reinterpret_cast<GroupIter const*>(base + 0x1c))
		{
			do
			{
				for (ScienceType* item = group->begin;; ++item)
				{
					if (item == group->end)
						return true;
					if (!player->hasScience(*item))
						break;
				}
				++group;
			} while (group != *reinterpret_cast<GroupIter const*>(base + 0x1c));
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
// Zero Hour's playerHasRootPrereqsForScience and getPurchasableSciences used to
// sit here. Both are built on ScienceInfo::m_rootSciences, which BFME does not
// have (Science.h has the proof: retail's ScienceInfo is exactly 0x30 bytes and
// friend_parseScienceDefinition never fills one in), so neither body can be
// right as written. Left out rather than guessed at.

//-----------------------------------------------------------------------------
// this is intended ONLY for use by INI::scanScience.
// Don't use it anywhere else. In particular, never, ever, ever
// call this with a hardcoded science name. (srj)
// ?friend_lookupScience@ScienceStore@@QBE?AW4ScienceType@@PBD@Z
ScienceType ScienceStore::friend_lookupScience(const char *scienceName) const
{
	NameKeyType nkt = NAMEKEY(scienceName);
	ScienceType st = (ScienceType)nkt;
	if (!isValidScience(st))
	{
		// BFME carries the diagnostic into the thrown object rather than a
		// DEBUG_CRASH that compiles away, so the message survives in release.
		throw INIException(3, "Science name %s not known! (Did you define it in Science.ini?)", scienceName);
	}
	return st;
}

//-----------------------------------------------------------------------------
Bool ScienceStore::isValidScience(ScienceType st) const
{
	const ScienceInfo* si = findScienceInfo(st);
	return si != NULL;
}

//-----------------------------------------------------------------------------
// ?parseScienceDefinition@INI@@ present-unmatched
void INI::parseScienceDefinition( INI* ini )
{
	ScienceStore::friend_parseScienceDefinition(ini);
}

