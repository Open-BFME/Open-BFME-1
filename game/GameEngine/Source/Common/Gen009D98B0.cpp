// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the RGB-color formatter at retail RVA 0x009D98B0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeRGBColorFormat[];

struct BfmeRGBColor
{
	float r;
	float g;
	float b;
};

class Gen009D98B0
{
public:
	Gen009D98B0 *bfmeEmit(const BfmeRGBColor *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D98B0 *Gen009D98B0::bfmeEmit(const BfmeRGBColor *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeRGBColorFormat, value->r, value->g, value->b);
	m_pending = false;
	return this;
}
