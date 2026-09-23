// ?bfmeSet1016@BfmeDst1016@@QAEXHHH@Z
// partial score=0.05 date=2026-09-23
// Open-BFME5 conversions.

class BfmeSrc1016
{
public:
	virtual void bfmeVS01016();
	virtual void bfmeVS11016();
	virtual void bfmeVS21016();
	virtual void bfmeVS31016();
	virtual void bfmeVS41016();
	virtual void bfmeVS51016();
	virtual void bfmeVS61016();
	virtual void bfmeVS71016();
	virtual void bfmeVS81016();
	virtual void bfmeVS91016();
	virtual void bfmeVS101016();
	virtual void bfmeVS111016();
	virtual void bfmeVS121016();
	virtual void bfmeVS131016();
	virtual void bfmeVS141016();
	virtual void bfmeVS151016();
	virtual void bfmeVS161016();
	virtual void bfmeVS171016();
	virtual void bfmeVS181016();
	virtual void bfmeVS191016();
	virtual void bfmeVS201016();
	virtual void bfmeVS211016();
	virtual void bfmeVS221016();
	virtual void bfmeVS231016();
	virtual void bfmeVS241016();
	virtual void bfmeVS251016();
	virtual void bfmeVS261016();
	virtual void bfmeVS271016();
	virtual void bfmeVS281016();
	virtual void bfmeVS291016();
	virtual void bfmeVS301016();
	virtual void bfmeVS311016();
	virtual void bfmeVS321016();
	virtual void bfmeVS331016();
	virtual void bfmeVS341016();
	virtual void bfmeVS351016();
	virtual void bfmeVS361016();
	virtual void bfmeVS371016();
	virtual void bfmeVS381016();
	virtual void bfmeVS391016();
	virtual void bfmeVS401016();
	virtual void bfmeVS411016();
	virtual void bfmeVS421016();
	virtual void bfmeVS431016();
	virtual void bfmeVS441016();
	virtual void bfmeVS451016();
	virtual void bfmeVS461016();
	virtual void bfmeVS471016();
	virtual void bfmeVS481016();
	virtual void bfmeVS491016();
	virtual void bfmeVS501016();
	virtual void bfmeVS511016();
	virtual void bfmeVS521016();
	virtual void bfmeVS531016();
	virtual void bfmeVS541016();
	virtual void bfmeVS551016();
	virtual void bfmeVS561016();
	virtual int bfmeGet1016();
};

class BfmeDst1016
{
public:
	void bfmeSet1016(int a, int b, int r);
};

class BfmeQ1016
{
public:
	void bfmeGo1016Q(int a, int b);

	char m_bfmePad[0x84];
	BfmeSrc1016 *m_bfmeSrc;
	char m_bfmePad2[0x40];
	BfmeDst1016 *m_bfmeDst;
};

void BfmeQ1016::bfmeGo1016Q(int a, int b)
{
	int r = m_bfmeSrc != 0 ? m_bfmeSrc->bfmeGet1016() : 0;

	m_bfmeDst->bfmeSet1016(a, b, r);
}

class BfmeIter1016
{
public:
	unsigned short bfmeNext1016(int a);
};

class BfmeR1016
{
public:
	BfmeR1016 &bfmeGo1016R(int a);

	BfmeIter1016 *m_bfmeIt;
	char m_bfmeOk;
};

BfmeR1016 &BfmeR1016::bfmeGo1016R(int a)
{
	int ok;

	if (m_bfmeOk != 0 && m_bfmeIt->bfmeNext1016(a) != 0xffff)
		ok = 1;
	else
		ok = 0;

	m_bfmeOk = (char)ok;
	return *this;
}

struct BfmeNode1016
{
	char m_bfmePad[4];
	int m_bfmeCount;
	BfmeNode1016 *m_bfmeNext;
	BfmeNode1016 *m_bfmePrev;
};

extern const float g_01076C24;
extern void rva009371E0Inc();

struct Bfme1016ArrayView
{
	char m_bfmePad00[0x0c];
	unsigned short *m_bfmeData0c;
};

struct Bfme1016TransformView
{
	char m_bfmePad00[0x44];
	float m_bfmeValues44[12];
	char m_bfmePad74[0x40];
};

