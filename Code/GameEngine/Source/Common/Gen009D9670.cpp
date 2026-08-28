// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the integer 3D-coordinate formatter at retail RVA 0x009D9670.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeICoord3DFormat[];

struct BfmeICoord3D
{
	int x;
	int y;
	int z;
};

class Gen009D9670
{
public:
	Gen009D9670 *bfmeEmit(const BfmeICoord3D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9670 *Gen009D9670::bfmeEmit(const BfmeICoord3D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeICoord3DFormat, value->x, value->y, value->z);
	m_pending = false;
	return this;
}
