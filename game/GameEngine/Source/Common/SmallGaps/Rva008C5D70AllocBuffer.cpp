// ?allocBuffer@Rva008C5D70Owner@@QAEXHH@Z
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
extern void* (__cdecl* Rva008C5D70Alloc)(unsigned int bytes);
struct Rva008C5D70Owner {
	int m_0;
	int m_width;
	int m_height;
	void* m_pixels;
	void allocBuffer(int width, int height);
};
void Rva008C5D70Owner::allocBuffer(int width, int height)
{
	m_width = width;
	m_height = height;
	m_pixels = Rva008C5D70Alloc(width * height * 4);
	memset(m_pixels, 0, m_height * m_width * 4);
}
