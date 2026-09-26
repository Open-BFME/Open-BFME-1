// ?bfmeSet1016@BfmeDst1016@@QAEXHHH@Z
// partial score=0.897 date=2026-09-23
// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME5 conversions.

#include "matrix3d.h"

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

struct Rva00925D10Buf
{
	char m_pad0[0xc];
	void *m_array;
};

class BfmeDst1016
{
public:
	void bfmeSet1016(int a, int b, int r);

	char m_pad0[0x28];
	int m_count;
	char m_pad1[4];
	Rva00925D10Buf *m_vert[2];
	char m_pad2[8];
	Rva00925D10Buf *m_norm[2];
	char m_pad3[0x10];
	Rva00925D10Buf *m_links;
	Rva00925D10Buf *m_runs;
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
			srcV[i] = (Vector3 *)m_vert[i]->m_array;
		else
			srcV[i] = 0;
		if (m_norm[i] != 0)
			srcN[i] = (Vector3 *)m_norm[i]->m_array;
		else
			srcN[i] = 0;
	}

	unsigned short *runs = (unsigned short *)m_runs->m_array;
	unsigned short *links = (unsigned short *)m_links->m_array;

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
			pa = srcV[0];
			pb = srcV[1];
			po = dstV;
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
			const Matrix3D &m = tree->m_pivots[b0].m_tm;
			const Vector3 *in;
			Vector3 *out;
			in = srcV[0];
			out = dstV;
			c = n;
			while (c--) {
				out->X = m[0].X * (*in)[0] + m[0].Y * (*in)[1] + m[0].Z * (*in)[2] + m[0].W;
				out->Y = m[1].X * in->X + m[1].Y * in->Y + m[1].Z * in->Z + m[1].W;
				out->Z = m[2].X * (*in)[0] + m[2].Y * (*in)[1] + m[2].Z * (*in)[2] + m[2].W;
				++in;
				++out;
			}
			in = srcN[0];
			out = dstN;
			c = n;
			while (c--) {
				out->X = m[0].X * in->X + m[0].Y * in->Y + m[0].Z * in->Z;
				out->Y = m[1].X * (*in)[0] + m[1].Y * (*in)[1] + m[1].Z * (*in)[2];
				out->Z = m[2].X * in->X + m[2].Y * in->Y + m[2].Z * in->Z;
				++in;
				++out;
			}
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
