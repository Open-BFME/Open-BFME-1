// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmeheightmap /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#define _STLP_USE_STATIC_LIB       // the retail floor list calls __node_alloc directly
// W3DFloorBuffer (vtable 0x01120360, terrain +0x30A4), retail 0x006F9050: the terrain's reset
// empties the floor list at +0x20, releasing each element's render object and texture.

#include <list>

typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		--m_numRefs;
		if (m_numRefs == 0)
			Delete_This();
	}

private:
	int m_numRefs;
};

// Pinned at 0x009EB7A0: the BFME texture release these buffers call.
class BFMETextureRelease
{
public:
	void Release_Ref();
};

struct BaseHeightMapFloorElement
{
	virtual ~BaseHeightMapFloorElement();
	char m_pad04[0x1c];
	BFMETextureRelease *m_texture;
	RefCountClass *m_renderObject;
	void *m_field28;
	char m_pad2c[0x1c];
	void *m_field48;
	char m_pad4c[0x30];
	bool m_active;
};

struct BaseHeightMapFloorBufferLayout
{
	char m_pad00[0x18];
	Int m_field18;
	char m_pad1c[4];
	_STL::list<void *> m_elements;
	Int m_field24;
};

class W3DFloorBuffer
{
public:
	void rva006F9050();
};

// ?rva006F9050@W3DFloorBuffer@@QAEXXZ
void W3DFloorBuffer::rva006F9050()
{
	BaseHeightMapFloorBufferLayout *buffer =
		reinterpret_cast<BaseHeightMapFloorBufferLayout *>(this);
	for (_STL::list<void *>::iterator it = buffer->m_elements.begin();
		it != buffer->m_elements.end(); ++it) {
		BaseHeightMapFloorElement *element =
			reinterpret_cast<BaseHeightMapFloorElement *>(*it);
		RefCountClass *renderObject = element->m_renderObject;
		element->m_active = false;
		if (renderObject) {
			renderObject->Release_Ref();
			element->m_renderObject = 0;
		}
		BFMETextureRelease *texture = element->m_texture;
		if (texture) {
			texture->Release_Ref();
			element->m_texture = 0;
		}
		element->m_field28 = 0;
		element->m_field48 = 0;
		element = reinterpret_cast<BaseHeightMapFloorElement *>(*it);
		if (element) {
			element->BaseHeightMapFloorElement::~BaseHeightMapFloorElement();
			::operator delete(element);
		}
	}
	buffer->m_elements.clear();
	buffer->m_field18 = 0;
	buffer->m_field24 = 0;
}
