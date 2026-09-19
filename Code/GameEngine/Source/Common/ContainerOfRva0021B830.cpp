// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0021B830Part
{
public:
	void *owner() const;
};

void *Rva0021B830Part::owner() const
{
	return (char *)this - 0x20;
}
