// ?bfmeApplyPair@LivingWorldPlayerArmy@@QAEXPAX0@Z
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: BfmeLivingWorldCampaignManager replenish-pair helper at retail
// 0x003B4510 (102B). ILT 0x00040F39. Caller Glo012F1024Item::j_0002d3e4.
// Looks up two GameLogic keys via bfmeFindFGE, then either LivingWorldArmy::
// replenish (flag clear) or findArmy(name)->bfmeApplyPair (flag set).

#include "PreRTS.h"
#include <vector>

class AsciiString;

class LivingWorldPlayerArmy;

class LivingWorldArmy
{
public:
	LivingWorldArmy(const LivingWorldArmy &other);
	virtual ~LivingWorldArmy();
	void replenish(LivingWorldPlayerArmy *playerArmy);	// ILT 0x0002C66A
	AsciiString getName() const;

private:
	char m_body[0xB0];
};

class LivingWorldPlayerArmy
{
public:
	LivingWorldArmy *findArmy(const AsciiString &name, int *outIndex);
	void bfmeApplyPair(void *a, void *b);

private:
	char m_prefix[0x30];
	std::vector<LivingWorldArmy> m_armies;
};

class BfmeResFGE;

class BfmeGlobFGE
{
public:
	BfmeResFGE *bfmeFindFGE(void *key);			// ILT 0x0004AD0E
};

extern BfmeGlobFGE *g_bfmeGameLogic1294;			// 0x012F0898

class BfmeLivingWorldCampaignManager
{
public:
	void bfmeReplenishPair(void *keyA, void *keyB, void *nameRef, unsigned char useNamed);
	LivingWorldPlayerArmy *findArmy(const AsciiString &name);	// ILT 0x00010302
};

// ?bfmeReplenishPair@BfmeLivingWorldCampaignManager@@QAEXPAX00E@Z
void BfmeLivingWorldCampaignManager::bfmeReplenishPair(
	void *keyA, void *keyB, void *nameRef, unsigned char useNamed)
{
	LivingWorldArmy *left =
		(LivingWorldArmy *)g_bfmeGameLogic1294->bfmeFindFGE(keyA);
	LivingWorldPlayerArmy *right =
		(LivingWorldPlayerArmy *)g_bfmeGameLogic1294->bfmeFindFGE(keyB);
	if (!left || !right)
		return;
	if (!useNamed)
	{
		left->replenish(right);
		return;
	}
	LivingWorldPlayerArmy *army =
		findArmy(*(const AsciiString *)nameRef);
	if (army)
		army->bfmeApplyPair(left, right);
}

// ?bfmeApplyPair@LivingWorldPlayerArmy@@QAEXPAX0@Z
//
// The caller at 0x003B4510 passes the manager's 0x58-byte player-army
// record as this, and the two GameLogic results as the pair arguments.  Each
// record's army vector starts at +0x30 and contains the independently
// established 0xB4-byte polymorphic LivingWorldArmy records.  Retail walks
// this vector by an explicit byte offset, appends matching records to the
// second argument, then removes the source record by the returned index.
void LivingWorldPlayerArmy::bfmeApplyPair(void *a, void *b)
{
	LivingWorldPlayerArmy *source = (LivingWorldPlayerArmy *)a;
	static LivingWorldArmy *const empty = (LivingWorldArmy *)0;
	unsigned int i = 0;
	if( m_armies.size() != 0 )
	{
		unsigned int offset = 0;
		for( ; i < m_armies.size(); ++i, offset += sizeof( LivingWorldArmy ) )
		{
			LivingWorldArmy &army = *(LivingWorldArmy *)((char *)&m_armies[0] + offset);
			int sourceIndex;
			LivingWorldArmy *found;
			{
				AsciiString name = army.getName();
				found = source->findArmy( name, &sourceIndex );
			}
			if( found != empty )
			{
				LivingWorldPlayerArmy *destination = (LivingWorldPlayerArmy *)b;
				destination->m_armies.push_back( *found );
				if( sourceIndex >= 0 && (unsigned int)sourceIndex < source->m_armies.size() )
					source->m_armies.erase( source->m_armies.begin() + sourceIndex );
			}
		}
	}
}
