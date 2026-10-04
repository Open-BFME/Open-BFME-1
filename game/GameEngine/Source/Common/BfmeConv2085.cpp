// Open-BFME5 keyed map copy, retail 0x003D1690.
//
// The two callees this body references are named by the ledger as the
// functions actually sitting behind the retail ILT thunks:
//
//   ILT 0x0003A49A -> ?j_0003a49a -> retail 0x003D4540, matched as
//     ??4LargeGroupAudioKeyMap@@QAEAAV0@ABV0@@Z (LargeGroupAudioKeyMapAssignment.cpp)
//   ILT 0x0002A4F0 -> ?j_0002a4f0 -> retail 0x003D1650, matched as
//     ?invoke@Rva003D1650@@QAEXXZ (MemberOffsetTailThunks.cpp), the
//     `add ecx,8 / jmp` forwarder into the vector<Gen003D1380Elem>
//     destructor at 0x003D1380 for the slot's member at +8.
//
// The base is therefore spelled with the defining name so the reference
// links, and the slot teardown calls the forwarder by its defining name
// before freeing the block, which is what retail's two calls do.

class UnicodeString
{
public:
	void set(const UnicodeString &o);
};

class Rva003D1650
{
public:
	void invoke(void);
};

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap &operator=(const LargeGroupAudioKeyMap &o);

	unsigned char m_bfmeHeadXF[0xc];
};

class BfmeMapXF : public LargeGroupAudioKeyMap
{
public:
	void bfmeAssignXF(const BfmeMapXF &o);

	UnicodeString m_bfmeTextXF;
	Rva003D1650 *m_bfmeSlotXF[4];
};

void BfmeMapXF::bfmeAssignXF(const BfmeMapXF &o)
{
	if (&o == this)
		return;

	Rva003D1650 **q = m_bfmeSlotXF;
	int n = 4;

	do
	{
		Rva003D1650 *p = *q;

		if (p)
		{
			p->invoke();
			delete p;
			*q = 0;
		}

		q++;
	}
	while (--n);

	LargeGroupAudioKeyMap::operator=(o);
	m_bfmeTextXF.set(o.m_bfmeTextXF);
}