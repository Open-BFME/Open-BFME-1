// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the unsigned-short formatter at retail RVA 0x009D95A0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
// Retail 0x01144328 is an MSVC pooled string literal ("%i=0x%x [ushort]\n"),
// suffix-shared with its neighbours, not a named global.
static const char kUnsignedShortFormat[] = "%i=0x%x [ushort]\n";

class Gen009D95A0
{
public:
	Gen009D95A0 *bfmeEmit(const unsigned short *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D95A0 *Gen009D95A0::bfmeEmit(const unsigned short *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	unsigned int widened = *value;
	bfmeAppend(this, kUnsignedShortFormat, widened, widened);
	m_pending = false;
	return this;
}
