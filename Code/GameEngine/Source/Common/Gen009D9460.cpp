// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the scalar byte formatter at retail RVA 0x009D9460.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeScalarByteFormat[];

class Gen009D9460
{
public:
	Gen009D9460 *bfmeEmit(const unsigned char *value);
private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9460 *Gen009D9460::bfmeEmit(const unsigned char *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeScalarByteFormat, static_cast<unsigned int>(*value));
	m_pending = false;
	return this;
}
