// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DStreakDraw constructor at retail 0x0077D930.
// The BFME streak module is a small DrawModule wrapper around a water-track
// render object; the local layouts keep the converted body independent of the
// still-unmatched implementation headers.

typedef int Int;
typedef char Char;
typedef bool Bool;

class Thing;
class ModuleData;

class DrawModule
{
public:
	DrawModule( Thing *, const ModuleData * );
	virtual ~DrawModule();
	virtual void drawModuleAnchor();

protected:
	const ModuleData * volatile m_moduleData;
	void *m_drawable;
};

class AsciiString
{
public:
	Char *m_data;

	Char *str( void ) const
	{
		if (m_data)
			return m_data + 8;
		return (Char *)0x0107388b;
	}
};

class W3DStreakDrawModuleDataBase
{
public:
	virtual void moduleDataAnchor();

private:
	Char m_pad04[ 4 ];
};

class W3DStreakDrawModuleData : public W3DStreakDrawModuleDataBase
{
public:
	Int m_at08;
	Int m_at0c;
	float m_at10;
	float m_at14;
	float m_at18;
	Int m_at1c;
	AsciiString m_textureName;
};

class TextureClass;

class BFMEWaterTrackTexture
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	BFMEWaterTrackTextureHandle()
		: m_texture( 0 )
	{
	}

	BFMEWaterTrackTextureHandle(
		const BFMEWaterTrackTextureHandle &source)
		: m_texture(source.m_texture)
	{
	}

	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

class BFMETextureRef
{
public:
	TextureClass *m_texture;

	BFMETextureRef()
		: m_texture( 0 )
	{
	}

	BFMETextureRef( const BFMETextureRef &source )
		: m_texture( source.m_texture )
	{
	}

	~BFMETextureRef()
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((Char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

struct BfmeStreakVector
{
	float x;
	float y;
	float z;
};

class ShaderClass
{
public:
	Int m_bits;

	ShaderClass( const ShaderClass &source )
		: m_bits( source.m_bits )
	{
	}

	static ShaderClass _PresetAdditiveShader;
};

class BfmeStreakVtableBase
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
};

class BfmeStreakObject : public BfmeStreakVtableBase
{
public:
	BfmeStreakObject();
	void setTexture( TextureClass *const &texture );
	void setShader( ShaderClass value );
	void setReal( Int value );
	void setVector( const BfmeStreakVector *value );
	void setInt( Int value );
	virtual void apply( Int value );

private:
	Char m_storage[ 0x108 ];
};

class BfmeGlobPB
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void configure( BfmeStreakObject *object );
};

extern BfmeGlobPB *g_bfmeGlobPB;
extern Int g_bfmeStreakDefault;

class W3DStreakDraw : public DrawModule
{
public:
	W3DStreakDraw( Thing *, const ModuleData * );
	const W3DStreakDrawModuleData *getData( void ) const
	{
		return (const W3DStreakDrawModuleData *)m_moduleData;
	}

private:
	BfmeStreakObject *m_streak;
	BFMETextureRef m_texture;
};

// ??0W3DStreakDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DStreakDraw::W3DStreakDraw( Thing *thing, const ModuleData *moduleData )
	: DrawModule( thing, moduleData ), m_texture()
{
	const W3DStreakDrawModuleData *data;
	m_streak = 0;
	data = getData();

	BFMEAssignWaterTrackTexture(
		m_texture.m_texture,
		BFMEGetWaterTrackTexture(
			data->m_textureName.str(), 0, 0));

	m_streak = new BfmeStreakObject();
	if (m_streak)
	{
		m_streak->setTexture( m_texture.m_texture );
		m_streak->setShader( ShaderClass::_PresetAdditiveShader );
		m_streak->setReal( data->m_at0c );
		BfmeStreakVector vector;
		vector.x = data->m_at10;
		vector.y = data->m_at14;
		vector.z = data->m_at18;
		m_streak->setVector( &vector );
		m_streak->setInt( data->m_at08 );
		g_bfmeGlobPB->configure( m_streak );
		m_streak->apply( 1 );
	}
}
