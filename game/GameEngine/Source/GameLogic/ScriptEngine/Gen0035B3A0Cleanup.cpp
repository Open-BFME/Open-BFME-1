// cl: /DNDEBUG /MD /EHsc

class NestedAt0C
{
public:
	void cleanup(void);
};

class NestedAt2C
{
public:
	void cleanup(void);
};

// The nested cleanups reach 0x0035AB70 (ILT 0x00011FEF) and 0x0035AD00;
// called as those ledger rows name them.
class Rva00359330StringRecordTable
{
public:
	void cleanup(void);
};

class Rva0035AD00Table
{
public:
	void cleanup(void);
};

class Gen0035B3A0
{
public:
	void cleanup(void);
	void unlink(void *slot);

private:
	void *m_unused0;
	int m_slot4;
	unsigned char m_pad[0xC - 8];
	NestedAt0C m_at0C;
	unsigned char m_pad2[0x2C - 0xC - sizeof(NestedAt0C)];
	NestedAt2C m_at2C;
};

// @?cleanup@Gen0035B3A0@@QAEXXZ 0x0035B3A0
void Gen0035B3A0::cleanup(void)
{
	unlink(this ? &m_slot4 : 0);
	((Rva00359330StringRecordTable *)&m_at0C)->cleanup();
	((Rva0035AD00Table *)&m_at2C)->cleanup();
}
