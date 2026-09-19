// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0005C220FieldDword
{
public:
	int get() const;
};

int Rva0005C220FieldDword::get() const
{
	return *(const int *)((const char *)this + 0x14);
}
