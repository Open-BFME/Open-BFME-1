// cl: /Od
// A run named by its start and length passed on as a pair of ends, built
// without optimisation. The frame holds something this body never names.

class BfmeThingOT
{
public:
	void bfmeSetOT(char *at, int many);

	void bfmeAssignOT(char *first, char *last);
};

void BfmeThingOT::bfmeSetOT(char *at, int many)
{
	unsigned char spare[0x68];

	bfmeAssignOT(at, at + many);
}
