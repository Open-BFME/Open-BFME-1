// cl: /DNDEBUG /MD /EHsc
//
// Clean reconstruction of the two-texture WaterRenderObjClass setting cleanup
// at retail 0x007A03F0.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureRef
{
public:
	~TextureRef()
	{
		if (texture != 0)
			texture->Release_Ref();
	}

private:
	TextureClass *texture;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
	struct Setting
	{
		Setting();
		~Setting();

		TextureRef skyTexture;
		TextureRef waterTexture;
	};
};

WaterRenderObjClass::Setting::~Setting()
{
}
