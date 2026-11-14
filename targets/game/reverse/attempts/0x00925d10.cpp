// ?bfmeSet1016@BfmeDst1016@@QAEXHHH@Z
// partial score=0.9902 date=2026-11-14
// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Open-BFME5 conversions.

#include "matrix3d.h"
#include "sharebuf.h"

extern float g_01076C24;
void rva009371E0Inc();

struct Rva00925D10Pivot
{
	char m_pad0[0x44];
	Matrix3D m_tm;
	char m_pad1[0x40];
};

struct Rva00925D10Tree
{
	char m_pad0[0x14];
	Rva00925D10Pivot *m_pivots;
};

struct Rva00925D10Rotator : public Matrix3D
{
	__forceinline void rotateVector3Array(const Vector3 *in, Vector3 *out, int count) const
	{
		while (count--)
		{
			out->X = Row[0].X * in->X + Row[0].Y * in->Y + Row[0].Z * in->Z;
			out->Y = Row[1].X * in->X + Row[1].Y * in->Y + Row[1].Z * in->Z;
			out->Z = Row[2].X * in->X + Row[2].Y * in->Y + Row[2].Z * in->Z;
			++in;
			++out;
		}
	}
};

class BfmeDst1016
{
public:
	void bfmeSet1016(int a, int b, int r);

	char m_pad0[0x28];
	int m_count;
	char m_pad1[4];
	ShareBufferClass<Vector3> *m_vert[2];
	char m_pad2[8];
	ShareBufferClass<Vector3> *m_norm[2];
	char m_pad3[0x10];
	ShareBufferClass<unsigned short> *m_links;
	ShareBufferClass<unsigned short> *m_runs;
};

void BfmeDst1016::bfmeSet1016(int a, int b, int r)
{
	Vector3 *&dstV = (Vector3 *&)a;
	Vector3 *&dstN = (Vector3 *&)b;
	Rva00925D10Tree *tree = (Rva00925D10Tree *)r;

	if (m_runs == 0 || m_links == 0 || tree == 0)
		return;

	int streams = 1;
	if (m_vert[1] != 0)
		streams = 2;

	Vector3 *srcV[2];
	Vector3 *srcN[2];
	int i;
	for (i = 0; i < streams; i++) {
		if (m_vert[i] != 0)
			srcV[i] = (Vector3 *)m_vert[i]->Get_Array();
		else
			srcV[i] = 0;
		if (m_norm[i] != 0)
			srcN[i] = (Vector3 *)m_norm[i]->Get_Array();
		else
			srcN[i] = 0;
	}

	unsigned short *runs = (unsigned short *)m_runs->Get_Array();
	unsigned short *links = (unsigned short *)m_links->Get_Array();

	rva009371E0Inc();

	int count = m_count;
	int left = count;
	while (left > 0) {
		int n = runs[1];
		runs += 2;
		left -= n;
		int b0 = links[0];
		int b1 = links[count];
		int c;
		if (streams == 2 && b1 != 0) {
			float w0 = (float)links[count * 2];
			float w1 = (float)links[count * 3];
			w0 *= g_01076C24;
			w1 *= g_01076C24;
			Matrix3D m0 = tree->m_pivots[b0].m_tm;
			Matrix3D m1 = tree->m_pivots[b1].m_tm;
			for (int r3 = 0; r3 < 3; r3++) {
				m0[r3] *= w0;
				m1[r3] *= w1;
			}
			const Vector3 *pa;
			const Vector3 *pb;
			Vector3 *po;
			po = dstV;
			pb = srcV[1];
			pa = srcV[0];
			c = n;
			while (c--) {
				po->X = m0[0].X * pa->X + m0[0].Y * pa->Y + m0[0].Z * pa->Z + m0[0].W + m1[0].X * pb->X + m1[0].Y * pb->Y + m1[0].Z * pb->Z + m1[0].W;
				po->Y = m0[1].X * pa->X + m0[1].Y * pa->Y + m0[1].Z * pa->Z + m0[1].W + m1[1].X * pb->X + m1[1].Y * pb->Y + m1[1].Z * pb->Z + m1[1].W;
				po->Z = m0[2].X * pa->X + m0[2].Y * pa->Y + m0[2].Z * pa->Z + m0[2].W + m1[2].X * pb->X + m1[2].Y * pb->Y + m1[2].Z * pb->Z + m1[2].W;
				++pa;
				++pb;
				++po;
			}
			pa = srcN[0];
			pb = srcN[1];
			po = dstN;
			c = n;
			while (c--) {
				po->X = m0[0].X * (*pa)[0] + m0[0].Y * (*pa)[1] + m0[0].Z * (*pa)[2] + m1[0].X * (*pb)[0] + m1[0].Y * (*pb)[1] + m1[0].Z * (*pb)[2];
				po->Y = m0[1].X * (*pa)[0] + m0[1].Y * (*pa)[1] + m0[1].Z * (*pa)[2] + m1[1].X * (*pb)[0] + m1[1].Y * (*pb)[1] + m1[1].Z * (*pb)[2];
				po->Z = m0[2].X * (*pa)[0] + m0[2].Y * (*pa)[1] + m0[2].Z * (*pa)[2] + m1[2].X * (*pb)[0] + m1[2].Y * (*pb)[1] + m1[2].Z * (*pb)[2];
				++pa;
				++pb;
				++po;
			}
		} else {
			const Matrix3D *pm = &tree->m_pivots[b0].m_tm;
			pm->mulVector3Array(srcV[0], dstV, n);
			((const Rva00925D10Rotator *)pm)->rotateVector3Array(srcN[0], dstN, n);
		}
		links += n;
		for (i = 0; i < streams; i++) {
			srcV[i] += n;
			srcN[i] += n;
		}
		dstV += n;
		dstN += n;
	}
}
