// cl: /O2 /Ob0

class Rva005A45D0
{
public:
	void *get(int index);
};

void *Rva005A45D0::get(int index)
{
	if (index < 0 || index >= 50)
		return (void *)0x010E8AD0;
	return ((void **)0x012B85D0)[index];
}
