// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the integer 3D-region formatter at retail RVA 0x009D9710.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeIRegion3DFormat[];

struct BfmeIRegion3D
{
	int x_min;
	int y_min;
	int z_min;
	int x_max;
	int y_max;
	int z_max;
};

class Gen009D9710
{
public:
	Gen009D9710 *bfmeEmit(const BfmeIRegion3D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9710 *Gen009D9710::bfmeEmit(const BfmeIRegion3D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeIRegion3DFormat,
		value->x_min, value->y_min, value->z_min,
		value->x_max, value->y_max, value->z_max);
	m_pending = false;
	return this;
}
