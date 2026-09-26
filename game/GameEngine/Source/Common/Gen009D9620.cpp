// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the 3D-coordinate formatter at retail RVA 0x009D9620.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeCoord3DFormat[];

struct BfmeCoord3D
{
	float x;
	float y;
	float z;
};

class Gen009D9620
{
public:
	Gen009D9620 *bfmeEmit(const BfmeCoord3D *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9620 *Gen009D9620::bfmeEmit(const BfmeCoord3D *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeCoord3DFormat, value->x, value->y, value->z);
	m_pending = false;
	return this;
}
