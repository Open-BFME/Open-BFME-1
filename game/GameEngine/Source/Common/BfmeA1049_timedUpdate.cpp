// Open-BFME5 conversion of the BFME timed update at retail 0x00535150.

typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

extern int(__cdecl *g_bfmeNowVNH)();
void bfmeFree1049(void *p);

class BfmeA1049
{
public:
	void bfmeStepA1049();
	void bfmeStepB1049();
	void bfmeGo1049B(Bool force);

	char m_bfmePad[0x44];
	void *m_bfmeP;
	char m_bfmePad2[0x54];
	UnsignedInt m_bfmeTime;
};

void BfmeA1049::bfmeGo1049B(Bool force)
{
	int(__cdecl *nowFunction)() = g_bfmeNowVNH;

	if (!force) {
		if (m_bfmeTime != 0) {
			UnsignedInt now = nowFunction();
			if (m_bfmeTime + 5000 > now)
				return;
		}
	}

	bfmeStepA1049();
	bfmeFree1049(m_bfmeP);
	bfmeStepB1049();
	m_bfmeTime = nowFunction();
}
