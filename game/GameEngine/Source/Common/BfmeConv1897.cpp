class BfmeThingAN;
class BfmeHandlerAN;

class BfmeMapAN
{
public:
	BfmeHandlerAN *bfmeFindAN(void *key);
};

class BfmeThingAN
{
public:
	int bfmeCheckAN(int mode, void *b, void *c);

	unsigned char m_bfmeHeadAN[0x264];
	BfmeMapAN m_bfmeMapAN;
};

class BfmeHandlerAN
{
public:
	char bfmeDoAN(BfmeThingAN *obj, void *b);
};

char __stdcall bfmeTryAN(BfmeThingAN *obj, void *b, void *c, void *d)
{
	if (obj == 0 || b == 0)
		return 0;

	BfmeHandlerAN *h = obj->m_bfmeMapAN.bfmeFindAN(d);

	if (h == 0)
		return 0;

	int r = obj->bfmeCheckAN(0, b, c);

	if (r == 3 || r == 2)
		return h->bfmeDoAN(obj, b);

	return 0;
}
