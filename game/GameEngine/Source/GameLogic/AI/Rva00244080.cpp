// cl: /DNDEBUG /MD /EHsc

struct BfmeRvaContainedNode
{
	BfmeRvaContainedNode *next;
	BfmeRvaContainedNode *previous;
	void *object;
};

class BfmeRvaPrimaryView
{
public:
#define BFME_RVA_SLOT( N ) virtual void slot##N(void) = 0
	BFME_RVA_SLOT( 00 ); BFME_RVA_SLOT( 01 ); BFME_RVA_SLOT( 02 ); BFME_RVA_SLOT( 03 );
	BFME_RVA_SLOT( 04 ); BFME_RVA_SLOT( 05 ); BFME_RVA_SLOT( 06 ); BFME_RVA_SLOT( 07 );
	BFME_RVA_SLOT( 08 ); BFME_RVA_SLOT( 09 ); BFME_RVA_SLOT( 10 ); BFME_RVA_SLOT( 11 );
	BFME_RVA_SLOT( 12 ); BFME_RVA_SLOT( 13 ); BFME_RVA_SLOT( 14 ); BFME_RVA_SLOT( 15 );
	BFME_RVA_SLOT( 16 ); BFME_RVA_SLOT( 17 ); BFME_RVA_SLOT( 18 ); BFME_RVA_SLOT( 19 );
	BFME_RVA_SLOT( 20 ); BFME_RVA_SLOT( 21 ); BFME_RVA_SLOT( 22 ); BFME_RVA_SLOT( 23 );
	BFME_RVA_SLOT( 24 ); BFME_RVA_SLOT( 25 ); BFME_RVA_SLOT( 26 ); BFME_RVA_SLOT( 27 );
	BFME_RVA_SLOT( 28 ); BFME_RVA_SLOT( 29 ); BFME_RVA_SLOT( 30 ); BFME_RVA_SLOT( 31 );
	BFME_RVA_SLOT( 32 ); BFME_RVA_SLOT( 33 ); BFME_RVA_SLOT( 34 ); BFME_RVA_SLOT( 35 );
	BFME_RVA_SLOT( 36 ); BFME_RVA_SLOT( 37 ); BFME_RVA_SLOT( 38 ); BFME_RVA_SLOT( 39 );
	BFME_RVA_SLOT( 40 ); BFME_RVA_SLOT( 41 ); BFME_RVA_SLOT( 42 ); BFME_RVA_SLOT( 43 );
	BFME_RVA_SLOT( 44 ); BFME_RVA_SLOT( 45 ); BFME_RVA_SLOT( 46 ); BFME_RVA_SLOT( 47 );
	BFME_RVA_SLOT( 48 ); BFME_RVA_SLOT( 49 ); BFME_RVA_SLOT( 50 ); BFME_RVA_SLOT( 51 );
	BFME_RVA_SLOT( 52 ); BFME_RVA_SLOT( 53 ); BFME_RVA_SLOT( 54 ); BFME_RVA_SLOT( 55 );
	BFME_RVA_SLOT( 56 ); BFME_RVA_SLOT( 57 ); BFME_RVA_SLOT( 58 ); BFME_RVA_SLOT( 59 );
	BFME_RVA_SLOT( 60 ); BFME_RVA_SLOT( 61 ); BFME_RVA_SLOT( 62 ); BFME_RVA_SLOT( 63 );
	BFME_RVA_SLOT( 64 ); BFME_RVA_SLOT( 65 ); BFME_RVA_SLOT( 66 ); BFME_RVA_SLOT( 67 );
	BFME_RVA_SLOT( 68 );
	virtual void notifyMembers(void) = 0;
#undef BFME_RVA_SLOT
};

class BfmeRvaAIView
{
public:
	void setHeldState(int, int);
};

class Rva00244080
{
public:
	void updateMembers(void);
};

void Rva00244080::updateMembers(void)
{
	if (*(unsigned char *)((char *)this + 0x118))
		((BfmeRvaPrimaryView *)this)->notifyMembers();

	BfmeRvaContainedNode *node =
		(*(BfmeRvaContainedNode **)((char *)this - 0xac))->next;
	while (node != *(BfmeRvaContainedNode **)((char *)this - 0xac))
	{
		void *object = node->object;
		BfmeRvaAIView *ai =
			*(BfmeRvaAIView **)((char *)object + 0x204);
		if (ai)
			((BfmeRvaAIView *)((char *)ai + 0x20))->setHeldState(0, 1);
		node = node->next;
	}
}
