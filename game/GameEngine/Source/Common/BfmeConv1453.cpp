// cl: /Od

char *bfmeFillV14(char *p, unsigned n, char v);
class BfmeStrV14
{
public:
	BfmeStrV14 *bfmeAssignV14(char *first, char *last, unsigned n, char v);
	void bfmeEraseV14(char *first, char *last);
	void bfmeInsertV14(char *at, unsigned n, char v);
};

BfmeStrV14 *BfmeStrV14::bfmeAssignV14(char *first, char *last, unsigned n, char v)
{
	char unused[8];
	unsigned dist = (unsigned)(last - first);

	if (dist >= n)
	{
		bfmeFillV14(first, n, v);
		bfmeEraseV14(first + n, last);
	}
	else
	{
		bfmeFillV14(first, dist, v);
		bfmeInsertV14(last, n - dist, v);
	}
	return this;
}
