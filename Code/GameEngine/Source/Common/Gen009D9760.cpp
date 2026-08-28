// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the 2D-coordinate formatter at retail RVA 0x009D9760.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeCoord2DFormat[];

struct BfmeCoord2D
{
	float x;
	float y;
};

class Gen009D9760
{
public:
	Gen009D9760 *bfmeEmit(const BfmeCoord2D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9760 *Gen009D9760::bfmeEmit(const BfmeCoord2D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeCoord2DFormat, value->x, value->y);
	m_pending = false;
	return this;
}
