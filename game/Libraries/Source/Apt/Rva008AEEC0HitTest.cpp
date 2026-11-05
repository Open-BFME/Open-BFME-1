// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008AEEC0: Apt native hit test registered at 0x00CB1C2E. One argument tests
// bounds overlap with another character; two or more test a point, or ask slot 30.

struct Rva8BB1A0Bounds
{
	float left;
	float top;
	float right;
	float bottom;
};

class AptValue
{
public:
	float toNumber();
	int toInteger() const;

	void *m_vtable;
	unsigned int m_flags;
};

class AptInteger : public AptValue
{
public:
	static AptInteger *Create(int value);
};

class BfmeQ1235
{
public:
	int m_bfme00;
	int m_bfme04;
};

class BfmeN1235
{
public:
	void bfmeDo1235(void *a, void *b);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x50 - 0x08];
	BfmeQ1235 *m_bfme50;
	char m_bfmePad54[4];
	BfmeN1235 *m_bfme58;
};

struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue **m_rva01338750;
};

typedef void (*BfmeProcVB)(void);
typedef int (__cdecl *Rva008AEEC0PointTest)(float x, float y, BfmeN1235 *owner);

// The array pointer at VA 0x01338750 is offset 8 of the existing stack
// object at VA 0x01338748, also witnessed by Rva008AE7C0CreateChannels.cpp.
extern Rva008AE770Stack Rva008AE770TheStack;
extern int g_bfmeB1038;
extern BfmeProcVB g_bfmeSlot30VB;

AptValue *__cdecl Rva008AEEC0(BfmeN1235 *owner, int count)
{
	if (count == 1)
	{
		AptValue *value = (*reinterpret_cast<AptValue **>(4 * (Rva008AE770TheStack.m_count - 1) + reinterpret_cast<unsigned int>(Rva008AE770TheStack.m_rva01338750)));
		int type = value->m_flags & 0x3f;
		if (type >= 0xc && type <= 0x13)
		{
			Rva8BB1A0Bounds mine;
			mine.left = 1.0e9f;
			mine.right = -1.0e9f;
			mine.bottom = -1.0e9f;
			mine.top = 1.0e9f;
			owner->bfmeDo1235((void *)g_bfmeB1038, &mine);

			Rva8BB1A0Bounds other;
			other.left = 1.0e9f;
			other.right = -1.0e9f;
			other.bottom = -1.0e9f;
			other.top = 1.0e9f;
			((BfmeN1235 *)value)->bfmeDo1235((void *)g_bfmeB1038, &other);

			if (other.left <= mine.right && other.right >= mine.left
				&& other.bottom >= mine.top && other.top <= mine.bottom)
				return AptInteger::Create(1);
		}
	}
	else if (count > 1)
	{
		float x = (*reinterpret_cast<AptValue **>(4 * (Rva008AE770TheStack.m_count - 1) + reinterpret_cast<unsigned int>(Rva008AE770TheStack.m_rva01338750)))->toNumber();
		float y = (*reinterpret_cast<AptValue **>(4 * (Rva008AE770TheStack.m_count - 2) + reinterpret_cast<unsigned int>(Rva008AE770TheStack.m_rva01338750)))->toNumber();
		if (count > 2 && (*reinterpret_cast<AptValue **>(4 * (Rva008AE770TheStack.m_count - 3) + reinterpret_cast<unsigned int>(Rva008AE770TheStack.m_rva01338750)))->toInteger() != 0)
			return AptInteger::Create(((Rva008AEEC0PointTest)g_bfmeSlot30VB)(x, y, owner));

		Rva8BB1A0Bounds mine;
		mine.left = 1.0e9f;
		mine.right = -1.0e9f;
		mine.bottom = -1.0e9f;
		mine.top = 1.0e9f;
		owner->bfmeDo1235((void *)g_bfmeB1038, &mine);

		if (x >= mine.left && x <= mine.right && y >= mine.top && y <= mine.bottom)
			return AptInteger::Create(1);
	}

	return AptInteger::Create(0);
}
