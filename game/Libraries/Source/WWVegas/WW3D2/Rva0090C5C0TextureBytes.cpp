// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

#include "ww3dformat.h"
extern unsigned __fastcall Get_Bits_Per_Pixel(WW3DFormat format);
struct Rva0090C5C0Texture
{
	unsigned char m_prefix[0x24];
	unsigned m_width;
	unsigned m_height;
	unsigned char m_between[8];
	unsigned m_surfaceCount;
	unsigned char m_after[4];
	WW3DFormat m_format;
};
class Rva0090C5C0TextureBytes
{
	unsigned char m_prefix[0x14];
	Rva0090C5C0Texture *m_texture;
public:
	unsigned bytes() const;
};
unsigned Rva0090C5C0TextureBytes::bytes() const
{
	Rva0090C5C0Texture *texture = m_texture;
	if (!texture)
		return 0;
	unsigned bytes = Get_Bits_Per_Pixel(texture->m_format) * texture->m_height * texture->m_width;
	bytes >>= 3;
	if (texture->m_surfaceCount != 1)
		bytes += bytes;
	return bytes + 0x48;
}
