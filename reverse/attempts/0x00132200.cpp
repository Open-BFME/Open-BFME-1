// ?bfmeSetHQ@BfmeXfHQ@@QAEXPAVMatrix3D@@@Z
// partial score=0.98 date=2026-09-09
// Naming &m_bfmeMatrixHQ in a local (selfMat) and reading/writing through it
// for BOTH matrix-copy loops fixed 19 of 25 diff lines (retail keeps one
// base register live across both loops; without the named pointer MSVC only
// keeps it for a few elements then falls back to esi-relative addressing).
// Remaining 6 diff lines are pure scheduling residue: (1) the rot/pos first
// two reads come out swapped vs retail no matter which order they're
// declared/assigned in -- every reordering tried (rot first, pos.X first,
// rot mid-pos) either leaves this pair swapped or makes it worse elsewhere;
// (2) the m_bfmeMHQ[7]/[11] extraction interleaves as read,read,store,store
// here vs retail's store,read,store,read -- reordering the three extraction
// statements changes which physical stack offset each field lands at (offset
// follows ASSIGNMENT order, not declaration order -- confirmed by a direct
// test), so it is not just a scheduling knob.
class Matrix3D
{
public:
	float Get_Z_Rotation() const;

	float m_bfmeMHQ[12];
};

class BfmeTripleHQ
{
public:
	float m_bfmeXHQ;
	float m_bfmeYHQ;
	float m_bfmeZHQ;
};

class BfmeXfHQ
{
public:
	virtual void bfmeVt0HQ();
	virtual void bfmeVt1HQ();
	virtual void bfmeVt2HQ();
	virtual void bfmeVt3HQ();
	virtual void bfmeVt4HQ();
	virtual void bfmeApplyHQ(Matrix3D *m, BfmeTripleHQ *t, float r);

	void bfmeSetHQ(Matrix3D *m);

	unsigned char m_bfmeGapHQ[4];
	Matrix3D m_bfmeMatrixHQ;
	BfmeTripleHQ m_bfmePosHQ;
	float m_bfme44HQ;
	unsigned char m_bfmeGap2HQ[0x14];
	int m_bfme5cHQ;
};

void BfmeXfHQ::bfmeSetHQ(Matrix3D *m)
{
	float rot = m_bfme44HQ;
	BfmeTripleHQ pos;
	Matrix3D old;

	pos.m_bfmeXHQ = m_bfmePosHQ.m_bfmeXHQ;
	pos.m_bfmeYHQ = m_bfmePosHQ.m_bfmeYHQ;
	pos.m_bfmeZHQ = m_bfmePosHQ.m_bfmeZHQ;

	Matrix3D *selfMat = &m_bfmeMatrixHQ;

	old.m_bfmeMHQ[0] = selfMat->m_bfmeMHQ[0];
	old.m_bfmeMHQ[1] = selfMat->m_bfmeMHQ[1];
	old.m_bfmeMHQ[2] = selfMat->m_bfmeMHQ[2];
	old.m_bfmeMHQ[3] = selfMat->m_bfmeMHQ[3];
	old.m_bfmeMHQ[4] = selfMat->m_bfmeMHQ[4];
	old.m_bfmeMHQ[5] = selfMat->m_bfmeMHQ[5];
	old.m_bfmeMHQ[6] = selfMat->m_bfmeMHQ[6];
	old.m_bfmeMHQ[7] = selfMat->m_bfmeMHQ[7];
	old.m_bfmeMHQ[8] = selfMat->m_bfmeMHQ[8];
	old.m_bfmeMHQ[9] = selfMat->m_bfmeMHQ[9];
	old.m_bfmeMHQ[10] = selfMat->m_bfmeMHQ[10];
	old.m_bfmeMHQ[11] = selfMat->m_bfmeMHQ[11];

	selfMat->m_bfmeMHQ[0] = m->m_bfmeMHQ[0];
	selfMat->m_bfmeMHQ[1] = m->m_bfmeMHQ[1];
	selfMat->m_bfmeMHQ[2] = m->m_bfmeMHQ[2];
	selfMat->m_bfmeMHQ[3] = m->m_bfmeMHQ[3];
	selfMat->m_bfmeMHQ[4] = m->m_bfmeMHQ[4];
	selfMat->m_bfmeMHQ[5] = m->m_bfmeMHQ[5];
	selfMat->m_bfmeMHQ[6] = m->m_bfmeMHQ[6];
	selfMat->m_bfmeMHQ[7] = m->m_bfmeMHQ[7];
	selfMat->m_bfmeMHQ[8] = m->m_bfmeMHQ[8];
	selfMat->m_bfmeMHQ[9] = m->m_bfmeMHQ[9];
	selfMat->m_bfmeMHQ[10] = m->m_bfmeMHQ[10];
	selfMat->m_bfmeMHQ[11] = m->m_bfmeMHQ[11];

	m_bfmePosHQ.m_bfmeXHQ = m_bfmeMatrixHQ.m_bfmeMHQ[3];
	m_bfmePosHQ.m_bfmeYHQ = m_bfmeMatrixHQ.m_bfmeMHQ[7];
	m_bfmePosHQ.m_bfmeZHQ = m_bfmeMatrixHQ.m_bfmeMHQ[11];
	m_bfme44HQ = m_bfmeMatrixHQ.Get_Z_Rotation();
	m_bfme5cHQ = 0;

	bfmeApplyHQ(&old, &pos, rot);
}
