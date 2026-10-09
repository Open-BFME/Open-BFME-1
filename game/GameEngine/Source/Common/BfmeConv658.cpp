extern int g_rva012F1030;

// Guarded function-local static, as in BfmeConv657.
int bfmeGoCWC()
{
	static int s_bfmeIdCWC = g_rva012F1030++;
	return s_bfmeIdCWC;
}
