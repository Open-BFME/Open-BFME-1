// cl: /DNDEBUG /MD /EHsc
//
// Clean reconstruction of the two-texture WaterRenderObjClass setting cleanup
// at retail 0x007A03F0.

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

class WaterRenderObjClass
{
public:
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
