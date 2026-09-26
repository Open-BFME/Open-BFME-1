// The readable W3DShaderManager donor defines this accessor immediately after
// endRenderToTexture.  Keep its one-pointer render-texture storage explicit in
// this small TU so the recovered body has the real manager identity rather than
// inheriting the address-derived global getter name.

struct IDirect3DTexture8;

#define BFME_RENDER_TEXTURE (*(IDirect3DTexture8 **)0x012F9D08)

class W3DShaderManager
{
public:
	static IDirect3DTexture8 *getRenderTexture(void);
};

IDirect3DTexture8 *W3DShaderManager::getRenderTexture(void)
{
	return BFME_RENDER_TEXTURE;
}
