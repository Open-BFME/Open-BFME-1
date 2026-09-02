// ??0Gen0002857E@@QAE@PAVGen0002857EOwner@@ABV?$StringBase@D@@@Z
// partial score=0.9 date=2026-09-02
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ??0Gen0002857E@@QAE@PAVGen0002857EOwner@@ABV?$StringBase@D@@@Z
// Copy-construct StringBase<char> at +0 from arg2, then clear the rest
// and store the owner pointer at +4.

struct BfmeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

template <typename T>
class StringBase
{
	friend class Gen0002857E;
	StringBase(const StringBase<T> &src);
	BfmeStringData *m_data;
};

class Gen0002857EOwner;

class Gen0002857E
{
public:
	Gen0002857E(Gen0002857EOwner *owner, const StringBase<char> &name);

private:
	struct Block9
	{
		int v[9];
		void clear()
		{
			int *p = v;
			p[0] = 0;
			p[1] = 0;
			p[2] = 0;
			p[3] = 0;
			p[4] = 0;
			p[5] = 0;
			p[6] = 0;
			p[7] = 0;
			p[8] = 0;
		}
	};

	StringBase<char> m_name;
	Gen0002857EOwner *m_owner;
	Block9 m_block;
	int m_2C;
	int m_30;
	int m_count;
	int m_stamp;
	int m_3C;
	char m_40;
	char m_41;
	char m_42;
};

Gen0002857E::Gen0002857E(Gen0002857EOwner *owner, const StringBase<char> &name)
	: m_name(name)
{
	m_count = 0;
	m_stamp = 0;
	m_41 = 0;
	m_2C = 0;
	m_30 = 0;
	m_3C = 0;
	m_40 = 0;
	m_42 = 0;
	m_owner = owner;
	Block9 &b = m_block;
	int z = 0;
	b.v[0] = z;
	b.v[1] = z;
	b.v[2] = z;
	b.v[3] = z;
	b.v[4] = z;
	b.v[5] = z;
	b.v[6] = z;
	b.v[7] = z;
	b.v[8] = z;
}
