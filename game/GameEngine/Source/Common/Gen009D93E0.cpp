// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the signed-byte formatter at retail RVA 0x009D93E0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
// Retail 0x011442AC is an MSVC pooled string literal ("%i=0x%x [byte]\n"),
// suffix-shared with its neighbours, not a named global.
static const char kSignedByteFormat[] = "%i=0x%x [byte]\n";

class Gen009D93E0
{
public:
	Gen009D93E0 *bfmeEmit(const signed char *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D93E0 *Gen009D93E0::bfmeEmit(const signed char *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	int widened = *value;
	bfmeAppend(this, kSignedByteFormat, widened, widened);
	m_pending = false;
	return this;
}
