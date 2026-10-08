// cl: /O2 /MD
// Retail 0x00C6DBB0 (41 B) is the dynamic initializer of the global BfmeStaticAAO
// g_bfmeStaticAAO (VA 0x0130E918). It constructs the object in place through the
// GeometryInfo five-argument constructor (ILT 0x00037B6E -> 0x00100580) with type 0,
// hollow true and three 2.0f extents, then registers bfmeTeardownAAO (0x00C70E90) with
// atexit. The global is declared the same way in BfmeConv2120.cpp, which defines its
// teardown.

enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };

class GeometryInfo
{
public:
	GeometryInfo(GeometryType, bool, float, float, float);
};

struct BfmeStaticAAO;
extern BfmeStaticAAO g_bfmeStaticAAO;

inline void *operator new(unsigned int, void *place) { return place; }

void bfmeTeardownAAO(void);

void rva00C6DBB0Initialize(void)
{
	new ((void *)&g_bfmeStaticAAO) GeometryInfo(GEOMETRY_SPHERE, true, 2.0f, 2.0f, 2.0f);
	atexit((void (*)(void))bfmeTeardownAAO);
}
