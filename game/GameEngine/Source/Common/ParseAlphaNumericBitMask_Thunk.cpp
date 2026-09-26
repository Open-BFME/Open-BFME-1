// cl: /Od /GZ
// Convert a compact alphanumeric set description to a bit mask.  The retail
// table maps A-Z/a-z to bits 0-25 and 0-3 to bits 27-30; every other byte is
// -1 and terminates the scan.  A null description preserves the fallback.

extern signed char GenCharToBit0012A430[256];

unsigned int ParseAlphaNumericBitMask(const char *description, unsigned int fallback)
{
	if (description == 0) {
		return fallback;
	}

	unsigned int mask = 0;
	int bit;
	for (; (bit = GenCharToBit0012A430[*description]) >= 0; ++description) {
		mask |= 1U << bit;
	}

	return mask;
}
