// cl: /EHs-c-

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Add_Ref() { ++*(unsigned short *)((char *)this + 4); }
	void Release_Ref();
};

struct Rva007AE6E0TextureHandle
{
	TextureBaseClass *m_texture;
};

class Rva007AE6E0TextureOwner
{
public:
	void assign( const Rva007AE6E0TextureHandle &handle );

private:
	unsigned char m_pad0[0x30];
	TextureBaseClass *m_texture;
};

void Rva007AE6E0TextureOwner::assign(
	const Rva007AE6E0TextureHandle &handle )
{
	if ( handle.m_texture != 0 ) {
		handle.m_texture->Add_Ref();
	}
	if ( m_texture != 0 ) {
		m_texture->Release_Ref();
	}
	m_texture = handle.m_texture;
}
