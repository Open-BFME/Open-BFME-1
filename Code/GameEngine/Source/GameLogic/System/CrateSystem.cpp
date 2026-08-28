// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: CrateSystem.cpp /////////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood Feb 2002
// Desc:   System responsible for Crates as code objects - ini, new/delete etc
///////////////////////////////////////////////////////////////////////////////////////////////////

#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>	// before PreRTS.h so node_alloc freelist is used (not NEWALLOC)
// BFME's KindOf list is longer than Zero Hour's, so KindOfMaskType is wider.
// Retail CrateTemplate zeroes six dwords for m_killedByTypeKindof (this+0x18
// through this+0x2F) where ZH's 121-bit mask needs four, which puts BFME's
// KINDOF_COUNT in (160,192]: std::bitset rounds to whole 32-bit words, so any
// count in that range gives the same six. Only the width is provable from
// these bytes - the names past ZH's list are not - so this substitutes a
// width-only KindOfMaskType rather than inventing enumerators. Scoped to this
// translation unit: reference/shims/bfmekindof/Common/KindOf.h carries the two
// extra names TunnelTracker proves, but it is still four dwords wide.
#define __KINDOF_H_
#include "Common/BitFlags.h"
enum KindOfType
{
	KINDOF_INVALID = -1,
	KINDOF_FIRST = 0,
	KINDOF_COUNT = 192						///< width pin only; see above
};
typedef BitFlags<KINDOF_COUNT>	KindOfMaskType;
#define MAKE_KINDOF_MASK(k) KindOfMaskType(KindOfMaskType::kInit, (k))
#define CLEAR_KINDOFMASK(m) ((m).clear())

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_VETERANCY_NAMES				// for TheVeterancyNames[]

#include "GameLogic/CrateSystem.h"
#include "Common/BitFlagsIO.h"

CrateSystem *TheCrateSystem = NULL;

CrateSystem::CrateSystem()
{
	m_crateTemplateVector.clear();
}

// BFME CrateSystem::~CrateSystem uses polymorphic `delete` (vtbl[0] + flag 1),
// not MemoryPoolObject::deleteInstance(). Pool-glue keeps ~CrateTemplate /
// operator delete protected; a local derived helper is the minimal access path.
namespace {
class CrateTemplateDeleteHelper : public CrateTemplate
{
public:
	static void destroy(CrateTemplate *p)
	{
		delete static_cast<CrateTemplateDeleteHelper *>(p);
	}
};
}

CrateSystem::~CrateSystem()
{
	Int count = m_crateTemplateVector.size();
	for( Int templateIndex = 0; templateIndex < count; templateIndex ++ )
	{
		CrateTemplate *currentTemplate = m_crateTemplateVector[templateIndex];
		if( currentTemplate )
		{
			CrateTemplateDeleteHelper::destroy(currentTemplate);
		}
	}
	m_crateTemplateVector.clear();
}

// ?init@CrateSystem@@UAEXXZ present-unmatched
void CrateSystem::init( void )
{
	reset();
}

// ?reset@CrateSystem@@UAEXXZ present-unmatched
void CrateSystem::reset( void )
{
	// clean up overrides
	std::vector<CrateTemplate *>::iterator it;
	for( it = m_crateTemplateVector.begin(); it != m_crateTemplateVector.end(); )
	{
		CrateTemplate *currentTemplate = *it;
		if( currentTemplate )
		{
			Overridable *tempCrateTemplate = currentTemplate->deleteOverrides();
			if (!tempCrateTemplate)
			{
				// base dude was an override - kill it from the vector
				it = m_crateTemplateVector.erase(it);
			}
			else
			{
				++it;
			}
		}
		else
		{
			it = m_crateTemplateVector.erase(it);
		}
	}
}

// BFME keeps m_loadType at INI+0x08; Zero Hour's header puts it at +0x2010
// because of the 8KB read buffer BFME does not have (docs/ini_loading.md).
static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

// BFME has a fourth INILoadType Zero Hour does not, value 4. Nothing names it.
static const INILoadType INI_LOAD_BFME_TYPE_4 = (INILoadType)4;

