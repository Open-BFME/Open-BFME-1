// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C9B60
{
	char m_pad[0x654];
	void *m_slots[10];

public:
	void *get(int index);
};

void *Rva000C9B60::get(int index)
{
	if (index < 0 || index >= 10)
		return 0;
	return m_slots[index];
}
