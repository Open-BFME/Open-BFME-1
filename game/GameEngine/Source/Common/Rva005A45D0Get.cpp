// cl: /O2 /Ob0

// Retail 0x012B85D0, defined with getCursorIndex in Mouse.cpp.
extern char *g_012B85D0[];

class Rva005A45D0
{
public:
	void *get(int index);
};

void *Rva005A45D0::get(int index)
{
	if (index < 0 || index >= 50)
		return (void *)"???";
	return (void *)g_012B85D0[index];
}
