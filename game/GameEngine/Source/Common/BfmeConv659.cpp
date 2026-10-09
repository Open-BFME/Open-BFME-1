extern int g_rva012F1030;

// Guarded function-local static, as in BfmeConv657.
int bfmeGoCWD()
{
	static int s_bfmeIdCWD = g_rva012F1030++;
	return s_bfmeIdCWD;
}
