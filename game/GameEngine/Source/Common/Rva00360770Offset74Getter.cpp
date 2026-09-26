// Retail 0x00360770 reads the unsigned field at offset 0x74; no owner identity is proven.
struct Rva00360770Offset74Getter
{
	unsigned char padding[ 0x74 ];
	unsigned int value;

	unsigned int getValue() const;
};

unsigned int Rva00360770Offset74Getter::getValue() const
{
	return value;
}
