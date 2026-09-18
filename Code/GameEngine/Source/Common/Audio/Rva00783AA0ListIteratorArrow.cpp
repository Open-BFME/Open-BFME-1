struct Rva00783AA0ListIteratorArrow
{
	unsigned char *pointer;

	unsigned char *payload() const;
};

unsigned char *Rva00783AA0ListIteratorArrow::payload() const
{
	return pointer + 4;
}
