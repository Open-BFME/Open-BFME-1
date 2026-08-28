// readable body of ?loadBridgesInVertexAndIndexBuffers@W3DBridgeBuffer@@IAEXPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
class RenderObjClass
{
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class RefMultiListIterator
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
class W3DBridgeBuffer
{
protected:
	void loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *);
};

class W3DBridgeBufferLoadBridgesShim
{
public:
	void loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *);
};

void W3DBridgeBuffer::loadBridgesInVertexAndIndexBuffers(RefMultiListIterator<RenderObjClass> *iterator)
{
	((W3DBridgeBufferLoadBridgesShim *)this)->loadBridgesInVertexAndIndexBuffers(iterator);
}
