class BfmeOwnerZA
{
public:
	int bfmeTryZA(void *a, void *b, float value);

	void bfmeDoZA(void *a, void *b, int mode, int zero, int amount, int flags,
	              float *out, char *ok);
};

int BfmeOwnerZA::bfmeTryZA(void *a, void *b, float value)
{
	char ok = 0;
	float out;

	bfmeDoZA(a, b, 0x100, 0, (int)value, 0, &out, &ok);

	return ok == 0 ? 1 : 0;
}
