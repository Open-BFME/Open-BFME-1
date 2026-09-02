class BfmeChunkVFC
{
public:
	unsigned int bfmeReadVFC(void *buffer, unsigned int bytes);
};

struct Rva0096D2C0Record
{
	char m_pad00[0x78];
	int m_value78;
	char m_tail7C[12];
};

class Rva0096D2C0Owner
{
public:
	bool readBlock(BfmeChunkVFC *loader, Rva0096D2C0Record *record);

private:
	char m_pad00[0x9C];
	int *m_destination;
};

bool Rva0096D2C0Owner::readBlock(BfmeChunkVFC *loader, Rva0096D2C0Record *record)
{
	if (loader->bfmeReadVFC(&record->m_value78, 16) != 16)
		return false;

	*m_destination = record->m_value78;
	return true;
}
