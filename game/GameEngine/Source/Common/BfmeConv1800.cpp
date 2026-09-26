class BfmeThingQZ
{
public:
	void bfmeGoQZ(void);
};

BfmeThingQZ * __cdecl bfmeLookupQZ(void *key);

class BfmeOwnerQZ
{
public:
	void bfmeRunQZ(void);

	unsigned char m_bfmeHeadQZ[8];
	void *m_bfmeKeyQZ;
};

void BfmeOwnerQZ::bfmeRunQZ(void)
{
	void *key = m_bfmeKeyQZ;
	BfmeThingQZ *thing = bfmeLookupQZ(key);

	if (thing)
		thing->bfmeGoQZ();
}
