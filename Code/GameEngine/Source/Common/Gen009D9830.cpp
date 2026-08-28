// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the integer 2D-region formatter at retail RVA 0x009D9830.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeIRegion2DFormat[];

struct BfmeIRegion2D
{
	int x_min;
	int y_min;
	int x_max;
	int y_max;
};

class Gen009D9830
{
public:
	Gen009D9830 *bfmeEmit(const BfmeIRegion2D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9830 *Gen009D9830::bfmeEmit(const BfmeIRegion2D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeIRegion2DFormat,
		value->x_min, value->y_min, value->x_max, value->y_max);
	m_pending = false;
	return this;
}
