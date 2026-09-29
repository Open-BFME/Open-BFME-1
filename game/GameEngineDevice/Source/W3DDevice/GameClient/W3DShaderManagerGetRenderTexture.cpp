// The readable W3DShaderManager donor defines this accessor immediately after
// endRenderToTexture.  Keep its one-pointer render-texture storage explicit in
// this small TU so the recovered body has the real manager identity rather than
// inheriting the address-derived global getter name.

struct IDirect3DTexture8;

class W3DShaderManager
{
public:
	// Retail 0x012F9D08: ?m_renderTexture@W3DShaderManager@@1PAUIDirect3DTexture8@@A
	static IDirect3DTexture8 *m_renderTexture;
	static IDirect3DTexture8 *getRenderTexture(void);
};

IDirect3DTexture8 *W3DShaderManager::getRenderTexture(void)
{
	return m_renderTexture;
}
