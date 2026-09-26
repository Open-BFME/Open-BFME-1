extern "C" unsigned int *__cdecl rva60A7F0FillWords(
	unsigned int *destination,
	unsigned int count,
	const unsigned int *value)
{
	while (count > 0) {
		*destination = *value;
		++destination;
		--count;
	}
	return destination;
}
