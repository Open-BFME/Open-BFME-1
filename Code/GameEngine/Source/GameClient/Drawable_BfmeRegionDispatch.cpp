// BFME Drawable region-renderer dispatch at retail 0x0041AA00.

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf( KindOfType kind ) const;
};

extern void bfmeRegionRenderA( void *region, int first, int second );
extern void bfmeRegionRenderB( void *region, int first, int second );
extern void bfmeRegionRenderC( void *region, int first, int second );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
private:
	unsigned char m_bfmePrefix[ 0xFC ];
	Thing *m_object;
	unsigned char m_bfmeBetween[ 0x2C0 ];

public:
	void bfmeRegionDispatch( int first, int second );
};

void Drawable::bfmeRegionDispatch( int first, int second )
{
	Thing *object = m_object;
	if( object == 0 )
		return;

	if( (*(unsigned char *)((unsigned char *)object + 0x90) & 4) != 0 )
	{
		bfmeRegionRenderA( (unsigned char *)this + 0x3C4, first, second );
		return;
	}

	if( object->isKindOf( KINDOF_STRUCTURE ) )
	{
		bfmeRegionRenderB( (unsigned char *)this + 0x3C4, first, second );
		return;
	}

	bfmeRegionRenderC( (unsigned char *)this + 0x3C4, first, second );
}
