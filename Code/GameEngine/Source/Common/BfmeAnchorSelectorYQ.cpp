// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the anchor point selector at retail 0x00423300, 111 bytes.  Own
// point, then the looked-up entry's, then a function-local static fallback at
// (-100, -100, 0) whose constructor is inlined into the guarded block.

class Vector3YQ
{
public:
	Vector3YQ(float x, float y, float z) : X(x), Y(y), Z(z) {}

	~Vector3YQ(void);

	float X;						// +0x00
	float Y;						// +0x04
	float Z;						// +0x08
};

class BfmeEntryYQ
{
public:
	char m_bfmePad00[0x38];					// +0x00
	Vector3YQ m_bfmePoint;					// +0x38
};

class BfmeThingYQ
{
public:
	BfmeEntryYQ *bfmeFindYQ(int kind, int flags);
};

class Gen_00423300
{
public:
	Vector3YQ *bfmeAnchorYQ(BfmeThingYQ *thing);

	char m_bfmePad00[0x08];					// +0x00
	Vector3YQ m_bfmeOwnPoint;				// +0x08
	bool m_bfmeHasOwn;					// +0x14
};

// ?bfmeAnchorYQ@Gen_00423300@@QAEPAVVector3YQ@@PAVBfmeThingYQ@@@Z
Vector3YQ *Gen_00423300::bfmeAnchorYQ(BfmeThingYQ *thing)
{
	if (m_bfmeHasOwn)
		return &m_bfmeOwnPoint;

	BfmeEntryYQ *entry = thing->bfmeFindYQ(1, 0);

	if (entry != 0)
		return &entry->m_bfmePoint;

	static Vector3YQ s_bfmeFallbackYQ(-100.0f, -100.0f, 0.0f);

	return &s_bfmeFallbackYQ;
}
