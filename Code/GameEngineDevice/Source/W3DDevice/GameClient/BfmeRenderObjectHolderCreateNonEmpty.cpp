// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class RenderObjClass;

RenderObjClass *Create_Render_Obj(const char *name);

class BfmeRenderObjectHolder
{
public:
	RenderObjClass *createNonEmptyRenderObject(AsciiString name);

private:
	unsigned char m_beforeRenderObject[0xc];
	RenderObjClass *m_renderObject;
};

RenderObjClass *BfmeRenderObjectHolder::createNonEmptyRenderObject(AsciiString name)
{
	void *data = *reinterpret_cast<void **>(&name);
	if (data && *reinterpret_cast<unsigned short *>(
		static_cast<unsigned char *>(data) + 4))
	{
		RenderObjClass *renderObject = Create_Render_Obj(
			static_cast<const char *>(data) + 8);
		m_renderObject = renderObject;
		return renderObject;
	}

	return 0;
}
