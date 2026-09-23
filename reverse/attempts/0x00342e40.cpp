// ?newMap@ScriptEngine@@UAEXXZ
// partial score=0.8394711992445704 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
// ScriptEngine::newMap at retail 0x00342E40.  The vtable slot, ScriptEngine
// field offsets, and BFME table ABI are independently witnessed in the repo.

#include <list>
#include <utility>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
// The released NameKeyGenerator.h and matched KEYNAME at 0x00098B70
// prove this is the 32-bit enum rather than an int typedef. The enum is
// only forwarded here to avoid importing the unreconstructed subsystem graph.
enum NameKeyType;

enum ScienceType
{
	Rva00342E40ScienceType = 0
};

#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
#include "Common/LatchRestore.h"

extern AsciiString KEYNAME(NameKeyType key);

class Player
{
public:
	NameKeyType getNameKey() const { return m_playerNameKey; }
	char m_beforeNameKey[0x20];
	NameKeyType m_playerNameKey;
};

class PlayerList
{
public:
	Player *getNthPlayer(Int index);
};

extern PlayerList *ThePlayerList;

class Rva0033E490Owner
{
public:
	void update(void *first, void *second);
};

extern void j_00023736(void);

static __forceinline void callRva0033E490(
	Rva0033E490Owner *owner, void *first, void *second)
{
	typedef void (Rva0033E490Owner::*Call)(void *, void *);
	union
	{
		void (*raw)(void);
		Call typed;
	} call;
	call.raw = j_00023736;
	(owner->*call.typed)(first, second);
}

struct BfmeTreeNode
{
	void *m_color;
	BfmeTreeNode *m_parent;
	BfmeTreeNode *m_left;
	BfmeTreeNode *m_right;
};

struct BfmeTree
{
	BfmeTreeNode *m_header;
	Int m_count;
	void *m_compare;
};

extern void j_00042294(void);
extern void j_0002e361(void);
extern void j_00027a75(void);
extern void j_000366ab(void);

typedef void (BfmeTree::*BfmeTreeErase)(BfmeTreeNode *);

static __forceinline void clearTree(BfmeTree *tree, void (*raw)(void))
{
	if (tree->m_count != 0)
	{
		union
		{
			void (*raw)(void);
			BfmeTreeErase typed;
		} erase;
		erase.raw = raw;
		(tree->*erase.typed)(tree->m_header->m_parent);
		tree->m_header->m_left = tree->m_header;
		tree->m_header->m_parent = 0;
		tree->m_header->m_right = tree->m_header;
		tree->m_count = 0;
	}
}

struct BfmeListHeader
{
	BfmeListHeader *m_next;
	BfmeListHeader *m_previous;
};

typedef _STL::pair<AsciiString, UnsignedInt> BfmePair;
typedef _STL::list<BfmePair> BfmeList;

namespace _STL
{
template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::begin;
	using vector<Type, Allocator>::end;
	using vector<Type, Allocator>::erase;
	using vector<Type, Allocator>::clear;
};
}

typedef _STL::public_vector<ScienceType, _STL::allocator<ScienceType> > ScienceVector;

class StringList
{
public:
	BfmeListHeader *m_header;
	void clear(void)
	{
		extern void j_0001900b(void);
		typedef void (StringList::*Call)(void);
		union
		{
			void (*raw)(void);
			Call typed;
		} call;
		call.raw = j_0001900b;
		(this->*call.typed)();
	}
};

class PairStringList
{
public:
	BfmeListHeader *m_header;
	void clear(void)
	{
		extern void j_000191af(void);
		typedef void (PairStringList::*Call)(void);
		union
		{
			void (*raw)(void);
			Call typed;
		} call;
		call.raw = j_000191af;
		(this->*call.typed)();
	}
};

struct BfmeValueRecord
{
	Int m_state;
	char m_beforeSecond[4];
	void *m_second;
	void *m_first;
	char *m_offset10;
};

struct BfmeTableValue
{
    char *Rva00342E40word10(Int i) { return m_records[i].m_offset10; }
    void *Rva00342E40address08(Int i) { return &m_records[i].m_second; }
    Int Rva00342E40next(Int i) { return m_records[i].m_state; }

	char m_beforeRecords[0x38];
	BfmeValueRecord *m_records;
	char m_beforeIndex[0x0c];
	Int m_index;
};

struct BfmeTableEntry
{
	char m_beforeValue[8];
	BfmeTableValue *m_value;
	char m_afterValue[12];
};

class BfmeTableERJ
{
public:
	Int getCount() const { return m_count; }
	BfmeTableEntry *at(Int index)
	{
		if (index >= 0 && index < m_count)
			return m_entries + index;
		return 0;
	}

	char m_beforeCount[0x28];
	Int m_count;
	BfmeTableEntry m_entries[1];
};

extern BfmeTableERJ *g_bfmeTableERJ;

