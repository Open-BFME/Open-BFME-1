// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the real RGBA-color formatter at retail RVA 0x009D9900.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);

struct BfmeRGBAColorReal
{
	float r;
	float g;
	float b;
	float a;
};

class Gen009D9900
{
public:
	Gen009D9900 *bfmeEmit(const BfmeRGBAColorReal *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9900 *Gen009D9900::bfmeEmit(const BfmeRGBAColorReal *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, "r:%1.3f,g:%1.3f,b:%1.3f,a:%1.3f [rgba]\n",
		value->r, value->g, value->b, value->a);
	m_pending = false;
	return this;
}
