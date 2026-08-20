// cl: /DNDEBUG /MD /EHsc

// Retail 0x0071BFB0. Return this+0x94.

class Gen_0071bfb0
{
public:
	unsigned char *addr(void);

private:
	unsigned char m_pad[0x94];
	unsigned char m_value;
};

// ?addr@Gen_0071bfb0@@QAEPAEXZ
unsigned char *Gen_0071bfb0::addr(void)
{
	return &m_value;
}
