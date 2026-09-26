struct Rva8BB1A0Bounds
{
	float left;
	float top;
	float right;
	float bottom;
};

class BfmeN1235
{
public:
	void bfmeDo1235(void *a, void *b);
	void bfmeInitEmpty1235(Rva8BB1A0Bounds *bounds);
};

extern int g_bfmeB1038;

void BfmeN1235::bfmeInitEmpty1235(Rva8BB1A0Bounds *bounds)
{
	unsigned *u = (unsigned *)bounds;
	unsigned neg = 0xCE6E6B28u;
	u[0] = 0x4E6E6B28u;
	u[2] = neg;
	u[3] = neg;
	u[1] = 0x4E6E6B28u;
	void *arg = (void *)g_bfmeB1038;
	bfmeDo1235(arg, bounds);
}
