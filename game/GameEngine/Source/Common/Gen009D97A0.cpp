// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the integer 2D-coordinate formatter at retail RVA 0x009D97A0.
// Retail 0x01144414 is this literal itself ("x:%i,y:%i [icoord2d]\n"), not a global:
// the pool entry is what the push names.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);

struct BfmeICoord2D
{
	int x;
	int y;
};

class Gen009D97A0
{
public:
	Gen009D97A0 *bfmeEmit(const BfmeICoord2D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D97A0 *Gen009D97A0::bfmeEmit(const BfmeICoord2D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, "x:%i,y:%i [icoord2d]\n", value->x, value->y);
	m_pending = false;
	return this;
}
