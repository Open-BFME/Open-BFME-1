// Open-BFME5 conversions.

extern "C" char g_bfmeV1196[];

struct BfmeSrc1196
{
	char m_bfmePad0[0x38];
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	char m_bfmePad1[0x78];
	float m_bfmebc;
};

struct BfmeA1196FloatView
{
	char m_bfmePad0[0x08];
	float m_bfme08;
	float m_bfme0c;
	char m_bfmePad1[0x04];
	float m_bfme14;
	bool m_bfme18;
};

struct BfmeG1196
{
	char m_bfmePad[0x1bc];
	float m_bfme1bc;
};

extern "C" BfmeG1196 *volatile g_bfmeG1196;

extern const float BfmeZeroRange;

class Object
{
public:
	float getShroudClearingRange() const;
};

struct BfmeObject1196
{
	char m_bfmePad0[0x38];
	float m_bfme38;
	float m_bfme3c;
	char m_bfmePad1[0x7c];
	float m_bfmebc;
};

struct BfmeDelta1196
{
	float x;
	float y;
	float z;
};

class BfmeA1196
{
public:
	BfmeA1196(BfmeSrc1196 *a, char b);
	bool allow(Object *object);
	char *volatile m_bfme00;
	volatile int m_bfme04;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile float m_bfme14;
	volatile char m_bfme18;
};

BfmeA1196::BfmeA1196(BfmeSrc1196 *a, char b)
{
	float v;

	m_bfme04 = 0;
	m_bfme00 = g_bfmeV1196;
	m_bfme08 = a->m_bfme38;
	m_bfme0c = a->m_bfme3c;
	m_bfme10 = a->m_bfme40;
	m_bfme18 = b;

	v = a->m_bfmebc;
	m_bfme14 = v;
	m_bfme14 = g_bfmeG1196->m_bfme1bc * 0.70710677f + v;
}

bool BfmeA1196::allow(Object *object)
{
	const BfmeA1196FloatView *self = reinterpret_cast<const BfmeA1196FloatView *>(this);
	const BfmeObject1196 *other = reinterpret_cast<const BfmeObject1196 *>(object);
	float range = object->getShroudClearingRange();
	if (range <= BfmeZeroRange || range == BfmeZeroRange)
		return !self->m_bfme18;

	range += self->m_bfme14;
	range += other->m_bfmebc;
	BfmeDelta1196 delta = { other->m_bfme38, other->m_bfme3c, BfmeZeroRange };
	delta.x -= self->m_bfme08;
	delta.y -= self->m_bfme0c;
	float distanceSquared = delta.y * delta.y + delta.x * delta.x;
	if (distanceSquared < range * range)
		return self->m_bfme18;
	return !self->m_bfme18;
}
