// cl: /DNDEBUG /MD /EHsc

// Retail 0x0074CD80 widens a signed-short range into an int range.  Same bytes
// as 0x0074AC00 / 0x0074D6A0; this dump row is converted independently.
extern "C" int *__cdecl rva0074CD80CopySignedShorts(
	const short *first, const short *last, int *result)
{
	register const short *current = first;
	register const short *finish = last;
	register int *output = result;
	register int count = finish - current;
	for (; count > 0; --count, ++current, ++output)
		*output = *current;
	return output;
}
