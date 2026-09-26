struct Rva00097130Offset28PointerGetter
{
	unsigned char unused[0x1c];
	unsigned int value;

	unsigned int *get_value();
};

unsigned int *Rva00097130Offset28PointerGetter::get_value()
{
	return &value;
}
