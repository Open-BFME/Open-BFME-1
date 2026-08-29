// Open-BFME5 conversions.

extern "C" float g_bfmeK1127;

class BfmeA1127
{
public:
	virtual void bfmeV001127(void) = 0;
	virtual void bfmeV011127(void) = 0;
	virtual void bfmeV021127(void) = 0;
	virtual void bfmeV031127(void) = 0;
	virtual void bfmeV041127(void) = 0;
	virtual void bfmeV051127(void) = 0;
	virtual void bfmeV061127(void) = 0;
	virtual void bfmeV071127(void) = 0;
	virtual void bfmeV081127(void) = 0;
	virtual void bfmeV091127(void) = 0;
	virtual void bfmeV101127(void) = 0;
	virtual void bfmeV111127(void) = 0;
	virtual void bfmeV121127(void) = 0;
	virtual void bfmeV131127(void) = 0;
	virtual void bfmeV141127(void) = 0;
	virtual void bfmeV151127(void) = 0;
	virtual void bfmeV161127(void) = 0;
	virtual void bfmeV171127(void) = 0;
	virtual void bfmeV181127(void) = 0;
	virtual char bfmeV191127(int a1, int a2, float *o1, float *o2) = 0;
	float bfmeGo1127(int a1, int a2);
};

float BfmeA1127::bfmeGo1127(int a1, int a2)
{
	float lo = 0.0f;
	float hi = 0.0f;

	if (!bfmeV191127(a1, a2, &lo, &hi))
		return g_bfmeK1127;

	return lo - hi;
}
