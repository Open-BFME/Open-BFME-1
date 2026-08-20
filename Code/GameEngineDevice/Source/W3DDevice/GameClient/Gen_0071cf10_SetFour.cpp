// cl: /DNDEBUG /MD /EHsc

// Retail 0x0071CF10. Store 1 at four large byte offsets.

class Gen_0071cf10
{
public:
	void enable(void);

private:
	unsigned char m_pad_1e1ccc[0x1E1CCC];
	unsigned char m_1e1ccc;
	unsigned char m_1e1ccd;
	unsigned char m_pad_1e1cd1[0x1E1CD1 - 0x1E1CCE];
	unsigned char m_1e1cd1;
	unsigned char m_pad_1e391c[0x1E391C - 0x1E1CD2];
	unsigned char m_1e391c;
};

// ?enable@Gen_0071cf10@@QAEXXZ
void Gen_0071cf10::enable(void)
{
	m_1e1cd1 = 1;
	m_1e391c = 1;
	m_1e1ccc = 1;
	m_1e1ccd = 1;
}
