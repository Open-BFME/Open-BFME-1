// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// BFME's bridge allocation uses a 0x20 vertex-buffer object.  The shared
// WW3D declaration is the 0x1c Zero Hour view, so keep the retail tail local
// to this TU while retaining the real constructor and base layout.
#define DX8VertexBufferClass ZH_DX8VertexBufferClass
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#undef DX8VertexBufferClass

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class DX8VertexBufferClass : public ZH_DX8VertexBufferClass {
public:
    enum UsageType { USAGE_DEFAULT=0, USAGE_DYNAMIC=1, USAGE_SOFTWAREPROCESSING=2, USAGE_NPATCHES=4 };
    DX8VertexBufferClass(unsigned FVF, unsigned short VertexCount, UsageType usage=USAGE_DEFAULT, unsigned vertex_size=0);
    unsigned bfme_tail;
};

void W3DBridgeBuffer::allocateBridgeBuffers(void)
{
    if (m_vertexBridge || m_indexBridge) {
        if (m_vertexBridge) {
            m_vertexBridge->Release_Ref();
            *(volatile ZH_DX8VertexBufferClass **)&m_vertexBridge = NULL;
        }
        if (m_indexBridge) {
            m_indexBridge->Release_Ref();
            *(volatile DX8IndexBufferClass **)&m_indexBridge = NULL;
        }
        if (m_vertexMaterial) {
            m_vertexMaterial->Release_Ref();
            *(volatile VertexMaterialClass **)&m_vertexMaterial = NULL;
        }
    }
    m_vertexBridge=::new DX8VertexBufferClass(DX8_FVF_XYZNDUV1,8004,DX8VertexBufferClass::USAGE_DYNAMIC);
    m_indexBridge=::new DX8IndexBufferClass(16004, DX8IndexBufferClass::USAGE_DYNAMIC);
    m_vertexMaterial=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    m_curNumBridgeVertices=0;
    m_curNumBridgeIndices=0;
}
