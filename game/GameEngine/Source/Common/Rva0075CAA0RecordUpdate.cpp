// Neutral ABI view for the unclaimed retail body at 0x0075CAA0.
// Its receiver shares the slot-zero +0xDC/+0xE0 layout used by the matched
// BfmeThingQF neighbor at 0x0075CA70; the public owner name is unrecovered.

struct Rva0075CAA0Ref
{
	virtual void release() = 0;
	int m_referenceCount;
};

struct Rva0075CAA0ValueRecord
{
	float m_value;
	int m_valuePart;
	int m_secondPart;
	int m_firstPart;
	int m_slotZeroInt;
	unsigned char m_slotZeroByte;
	unsigned char m_slotZeroFlag;
	unsigned char m_padding[6];
};

struct Rva0075CAA0ReferenceRecord
{
	Rva0075CAA0Ref *m_reference;
	unsigned char m_padding[0x18];
};

struct Rva0075CAA0ReferenceView
{
	char m_padding[0xdc];
	Rva0075CAA0ReferenceRecord m_records[8];
};

union Rva0075CAA0Storage
{
	Rva0075CAA0ValueRecord m_values[16];
	Rva0075CAA0ReferenceView m_references;
};

class Rva0075CAA0Owner
{
public:
	void update(int index, Rva0075CAA0Ref *replacement,
		unsigned char flag, int firstPart, int secondPart, float value,
		int valuePart, unsigned char slotZeroByte, int slotZeroInt);

private:
	Rva0075CAA0Storage m_storage;
};

void Rva0075CAA0Owner::update(int index, Rva0075CAA0Ref *replacement,
	unsigned char flag, int firstPart, int secondPart, float value,
	int valuePart, unsigned char slotZeroByte, int slotZeroInt)
{
	Rva0075CAA0Ref *oldReference = m_storage.m_references.m_records[index].m_reference;
	if (oldReference != 0)
	{
		if (--oldReference->m_referenceCount == 0)
			oldReference->release();
		m_storage.m_references.m_records[index].m_reference = 0;
	}

	if (replacement == 0)
		return;

	m_storage.m_references.m_records[index].m_reference = replacement;
	++replacement->m_referenceCount;
	m_storage.m_values[index + 8].m_firstPart = firstPart;
	m_storage.m_values[index + 8].m_secondPart = secondPart;
	m_storage.m_values[index + 8].m_value = value;
	m_storage.m_values[index + 8].m_valuePart = valuePart;
	m_storage.m_values[index + 8].m_slotZeroByte = slotZeroByte;
	m_storage.m_values[index + 8].m_slotZeroInt = slotZeroInt;
	m_storage.m_values[index + 8].m_slotZeroFlag = flag;
}
