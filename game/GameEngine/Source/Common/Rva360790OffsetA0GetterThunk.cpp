struct Rva360790OffsetA0GetterThunk
{
	unsigned int getValue() const;

	unsigned char padding[0xa0];
	unsigned int value;
};

unsigned int Rva360790OffsetA0GetterThunk::getValue() const
{
	return value;
}
