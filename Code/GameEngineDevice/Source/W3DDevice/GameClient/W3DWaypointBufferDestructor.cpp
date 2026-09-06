// cl: /DNDEBUG /MD /EHsc
// readable body of ??1W3DWaypointBuffer@@QAE@XZ

typedef int Int;

class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	Int NumRefs;
};

class RenderObjClass : public RefCountClass {};
class SegmentedLineClass : public RefCountClass {};

class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureRef
{
public:
	TextureRef() : m_ptr(0) {}
	~TextureRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	TextureClass *m_ptr;
};

class W3DWaypointBuffer
{
public:
	~W3DWaypointBuffer();

private:
	RenderObjClass *m_waypointNodeRobj;
	SegmentedLineClass *m_line;
	TextureRef m_texture;
};

W3DWaypointBuffer::~W3DWaypointBuffer()
{
	if (m_waypointNodeRobj)
	{
		m_waypointNodeRobj->Release_Ref();
		m_waypointNodeRobj = 0;
	}
	if (m_line)
	{
		m_line->Release_Ref();
		m_line = 0;
	}
}
