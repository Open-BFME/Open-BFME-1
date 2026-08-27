// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the integer formatter at retail RVA 0x009D94A0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeIntegerFormat[];
class Gen009D94A0 { public: Gen009D94A0 *bfmeEmit(const int *value); private: unsigned char m_pad[4]; bool m_pending; };
Gen009D94A0 *Gen009D94A0::bfmeEmit(const int *value)
{
	if (!m_pending) bfmeAppend(this, 0);
	int widened = *value;
	bfmeAppend(this, g_bfmeIntegerFormat, widened, widened);
	m_pending = false;
	return this;
}
