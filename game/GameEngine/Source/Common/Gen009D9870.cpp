// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the real-range formatter at retail RVA 0x009D9870.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);

struct BfmeRealRange
{
	float lo;
	float hi;
};

class Gen009D9870
{
public:
	Gen009D9870 *bfmeEmit(const BfmeRealRange *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9870 *Gen009D9870::bfmeEmit(const BfmeRealRange *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, "%1.6f to %1.6f [range]\n", value->lo, value->hi);
	m_pending = false;
	return this;
}