void BfmeDst1016::bfmeSet1016(int a, int b, int r)
{
	char *self = (char *)this;
	Bfme1016ArrayView *runs = *(Bfme1016ArrayView **)(self + 0x5c);
	if (runs == 0)
		return;
	Bfme1016ArrayView *indices = *(Bfme1016ArrayView **)(self + 0x58);
	if (indices == 0)
		return;
	if (r == 0)
		return;

	int streams = *(int *)(self + 0x34) != 0 ? 2 : 1;
	float *inputA[2];
	float *inputB[2];
	for (int i = 0; i < streams; ++i) {
		Bfme1016ArrayView *arrayA = *(Bfme1016ArrayView **)(self + 0x30 + i * 4);
		Bfme1016ArrayView *arrayB = *(Bfme1016ArrayView **)(self + 0x40 + i * 4);
		inputA[i] = arrayA != 0 ? (float *)arrayA->m_bfmeData0c : 0;
		inputB[i] = arrayB != 0 ? (float *)arrayB->m_bfmeData0c : 0;
	}

	unsigned short *runData = runs->m_bfmeData0c;
	unsigned short *indexData = indices->m_bfmeData0c;
	unsigned char *transformData = *(unsigned char **)((char *)r + 0x14);
	rva009371E0Inc();

	int total = *(int *)(self + 0x28);
	if (total <= 0)
		return;

	float *outputA = (float *)a;
	float *outputB = (float *)b;
	int remaining = total;
	do {
		int count = runData[1];
		runData += 2;
		remaining -= count;

		unsigned short idA = indexData[0];
		unsigned short idB = indexData[total];
		unsigned short weightA = indexData[total * 2];
		unsigned short weightB = indexData[total * 3];
		Bfme1016TransformView *transformA = (Bfme1016TransformView *)(transformData + idA * 0xb4);
		float matrixA[12];
		float scaleA = (float)weightA * g_01076C24;
		for (int k = 0; k < 12; ++k)
			matrixA[k] = transformA->m_bfmeValues44[k] * scaleA;

		if (streams == 2 && idB != 0) {
			Bfme1016TransformView *transformB = (Bfme1016TransformView *)(transformData + idB * 0xb4);
			float matrixB[12];
			float scaleB = (float)weightB * g_01076C24;
			for (int k = 0; k < 12; ++k)
				matrixB[k] = transformB->m_bfmeValues44[k] * scaleB;

			for (int j = 0; j < count; ++j) {
				float ax = inputA[0][j * 3];
				float ay = inputA[0][j * 3 + 1];
				float az = inputA[0][j * 3 + 2];
				float bx = inputA[1][j * 3];
				float by = inputA[1][j * 3 + 1];
				float bz = inputA[1][j * 3 + 2];
				outputA[0] = matrixA[0] * ax + matrixA[1] * ay + matrixA[2] * az + matrixA[3]
					+ matrixB[0] * bx + matrixB[1] * by + matrixB[2] * bz + matrixB[3];
				outputA[1] = matrixA[4] * ax + matrixA[5] * ay + matrixA[6] * az + matrixA[7]
					+ matrixB[4] * bx + matrixB[5] * by + matrixB[6] * bz + matrixB[7];
				outputA[2] = matrixA[8] * ax + matrixA[9] * ay + matrixA[10] * az + matrixA[11]
					+ matrixB[8] * bx + matrixB[9] * by + matrixB[10] * bz + matrixB[11];

				ax = inputB[0][j * 3];
				ay = inputB[0][j * 3 + 1];
				az = inputB[0][j * 3 + 2];
				bx = inputB[1][j * 3];
				by = inputB[1][j * 3 + 1];
				bz = inputB[1][j * 3 + 2];
				outputB[0] = matrixA[0] * ax + matrixA[1] * ay + matrixA[2] * az + matrixA[3]
					+ matrixB[0] * bx + matrixB[1] * by + matrixB[2] * bz + matrixB[3];
				outputB[1] = matrixA[4] * ax + matrixA[5] * ay + matrixA[6] * az + matrixA[7]
					+ matrixB[4] * bx + matrixB[5] * by + matrixB[6] * bz + matrixB[7];
				outputB[2] = matrixA[8] * ax + matrixA[9] * ay + matrixA[10] * az + matrixA[11]
					+ matrixB[8] * bx + matrixB[9] * by + matrixB[10] * bz + matrixB[11];
				outputA += 3;
				outputB += 3;
			}
		} else {
			for (int j = 0; j < count; ++j) {
				float x = inputA[0][j * 3];
				float y = inputA[0][j * 3 + 1];
				float z = inputA[0][j * 3 + 2];
				outputA[0] = matrixA[0] * x + matrixA[1] * y + matrixA[2] * z + matrixA[3];
				outputA[1] = matrixA[4] * x + matrixA[5] * y + matrixA[6] * z + matrixA[7];
				outputA[2] = matrixA[8] * x + matrixA[9] * y + matrixA[10] * z + matrixA[11];

				x = inputB[0][j * 3];
				y = inputB[0][j * 3 + 1];
				z = inputB[0][j * 3 + 2];
				outputB[0] = matrixA[0] * x + matrixA[1] * y + matrixA[2] * z + matrixA[3];
				outputB[1] = matrixA[4] * x + matrixA[5] * y + matrixA[6] * z + matrixA[7];
				outputB[2] = matrixA[8] * x + matrixA[9] * y + matrixA[10] * z + matrixA[11];
				outputA += 3;
				outputB += 3;
			}
		}
		indexData += count;
	} while (remaining > 0);
}

class BfmeList1016
{
public:
	void bfmeErase1016(int n);

	BfmeNode1016 *m_bfmeHead;
	int m_bfmeSize;
};

extern BfmeList1016 g_bfmeList1016;

void bfmeGo1016T(void)
{
	if (g_bfmeList1016.m_bfmeSize != 0) {
		g_bfmeList1016.bfmeErase1016(g_bfmeList1016.m_bfmeHead->m_bfmeCount);
		g_bfmeList1016.m_bfmeHead->m_bfmeNext = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeHead->m_bfmeCount = 0;
		g_bfmeList1016.m_bfmeHead->m_bfmePrev = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeSize = 0;
	}
}
