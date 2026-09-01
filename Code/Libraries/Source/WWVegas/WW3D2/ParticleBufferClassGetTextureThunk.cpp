// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ParticleBufferClass::Get_Texture, retail 0x00988F60.

class TextureClass;

class ParticleBufferClass
{
public:
	class TextureHandleClass
	{
	public:
		TextureHandleClass( TextureClass *texture ) : m_texture( texture ) {}

	private:
		TextureClass *m_texture;
	};

	class PointGroupShim
	{
	public:
		TextureHandleClass getTexture() const;
	};

	class LineGroupShim
	{
	public:
		TextureHandleClass getTexture() const;
	};

	class LineRendererShim
	{
	public:
		TextureHandleClass getTexture() const;
	};

	TextureHandleClass Get_Texture() const;

private:
	unsigned char m_prefix[ 0x208 ];
	PointGroupShim *m_pointGroup;
	LineRendererShim *m_lineRenderer;
	LineGroupShim *m_lineGroup;
};

// ?Get_Texture@ParticleBufferClass@@QBE?AVTextureHandleClass@1@XZ
ParticleBufferClass::TextureHandleClass ParticleBufferClass::Get_Texture() const
{
	// Retail keeps the empty handle's pointer slot as a stack temporary even
	// though the three successful arms construct directly into the caller's
	// return storage.
	TextureClass *volatile emptyTexture = 0;

	if (m_pointGroup)
		return m_pointGroup->getTexture();
	if (m_lineGroup)
		return m_lineGroup->getTexture();
	if (m_lineRenderer)
		return m_lineRenderer->getTexture();
	return TextureHandleClass( 0 );
}
