// cl: /O2 /Ob0

class Rva00087BD0
{
	char pad[0xE0];
	char *m_arr[1];

public:
	void *get(int i);
};

void *Rva00087BD0::get(int i)
{
	if (m_arr[i])
		return m_arr[i] + 4;
	return 0;
}
