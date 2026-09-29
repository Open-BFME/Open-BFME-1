// cl: /O2 /Ob0

extern void *g_012B85D0[];

class Rva005A45D0
{
public:
	void *get(int index);
};

void *Rva005A45D0::get(int index)
{
	if (index < 0 || index >= 50)
		return (void *)"???";
	return g_012B85D0[index];
}
