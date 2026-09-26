// ?get@Rva0043A560ByteAt0D@@QBEEXZ
// cl: /O2 /GR- /EHsc-

class Rva0043A560ByteAt0D
{
public:
	unsigned char get(void) const;
};

unsigned char Rva0043A560ByteAt0D::get(void) const
{
	return *((const unsigned char *)this + 0x0d);
}
