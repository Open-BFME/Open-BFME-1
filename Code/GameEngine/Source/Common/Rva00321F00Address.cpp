// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00321F00
{
public:
	void *address(void);
};

void *Rva00321F00::address(void)
{
	return (char *)this + 0x18;
}
