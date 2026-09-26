// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeE1224;

class BfmeS1238
{
public:
	BfmeS1238 *bfmeAt1238B(int index);
};

class BfmeA1224
{
public:
	BfmeE1224 *bfmeSub1224(int index);

	char m_bfmePad00[8];
	BfmeS1238 m_bfme08;
	char m_bfmePad0c[0x18 - 0x0c];
	BfmeE1224 **m_bfme18;
	int m_bfme1c;
};

BfmeE1224 *BfmeA1224::bfmeSub1224(int index)
{
	if (index < (m_bfme1c & 0xff))
		return m_bfme18[index];
	int count = m_bfme1c & 0xff;
	return (BfmeE1224 *)m_bfme08.bfmeAt1238B(index - count);
}
