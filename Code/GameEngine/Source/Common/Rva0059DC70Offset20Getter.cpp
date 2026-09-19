// mov eax,[ecx+0x14] / ret -- the body proves only this dword field.

struct Rva0059DC70Offset20Getter
{
	unsigned char unused[0x14];
	unsigned int value;

	unsigned int get_value();
};

unsigned int Rva0059DC70Offset20Getter::get_value()
{
	return value;
}
