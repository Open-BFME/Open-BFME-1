// Open-BFME5 conversions.

struct BfmeVec4_1236
{
	float x;
	float y;
	float z;
	float w;
};

class BfmeB1236
{
public:
	void bfmeApply1236(void *a);
	void bfmeEmit1236(void *a, int b, void *c);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x10 - 0x08];
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	BfmeVec4_1236 m_bfme28;
	BfmeVec4_1236 m_bfme38;
	int m_bfme48;
	void *m_bfme4c;
};

class BfmeA1236
{
public:
	void bfmeBegin1236();
	void bfmePush1236(void *a);
	void bfmeMark1236();
	void bfmeSet1236(void *a);
	void bfmePop1236();
	void bfmeEnd1236();
};

void bfmeGo1236(BfmeA1236 *a, BfmeB1236 *b, void *c)
{
	a->bfmeBegin1236();
	a->bfmePush1236(&b->m_bfme28);
	a->bfmeMark1236();
	if ((b->m_bfme04 & 0x3f) == 0xf && !((unsigned char)(~(b->m_bfme04 >> 15)) & 1))
		b->bfmeApply1236(b->m_bfme4c);
	a->bfmeSet1236(&b->m_bfme10);
	b->bfmeEmit1236(a, 0, c);
	a->bfmePop1236();
	a->bfmeEnd1236();
}

struct BfmeTransform1236
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	float m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	float m_bfme3c;
	BfmeVec4_1236 m_bfme40;
	BfmeVec4_1236 m_bfme50;
};

extern BfmeTransform1236 *g_bfmeArenaCursor;
void bfmeCombine1236(BfmeTransform1236 *result, BfmeTransform1236 *left, BfmeTransform1236 *right);

void bfmeTransform1236(void *context, BfmeB1236 *b, void *tail)
{
	if ((b->m_bfme04 & 0x3f) == 0xf && !((unsigned char)(~(b->m_bfme04 >> 15)) & 1))
		b->bfmeApply1236(b->m_bfme4c);

	BfmeTransform1236 *previous = g_bfmeArenaCursor;
	BfmeTransform1236 *current = ++g_bfmeArenaCursor;
	current->m_bfme00 = b->m_bfme10;
	current->m_bfme04 = b->m_bfme14;
	current->m_bfme08 = 0;
	current->m_bfme0c = 0;
	current->m_bfme10 = b->m_bfme18;
	current->m_bfme14 = b->m_bfme1c;
	current->m_bfme18 = 0;
	current->m_bfme1c = 0;
	current->m_bfme20 = 0;
	current->m_bfme24 = 0;
	current->m_bfme28 = 1.0f;
	current->m_bfme2c = 0;
	current->m_bfme30 = b->m_bfme20;
	current->m_bfme34 = b->m_bfme24;
	current->m_bfme38 = 0;
	current->m_bfme3c = 1.0f;
	current->m_bfme40 = b->m_bfme28;
	current->m_bfme50 = b->m_bfme38;

	bfmeCombine1236(current, previous, current);
	current->m_bfme40.x *= previous->m_bfme40.x;
	current->m_bfme40.y *= previous->m_bfme40.y;
	current->m_bfme40.z *= previous->m_bfme40.z;
	current->m_bfme40.w *= previous->m_bfme40.w;
	current->m_bfme50.x += previous->m_bfme50.x;
	current->m_bfme50.y += previous->m_bfme50.y;
	current->m_bfme50.z += previous->m_bfme50.z;
	current->m_bfme50.w += previous->m_bfme50.w;
	b->bfmeEmit1236(context, (int)current, tail);
	--g_bfmeArenaCursor;
}

class BfmeZero1236
{
public:
	BfmeZero1236();

private:
	int m_values[32];
	int m_extra;
};

BfmeZero1236::BfmeZero1236()
{
	m_extra = 0;
	for (int i = 0; i < 32; ++i)
		m_values[i] = 0;
}
