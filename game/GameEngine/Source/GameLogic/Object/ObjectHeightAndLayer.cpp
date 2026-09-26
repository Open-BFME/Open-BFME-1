// cl: /DNDEBUG /MD /EHsc

// The three Object bodies about how this object sits above the terrain:
//
//   bfmeGetNonnegativePreferredLocomotorHeight 0x001BE030  the locomotor's height, clamped
//   bfmeHasSignificantPreferredLocomotorHeight 0x001BEF60  ...and is it worth acting on
//   bfmeExpireForcedGroundLayer                0x001BF150  drop a forced ground layer
//
// The first two are the same walk -- m_ai at +0x204, its m_curLocomotor at
// +0x1CC, getPreferredHeight, compared against the shared 0.0f at 0x01075350 --
// written out twice in two files, down to the same two class declarations. They
// differ only in what they do with the answer: one returns it, the other also
// tests it against BFME's 0.1 threshold. One copy of the walk now.
//
// The two files did disagree on one thing, and the ledger settles it: Bool.
// bfmeHasSignificant... typedef'd Bool to `int` where every neighbouring file
// typedef's it to `bool`, and for itself that file is right --
// ?bfmeHasSignificantPreferredLocomotorHeight@Object@@QBEHXZ returns H, a plain
// int, not _N. The merged TU drops the contested typedef from that signature and
// spells the return Int outright, so no body depends on which meaning of Bool is
// in scope where it happens to sit.
//
// bfmeExpireForcedGroundLayer joins them because it is the same question from the
// other end: it gives up a forced ground layer once the pathfinder agrees the
// object is over layer 1 again. It contributes m_forceGroundLayer at +0x3A8 and
// its frame stamp at +0x3AC -- a byte and a dword three bytes of padding apart,
// which is exactly what retail's `mov byte ptr [esi+0x3a8]` beside
// `mov dword ptr [esi+0x3ac]` shows -- plus m_position at +0x38, the same offset
// ObjectGeometry.cpp and ObjectSpecialPowers.cpp read it at.
//
// Coord3D keeps its constructors here: bfmeLayerForPosition takes the position BY
// VALUE, and retail builds that copy on the stack with an fld/fstp pair and one
// integer move rather than a block copy, which is what the copy constructor
// produces.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class Object;

// The shared 0.0f at retail 0x01075350; both height bodies compare against it
// rather than against an immediate.
extern Real g_bfmeZeroCY;
// BFME's 0.1 significance threshold.
extern Real g_bfmeScaleBK;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
	Coord3D(const Coord3D &other)
		: x(other.x), y(other.y), z(other.z) {}
	~Coord3D() {}

	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
public:
	// Reaches a four-byte body that reads retail's m_preferredHeight at +0x3C.
	Real getPreferredHeight() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[0x1cc];
	Locomotor *m_curLocomotor;			// +0x1CC
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Int bfmeLayerForPosition(Object *object, Coord3D position);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	unsigned char m_unmodelled_000[0x0c];
	Pathfinder *m_pathfinder;			// +0x0C
};

extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled_000[0x3c];
	UnsignedInt m_frame;				// +0x3C
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	Int bfmeHasSignificantPreferredLocomotorHeight() const;
	void bfmeExpireForcedGroundLayer();

private:
	unsigned char m_unmodelled_000[0x38];
	Coord3D m_position;				// +0x038
	unsigned char m_unmodelled_044[0x204 - 0x44];
	AIUpdateInterface *m_ai;			// +0x204
	unsigned char m_unmodelled_208[0x3a8 - 0x208];
	Bool m_forceGroundLayer;			// +0x3A8
	unsigned char m_unmodelled_3a9[3];
	UnsignedInt m_forceGroundLayerFrame;		// +0x3AC
};

// ?bfmeGetNonnegativePreferredLocomotorHeight@Object@@QBEMXZ
//
// Four callers use this value in movement, toppling and wheel-transform code, but
// none exposes the wrapper's retail spelling; the bfme prefix is descriptive, and
// const records observed query-only behaviour rather than symbol metadata.
Real Object::bfmeGetNonnegativePreferredLocomotorHeight() const
{
	AIUpdateInterface *ai = m_ai;
	if (ai != 0)
	{
		Locomotor *locomotor = ai->m_curLocomotor;
		if (locomotor != 0)
		{
			Real height = locomotor->getPreferredHeight();
			if (height > g_bfmeZeroCY)
				return height;
		}
	}
	return g_bfmeZeroCY;
}

// ?bfmeHasSignificantPreferredLocomotorHeight@Object@@QBEHXZ
//
// Require the preferred height to exceed both zero and BFME's 0.1 threshold.
Int Object::bfmeHasSignificantPreferredLocomotorHeight() const
{
	AIUpdateInterface *ai = m_ai;
	if (ai)
	{
		Locomotor *locomotor = ai->m_curLocomotor;
		if (locomotor)
		{
			Real height = locomotor->getPreferredHeight();
			if (height > g_bfmeZeroCY && height > g_bfmeScaleBK)
				return true;
		}
	}
	return false;
}

// ?bfmeExpireForcedGroundLayer@Object@@QAEXXZ
void Object::bfmeExpireForcedGroundLayer()
{
	if (m_forceGroundLayer &&
		m_forceGroundLayerFrame + 13 <= TheGameLogic->m_frame)
	{
		Coord3D position(m_position);
		if (TheAI->m_pathfinder->bfmeLayerForPosition(
			this, position) == 1)
		{
			m_forceGroundLayer = false;
			m_forceGroundLayerFrame = static_cast<UnsignedInt>(-1);
		}
	}
}
