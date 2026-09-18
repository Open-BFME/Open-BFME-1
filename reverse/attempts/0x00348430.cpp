// ?reset@ScriptEngine@@UAEXXZ
// partial score=0.6 date=2026-09-17
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ScriptEngine::reset, retail 0x00348430, 1924 bytes.
//
// The BFME ScriptEngine layout is not the Zero Hour header layout.  The
// offsets below are witnessed by the reset body and by the neighbouring
// ScriptEngine bodies; the names stay local where the binary does not prove a
// semantic replacement.

#define private public
#include <algorithm>
#include <list>
#include <vector>
#undef private

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);

// BFME's one-pointer narrow string view.  The base operations resolve to the
// existing retail StringBase/UnicodeString bodies at 0x00887B60,
// 0x00887C90 and 0x00887940.
struct BfmeStringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	char m_text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

protected:
	StringBase(void) : m_data(0) {}
	__forceinline ~StringBase(void) { releaseBuffer(); }
	BfmeStringData *m_data;

private:
	StringBase(const StringBase &);
	void set(const StringBase &);
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	__forceinline ~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&that);
		return *this;
	}
	__forceinline void clear(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

// ScriptEngine's named-object vector is the one BFME list whose first field
// is the retail UnicodeString ABI.  Keep the public setter name here: it is
// the direct callee in reset's copy loop, rather than the AsciiString helper.
class UnicodeString : private StringBase<char>
{
public:
	UnicodeString(void) {}
	UnicodeString(const UnicodeString &that) : StringBase<char>(that) {}
	__forceinline ~UnicodeString(void) {}
	void set(const UnicodeString &that);
	__forceinline void clear(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

// The five map headers at +0x16040, +0x1604C, +0x16058, +0x16064 and
// +0x16070 all have the STLport tree header shape.  Their erase helpers are
// the exact ILT contracts printed by tools/callees.py.
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
extern void j_0000db2a(void);

typedef void (BfmeTree::*BfmeTreeErase)(BfmeTreeNode *);

#define BFME_CLEAR_TREE(TREE, THUNK) \
	do { \
		BfmeTree *tree = &(TREE); \
		if (tree->m_count != 0) { \
			union { void (*raw)(void); BfmeTreeErase member; } erase; \
			erase.raw = (THUNK); \
			(tree->*erase.member)(tree->m_header->m_parent); \
			tree->m_header->m_left = tree->m_header; \
			tree->m_header->m_parent = 0; \
			tree->m_header->m_right = tree->m_header; \
			tree->m_count = 0; \
		} \
	} while (0)

// AttackPriorityInfo is the 0x10-byte BFME record at +0x1607C.  Its reset
// helper is the j_00049b57 ILT (retail body 0x0034DDC0).
struct BfmeAttackPriorityInfo
{
	void *m_unknown;
	AsciiString m_name;
	Int m_defaultPriority;
	void *m_priorityMap;
};

extern void j_00049b57(void);

typedef void (BfmeAttackPriorityInfo::*BfmeAttackPriorityReset)(void);

static __forceinline void resetAttackPriorityInfo(BfmeAttackPriorityInfo *info)
{
	union { void (*raw)(void); BfmeAttackPriorityReset member; } reset;
	reset.raw = j_00049b57;
	(info->*reset.member)();
}

// SequentialScript's first virtual slot is its scalar-deleting destructor;
// the next link is witnessed at +0x28 by the reset loop.
class SequentialScript
{
public:
	virtual void deleteInstance(Int destroy) = 0;

	char m_beforeNext[0x24];
	SequentialScript *m_nextScriptInSequence;
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes();

	void deleteInstance(void)
	{
		delete this;
	}
};

// The reset dispatches use the fourth vtable slot after the two subsystem
// base slots, i.e. vtable +0x10.  Only that ABI is needed here.
class BfmeResetSubsystem
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void reset(void) = 0;
};

class GameEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void setFramesPerSecondLimit(Int fps) = 0;
};

class GlobalData
{
public:
	char m_beforeFps[0x24];
	Int m_framesPerSecondLimit;
};

class BfmeInGameUI_setInputEnabled
{
public:
	void setInputEnabled(Bool enabled);
};

class BfmeMouse_setVisibility
{
public:
	void setVisibility(Bool visible);
};

// Direct singleton addresses are used here because the evidence names the
// storage addresses, while their TU-local pointee types differ across the
// already-landed BFME shims.
#define TheGameEngine (*(GameEngine **)0x012ED524)
#define TheWritableGlobalData (*(GlobalData **)0x012ED5C8)
#define TheInGameUI (*(BfmeInGameUI_setInputEnabled **)0x012F148C)
#define TheMouse (*(BfmeMouse_setVisibility **)0x012F4C5C)
#define TheScriptActions (*(BfmeResetSubsystem **)0x012F0620)
#define TheScriptConditions (*(BfmeResetSubsystem **)0x012F06B0)

struct NamedReveal
{
	__forceinline ~NamedReveal(void)
	{
		m_player.clear();
		m_waypoint.clear();
		m_name.clear();
	}

	AsciiString m_name;
	AsciiString m_waypoint;
	Int m_word;
	AsciiString m_player;
};

struct NamedObject
{
	UnicodeString m_name;
	void *m_object;
};

struct BfmeNamedRevealVectorLayout
{
	NamedReveal *m_start;
	NamedReveal *m_finish;
	NamedReveal *m_endOfStorage;
};

static __forceinline void clearNamedRevealVector(
	std::vector<NamedReveal> &values)
{
	BfmeNamedRevealVectorLayout *raw =
		(BfmeNamedRevealVectorLayout *)&values;
	NamedReveal *first = raw->m_start;
	NamedReveal *last = raw->m_finish;
	NamedReveal *newEnd = _STL::__copy_ptrs(
		last, last, first, _STL::__false_type());

	for (NamedReveal *it = newEnd; it != last; ++it) {
		it->m_player.clear();
		it->m_waypoint.clear();
		it->m_name.clear();
	}
	raw->m_finish = newEnd;
}

struct BfmeNamedObjectVectorLayout
{
	NamedObject *m_start;
	NamedObject *m_finish;
	NamedObject *m_endOfStorage;
};

static __forceinline void clearNamedObjectVector(
	std::vector<NamedObject> &values)
{
	BfmeNamedObjectVectorLayout *raw =
		(BfmeNamedObjectVectorLayout *)&values;
	NamedObject *first = raw->m_start;
	NamedObject *last = raw->m_finish;
	NamedObject *newEnd = _STL::__copy_ptrs(
		last, raw->m_finish, first, _STL::__false_type());

	for (NamedObject *it = newEnd; it != last; ++it)
		it->m_name.clear();
	raw->m_finish = newEnd;
}

struct AsciiStringObjectIDPair
{
	AsciiString m_name;
	UnsignedInt m_objectID;
};
typedef std::list<AsciiString> ListAsciiString;
typedef std::list<AsciiStringObjectIDPair> ListAsciiStringObjectID;

struct BfmeListHeaderLayout
{
	BfmeListHeaderLayout *m_next;
	BfmeListHeaderLayout *m_previous;
};

struct BfmeListLayout
{
	BfmeListHeaderLayout *m_header;
};

static __forceinline void clearAsciiStringObjectIDList(
	std::list<AsciiStringObjectIDPair> &values)
{
	BfmeListHeaderLayout *header =
		((BfmeListLayout *)&values)->m_header;
	BfmeListHeaderLayout *node = header->m_next;
	while (node != header) {
		BfmeListHeaderLayout *next = node->m_next;
		((AsciiStringObjectIDPair *)((char *)node + 8))->m_name.clear();
		_STL::__node_alloc<true, 0>::_M_deallocate(node, 0x10);
		node = next;
	}
	header->m_next = header;
	header->m_previous = header;
}

struct AsciiStringCoord3DPair
{
	AsciiString m_name;
	Real m_x;
	Real m_y;
	Real m_z;
};

typedef std::list<AsciiStringCoord3DPair> ListAsciiStringCoord3D;

struct BreezeInfo
{
	Real m_direction;
	Real m_directionX;
	Real m_directionY;
	Real m_intensity;
	Real m_lean;
	Real m_randomness;
	UnsignedShort m_breezePeriod;
	UnsignedShort m_breezeVersion;
};

// The object-count tree's node is 0x18 bytes: STLport's four-pointer tree
// base followed by {AsciiString, Int}.
struct ObjectTypeCountNode
{
	void *m_links[4];
	AsciiString m_name;
	Int m_countValue;
};

struct ObjectTypeCount
{
	ObjectTypeCountNode *m_header;
	Int m_count;
	void *m_compare;
};

extern void j_0000d0d0(void);

typedef void (ObjectTypeCount::*ObjectTypeCountErase)(ObjectTypeCountNode *);

static __forceinline void clearObjectTypeCount(ObjectTypeCount *tree)
{
	if (tree->m_count != 0) {
		ObjectTypeCountNode *node = tree->m_header->m_links[1]
			? (ObjectTypeCountNode *)tree->m_header->m_links[1] : 0;
		while (node != 0) {
			union { void (*raw)(void); ObjectTypeCountErase member; } erase;
			erase.raw = j_0000d0d0;
			(tree->*erase.member)(
				(ObjectTypeCountNode *)node->m_links[3]);
			ObjectTypeCountNode *left =
				(ObjectTypeCountNode *)node->m_links[2];
			node->m_name.~AsciiString();
			_STL::__node_alloc<true, 0>::_M_deallocate(node, 0x18);
			node = left;
		}
		tree->m_header->m_links[2] = tree->m_header;
		tree->m_header->m_links[1] = 0;
		tree->m_header->m_links[3] = tree->m_header;
		tree->m_count = 0;
	}
}

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void reset(void);

private:
	char m_beforeSequentialScripts[8];
	std::vector<SequentialScript *> m_sequentialScripts;
	char m_beforeTrees[0x16040 - 0x18];
	BfmeTree m_counterTree;
	BfmeTree m_flagTree;
	BfmeTree m_unitReferenceTree;
	BfmeTree m_teamReferenceTree;
	BfmeTree m_humanImpassableTree;
	BfmeAttackPriorityInfo m_attackPriorityInfo[256];
	Int m_numAttackInfo;
	Int m_endGameTimer;
	Int m_closeWindowTimer;
	AsciiString m_unidentifiedString;
	void *m_callingTeam;
	void *m_callingObject;
	void *m_conditionTeam;
	void *m_conditionObject;
	std::vector<NamedObject> m_namedObjects;
	Bool m_firstUpdate;
	void *m_currentPlayer;
	void *m_skirmishHumanPlayer;
	Int m_fade;
	Bool m_fadeActive;
	Real m_minFade;
	Real m_maxFade;
	Real m_curFadeValue;
	Int m_curFadeFrame;
	Int m_fadeFramesIncrease;
	Int m_fadeFramesHold;
	Int m_fadeFramesDecrease;
	Int m_frameObjectCountChanged;
	Int m_unidentifiedDifficultyWord;
	ObjectTypeCount m_objectCounts[32];
	ListAsciiString m_completedVideo;
	std::list<AsciiStringObjectIDPair> m_testingSpeech;
	std::list<AsciiStringObjectIDPair> m_testingAudio;
	ListAsciiString m_uiInteractions;
	ListAsciiString m_unidentifiedList;
	ListAsciiStringObjectID m_triggeredSpecialPowers[32];
	ListAsciiStringObjectID m_midwaySpecialPowers[32];
	ListAsciiStringObjectID m_finishedSpecialPowers[32];
	ListAsciiStringObjectID m_completedUpgrades[32];
	std::vector<Int> m_acquiredSciences[32];
	ListAsciiStringCoord3D m_toppleDirections;
	std::vector<NamedReveal> m_namedReveals;
	BreezeInfo m_breezeInfo;
	Int m_gameDifficulty;
	Bool m_freezeByScript;
	char m_beforeAllObjectTypes[3];
	std::vector<ObjectTypes *> m_allObjectTypeLists;
	Bool m_objectsShouldReceiveDifficultyBonus;
	Bool m_ChooseVictimAlwaysUsesNormal;
	Bool m_shownMPLocalDefeatWindow;

	std::vector<SequentialScript *>::iterator cleanupSequentialScript(
		std::vector<SequentialScript *>::iterator it,
		Bool cleanDanglers)
	{
		SequentialScript *seqScript = *it;
		if (!seqScript)
			return m_sequentialScripts.erase(it);

		if (cleanDanglers) {
			while (seqScript) {
				SequentialScript *scriptToDelete = seqScript;
				seqScript = seqScript->m_nextScriptInSequence;
				scriptToDelete->deleteInstance(1);
			}
			*it = 0;
		}

		if (*it == 0)
			return m_sequentialScripts.erase(it);

		return it + 1;
	}

	__forceinline void removeObjectTypes(ObjectTypes *typesToRemove)
	{
		if (!typesToRemove)
			return;

		std::vector<ObjectTypes *>::iterator it = std::find(
			m_allObjectTypeLists.begin(), m_allObjectTypeLists.end(),
			typesToRemove);
		if (it == m_allObjectTypeLists.end())
			return;

		typesToRemove->deleteInstance();
		m_allObjectTypeLists.erase(it);
	}
};

