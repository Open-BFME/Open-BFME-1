void bfmeFreeBOF(void *what);

class BfmeThingBOF
{
public:
	void bfmeOneBOF();
	void bfmeTwoBOF();
	void bfmeGoBOF();
	unsigned char m_bfmeHead[0x44];
	void *m_bfmeWhat;
};

void BfmeThingBOF::bfmeGoBOF()
{
	bfmeOneBOF();
	bfmeFreeBOF(m_bfmeWhat);
	bfmeTwoBOF();
}
