// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ScienceStore::playerHasRootPrereqsForScience, retail 0x000E8040.
//
// The control-bar callers pass TheScienceStore, a Player pointer, and a
// ScienceType to this two-argument member before checking hasScience,
// playerHasPrereqsForScience, and the purchase cost.  Retail constructs a
// temporary STLport map<int,bool> and hands it to the three-argument recursive
// science prerequisite helper at 0x000E7C20.  The helper's original spelling
// is not established by the available headers, so its TU-local declaration is
// deliberately address-derived and pinned to the verified retail body; the
// compiler's call resolver selects the image's incremental thunk at each site.

#include <map>

typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Player;

class Player
{
public:
	Bool hasScience( ScienceType st ) const;
};

struct SciencePrereqGroup
{
	ScienceType *m_begin;
	ScienceType *m_end;
	ScienceType *m_capacity;
};

class ScienceInfo
{
public:
	char m_head[ 0x18 ];
	SciencePrereqGroup *m_prereqGroups;
	SciencePrereqGroup *m_prereqGroupsEnd;
};

class ScienceStore
{
public:
	Bool playerHasRootPrereqsForScience( const Player *player, ScienceType st ) const;

private:
	const ScienceInfo *findScienceInfo( ScienceType st ) const;

	Bool rva000E7C20SciencePrereqMemo( const Player *player, ScienceType st,
		void *memo ) const;
};

Bool ScienceStore::rva000E7C20SciencePrereqMemo( const Player *player, ScienceType st,
	void *memo ) const
{
	std::map<ScienceType, Bool> *values = (std::map<ScienceType, Bool> *)memo;
	std::map<ScienceType, Bool>::iterator found = values->find( st );
	if ( found != values->end() )
		return found->second;

	Bool result;
	if ( player->hasScience( st ) )
	{
		result = true;
	}
	else
	{
		result = false;
		const ScienceInfo *science = findScienceInfo( st );
		if ( science )
		{
			SciencePrereqGroup *group = science->m_prereqGroups;
			if ( group != science->m_prereqGroupsEnd )
			{
				do
				{
					ScienceType *item = group->m_begin;
					Bool groupOK = true;
					if ( item != group->m_end )
					{
						do
						{
							if ( !rva000E7C20SciencePrereqMemo( player, *item, memo ) )
							{
								groupOK = false;
								break;
							}
							++item;
						} while ( item != group->m_end );
					}
					if ( groupOK )
					{
						result = true;
						break;
					}
					++group;
				}
				while ( group != science->m_prereqGroupsEnd );
			}
		}
	}

	values->insert( std::make_pair( st, result ) );
	return result;
}

Bool ScienceStore::playerHasRootPrereqsForScience( const Player *player, ScienceType st ) const
{
	std::map<ScienceType, Bool> memo;
	return rva000E7C20SciencePrereqMemo( player, st, &memo );
}
