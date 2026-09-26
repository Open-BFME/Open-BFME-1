struct Rva2613E0TripleResetThunk
{
	Rva2613E0TripleResetThunk *reset();

	void *table;
	unsigned int first;
	unsigned int second;
	unsigned int third;
};

Rva2613E0TripleResetThunk *Rva2613E0TripleResetThunk::reset()
{
	first = 0;
	second = 0;
	third = 0;
	return this;
}
