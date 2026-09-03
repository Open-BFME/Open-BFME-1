// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// BFME W3DTreeBuffer::pushAsideTree.  The tree records begin at +0x1548 and
// retain the Zero Hour push-aside algorithm with BFME's +0x40 tree-type,
// +0x5c drawable, and +0x70..+0x74 push bookkeeping fields.

#include "Lib/BaseType.h"
#include "Common/GameType.h"

class GlobalData
{
};

extern GlobalData *TheWritableGlobalData;

class GameLogic
{
public:
	int getFrame(void) const
	{
		return *(const int *)((const char *)this + 0x3c);
	}
};

extern GameLogic *TheBfmeGameLogic;

struct BfmeTreeData
{
	char m_pad00[0x10];
	UnsignedInt m_framesToMoveOutward;
};

struct BfmeTreeType
{
	BfmeTreeData *m_data;
	char m_pad04[0x58];
};

struct BfmeTree
{
	Coord3D m_location;
	char m_pad0c[0x34];
	int m_treeType;
	char m_pad44[0x18];
	DrawableID m_drawableID;
	Real m_pushAside;
	Real m_pushAsideDelta;
	Real m_pushAsideSin;
	Real m_pushAsideCos;
	ObjectID m_pushAsideSource;
	UnsignedInt m_lastFrameUpdated;
	char m_pad78[0x2c];
};

class W3DTreeBuffer
{
public:
	void pushAsideTree(DrawableID id, const Coord3D *pusherPos,
		const Coord3D *pusherDirection, ObjectID pusherID);

private:
	char m_pad00[0x1548];
	BfmeTree m_trees[12000];
	Int m_numTrees;
	UnsignedByte m_anythingChanged;
	UnsignedByte m_anyPushChanged;
	UnsignedByte m_updateAllKeys;
	char m_pad1e1ccf[0x25];
	BfmeTreeType m_treeTypes[64];
};

void W3DTreeBuffer::pushAsideTree(DrawableID id, const Coord3D *pusherPos,
	const Coord3D *pusherDirection, ObjectID pusherID)
{
	if (*(const unsigned char *)((const char *)TheWritableGlobalData + 0x18) == 0)
		return;

	Int i;
	for (i=0; i<m_numTrees; i++) {
		BfmeTree *tree = &m_trees[i];
		if (tree->m_drawableID == id) {
			UnsignedInt lastFrame = tree->m_lastFrameUpdated;
			tree->m_lastFrameUpdated = TheBfmeGameLogic->getFrame();
			if (tree->m_pushAsideSource == pusherID) {
				if (tree->m_lastFrameUpdated - lastFrame < 3)
					return;
			}

			if (tree->m_pushAside != 0.0f)
				return;

			tree->m_pushAsideSource = pusherID;
			Coord3D delta;
			delta.set(tree->m_location.x, tree->m_location.y, tree->m_location.z);
			delta.sub(pusherPos);
			if (pusherDirection->x * delta.y - pusherDirection->y * delta.x > 0.0f) {
				tree->m_pushAsideCos = -pusherDirection->y;
				tree->m_pushAsideSin = pusherDirection->x;
			} else {
				tree->m_pushAsideCos = pusherDirection->y;
				tree->m_pushAsideSin = -pusherDirection->x;
			}

			m_anyPushChanged = 1;
			tree->m_pushAsideDelta = 1.0f / ((Real)m_treeTypes[tree->m_treeType].m_data->m_framesToMoveOutward * *(Real *)((char *)this + 0x1e3910));
		}
	}
}
