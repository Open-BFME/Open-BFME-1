// cl: /DNDEBUG /MD /EHsc

// Retail 0x0074AC00 widens a signed-short range into an int range.  The body
// has the same shape as STLport's random-access copy loop; its owning template
// instantiation is not independently named, so this entry stays RVA-derived.
extern "C" int *__cdecl rva0074AC00CopySignedShorts(
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
