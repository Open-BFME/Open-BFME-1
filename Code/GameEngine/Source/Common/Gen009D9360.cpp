// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the byte formatter at retail RVA 0x009D9360.

extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeByteFormat[];

struct BfmeByteValue
{
	unsigned char kind;
	unsigned char value;
};

class Gen009D9360
{
public:
	Gen009D9360 *bfmeEmit(const BfmeByteValue *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9360 *Gen009D9360::bfmeEmit(const BfmeByteValue *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeByteFormat, static_cast<unsigned int>(value->value));
	m_pending = false;
	return this;
}
