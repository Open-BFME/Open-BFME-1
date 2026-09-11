// ?build@Gen003BD7D0Node@@QAEPAVGen003BD8D0Built@@XZ
// Retail 0x003A3E90 (46 bytes).  Rva003BF540::act calls this body on the
// lookup result; the matching caller and the pinned 0x00046150 helper establish
// the node/global family.  The body builds the three-word request consumed by
// Glo012F1028's +0x28 subobject.

class Gen003BD8D0Built
{
};

class BfmeJ1052
{
public:
	void bfmeUse1052( int *value );
};

class Glo012F1028Type
{
public:
	char m_pad00[0x28];
	BfmeJ1052 *m_bfmeSub;
};

extern Glo012F1028Type * volatile Glo012F1028;

class Gen003BD7D0Node
{
public:
	char m_pad00[0x0c];
	int m_at0C;
	int m_at10;

	Gen003BD8D0Built *build();
};

Gen003BD8D0Built *Gen003BD7D0Node::build()
{
	int value[3];
	value[0] = m_at0C;
	value[1] = m_at10;
	value[2] = 0;
	int *valueAddress = value;
	BfmeJ1052 *sub = Glo012F1028->m_bfmeSub;
	typedef Gen003BD8D0Built *(BfmeJ1052::*ReturnCall)( int * );
	typedef void (BfmeJ1052::*VoidCall)( int * );
	union
	{
		ReturnCall asReturn;
		VoidCall asVoid;
	} call;
	call.asVoid = &BfmeJ1052::bfmeUse1052;
	return (sub->*call.asReturn)(valueAddress);
}
