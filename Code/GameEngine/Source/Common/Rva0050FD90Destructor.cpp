// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1W3DDisplayString (0x006F4C50, W3DDisplayString.cpp);
// same single-vtable shape, but this body reports through the shared action sink
// g_mgr12F19E8 (same global as the 0x00470360 neighbour) before zeroing a
// separate global and chaining to the already-landed base destructor
// Gen_dtor_004654c0.

class GenActionSink
{
public:
	void add(void *a, const char *b, int c, const char *d, int e, int f, int g, int h);
};

extern GenActionSink *g_mgr12F19E8;
extern int g_glob12F496C;

class Gen_dtor_004654c0
{
public:
	virtual ~Gen_dtor_004654c0();
};

class Rva0050FD90 : public Gen_dtor_004654c0
{
public:
	virtual ~Rva0050FD90();
};

// ?d_0050fd90@@YAXXZ
Rva0050FD90::~Rva0050FD90()
{
	g_mgr12F19E8->add((void *)0xb, (const char *)0x1104fdc, 0, 0, 0, 0, 0, 0);
	g_glob12F496C = 0;
}
