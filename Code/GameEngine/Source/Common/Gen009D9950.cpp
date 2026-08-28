// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the integer RGBA-color formatter at retail RVA 0x009D9950.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeRGBAColorIntFormat[];

struct BfmeRGBAColorInt
{
	int r;
	int g;
	int b;
	int a;
};

class Gen009D9950
{
public:
	Gen009D9950 *bfmeEmit(const BfmeRGBAColorInt *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9950 *Gen009D9950::bfmeEmit(const BfmeRGBAColorInt *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeRGBAColorIntFormat,
		value->r, value->g, value->b, value->a);
	m_pending = false;
	return this;
}
