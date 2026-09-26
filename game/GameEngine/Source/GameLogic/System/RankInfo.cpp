// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: RankInfo.cpp /////////////////////////////////////////////////////////
// Created:   Steven Johnson, Sep 2002
// Desc:      
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/INI.h"
#include "Common/INIException.h"
#include "Common/Player.h"
#include "Common/Science.h"
#include "Common/UnicodeString.h"
#include "Common/STLTypedefs.h"
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
// BFME's 0x38-byte RankInfo has five words that the Zero Hour header omits.
class RankInfo : public Overridable
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( RankInfo, "RankInfo" );
public:
	RankInfo() throw();
	RankInfo &operator=(const RankInfo &);

	UnicodeString m_rankName;
	Int m_skillPointsNeeded;
	Int m_bfme_14;
	Int m_bfme_18;
	Int m_bfme_1c;
	Int m_bfme_20;
	Int m_bfme_24;
	Int m_sciencePurchasePointsGranted;
	ScienceVec m_sciencesGranted;
};

class RankInfoStore : public SubsystemInterface
{
public:
	virtual ~RankInfoStore();

	void init();
	void reset();
	void update() { }

	Int getRankLevelCount() const;
	const RankInfo* getRankInfo(Int level) const;
	static void friend_parseRankDefinition(INI* ini);

private:
	typedef std::vector<RankInfo*> RankInfoVec;
	RankInfoVec m_rankInfos;
};

extern RankInfoStore* TheRankInfoStore;

#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")

RankInfoStore* TheRankInfoStore = NULL;

typedef void (*RankInfoPlacementDelete)(void *, RankInfo::RankInfoMagicEnum);
RankInfoPlacementDelete g_rankInfoPlacementDelete = &RankInfo::operator delete;

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/System/RankInfoDestructors.cpp
// ??1RankInfo@@MAE@XZ present-unmatched
RankInfo::~RankInfo()
{
}


//-----------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/System/RankInfoDestructors.cpp
// ??1RankInfoStore@@UAE@XZ present-unmatched
RankInfoStore::~RankInfoStore()
{
	Int level;
	for (level =0; level < getRankLevelCount(); level++)
	{
		RankInfo* ri = m_rankInfos[level];
		if (ri)
		{
			ri->deleteInstance();
		}
	}
	m_rankInfos.clear();
}


//-----------------------------------------------------------------------------
void RankInfoStore::init()
{
	DEBUG_ASSERTCRASH(m_rankInfos.empty(), ("Hmm"));
	m_rankInfos.clear();
}

//-----------------------------------------------------------------------------
// BFME's reset uses the original three-field Overridable layout and deleting
// destructor, before Zero Hour's memory-pool deleteInstance path.
class BfmeRankOverrideView
{
public:
	virtual ~BfmeRankOverrideView();

	BfmeRankOverrideView *m_nextOverride;
	bool m_isOverride;

	BfmeRankOverrideView *deleteOverrides()
	{
		if (m_isOverride)
		{
			delete this;
			return NULL;
		}
		if (m_nextOverride)
			m_nextOverride = m_nextOverride->deleteOverrides();
		return this;
	}
};

void RankInfoStore::reset()
{
	for (RankInfoVec::iterator it = m_rankInfos.begin(); it != m_rankInfos.end(); /*++it*/)
	{
		BfmeRankOverrideView *ri = (BfmeRankOverrideView *)*it;
		if (ri)
		{
			BfmeRankOverrideView *temp = ri->deleteOverrides();
			if (!temp)
			{
				it = m_rankInfos.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

//-----------------------------------------------------------------------------
Int RankInfoStore::getRankLevelCount() const
{ 
	return m_rankInfos.size(); 
}

//-----------------------------------------------------------------------------
// note that level is 1...n, NOT 0...n-1
const RankInfo* RankInfoStore::getRankInfo(Int level) const 
{ 
	if (level >= 1 && level <= getRankLevelCount())
	{
		const RankInfo* ri = m_rankInfos[level-1];
		if (ri)
		{
			return (const RankInfo*)ri->getFinalOverride();
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ?parseRankDefinition@INI@@SAXPAV1@@Z present-unmatched
void INI::parseRankDefinition( INI* ini )
{
	RankInfoStore::friend_parseRankDefinition(ini);
}

void RankInfoStore::friend_parseRankDefinition( INI* ini )
{
	if (TheRankInfoStore)
	{
		Int rank = INI::scanInt(ini->getNextToken());

		static const FieldParse myFieldParse[] =
		{
			{ "RankName", INI::parseAndTranslateLabel, NULL, offsetof( RankInfo, m_rankName ) },
			{ "SkillPointsNeeded", INI::parseInt, NULL, offsetof( RankInfo, m_skillPointsNeeded ) },
			{ "SciencesGranted", INI::parseScienceVector, NULL, offsetof( RankInfo, m_sciencesGranted ) },
			{ "SciencePurchasePointsGranted", INI::parseUnsignedInt, NULL, offsetof( RankInfo, m_sciencePurchasePointsGranted ) },
			{ 0, 0, 0, 0 }
		};

		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
		{
			if (rank < 1 || rank > TheRankInfoStore->m_rankInfos.size())
			{
				throw INIException( 3, "Rank not found in map.ini" );
			}

			RankInfo* info = TheRankInfoStore->m_rankInfos[rank-1];
			if (!info)
			{
				throw INIException( 3, "Rank not found in map.ini" );
			}

			RankInfo* newInfo = newInstance(RankInfo);
			info = (RankInfo*)(info->friend_getFinalOverride());

			*newInfo = *info;
			info->setNextOverride(newInfo);
			newInfo->markAsOverride();

			ini->initFromINI(newInfo, myFieldParse);
		}
		else
		{
			if (rank != TheRankInfoStore->m_rankInfos.size() + 1)
			{
				throw INIException( 3, "Ranks must increase monotonically" );
			}
			RankInfo* info = newInstance(RankInfo);
			ini->initFromINI(info, myFieldParse);
			TheRankInfoStore->m_rankInfos.push_back(info);
		}
	}
}
