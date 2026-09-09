// ?insert@W3DRoadBufferInsertTeeShim@@QAEXVVector2@@HM@Z
// partial score=0.9 date=2026-09-09
// Body for retail 0x0070BC00, reached through the incremental-link thunk
// ?insertTee@W3DRoadBuffer@@IAEXVVector2@@HM@Z (0x00007522, already matched
// via Code/GameEngine/Source/Common/RTS/W3DRoadBufferInsertTeeThunk.cpp).
// Belongs inline in Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
// (real headers, real W3DRoadBuffer class, TRoadPt, offset3Way/offsetH/xpSign
// already matched in that TU) as a sibling of the already-landed
// W3DRoadBufferInsertYShim::insertY immediately below it.  ZH source:
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
// W3DRoadBuffer::insertTee, plus the BFME-only m_initialized guard.
//
// State: compiles to 2623 bytes vs retail's 2625 (2 bytes short), all
// forward-jump displacements consequently 5-8 bytes off from the size delta.
// Two concrete remaining residues once *(volatile Bool*)&doNN = false; is
// used for do12/do13/do32's initial-false stores (this alone reproduces
// retail's three separate `mov byte ptr [esp+N], 0` immediate stores instead
// of a shared `xor bl,bl` + three `mov [slot],bl`, matching retail's exact
// bytes there -- do NOT also make the "= true" assignments volatile, that
// regresses to 2630B by moving `do12=true` off its retail stack slot
// [esp+0x12] onto a register store; plain `do12=true;` etc. is right):
//   1. do12 and do13 land on swapped stack slots: retail is [esp+0x12]=do12,
//      [esp+0x13]=do13; ours is the reverse. Declaration order (do12,do13,do32
//      vs do13,do12,do32) was tried and made no difference -- this is pure
//      register/stack allocator residue, not source-controllable so far.
//   2. Retail keeps `mirror` in register bl and defers its `xor bl,bl` zero
//      far downstream (right before first use inside the slant-tee branch,
//      interleaved with the Rotate() fsin/fcos code at retail+0x4ef); making
//      `mirror` volatile does NOT reproduce this (tried, regresses to 2630B
//      via unrelated store-vs-register churn) -- the deferred-register-zero
//      scheduling for `mirror` is the remaining unexplained gap.
// t=45min model=sonnet-5

class Vector2 { public: float X, Y; };

class W3DRoadBufferInsertTeeShim /* : public W3DRoadBuffer */
{
public:
	void insert(Vector2 loc, int index1, float scale);
};

