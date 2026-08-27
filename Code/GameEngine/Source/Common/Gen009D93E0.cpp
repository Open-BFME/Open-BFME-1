// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the signed-byte formatter at retail RVA 0x009D93E0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeSignedByteFormat[];

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
	bfmeAppend(this, g_bfmeSignedByteFormat, widened, widened);
	m_pending = false;
	return this;
}
