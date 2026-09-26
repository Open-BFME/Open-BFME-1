// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims
// Complete retail 0x0072FDF0..0x0072FE8A, including RET4 at +0x97.
// The Ghidra 148-byte inventory stops before the epilogue; the full body is 154.
// Identity: W3DTerrainTracks.cpp init source, matched system resource helper,
// matched track constructor, and W3DTerrainVisual initialization caller.
#include "vertmaterial.h"
#include "shader.h"

class SceneClass;
class TerrainTracksRenderObjClass {
public:
    // The complete matched 169-byte constructor makes no calls and cannot throw.
    TerrainTracksRenderObjClass() throw();
    unsigned char body[0x12fc];
    TerrainTracksRenderObjClass *m_nextSystem, *m_prevSystem;
};
struct GlobalData {
    unsigned char beforeTracks[0x1f0];
    int m_maxTerrainTracks;
};
extern GlobalData *TheGlobalData;
class TerrainTracksRenderObjClassSystem {
public:
    void init(SceneClass *scene);
    void ReAcquireResources();
    void *m_vertexBuffer, *m_indexBuffer;
    VertexMaterialClass *m_vertexMaterialClass;
    ShaderClass m_shaderClass;
    TerrainTracksRenderObjClass *m_usedModules, *m_freeModules;
    SceneClass *m_TerrainTracksScene;
};

void TerrainTracksRenderObjClassSystem::init(SceneClass *scene) {
    const int numModules = TheGlobalData->m_maxTerrainTracks;
    m_TerrainTracksScene = scene;
    ReAcquireResources();
    m_vertexMaterialClass = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    m_shaderClass = ShaderClass::_PresetAlphaShader;
    if (m_freeModules || m_usedModules) return;
    for (int i = 0; i < numModules; ++i) {
        TerrainTracksRenderObjClass *mod = new TerrainTracksRenderObjClass;
        if (!mod) return;
        mod->m_prevSystem = 0;
        mod->m_nextSystem = m_freeModules;
        if (m_freeModules) m_freeModules->m_prevSystem = mod;
        m_freeModules = mod;
    }
}
