struct Rva000B5A10BitSelectPointer
{
	void *select();
};

void *Rva000B5A10BitSelectPointer::select()
{
	if ( *(unsigned char *)((char *)this + 0x98) & 1 )
		return (char *)this + 0x9C;
	return (char *)this + 8;
}
