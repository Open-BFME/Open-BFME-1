// Retail RVA 0x00270070 reads the dword at offset 0xBC through an override chain.
// The neighboring accessors establish the recursive Overridable layout and ABI.

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class Rva00270070OverrideData : public Overridable
{
public:
	char m_unreconstructed_08[0xBC - 8];
	int m_field;
};

class Rva00270070
{
public:
	int field(void) const;

private:
	void *m_unreconstructed_00;
	const Rva00270070OverrideData *m_data;
};

int Rva00270070::field(void) const
{
	const Rva00270070OverrideData *data = m_data;
	const Rva00270070OverrideData *finalData;
	if (data == 0)
		finalData = data;
	else
	{
		finalData = (const Rva00270070OverrideData *)
			(data->m_nextOverride ? data->m_nextOverride->getFinalOverride() : data);
	}
	return finalData->m_field;
}
