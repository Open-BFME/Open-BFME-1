// cl: /O2 /Ob0

class Rva00694B40
{
public:
	int *get(int *p);
};

int *Rva00694B40::get(int *p)
{
	if (!p)
		return p;
	return (int *)p[2];
}
