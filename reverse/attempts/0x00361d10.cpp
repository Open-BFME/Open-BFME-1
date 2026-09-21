// ?registerNetworkStringIdentities@Rva00361D10Host@@QBEXXZ
// partial score=0.4 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail 0x00361D10 (191B).
// Walks the BfmeSubDVB-shaped vector-of-Rva00361960 view at this+0x18/+0x1c
// (same 0x18-head/0x58-stride shape as the landed BfmeConv787.cpp siblings
// BfmeHostFM/BfmeSubDVB, and Rva00361960::copyString is the SAME landed
// callee BfmeConv787.cpp's BfmeSubDVB::bfmeTwoDVB(int) already calls
// through that view). For each element whose type tag (+0x20) is 3, or is
// 4 with a zero flag byte at +8, copies its shared string and registers it
// against the object at global Glo012F1028 (0x12F1028) via the landed
// Rva003C0350::run(key,src), with src = a MATCH COUNT (only incremented on
// a hit), not the loop index -- retail keeps two separate counters (edi
// for the true loop position used against size(), ebx for the match
// count passed to run()).
//
// PARTIAL: identity, callees, field/vector shape, and the two-counter
// split all reproduce; the EH scope-table DIR32 and 22 leading bytes are
// byte-exact. Residue is register allocation in the size()/count prologue
// (retail keeps the running match count in ebx and loads begin/end into
// edx/ecx before subtracting; every source ordering tried here -- direct
// pointer subtraction, explicit begin/end locals -- keeps choosing
// ebp/esi and folds one load into a memory operand instead), which
// re-encodes most of the loop body even though the instruction sequence
// is the same shape. register/store/loop/frame shape_search (4 trials)
// plateaued at the same score. Best: 76/191 matching bytes (0.40).

typedef int Int;

class BfmeSharedString
{
public:
	BfmeSharedString(const BfmeSharedString &other);
	~BfmeSharedString();
	void *m_data;
};

class Rva00361960
{
public:
	BfmeSharedString copyString();

private:
	unsigned char m_bfmeBody[0x58];
};

class Rva00361E80Vector
{
public:
	int size() const { return m_end - m_begin; }

	Rva00361960 *m_begin;
	Rva00361960 *m_end;
};

class Rva003C0350
{
public:
	void run(void *key, void *src);
};

#define Glo012F1028AsRun (*(Rva003C0350 **)0x012F1028)

class Rva00361D10Host
{
public:
	void registerNetworkStringIdentities() const;

private:
	unsigned char m_bfmeHead[0x18];
	Rva00361E80Vector m_bfmeVectorTwo;
};

void Rva00361D10Host::registerNetworkStringIdentities() const
{
	if (m_bfmeVectorTwo.size() != 0)
	{
		Int matchCount = 0;
		Int offset = 0;
		Int i = 0;
		do
		{
			Rva00361960 *elem = (Rva00361960 *)((char *)m_bfmeVectorTwo.m_begin + offset);
			int type = *(int *)((char *)elem + 0x20);
			if (type == 3 || (type == 4 && *(unsigned char *)((char *)elem + 8) == 0))
			{
				BfmeSharedString s = elem->copyString();
				Glo012F1028AsRun->run(&s, (void *)matchCount);
				++matchCount;
			}
			++i;
			offset += sizeof(Rva00361960);
		} while (i < m_bfmeVectorTwo.size());
	}
}
