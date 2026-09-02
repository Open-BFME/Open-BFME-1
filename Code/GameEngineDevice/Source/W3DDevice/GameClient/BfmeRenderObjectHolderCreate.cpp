// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class RenderObjClass;

RenderObjClass *Create_Render_Obj(const char *name);

class BfmeRenderObjectHolder
{
public:
	RenderObjClass *createRenderObject(AsciiString name);

private:
	unsigned char m_beforeRenderObject[8];
	RenderObjClass *m_renderObject;
};

RenderObjClass *BfmeRenderObjectHolder::createRenderObject(AsciiString name)
{
	RenderObjClass *renderObject = Create_Render_Obj(name.str());
	m_renderObject = renderObject;
	return renderObject;
}
