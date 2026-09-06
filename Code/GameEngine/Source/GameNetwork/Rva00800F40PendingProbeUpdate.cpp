// EA FESL gamebrowser pending-probe update at retail 0x00800F40.
//
// The method is reached through the secondary subobject at +4 of the
// gamebrowser owner.  Its +0xC0/+0xC4/+0xC8 and +0x1F0 fields therefore line
// up with the owner's +0xC4/+0xC8/+0xCC and +0x1F4 fields.  The probe records
// are the already recovered 0x24-byte slots from the neighboring demangler
// constructor, and the cursor below starts at each slot's +4 field exactly as
// the retail loop does.

class FeslEchoNotifier
{
public:
	void notifyEcho();
};

class BfmeI1052
{
	public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
};

class BfmeH1052
{
public:
	void bfmeDo1052(int a, BfmeI1052 *p, int r);
};

class BfmeSinkVNC
{
public:
	virtual void bfmeDropVNC(int a, void *p);
};

struct BfmeSlotVNC
{
	void *m_bfme00;
	int m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	void *m_bfme0c;
	BfmeI1052 m_bfme10;
	int m_bfme20;
};

// The compiler-visible cursor begins at BfmeSlotVNC::m_bfme04.  Four bytes
// before it is the slot's m_bfme00, and the next record begins 0x24 bytes
// later, so the loop uses an explicit byte stride rather than inventing a
// second object layout.
struct BfmeSlotCursorVNC
{
	int m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	void *m_bfme0c;
	BfmeI1052 m_bfme10;
	int m_bfme20;
};

struct Rva007EB810Diag
{
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva00800F40PendingProbeUpdate
{
public:
	void update(unsigned int now);

	char m_pad00[8];
	BfmeSinkVNC *m_bfme0c;
	char m_pad0c[0xb4];
	unsigned int m_bfme0c0;
	int m_bfme0c4;
	int m_bfme0c8;
	char m_padcc[4];
	BfmeSlotVNC m_bfme0d0[8];
	int m_bfme1f0;
};

void Rva00800F40PendingProbeUpdate::update(unsigned int now)
{
	int zero = 0;

	if (m_bfme0c4 != zero && now > m_bfme0c0)
	{
		int tries = ++m_bfme0c8;
		if (tries > 4)
			m_bfme0c4 = zero;
		else
		{
			m_bfme0c0 = now + 0xc8;
			((FeslEchoNotifier *)((char *)this - 4))->notifyEcho();
		}
	}

	if (m_bfme1f0 != zero)
	{
		BfmeSlotCursorVNC *slot =
			(BfmeSlotCursorVNC *)((char *)m_bfme0d0 + 4);
		int n = 8;

		do
		{
			volatile int *keyPtr = (volatile int *)((char *)slot - 4);
			int key = *keyPtr;
			if (key != zero && now > slot->m_bfme20)
			{
				int probes = ++slot->m_bfme04;
				int limit = slot->m_bfme08 ? 0x14 : 4;

				if (probes > limit)
				{
					m_bfme0c->bfmeDropVNC(-0x66, slot->m_bfme0c);
					*(int *)((char *)slot - 4) = zero;
					slot->m_bfme04 = zero;
					slot->m_bfme0c = 0;
					slot->m_bfme20 = zero;
					slot->m_bfme08 = (char)zero;
					--m_bfme1f0;
					if (m_bfme1f0 < zero)
						Rva007EB810Get()->fail(
							"mNumProbes >= 0",
							"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserdemangler.cpp",
							0x147);
				}
				else
				{
					slot->m_bfme20 = now + 0xc8;
					((BfmeH1052 *)((char *)this - 4))->bfmeDo1052(
						1, &slot->m_bfme10, key);
				}
			}

			slot = (BfmeSlotCursorVNC *)((char *)slot + 0x24);
			--n;
		} while (n != zero);
	}
}
