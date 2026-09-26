// cl: /O2 /Ob0

unsigned __fastcall rva00902550Power2Clamp(unsigned value, unsigned maximum)
{
	unsigned result = 1;
	while (result < value) {
		result <<= 1;
	}
	if (result >= maximum) {
		result = maximum;
	}
	return result;
}
