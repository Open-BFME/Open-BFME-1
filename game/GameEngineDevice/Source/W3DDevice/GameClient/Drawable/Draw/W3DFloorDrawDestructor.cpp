// cl: /DNDEBUG /MD /EHsc

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
protected:
	StringInlineData<T> *m_data;

	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class Rva006CCCA0Owner
{
public:
	void loadSchemeVariant( void *rawHandle, AsciiString name );
};

// Retail defines this global in BaseHeightMap.cpp as BaseHeightMapRenderObjClass *.
// The loadSchemeVariant call is reached through the TU-local view above.
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class Rva00759350TailDtor
{
public:
	virtual ~Rva00759350TailDtor();
	virtual void drawModuleAnchor() = 0;
};

class W3DFloorDraw : public Rva00759350TailDtor
{
public:
	virtual ~W3DFloorDraw();

private:
	const void *m_moduleData;
	void *m_drawable;
};

// ??1W3DFloorDraw@@UAE@XZ
W3DFloorDraw::~W3DFloorDraw()
{
	if ( m_moduleData )
	{
		void *drawable = m_drawable;
		if ( drawable )
		{
			reinterpret_cast<Rva006CCCA0Owner *>(TheTerrainRenderObject)->loadSchemeVariant(
				drawable,
				*(const AsciiString *)((const char *)m_moduleData + 8) );
		}
	}
}
