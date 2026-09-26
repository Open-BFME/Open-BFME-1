// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the 3D-region formatter at retail RVA 0x009D96B0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeRegion3DFormat[];

struct BfmeRegion3D
{
	float x_min;
	float y_min;
	float z_min;
	float x_max;
	float y_max;
	float z_max;
};

class Gen009D96B0
{
public:
	Gen009D96B0 *bfmeEmit(const BfmeRegion3D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D96B0 *Gen009D96B0::bfmeEmit(const BfmeRegion3D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeRegion3DFormat,
		value->x_min, value->y_min, value->z_min,
		value->x_max, value->y_max, value->z_max);
	m_pending = false;
	return this;
}
