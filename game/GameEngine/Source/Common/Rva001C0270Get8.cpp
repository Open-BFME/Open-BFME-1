// cl: /DNDEBUG /MD /O2

class Rva001C0270
{
public:
	void *get(void);
};

void *Rva001C0270::get(void)
{
	return *(char **)this + 8;
}
