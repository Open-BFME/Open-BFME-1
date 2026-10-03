// 0x000283D5 is retail's 5-byte ILT thunk (?j_000283d5@@YAXXZ); the
// __cdecl routine behind it is routed through the thunk's address.
extern void j_000283d5();

typedef void *(__cdecl *BfmeMakeASBCall)(int, int);

class BfmeThingASB
{
public:
	BfmeThingASB *bfmeInitASB();
	int m_bfmeZero;
	unsigned char m_bfmeGap[4];
	void *m_bfmeGot;
	unsigned int m_bfmeScale;
	int m_bfmeCount;
	bool m_bfmeFlag;
};

BfmeThingASB *BfmeThingASB::bfmeInitASB()
{
	m_bfmeZero = 0;
	m_bfmeGot = ((BfmeMakeASBCall)j_000283d5)(0, 0);
	m_bfmeScale = 0x3f800000;
	m_bfmeCount = 0;
	m_bfmeFlag = false;
	return this;
}
