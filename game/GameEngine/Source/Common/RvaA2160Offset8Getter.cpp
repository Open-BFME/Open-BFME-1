// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

struct RvaA2160Offset8Getter
{
	unsigned char unused[8];
	unsigned int value;

	unsigned int get_value();
};

unsigned int RvaA2160Offset8Getter::get_value()
{
	return value;
}
