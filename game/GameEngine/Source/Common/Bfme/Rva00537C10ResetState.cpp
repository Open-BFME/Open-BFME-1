// cl: /DNDEBUG /MD /EHsc

class Rva00537C10
{
	unsigned char padding[0x1b4];
	unsigned char active;
	unsigned char gap[7];
	int state;

public:
	void reset();
};

void Rva00537C10::reset()
{
	active = 1;
	state = -1;
}
