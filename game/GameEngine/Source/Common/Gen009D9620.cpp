// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the 3D-coordinate formatter at retail RVA 0x009D9620.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
// The format is retail's pooled .rdata literal at 0x01144348, passed inline.

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
	bfmeAppend(this, "x:%1.6f,y:%1.6f,z:%1.6f [coord3d]\n", value->x, value->y, value->z);
	m_pending = false;
	return this;
}
