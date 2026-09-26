// Retail @ 0x006C5BE0, integer exponentiation for a double base.

static const double g_rva006C5BE0One = 1.0;

double Rva006C5BE0(double value, int exponent)
{
	int magnitude = exponent;
	if (magnitude < 0)
		magnitude = -magnitude;

	double result = g_rva006C5BE0One;
	do
	{
		if (magnitude & 1)
			result *= value;
		magnitude = (int)((unsigned int)magnitude >> 1);
		if (magnitude != 0)
			value *= value;
	} while (magnitude != 0);

	if (exponent < 0)
		result = g_rva006C5BE0One / result;
	return result;
}
