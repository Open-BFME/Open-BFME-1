// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;

typedef bool Bool;

#include "ascii_string.h"

class DrawableModule
{
	protected:
	virtual ~DrawableModule();
};

class DrawableModuleLayoutBase : public DrawableModule
{
	protected:
	virtual ~DrawableModuleLayoutBase() {}

private:
	void *m_moduleData;
	void *m_drawable;
};

class DebrisDrawInterface
{
public:
	virtual void debrisDrawInterfaceAnchor();
};

class RenderObjClass
{
public:
	virtual void deleteThis();

	void releaseRef()
	{
		if (--m_refCount == 0)
			deleteThis();
	}

private:
	int m_refCount;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DScene.h
class RTS3DScene
{
public:
	virtual void sceneSlot0();
	virtual void sceneSlot1();
	virtual void sceneSlot2();
	virtual void Remove_Render_Object(RenderObjClass *object);
};

class Gen0003AC38
{
public:
	void handle(void *object);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;					// 0x012F8058
};


class W3DDebrisDraw : public DrawableModuleLayoutBase,
	public DebrisDrawInterface
{
	protected:
	virtual ~W3DDebrisDraw();

private:
	AsciiString m_modelName;
	int m_modelColor;
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
	RenderObjClass *m_renderObject;
	RenderObjClass *m_anims[3];
	void *m_fxFinal;
	int m_state;
	int m_frames;
	Bool m_finalStop;
	void *m_shadow;
};

// ??1W3DDebrisDraw@@MAE@XZ
W3DDebrisDraw::~W3DDebrisDraw()
{
	register int zero = 0;
	if ((void *)((Gen0003AC38 *&)TheW3DShadowManager) != (void *)zero)
	{
		void *shadow = m_shadow;
		if (shadow != (void *)zero)
		{
			((Gen0003AC38 *&)TheW3DShadowManager)->handle(shadow);
			*(volatile int *)&m_shadow = zero;
		}
	}
	RenderObjClass *renderObject = m_renderObject;
	if (renderObject != (RenderObjClass *)zero)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(renderObject);
		if (m_renderObject != (RenderObjClass *)zero)
		{
			m_renderObject->releaseRef();
			*(volatile int *)&m_renderObject = zero;
		}
		*(volatile int *)&m_renderObject = zero;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (m_anims[i] != (RenderObjClass *)zero)
		{
			m_anims[i]->releaseRef();
			*(volatile int *)&m_anims[i] = zero;
		}
		*(volatile int *)&m_anims[i] = zero;
	}
}
