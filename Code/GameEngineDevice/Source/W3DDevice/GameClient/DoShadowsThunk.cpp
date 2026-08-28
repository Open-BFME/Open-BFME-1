// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift DoShadows free function to clean C++.

class FrustumClass;

class Vector3
{
	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class CameraClass : public RenderObjClass
{
public:
	const FrustumClass &Get_Frustum() const
	{
		Update_Frustum();
		return *(const FrustumClass *)((const char *)this + 0x104);
	}


protected:
	void Update_Frustum() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rinfo.h
class RenderInfoClass
{
public:
	CameraClass &Camera;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShadow.h
class W3DShadowManager
{
public:
	bool isShadowScene() { return m_isShadowScene; }
	void queueShadows(bool state) { m_isShadowScene = state; }

private:
	bool m_isShadowScene;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadow.h
class W3DProjectedShadowManager
{
public:
	int renderShadows(RenderInfoClass &);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadow.h
class W3DVolumetricShadowManager
{
public:
	void renderShadows(bool);
};

extern const FrustumClass *shadowCameraFrustum;
extern Vector3 ShadowCameraPosition;
extern W3DShadowManager *TheW3DShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;

// ?DoShadows@@YAXAAVRenderInfoClass@@_N@Z
void __cdecl DoShadows(RenderInfoClass &rinfo, bool stencilPass)
{
	shadowCameraFrustum = &rinfo.Camera.Get_Frustum();
	ShadowCameraPosition = rinfo.Camera.Get_Position();

	if (stencilPass == false && TheW3DProjectedShadowManager)
	{
		if (TheW3DShadowManager->isShadowScene())
			TheW3DProjectedShadowManager->renderShadows(rinfo);
	}

	if (stencilPass == true && TheW3DVolumetricShadowManager)
	{
		if (TheW3DShadowManager->isShadowScene())
			TheW3DVolumetricShadowManager->renderShadows(0);
	}

	if (TheW3DShadowManager && stencilPass)
		TheW3DShadowManager->queueShadows(false);
}
