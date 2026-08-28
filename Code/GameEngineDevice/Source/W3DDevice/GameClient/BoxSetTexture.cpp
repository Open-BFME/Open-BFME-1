// cl: /DNDEBUG /MD /EHsc

// BoxSetTexture, retail 0x00905AC0. A reference-counted slot assignment with
// the usual add-then-release order, so assigning a texture to itself is safe -
// though retail does not even get that far, since the whole body is inside a
// test that the slot is changing.
//
// The slots are the array at 0x01340EC8 and the dirty mask is the dword at
// 0x0133F49C, which takes bit 6 upwards - 0x40 shifted by the index.
//
// Add_Ref is inlined to a word increment at +0x04 of the texture; Release_Ref
// is a call, and the ledger already names it.

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref( void );

	unsigned char m_unmodelled_00[4];
	unsigned short m_refCount;				// +0x04
};

extern TextureBaseClass *TheBoxTextures[];	// 0x01340EC8
extern UnsignedInt TheBoxTextureDirtyMask;	// 0x0133F49C

// ?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z
void BoxSetTexture( UnsignedInt index, TextureBaseClass *&tex )
{
	if( tex != TheBoxTextures[ index ] )
	{
		if( tex )
			++tex->m_refCount;

		if( TheBoxTextures[ index ] )
			TheBoxTextures[ index ]->Release_Ref();

		TheBoxTextures[ index ] = tex;

		TheBoxTextureDirtyMask |= 0x40 << index;
	}
}
