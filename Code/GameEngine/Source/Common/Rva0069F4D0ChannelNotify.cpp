// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Notify channel at this+0xB8+index*0x1C4; if index==2 also walk all three.

class Rva0069F4D0Block
{
public:
	void notify(void *arg, int which);
};

class Rva0069F4D0Owner
{
public:
	void notify(void *arg, int index);
};

void Rva0069F4D0Owner::notify(void *arg, int index)
{
	void *held = arg;
	int idx = index;
	Rva0069F4D0Owner *self = this;
	((Rva0069F4D0Block *)((char *)self + 0xB8 + idx * 0x1C4))->notify(held, idx);
	if (idx == 2)
	{
		int i = 0;
		char *block = (char *)self;
		block += 0xB8;
		while (i < 3)
		{
			if (i != 2)
				((Rva0069F4D0Block *)block)->notify(held, 2);
			++i;
			block += 0x1C4;
		}
	}
}
