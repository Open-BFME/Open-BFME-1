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
	m_at0C.cleanup();
	m_at2C.cleanup();
}
