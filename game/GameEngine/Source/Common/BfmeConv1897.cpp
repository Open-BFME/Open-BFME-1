// Retail 0x000C4280 routes all three of its member calls through ILT thunks:
// the handler lookup goes through 0x0003C8E9 (+0x18), the check through
// 0x00034C93 (+0x39) and the forward through 0x00025EE1 (+0x4C). The only
// names defined at those addresses are the ?j_ thunk symbols (defined in
// game/gen_small/thunks_029.cpp, thunks_025.cpp and thunks_018.cpp), so each
// call is spelled as that thunk's own symbol instead of an invented member.
// The calls stay __thiscall - the receiver travels in ECX - which is the shape
// a pointer-to-member call emits; this is the routing idiom Object.cpp uses
// for the same 0x0003C8E9 thunk.

class BfmeThingAN;
class BfmeHandlerAN;

class BfmeMapAN
{
};

class BfmeThingAN
{
public:
	unsigned char m_bfmeHeadAN[0x264];
	BfmeMapAN m_bfmeMapAN;
};

class BfmeHandlerAN
{
};

struct Rva000C4280Call {};

extern "C" void __identifier("?j_0003c8e9@@YAXXZ")();
extern "C" void __identifier("?j_00034c93@@YAXXZ")();
extern "C" void __identifier("?j_00025ee1@@YAXXZ")();

static __forceinline BfmeHandlerAN *rva000C4280Find(const void *map, void *key)
{
	typedef BfmeHandlerAN *(Rva000C4280Call::*Call)(void *) const;
	union { void (*raw)(); Call member; } route;
	route.raw = __identifier("?j_0003c8e9@@YAXXZ");
	return (reinterpret_cast<Rva000C4280Call *>(const_cast<void *>(map))->*route.member)(key);
}

static __forceinline int rva000C4280Check(const void *obj, int mode, void *b, void *c)
{
	typedef int (Rva000C4280Call::*Call)(int, void *, void *) const;
	union { void (*raw)(); Call member; } route;
	route.raw = __identifier("?j_00034c93@@YAXXZ");
	return (reinterpret_cast<Rva000C4280Call *>(const_cast<void *>(obj))->*route.member)(mode, b, c);
}

static __forceinline char rva000C4280Do(const void *handler, BfmeThingAN *obj, void *b)
{
	typedef char (Rva000C4280Call::*Call)(BfmeThingAN *, void *) const;
	union { void (*raw)(); Call member; } route;
	route.raw = __identifier("?j_00025ee1@@YAXXZ");
	return (reinterpret_cast<Rva000C4280Call *>(const_cast<void *>(handler))->*route.member)(obj, b);
}

char __stdcall bfmeTryAN(BfmeThingAN *obj, void *b, void *c, void *d)
{
	if (obj == 0 || b == 0)
		return 0;

	BfmeHandlerAN *h = rva000C4280Find(&obj->m_bfmeMapAN, d);

	if (h == 0)
		return 0;

	int r = rva000C4280Check(obj, 0, b, c);

	if (r == 3 || r == 2)
		return rva000C4280Do(h, obj, b);

	return 0;
}