struct BfmeStringHold
{
	void *m_vtable;
	void *m_data;
	AsciiString *m_target;
};

struct BreezeInfo
{
	float m_direction;
	float m_directionX;
	float m_directionY;
	float m_intensity;
	float m_lean;
	float m_randomness;
	short m_breezePeriod;
	short m_breezeVersion;
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void newMap(void);

private:
	char m_beforeSequentialScripts[8];
	char m_sequentialScripts[12];
	char m_beforeTrees[0x16040 - 0x1c];
	BfmeTree m_counterTree;
	BfmeTree m_flagTree;
	BfmeTree m_unitReferenceTree;
	BfmeTree m_teamReferenceTree;
	BfmeTree m_humanImpassableTree;
	char m_attackPriorityInfo[0x1000];
	Int m_numAttackInfo;
	Int m_endGameTimer;
	Int m_closeWindowTimer;
	AsciiString m_unidentifiedString;
	void *m_callingTeam;
	void *m_callingObject;
	void *m_conditionTeam;
	void *m_conditionObject;
	char m_namedObjects[12];
	Bool m_firstUpdate;
	char m_paddingFirstUpdate[3];
	void *m_currentPlayer;
	void *m_skirmishHumanPlayer;
	Int m_fade;
	Bool m_fadeActive;
	char m_paddingFadeActive[3];
	float m_minFade;
	float m_maxFade;
	float m_curFadeValue;
	Int m_curFadeFrame;
	Int m_fadeFramesIncrease;
	Int m_fadeFramesHold;
	Int m_fadeFramesDecrease;
	Int m_frameObjectCountChanged;
	Int m_unidentifiedDifficultyWord;
	BfmeTree m_objectCounts[32];
	StringList m_completedVideo;
	PairStringList m_testingSpeech;
	PairStringList m_testingAudio;
	StringList m_uiInteractions;
	StringList m_unidentifiedList;
	BfmeList m_triggeredSpecialPowers[32];
	BfmeList m_midwaySpecialPowers[32];
	BfmeList m_finishedSpecialPowers[32];
	BfmeList m_completedUpgrades[32];
	ScienceVector m_acquiredSciences[32];
	BfmeList m_toppleDirections;
	char m_namedReveals[12];
	BreezeInfo m_breezeInfo;
	Int m_gameDifficulty;
	Bool m_freezeByScript;
	char m_beforeAllObjectTypes[3];
	char m_allObjectTypeLists[12];
	Bool m_objectsShouldReceiveDifficultyBonus;
	Bool m_chooseVictimAlwaysUsesNormal;
	Bool m_shownMPLocalDefeatWindow;
	char m_paddingDebugFrame;
	Bool m_useLogicDebugFrame;
	char m_paddingProfiling;
	double m_numFrames;
	double m_totalUpdateTime;
	double m_maxUpdateTime;
	double m_curUpdateTime;
};

void ScriptEngine::newMap(void)
{
	clearTree(&m_counterTree, j_00042294);
	clearTree(&m_flagTree, j_0002e361);
	clearTree(&m_unitReferenceTree, j_00027a75);
	clearTree(&m_teamReferenceTree, j_000366ab);

	m_numFrames = 0;
	m_endGameTimer = -1;
	m_totalUpdateTime = 0;
	m_closeWindowTimer = -1;
	m_maxUpdateTime = 0;

	m_completedVideo.clear();
	m_uiInteractions.clear();
	m_testingSpeech.clear();
	m_testingAudio.clear();
	m_unidentifiedList.clear();

	ScienceVector *acquired = m_acquiredSciences;
	BfmeList *special = m_midwaySpecialPowers;
	Int count = 32;
	do
	{
		special[-32].clear();
		special[0].clear();
		special[32].clear();
		acquired->clear();
		special[64].clear();
		++special;
		++acquired;
		--count;
	} while (count != 0);

	for (Int i = 0; i < g_bfmeTableERJ->getCount(); ++i)
	{
		Player *player = ThePlayerList->getNthPlayer(i);
		m_currentPlayer = player;
        LatchRestore<AsciiString> restore(m_unidentifiedString, KEYNAME(player->getNameKey()));
        BfmeTableEntry *entry = g_bfmeTableERJ->at(i);
        BfmeTableValue *value = entry->m_value;
        if (value != 0)
        {
            for (Int index = value->m_index; index != -1; )
            {
                callRva0033E490((Rva0033E490Owner *)this,
                    *(char **)(index * 20 + (unsigned)value->m_records + 16) + 4,
                    value->Rva00342E40address08(index));
                index = value->Rva00342E40next(index);
            }
        }

	}

	m_curFadeFrame = 0;
	m_maxFade = 0;
	m_fadeFramesIncrease = 0;
	m_fadeFramesHold = 0;
	m_fadeFramesDecrease = 0;
	m_curFadeValue = 0;
	m_firstUpdate = true;
	m_fade = 4;
	m_minFade = 1.0f;
}
