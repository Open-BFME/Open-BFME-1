// Callees (tools/callees.py 0x16C930 56): ILT 0x9C41 -> 0x001BE270
// AssistedTargetingObjectShim::find, ILT 0x28F74 -> 0x001E1770 Rva001E1770ByteField::get.
class AssistedTargetingObjectShim
{
public:
	void *find(int out);
};

class Rva001E1770ByteField
{
public:
	unsigned char get(void) const;
};

class BfmeInnerFX
{
public:

	unsigned char m_bfmeHeadFX[0x68];
	int m_bfmeValueFX;
};

class BfmeThingFX
{
public:
	unsigned char m_bfmeHeadFX[4];
	BfmeInnerFX *m_bfmeInnerFX;
};

class BfmeHolderFX
{
public:
	unsigned char m_bfmeHeadFX[0x10];
	AssistedTargetingObjectShim *m_bfmeFinderFX;
};

class BfmeOwnerFX
{
public:
	char bfmeCheckFX(void);

	unsigned char m_bfmeHeadFX[0x1c];
	BfmeHolderFX *m_bfmeHolderFX;
};

char BfmeOwnerFX::bfmeCheckFX(void)
{
	int scratch;
	int *out = &scratch;
	AssistedTargetingObjectShim *finder = m_bfmeHolderFX->m_bfmeFinderFX;

	BfmeThingFX *thing = (BfmeThingFX *)finder->find((int)out);
	if (thing != 0)
	{
		if (reinterpret_cast<Rva001E1770ByteField *>(thing->m_bfmeInnerFX)->get())
			return 1;

		if (thing->m_bfmeInnerFX->m_bfmeValueFX >= 0)
			return 1;
	}

	return 0;
}