extern void j_0001c5df(void);

// ?reset@ScriptEngine@@UAEXXZ
void ScriptEngine::reset(void)
{
	if (TheGameEngine && TheWritableGlobalData)
		TheGameEngine->setFramesPerSecondLimit(
			TheWritableGlobalData->m_framesPerSecondLimit);

	if (TheInGameUI)
		TheInGameUI->setInputEnabled(true);
	if (TheMouse)
		TheMouse->setVisibility(true);
	if (TheScriptActions)
		TheScriptActions->reset();
	if (TheScriptConditions)
		TheScriptConditions->reset();

	m_numAttackInfo = 1;
	m_endGameTimer = -1;
	m_closeWindowTimer = -1;
	m_firstUpdate = true;
	m_callingTeam = 0;
	m_callingObject = 0;
	m_conditionTeam = 0;
	m_conditionObject = 0;
	m_currentPlayer = 0;
	m_skirmishHumanPlayer = 0;
	m_frameObjectCountChanged = 0;
	m_unidentifiedDifficultyWord = 0;
	m_fade = 0;
	m_curFadeFrame = 0;
	m_minFade = 1.0f;
	m_maxFade = 0.0f;
	m_fadeFramesIncrease = 0;
	m_fadeFramesHold = 0;
	m_fadeFramesDecrease = 0;
	m_curFadeValue = 0.0f;
	m_fadeActive = false;
	m_shownMPLocalDefeatWindow = false;

	BFME_CLEAR_TREE(m_counterTree, j_00042294);
	BFME_CLEAR_TREE(m_flagTree, j_0002e361);
	BFME_CLEAR_TREE(m_unitReferenceTree, j_00027a75);
	BFME_CLEAR_TREE(m_teamReferenceTree, j_000366ab);
	BFME_CLEAR_TREE(m_humanImpassableTree, j_0000db2a);

	const Real pi = 3.14159265358979323846f;
	m_breezeInfo.m_direction = pi / 3.0f;
	m_breezeInfo.m_directionX = sinf(m_breezeInfo.m_direction);
	m_breezeInfo.m_directionY = cosf(m_breezeInfo.m_direction);
	m_breezeInfo.m_intensity = 0.07f * pi / 8.0f;
	m_breezeInfo.m_lean = pi / 200.0f;
	m_breezeInfo.m_breezePeriod = 10 * 5;
	m_breezeInfo.m_randomness = 0.2f;
	m_breezeInfo.m_breezeVersion = 0;

	m_freezeByScript = false;
	m_gameDifficulty = 1;
	m_objectsShouldReceiveDifficultyBonus = true;
	m_ChooseVictimAlwaysUsesNormal = false;

	for (std::vector<SequentialScript *>::iterator it =
		m_sequentialScripts.begin(); it != m_sequentialScripts.end(); )
		it = cleanupSequentialScript(it, true);

	for (std::vector<ObjectTypes *>::iterator it =
		m_allObjectTypeLists.begin(); it != m_allObjectTypeLists.end();
		it = m_allObjectTypeLists.begin()) {
		if (*it)
			removeObjectTypes(*it);
		else
			m_allObjectTypeLists.erase(it);
	}

	clearNamedRevealVector(m_namedReveals);
	clearNamedObjectVector(m_namedObjects);

	m_completedVideo.clear();
	m_uiInteractions.clear();
	clearAsciiStringObjectIDList(m_testingSpeech);
	clearAsciiStringObjectIDList(m_testingAudio);
	m_unidentifiedList.clear();

	for (Int i = 0; i < 32; ++i) {
		clearAsciiStringObjectIDList(m_triggeredSpecialPowers[i]);
		clearAsciiStringObjectIDList(m_midwaySpecialPowers[i]);
		clearAsciiStringObjectIDList(m_finishedSpecialPowers[i]);
		clearAsciiStringObjectIDList(m_completedUpgrades[i]);
		m_acquiredSciences[i].clear();
	}

	j_0001c5df();

	for (Int i = 0; i < 256; ++i)
		resetAttackPriorityInfo(&m_attackPriorityInfo[i]);

	for (Int i = 0; i < 32; ++i)
		clearObjectTypeCount(&m_objectCounts[i]);

	m_toppleDirections.clear();
}
