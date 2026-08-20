// cl: /DNDEBUG /MD /EHsc

// Retail 0x006FCDF0. m_cc = 0; then virtual slot 0x10(0).

class Gen_006fcdf0
{
public:
	void run(void);
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(int);

private:
	unsigned char m_pad[0xCC - 4];
	int m_cc;
};

// ?run@Gen_006fcdf0@@QAEXXZ
void Gen_006fcdf0::run(void)
{
	m_cc = 0;
	v4(0);
}