void W3DRoadBufferInsertTeeShim::insert(Vector2 loc, int index1, float scale)
{
	// BFME added a guard vs ZH: refuses to insert before init (proven by
	// target byte read of this+0xc, m_initialized's proven offset).
	if (!m_initialized) return;

	if (insertY(loc,index1, scale)) {
		return;
	}

	TRoadPt *pr1=NULL, *pr2=NULL, *pr3=NULL;
	TRoadPt *pc1=NULL, *pc2=NULL, *pc3=NULL;

	if (m_roads[index1].m_pt1.loc == loc) {
		pr1 = &m_roads[index1].m_pt2;
		pc1 = &m_roads[index1].m_pt1;
	} else {
		pr1 = &m_roads[index1].m_pt1;
		pc1 = &m_roads[index1].m_pt2;
	}
	Int i;
	Int index2=0;
	Int index3=0;
	for (i = index1+1; i<m_numRoads; i++) {
		if (m_roads[i].m_pt1.loc == loc) {
			m_roads[i].m_pt1.count = -2;
			if (pr2==NULL) { pr2 = &m_roads[i].m_pt2; pc2 = &m_roads[i].m_pt1; index2 = i; }
			else { pr3 = &m_roads[i].m_pt2; pc3 = &m_roads[i].m_pt1; index3 = i; }
		}
		if (m_roads[i].m_pt2.loc == loc) {
			m_roads[i].m_pt2.count = -2;
			if (pr2==NULL) { pr2 = &m_roads[i].m_pt1; pc2 = &m_roads[i].m_pt2; index2 = i; }
			else { pr3 = &m_roads[i].m_pt1; pc3 = &m_roads[i].m_pt2; index3 = i; }
		}
	}
	if (pr2 == NULL || pr3 == NULL) return;

	Vector2 v1 = pr1->loc - loc; v1.Normalize();
	Vector2 v2 = pr2->loc - loc; v2.Normalize();
	Vector2 v3 = pr3->loc - loc; v3.Normalize();
	Real dot12 = v1.Dot_Product(v1, v2);
	Real dot13 = v1.Dot_Product(v1, v3);
	Real dot32 = v1.Dot_Product(v3, v2);

	// Order matters for the immediate-store shape retail uses -- see header note.
	Bool do12, do13, do32;
	*(volatile Bool *)&do12 = false;
	*(volatile Bool *)&do13 = false;
	*(volatile Bool *)&do32 = false;

	if (dot12<dot13) {
		if (dot12<dot32) { do12 = true; } else { do32 = true; }
	} else {
		if (dot13<dot32) { do13 = true; } else { do32 = true; }
	}

	Vector2 upVector;
	Vector2 decider;
	if (do12) { upVector = v2-v1; decider = v3; }
	if (do13) { upVector = v3-v1; decider = v2; }
	if (do32) { upVector = v2-v3; decider = v1; }
	upVector.Normalize();

	const Real cos60 = 0.5f;
	Real dot = fabs(Vector2::Dot_Product(upVector, decider));
	if (dot > cos60) {
		Real angle = (PI/2);
		Real xpdct = Vector3::Cross_Product_Z(Vector3(upVector.X,upVector.Y,0), Vector3(decider.X, decider.Y,0));
		Bool mirror = false;   // retail: register bl, zeroed just before first use -- see note 2 above.
		if (xpdct<0) { angle = -angle; mirror = true; }
		upVector.Normalize();
		upVector *= 0.5*scale;
		Vector2 teeVector(upVector);
		teeVector.Rotate(angle);

		Bool flip;
		if (do12) { flip = xpSign(teeVector, v3) == 1; offsetH(pc1, pc2, pc3, loc, upVector, teeVector, flip, mirror, m_roads[index1].m_widthInTexture); }
		if (do13) { flip = xpSign(teeVector, v2) == 1; offsetH(pc1, pc3, pc2, loc, upVector, teeVector, flip, mirror, m_roads[index1].m_widthInTexture); }
		if (do32) { flip = xpSign(teeVector, v1) == 1; offsetH(pc3, pc2, pc1, loc, upVector, teeVector, flip, mirror, m_roads[index1].m_widthInTexture); }

		pc1->last = true; pc1->count = 0;
		pc2->last = true; pc2->count = 0;
		pc3->last = true; pc3->count = 0;

		CHECK_SEGMENTS;
		m_roads[m_numRoads].m_pt1.loc.Set(loc);
		m_roads[m_numRoads].m_pt2.loc.Set(loc+teeVector);
		m_roads[m_numRoads].m_pt1.last = true;
		m_roads[m_numRoads].m_pt2.last = true;
		m_roads[m_numRoads].m_scale = m_roads[index1].m_scale;
		m_roads[m_numRoads].m_widthInTexture = m_roads[index1].m_widthInTexture;
		m_roads[m_numRoads].m_pt1.count = -3;
		m_roads[m_numRoads].m_type = flip?THREE_WAY_H_FLIP:THREE_WAY_H;
		m_roads[m_numRoads].m_uniqueID = m_roads[index1].m_uniqueID;
		m_numRoads++;
	} else {
		Real angle = (PI/2);
		Real xpdct = Vector3::Cross_Product_Z(Vector3(upVector.X,upVector.Y,0), Vector3(decider.X, decider.Y,0));
		if (xpdct<0) angle = -angle;
		upVector.Normalize();
		upVector *= 0.5*scale;
		Vector2 teeVector(upVector);
		teeVector.Rotate(angle);

		if (do12) offset3Way(pc1, pc2, pc3, loc, upVector, teeVector, m_roads[index1].m_widthInTexture);
		if (do13) offset3Way(pc1, pc3, pc2, loc, upVector, teeVector, m_roads[index1].m_widthInTexture);
		if (do32) offset3Way(pc3, pc2, pc1, loc, upVector, teeVector, m_roads[index1].m_widthInTexture);

		pc1->last = true; pc1->count = 0;
		pc2->last = true; pc2->count = 0;
		pc3->last = true; pc3->count = 0;

		CHECK_SEGMENTS;
		m_roads[m_numRoads].m_pt1.loc.Set(loc);
		m_roads[m_numRoads].m_pt2.loc.Set(loc+teeVector);
		m_roads[m_numRoads].m_pt1.last = true;
		m_roads[m_numRoads].m_pt2.last = true;
		m_roads[m_numRoads].m_scale = m_roads[index1].m_scale;
		m_roads[m_numRoads].m_widthInTexture = m_roads[index1].m_widthInTexture;
		m_roads[m_numRoads].m_pt1.count = -3;
		m_roads[m_numRoads].m_type = TEE;
		m_roads[m_numRoads].m_uniqueID = m_roads[index1].m_uniqueID;
		m_numRoads++;
	}
}
