// cl: /Od
// A run named by its start passed on as a pair of ends, the length coming from
// the worker below, built without optimisation. Both callees are pinned by
// address; nothing here names them.

int bfmeMakeOX(void *one);

class BfmeThingPL
{
public:
	void bfmeGoPL(char *at);

	void bfmeAssignPL(char *first, char *last);
};

void BfmeThingPL::bfmeGoPL(char *at)
{
	unsigned char spare[0x68];

	bfmeAssignPL(at, at + bfmeMakeOX(at));
}
