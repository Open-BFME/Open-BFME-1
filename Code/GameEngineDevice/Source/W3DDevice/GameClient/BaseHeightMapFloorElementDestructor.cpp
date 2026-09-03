// cl: /DNDEBUG /MD /EHsc
//
// BaseHeightMap's floor-buffer element destructor, retail 0x006F8290.
// The element is referenced by BaseHeightMap::clear30A4; its anonymous class
// name remains the generated name carried by that call site.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureRef
{
public:
	TextureBaseClass *m_ptr;
	~TextureRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		--m_refs;
		if (m_refs == 0)
			Delete_This();
	}

	int m_refs;
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase();
	StringBase(const StringBase<T> &other);
	~StringBase();
	int *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	~AsciiString() {}
};

class __declspec(novtable) Gen_dtor_006f8910
{
public:
	virtual ~Gen_dtor_006f8910();

private:
	unsigned char m_pad04[0x1c];
	TextureRef m_texture;
	RefCountClass *m_renderObject;
	void *m_field28;
	unsigned char m_pad2c[0x1c];
	void *m_field48;
	unsigned char m_pad4c[0x30];
	bool m_active;
	unsigned char m_pad7d[0xb];
	AsciiString m_name;
};

// ??1Gen_dtor_006f8910@@UAE@XZ
Gen_dtor_006f8910::~Gen_dtor_006f8910()
{
	m_active = false;
	if (m_renderObject)
	{
		m_renderObject->Release_Ref();
		m_renderObject = 0;
	}
	if (m_texture.m_ptr)
	{
		m_texture.m_ptr->Release_Ref();
		m_texture.m_ptr = 0;
	}
	m_field28 = 0;
	m_field48 = 0;
}
