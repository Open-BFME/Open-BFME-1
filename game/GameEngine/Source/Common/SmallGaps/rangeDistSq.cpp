// ?rangeDistSq@@YAHHHH@Z
int rangeDistSq(int lo, int len, int x)
{
	if (x < lo)
		return (lo - x - 1) * (lo - x - 1);
	if (x >= lo + len) {
		int d = x - lo - len;
		return d * d;
	}
	return 0;
}
