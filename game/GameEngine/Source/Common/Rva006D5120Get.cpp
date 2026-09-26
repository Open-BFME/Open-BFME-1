// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva006D5120
{
public:
	int get() const;
};

int Rva006D5120::get() const
{
	return *(const int *)this;
}
