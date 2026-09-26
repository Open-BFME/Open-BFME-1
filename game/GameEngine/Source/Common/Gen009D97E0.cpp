// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the 2D-region formatter at retail RVA 0x009D97E0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeRegion2DFormat[];

struct BfmeRegion2D
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class Gen009D97E0
{
public:
	Gen009D97E0 *bfmeEmit(const BfmeRegion2D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D97E0 *Gen009D97E0::bfmeEmit(const BfmeRegion2D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeRegion2DFormat,
		value->x_min, value->y_min, value->x_max, value->y_max);
	m_pending = false;
	return this;
}
