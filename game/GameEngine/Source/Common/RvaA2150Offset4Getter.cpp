// cl: /DNDEBUG /MD /EHs-c-

struct RvaA2150Offset4Getter
{
	unsigned char unused[4];
	unsigned int value;

	unsigned int get_value();
};

unsigned int RvaA2150Offset4Getter::get_value()
{
	return value;
}
