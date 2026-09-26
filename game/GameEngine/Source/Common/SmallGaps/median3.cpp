// ?median3@@YAMMMM@Z
float median3(float a, float b, float c)
{
	return a < b ? (b < c ? b : (a < c ? c : a)) : (a < c ? a : (b < c ? c : b));
}
