// cl: /DNDEBUG /MD /EHsc

// The global at 0x012F0FF8 is the LightPointSystem (see
// LightPointSystemRva0039C260.cpp); +0x274 is the level-index store its
// rva0039CB60/rva0039C260 pair adds to and erases from.
class BfmeUniqueIntegerStoreC8C0
{
private:
	unsigned int m_unmodelled_00;
};

class LightPointSystem
{
public:
	void rva0039C260(BfmeUniqueIntegerStoreC8C0 *indices, void *context);
};

extern LightPointSystem *g_bfmeSinkBRB;

class BfmeItemEUA
{
public:
	void bfmeRunEUAe(void *context);

private:
	unsigned char m_unmodelled_000[0x274];
	BfmeUniqueIntegerStoreC8C0 m_at274;
};

void BfmeItemEUA::bfmeRunEUAe(void *context)
{
	if (g_bfmeSinkBRB)
	{
		g_bfmeSinkBRB->rva0039C260(&m_at274, context);
	}
}