void CrateSystem::parseCrateTemplateDefinition(INI* ini)
{
	AsciiString name;

	// read the crateTemplate name. Assignment rather than set(c): BFME inlines
	// strlen and calls the two-argument set, which is what operator= expands to.
	name = ini->getNextToken();

	CrateTemplate *crateTemplate = TheCrateSystem->friend_findCrateTemplate(name);
	if (crateTemplate == NULL) {
		crateTemplate = TheCrateSystem->newCrateTemplate(name);

		if (retailLoadType(ini) == INI_LOAD_CREATE_OVERRIDES) {
			crateTemplate->markAsOverride();
		}
	} else {
		// Two load types take an override here, not one, and retail loads
		// m_loadType once and compares it twice -- hence the local.
		const INILoadType loadType = retailLoadType(ini);
		if (loadType == INI_LOAD_CREATE_OVERRIDES || loadType == INI_LOAD_BFME_TYPE_4) {
			crateTemplate = TheCrateSystem->newCrateTemplateOverride(crateTemplate);
		}
	}

	// parse the ini weapon definition
	ini->initFromINI(crateTemplate, crateTemplate->getFieldParse());
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/CrateSystem_newCrateTemplate_Thunk.cpp
// ?newCrateTemplate@CrateSystem@@QAEPAVCrateTemplate@@VAsciiString@@@Z present-unmatched
CrateTemplate *CrateSystem::newCrateTemplate( AsciiString name )
{
	// sanity
	if(name.isEmpty())
		return NULL;

	// allocate a new weapon
	CrateTemplate *ct = newInstance(CrateTemplate);

	// if the default template is present, get it and copy over any data to the new template
	const CrateTemplate *defaultCT = findCrateTemplate(AsciiString("DefaultCrate"));
	if(defaultCT)
	{
		*ct = *defaultCT;
	}

	ct->setName( name );
	m_crateTemplateVector.push_back(ct);

	return ct;
}

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/System/CrateSystem_newCrateTemplateOverride.cpp
// ?newCrateTemplateOverride@CrateSystem@@QAEPAVCrateTemplate@@PAV2@@Z present-unmatched
CrateTemplate *CrateSystem::newCrateTemplateOverride( CrateTemplate *crateToOverride )
{
	if (!crateToOverride) {
		return NULL;
	}

	CrateTemplate *newOverride = newInstance(CrateTemplate);
	*newOverride = *crateToOverride;

	newOverride->markAsOverride();

	crateToOverride->setNextOverride(newOverride);
	return newOverride;
}

// ?findCrateTemplate@CrateSystem@@QBEPBVCrateTemplate@@VAsciiString@@@Z present-unmatched
const CrateTemplate *CrateSystem::findCrateTemplate(AsciiString name) const
{
	// search weapon list for name
	for (Int i = 0; i < m_crateTemplateVector.size(); i++)
		if(m_crateTemplateVector[i]->getName() == name) {
			CrateTemplateOverride overridable(m_crateTemplateVector[i]);
			return overridable;
		}
		

	return NULL;
}

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/System/CrateSystem_friend_findCrateTemplate.cpp
// ?friend_findCrateTemplate@CrateSystem@@QAEPAVCrateTemplate@@VAsciiString@@@Z present-unmatched
CrateTemplate *CrateSystem::friend_findCrateTemplate(AsciiString name)
{
	// search weapon list for name
	for (Int i = 0; i < m_crateTemplateVector.size(); i++)
		if(m_crateTemplateVector[i]->getName() == name) {
			CrateTemplateOverride overridable(m_crateTemplateVector[i]);
			return const_cast<CrateTemplate*>((const CrateTemplate *)overridable);
		}
	return NULL;
}



//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
const FieldParse CrateTemplate::TheCrateTemplateFieldParseTable[] = 
{
	{ "CreationChance",		INI::parseReal,													NULL,									offsetof( CrateTemplate, m_creationChance ) },
	{ "VeterancyLevel",		INI::parseIndexList,										TheVeterancyNames,		offsetof( CrateTemplate, m_veterancyLevel ) },
	{ "KilledByType",			KindOfMaskType::parseFromINI,												NULL,									offsetof( CrateTemplate, m_killedByTypeKindof) },
	{ "CrateObject",			CrateTemplate::parseCrateCreationEntry,	NULL,									NULL },
	{ "KillerScience",		INI::parseScience,											NULL,									offsetof( CrateTemplate, m_killerScience) },
	{ "OwnedByMaker",			INI::parseBool,													NULL,									offsetof( CrateTemplate, m_isOwnedByMaker) },
	{ NULL,								NULL,																		NULL,									NULL },		// keep this last!
};

CrateTemplate::CrateTemplate()
{
	m_name = "";

	m_creationChance = 0;
	CLEAR_KINDOFMASK(m_killedByTypeKindof);
	m_veterancyLevel = LEVEL_INVALID;
	m_killerScience = SCIENCE_INVALID;
	m_possibleCrates.clear();
	m_isOwnedByMaker = FALSE;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/System/CrateTemplateDtor.cpp
// ??1CrateTemplate@@MAE@XZ present-unmatched
CrateTemplate::~CrateTemplate()
{
	m_possibleCrates.clear();
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/CrateTemplate_parseCrateCreationEntryMethodThunk.cpp
// ?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z present-unmatched
void CrateTemplate::parseCrateCreationEntry( INI* ini, void *instance, void *, const void*  )
{
	CrateTemplate *self = (CrateTemplate *)instance;

	const char *token = ini->getNextToken();
	AsciiString crateName = token;

	token = ini->getNextToken();
	Real crateValue;
	if (sscanf( token, "%f", &crateValue ) != 1)
		throw INI_INVALID_DATA;

	crateCreationEntry newEntry;
	newEntry.crateName = crateName;
	newEntry.crateChance = crateValue;

	self->m_possibleCrates.push_back( newEntry );
}

