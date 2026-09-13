// readable body of ?renderTrees@BaseHeightMapRenderObjClass@@QAEXPAVCameraClass@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class CameraClass
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
    void renderTrees(CameraClass *);
};

class BaseHeightMapRenderTreesShim
{
public:
    void render(CameraClass *camera);
};

void BaseHeightMapRenderObjClass::renderTrees(CameraClass *camera)
{
    ((BaseHeightMapRenderTreesShim *)this)->render(camera);
}
