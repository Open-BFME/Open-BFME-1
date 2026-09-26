// ?d_006da2d0@@YAXXZ
// partial score=0.05 date=2026-09-26
// Partial reconstruction for retail RVA 0x006DA2D0.
// Best measured shape: inline render-state updates with temporary StringClass locals.
// Owner: W3DBridgeBuffer.cpp; replace its drawBridges and add the include prelude below to measure.
#define private public
#define protected public
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#include "WW3D2/DX8Wrapper.h"
#undef protected
#undef private

void W3DBridgeBuffer::drawBridges(CameraClass * camera, Bool wireframe, TextureClass *cloudTexture)
{
	Int curBridge;
	if (TheTerrainLogic) {
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			m_bridges[curBridge].setEnabled(false);
		}
		Bool changed = false;
		for (Bridge *bridge = TheTerrainLogic->getFirstBridge(); bridge; bridge = bridge->getNext()) {
			BridgeInfo info;
			bridge->getBridgeInfo(&info);
			if (info.bridgeIndex<0 || info.bridgeIndex>=m_numBridges) {
				continue;
			}
			m_bridges[info.bridgeIndex].setEnabled(true);
			if (m_bridges[info.bridgeIndex].getDamageState() != info.curDamageState) {
				changed = true;
				enum BodyDamageType curState = m_bridges[info.bridgeIndex].getDamageState();
				m_bridges[info.bridgeIndex].setDamageState(info.curDamageState);
				if (!m_bridges[info.bridgeIndex].load(info.curDamageState)) {
					m_bridges[info.bridgeIndex].load(curState);
					m_bridges[info.bridgeIndex].setDamageState(info.curDamageState);
				}
			}
		}
		if (changed) {
			loadBridgesInVertexAndIndexBuffers(NULL);
		}
	} else {
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			m_bridges[curBridge].setEnabled(true);
		}
	}

	if (m_curNumBridgeIndices == 0) {
		return;
	}

	DX8Wrapper::Set_Material(m_vertexMaterial);
	DX8Wrapper::Set_Index_Buffer(m_indexBridge,0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBridge);
	if (ShaderClass::ShaderDirty || ((unsigned&)detailAlphaShader != (unsigned&)DX8Wrapper::render_state.shader)) {
		DX8Wrapper::render_state.shader = detailAlphaShader;
		DX8Wrapper::render_state_changed |= 0x8000;
		StringClass str;
	}
	DX8Wrapper::Apply_Render_State_Changes();

	if (!wireframe && cloudTexture) {
		W3DShaderManager::setTexture(1,cloudTexture);
		W3DShaderManager::setShader(W3DShaderManager::ST_CLOUD_TEXTURE,1);
	}

	for (curBridge=0; curBridge<m_numBridges; curBridge++) {
		if (m_bridges[curBridge].isEnabled() && m_bridges[curBridge].isVisible()) {
			m_bridges[curBridge].renderBridge(wireframe);
		}
	}

	if (!wireframe && cloudTexture) {
		W3DShaderManager::resetShader(W3DShaderManager::ST_CLOUD_TEXTURE);
	}

	if (!wireframe && TheTerrainRenderObject->getShroud()) {
		DX8Wrapper::Invalidate_Cached_Render_States();
		if (ShaderClass::ShaderDirty || ((unsigned&)ShaderClass::_PresetOpaqueShader != (unsigned&)DX8Wrapper::render_state.shader)) {
			DX8Wrapper::render_state.shader = ShaderClass::_PresetOpaqueShader;
			DX8Wrapper::render_state_changed |= 0x8000;
			StringClass str;
		}
		DX8Wrapper::Set_Material(m_vertexMaterial);
		DX8Wrapper::Set_Index_Buffer(m_indexBridge,0);
		DX8Wrapper::Set_Vertex_Buffer(m_vertexBridge);
		DX8Wrapper::Apply_Render_State_Changes();
		W3DShaderManager::setTexture(0,TheTerrainRenderObject->getShroud()->getShroudTexture());
		W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 0);
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			if (m_bridges[curBridge].isEnabled() && m_bridges[curBridge].isVisible()) {
				m_bridges[curBridge].renderBridge(TRUE);
			}
		}
		W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
	}
}
