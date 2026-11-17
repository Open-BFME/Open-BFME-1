// ?DoXfer@LivingWorldEyeTower@@UAEXAAVXfer@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source
// stlport
//
// LivingWorldEyeTower::DoXfer, retail RVA 0x0060CFE0, 402 bytes (ret 4 at
// +0x18F). The matched LivingWorldEyeTower constructor 0x0060CCC0 installs
// vftable 0x01115F10, whose slot 2 is the "LivingWorldEyeTower" name getter
// 0x0060CD70 and whose slot 3 (the BFME Snapshot DoXfer slot) reaches this
// body through ILT 0x00002E82; the ILT oracle confirms
// ?DoXfer@LivingWorldEyeTower@@UAEXAAVXfer@@@Z. The body transfers the
// version, the point count and the Coord2D points of the vector at +0x3C
// (the vector the matched destructor and getPair use). On load it rebuilds
// the vector and then, inside the GameLogic FP-mode nesting count, repeats
// the matched handle() step (0x0060CBB0, inlined here).

#include "Common/System/xfer.h"
#include <vector>

// The ILT confirms the class key of the element type through the helpers this
// body calls: ??$_Construct@VCoord2D@@V1@@_STL@@YAXPAVCoord2D@@ABV1@@Z
// (0x001E21F0, via ILT 0x00046AF1) and
// ?_M_insert_overflow@?$vector@VCoord2D@@...@IAEXPAVCoord2D@@ABV3@ABU__false_type@2@I_N@Z
// (0x001E9020, via ILT 0x0001CB9D). Retail inlines the copy loop of
// vector::clear and runs no constructor for the transfer temporary, so this TU
// sees Coord2D with inline members; WWMath/coord2d.h declares them out of
// line, which keeps that loop out of line.
// class-gate: allow Coord2D the canonical header is a bare struct, but the ILT confirms the class key V for this body's vector helpers, and the proven codegen needs inline default/copy constructors (402/402, 0 non-reloc diffs).
class Coord2D
{
public:
	Coord2D() {}
	Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}

	float x;
	float y;
};

// The global at 0x012F0898 is retail's `GameLogic *TheGameLogic`; this TU
// reads two of its fields through an address-derived view, re-reading the
// global at each use as the body does.
class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva0060CFE0Logic
{
	char m_pad000[0x10C];
	int m_at10C;
	char m_pad110[0x90];
	int m_at1A0;		// FP-mode nesting count: setFPMode runs when it is zero
};

static inline Rva0060CFE0Logic *gameLogic()
{
	return (Rva0060CFE0Logic *)TheGameLogic;
}

extern void setFPMode();

struct XferVersion : Xfer::Version
{
	XferVersion(unsigned char version)
	{
		data[0] = version;
		data[1] = version;
	}
};

// The point record the matched getPair (0x0060CA40) returns, by its ledger
// name.
struct Gen0060CBB0Pair
{
	float first;
	float second;
};

// Layout of the matched LivingWorldEyeTower state methods (0x74 bytes).
class LivingWorldEyeTower
{
public:
	virtual ~LivingWorldEyeTower();
	virtual void DoXfer(Xfer &xfer);

	void handleInlined()
	{
		Gen0060CBB0Pair *pair = getPair();
		m_current.x = pair->first;
		m_current.y = pair->second;
		if (m_points.size() == 0) {
			m_state = 1;
			m_rate6C = 0;
			return;
		}
		processItems();
	}

private:
	Gen0060CBB0Pair *getPair();
	void processItems();

	char m_unmodelled04[0x38];
	std::vector<Coord2D> m_points;
	unsigned int m_state;
	Coord2D m_to;
	Coord2D m_from;
	Coord2D m_current;
	float m_rate64;
	float m_progress68;
	float m_rate6C;
	float m_progress70;
};

// ?DoXfer@LivingWorldEyeTower@@UAEXAAVXfer@@@Z
void LivingWorldEyeTower::DoXfer(Xfer &xfer)
{
	{
		XferVersion version(1);
		xfer == version;
	}

	int count = m_points.size();
	xfer == count;

	if (xfer.IsLoading()) {
		m_points.clear();
		for (int i = 0; i < count; ++i) {
			Coord2D point;
			xfer == point;
			m_points.push_back(point);
		}

		if (gameLogic()) {
			bool rejected = gameLogic()->m_at10C == 5 || gameLogic()->m_at10C == 1;
			if (rejected)
				throw;
			int *depth = &gameLogic()->m_at1A0;
			if (*depth == 0)
				setFPMode();
			++*depth;
		}

		handleInlined();

		if (gameLogic())
			--gameLogic()->m_at1A0;
	} else {
		for (int i = 0; i < count; ++i)
			xfer == m_points[i];
	}
}
