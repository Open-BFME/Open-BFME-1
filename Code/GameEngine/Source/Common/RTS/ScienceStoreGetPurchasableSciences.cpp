// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ScienceStore::getPurchasableSciences, retail 0x000E7D30 (479 bytes).
//
// Zero Hour twin: GeneralsMD Common/RTS/Science.cpp. BFME keeps the shape --
// clear both output vectors, walk m_sciences through each final override,
// skip unpurchasable and already-owned sciences, then sort the rest into
// purchasable and potentially-purchasable -- with two BFME changes the bytes
// show. The cost test is getSciencePurchaseCost (0x000E6D70) inlined, with its
// findScienceInfo walk and the multiplayer cost field. And the root-prereq test
// is the memoised helper at 0x000E7C20 fed one map<ScienceType,Bool> built
// before the loop (the __new_alloc header allocation up front, its _Rb_tree
// destructor 0x000E74C0 at the end), not playerHasRootPrereqsForScience, which
// builds a fresh map per call.

#include <map>
#include <vector>

typedef bool Bool;
typedef int Int;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

typedef std::vector<ScienceType> ScienceVec;

class Player
{
public:
	Bool hasScience( ScienceType st ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_unmodelled00;
	Overridable *m_nextOverride;
};

// Offsets from reference/shims/science/Common/Science.h (pinned by
// friend_parseScienceDefinition@0xE8630): m_science +0x0C, the purchase cost
// +0x24, and the BFME multiplayer cost +0x28 that the Science field table at
// 0x01084D40 binds to "SciencePurchasePointCostMP".
class ScienceInfo : public Overridable
{
	friend class ScienceStore;

	Int m_unmodelled08;
	ScienceType m_science;
	char m_unmodelled10[ 0x14 ];
	Int m_sciencePurchasePointCost;
	Int m_sciencePurchasePointCostMP;
};

class GameLogic;
extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	Bool isMultiplayer( void );
};
extern RecorderClass *TheRecorder;

class ScienceStore
{
public:
	Bool playerHasPrereqsForScience( const Player *player, ScienceType st ) const;

	Int getSciencePurchaseCost( ScienceType st ) const
	{
		const ScienceInfo *si = findScienceInfo( st );
		if ( si )
		{
			// The game-mode word at TheGameLogic+0x10C, read exactly as the
			// landed getSciencePurchaseCost (0x000E6D70) reads it.
			const Int mode = *reinterpret_cast<const Int *>( reinterpret_cast<const char *>( TheGameLogic ) + 0x10c );
			if ( mode == 1 || mode == 5 || mode == 2 ||
				( mode == 3 && TheRecorder && TheRecorder->isMultiplayer() ) )
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

	void getPurchasableSciences( const Player *player, ScienceVec &purchasable,
		ScienceVec &potentiallyPurchasable ) const;

private:
	const ScienceInfo *findScienceInfo( ScienceType st ) const
	{
		for ( ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it )
		{
			const ScienceInfo *si = (const ScienceInfo *)( *it )->getFinalOverride();
			if ( si->m_science == st )
			{
				return si;
			}
		}
		return 0;
	}

	Bool rva000E7C20SciencePrereqMemo( const Player *player, ScienceType st,
		void *memo ) const;

	typedef std::vector<ScienceInfo *> ScienceInfoVec;

	void *m_unmodelled00;
	Int m_unmodelled04;
	ScienceInfoVec m_sciences;
};

void ScienceStore::getPurchasableSciences( const Player *player, ScienceVec &purchasable,
	ScienceVec &potentiallyPurchasable ) const
{
	std::map<ScienceType, Bool> memo;
	purchasable.clear();
	potentiallyPurchasable.clear();
	for ( ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it )
	{
		const ScienceInfo *si = (const ScienceInfo *)( *it )->getFinalOverride();

		if ( getSciencePurchaseCost( si->m_science ) == 0 )
		{
			// 0 means "cannot be purchased"
			continue;
		}

		if ( player->hasScience( si->m_science ) )
		{
			continue;
		}

		if ( playerHasPrereqsForScience( player, si->m_science ) )
		{
			purchasable.push_back( si->m_science );
		}
		else if ( rva000E7C20SciencePrereqMemo( player, si->m_science, &memo ) )
		{
			potentiallyPurchasable.push_back( si->m_science );
		}
	}
}
