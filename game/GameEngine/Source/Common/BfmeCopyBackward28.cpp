// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

struct BfmeRecord28
{
	UnsignedInt m_words[7];
};

BfmeRecord28 *bfmeCopyBackward28(
	BfmeRecord28 *first, BfmeRecord28 *last, BfmeRecord28 *result)
{
	int count = last - first;
	while (count > 0)
	{
		--last;
		--result;
		*result = *last;
		--count;
	}
	return result;
}
