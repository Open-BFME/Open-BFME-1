// cl: /DNDEBUG /MD /EHsc

// BFME keeps a larger DrawableModule layout than the reference headers expose.
// This translation unit declares only the fields and virtual slots that this
// destructor uses.

class RenderObjClass
{
public:
	virtual void Delete_This();

	void Release_Ref() const
	{
		--m_refCount;
		if (m_refCount == 0)
			const_cast<RenderObjClass *>(this)->Delete_This();
	}

private:
	mutable int m_refCount;
};

class Shadow;

class W3DShadowManager
{
public:
	void removeShadow(Shadow *shadow);
};

class SceneClass
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void Remove_Render_Object(RenderObjClass *renderObject);
};

extern W3DShadowManager *TheW3DShadowManager;

class W3DDisplay
{
public:
	static SceneClass *m_3DScene;
};

class DrawableModule
{
	protected:
	virtual ~DrawableModule();
};

class DrawModule : public DrawableModule
{
public:
	virtual ~DrawModule() {}

private:
	char m_padding[8];
};

class W3DDefaultDraw : public DrawModule
{
protected:
	virtual ~W3DDefaultDraw();

private:
	RenderObjClass *m_renderObject;
	Shadow *m_shadow;
};

W3DDefaultDraw::~W3DDefaultDraw()
{
	register int zero = 0;
	if (TheW3DShadowManager != (W3DShadowManager *)zero)
	{
		if (m_shadow != (Shadow *)zero)
		{
			TheW3DShadowManager->removeShadow(m_shadow);
			m_shadow = (Shadow *)zero;
		}
	}
	if (m_renderObject != (RenderObjClass *)zero)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(m_renderObject);
		if (m_renderObject != (RenderObjClass *)zero)
		{
			m_renderObject->Release_Ref();
			*(volatile int *)&m_renderObject = zero;
		}
		*(volatile int *)&m_renderObject = zero;
	}
}
