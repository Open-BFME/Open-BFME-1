// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the 64-bit integer formatter at retail RVA 0x009D94E0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);

class Gen009D94E0
{
public:
	Gen009D94E0 *bfmeEmit(const __int64 *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D94E0 *Gen009D94E0::bfmeEmit(const __int64 *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, "%I64i=0x%I64x [int64]\n", *value, *value);
	m_pending = false;
	return this;
}
