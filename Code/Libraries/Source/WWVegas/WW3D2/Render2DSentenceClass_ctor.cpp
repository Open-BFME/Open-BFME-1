// cl: /DNDEBUG /MD /EHsc
// BFME Render2DSentenceClass constructor at retail 0x00940BF0.

struct TextureStatisticsStructWide;

template<class T>
class VectorClassWide
{
public:
	VectorClassWide(unsigned size, T const *array);
	virtual ~VectorClassWide();
	virtual bool equal(VectorClassWide const &other) const;
	virtual bool resize(int size, T const *array = 0);
	virtual void clear();
	virtual int id(T const *ptr);
	virtual int id(T const &object);

protected:
	T *m_vector;
	int m_vectorMax;
	bool m_valid;
	bool m_allocated;
	bool m_pad[2];
};

template<class T>
class DynamicVectorClassWide : public VectorClassWide<T>
{
public:
	DynamicVectorClassWide(unsigned size = 0, T const *array = 0)
		: VectorClassWide<T>(size, array)
	{
		m_growthStep = 10;
		m_activeCount = 0;
	}

protected:
	int m_activeCount;
	int m_growthStep;
};

template<class T>
class VectorClass
{
public:
	VectorClass(int size, T const *array);
	virtual ~VectorClass();
	virtual bool equal(VectorClass const &other) const;
	virtual bool resize(int size, T const *array = 0);
	virtual void clear();
	virtual int id(T const *ptr);
	virtual int id(T const &object);

protected:
	T *m_vector;
	int m_vectorMax;
	bool m_valid;
	bool m_allocated;
	bool m_pad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(int size = 0, T const *array = 0)
		: VectorClass<T>(size, array)
	{
		m_growthStep = 10;
		m_activeCount = 0;
	}

protected:
	int m_activeCount;
	int m_growthStep;
};

class EnumParameterClass
{
public:
	struct _ENUM_VALUE;
};

struct BfmeItemDC;

class BfmeThingDC
{
public:
	BfmeThingDC(BfmeItemDC *item);

	BfmeItemDC *m_item;
};

class Zero2
{
public:
	Zero2() : m_x(0), m_y(0) {}

	float m_x;
	float m_y;
};

class Zero2i
{
public:
	Zero2i() : m_x(0), m_y(0) {}

	int m_x;
	int m_y;
};

class ShaderValues
{
public:
	ShaderValues() : m_x(1.0f), m_y(1.0f) {}

	float m_x;
	float m_y;
};

class Zero4
{
public:
	Zero4() : m_a(0), m_b(0), m_c(0), m_d(0) {}

	int m_a;
	int m_b;
	int m_c;
	int m_d;
};

class Render2DSentenceClass
{
public:
	struct PendingSurfaceStruct;

	Render2DSentenceClass();
	virtual void Reset();

	DynamicVectorClassWide<TextureStatisticsStructWide> m_sentenceData;
	DynamicVectorClass<PendingSurfaceStruct> m_pendingSurfaces;
	DynamicVectorClass<EnumParameterClass::_ENUM_VALUE> m_renderers;

	void *m_font;
	Zero2 m_baseLocation;
	Zero2 m_location;
	Zero2 m_cursor;
	Zero2i m_textureOffset;
	int m_textureStartX;
	int m_currentTextureSize;
	int m_textureSizeHint;
	BfmeThingDC m_currentSurface;
	unsigned char m_monoSpaced;
	float m_wrapWidth;
	unsigned char m_centered;
	Zero4 m_clipRect;
	Zero4 m_drawExtents;
	unsigned char m_clippingEnabled;
	unsigned char m_parseHotKey;
	unsigned char m_hardWordWrap;
	void *m_lockedPtr;
	int m_lockedStride;
	void *m_currentTexture;
	ShaderValues m_shader;
	Zero2i m_tail;
};

Render2DSentenceClass::Render2DSentenceClass()
	: m_sentenceData(0, 0),
	  m_pendingSurfaces(0, 0),
	  m_renderers(0, 0),
	  m_font(0),
	  m_baseLocation(),
	  m_location(),
	  m_cursor(),
	  m_textureOffset(),
	  m_textureStartX(0),
	  m_currentTextureSize(0),
	  m_textureSizeHint(0),
	  m_currentSurface(0),
	  m_monoSpaced(0),
	  m_wrapWidth(0),
	  m_centered(0),
	  m_clipRect(),
	  m_drawExtents(),
	  m_clippingEnabled(0),
	  m_parseHotKey(0),
	  m_hardWordWrap(0),
	  m_lockedPtr(0),
	  m_lockedStride(0),
	  m_currentTexture(0),
	  m_shader(),
	  m_tail()
{
}
