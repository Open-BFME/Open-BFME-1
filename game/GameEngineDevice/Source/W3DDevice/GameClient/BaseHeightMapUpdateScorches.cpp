// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmeheightmap /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ?updateScorches@BaseHeightMapScorchUpdater@@QAEXXZ
// BFME BaseHeightMapRenderObjClass::updateScorches, reached through ILT
// 0x00032966 from the matched BaseHeightMapRenderObjClass::drawScorches, which
// calls it through the BaseHeightMapScorchUpdater alias of the render object.
// Ported from the Zero Hour updateScorches with the BFME changes the retail body
// shows: skipped scorches (flag byte), the border read once before the locks,
// 16-bit heights, the per-scorch UV offsets and a vertex-budget rollback.
#include "Lib/BaseType.h"
#include <math.h>
#include "vector3.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// The flip-state query retail calls (ILT 0x000489A5) is the matched
// Gen_0074B410::bfmeBitA body; call it by that ledger name.
class Gen_0074B410
{
public:
	bool bfmeBitA(int x, int y) const;
};

struct BFMEScorchEntry
{
	Vector3 location;
	Real radius;
	Int scorchType;
	UnsignedByte flag;
};

class BaseHeightMapScorchUpdater
{
public:
	void updateScorches();

private:
	inline UnsignedShort getClipHeight(Int x, Int y) const
	{
		Int xExtent = m_map->getXExtent();
		Int yExtent = m_map->getYExtent();
		if (x < 0)
			x = 0;
		else if (x >= xExtent)
			x = xExtent - 1;
		if (y < 0)
			y = 0;
		else if (y >= yExtent)
			y = yExtent - 1;
		// BFME stores 16-bit heights behind m_data.
		return reinterpret_cast<UnsignedShort *>(m_map->getDataPtr())[x + y * xExtent];
	}

	UnsignedByte m_pad00[0xd0];
	DX8VertexBufferClass *m_vertexScorch;
	DX8IndexBufferClass *m_indexScorch;
	void *m_scorchTexture;
	Int m_curNumScorchVertices;
	Int m_curNumScorchIndices;
	BFMEScorchEntry m_scorches[500];
	Int m_numScorches;
	Int m_scorchesInBuffer;
	Int m_nextScorch;
	UnsignedByte m_pad2fd0[0x24];
	WorldHeightMap *m_map;
};

struct BFMEScorchGlobalView
{
	UnsignedByte prefix[0x9bc];
	Real terrainAmbient[3];
	UnsignedByte betweenAmbientAndDiffuse[0x18];
	Real terrainDiffuse[3];
};

#define SCORCH_MARKS_IN_TEXTURE 9
#define SCORCH_PER_ROW 3
#define MAX_SCORCH_VERTEX 8194
#define MAX_SCORCH_INDEX 49164
#define BFME_MAP_XY_FACTOR 10.0f
#define BFME_MAP_HEIGHT_SCALE (BFME_MAP_XY_FACTOR / 256.0f)
// CRT floor/ceil through a double local: the loop-local double is what gives the
// retail body its 8-byte aligned frame (docs/shape_levers.md, aligned prologue).
static inline Real bfmeFloorD(Real f) { double d = floor(f); return (Real)d; }
static inline Real bfmeCeilD(Real f) { double d = ceil(f); return (Real)d; }
void BaseHeightMapScorchUpdater::updateScorches()
{
	if (m_scorchesInBuffer > 1) {
		return;
	}
	if (m_numScorches == 0) {
		return;
	}
	if (!m_indexScorch || !m_vertexScorch) {
		return;
	}
	m_scorchesInBuffer = 0;
	m_curNumScorchVertices = 0;
	m_curNumScorchIndices = 0;

	const BFMEScorchGlobalView *global = reinterpret_cast<const BFMEScorchGlobalView *>(TheWritableGlobalData);
	Real shadeR, shadeG, shadeB;
	shadeR = global->terrainAmbient[0];
	shadeG = global->terrainAmbient[1];
	shadeB = global->terrainAmbient[2];
	shadeR += global->terrainDiffuse[0] / 2;
	shadeG += global->terrainDiffuse[1] / 2;
	shadeB += global->terrainDiffuse[2] / 2;
	shadeR *= 255.0f;
	shadeG *= 255.0f;
	shadeB *= 255.0f;
	Int diffuse = (Int)shadeR;
	diffuse |= 0xffffff00;
	diffuse <<= 8;
	diffuse |= (Int)shadeG;
	diffuse <<= 8;
	diffuse |= (Int)shadeB;
	Int borderSize = m_map->getBorderSizeInline();

	DX8IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexScorch);
	UnsignedShort *curIb = lockIdxBuffer.Get_Index_Array();

	DX8VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexScorch);
	VertexFormatXYZDUV1 *curVb = (VertexFormatXYZDUV1 *)lockVtxBuffer.Get_Vertex_Array();

	Int curScorch;
	for (curScorch = m_numScorches - 1; curScorch >= 0; curScorch--) {
		// The flag read into a local is what makes retail reload the entry
		// pointer before the counter at the loop latch.
		UnsignedByte flag = m_scorches[curScorch].flag;
		if (flag) {
			continue;
		}
		m_scorchesInBuffer++;
		Int type = m_scorches[curScorch].scorchType;
		if (type < 0) {
			type = 0;
		}
		if (type >= SCORCH_MARKS_IN_TEXTURE) {
			type = 0;
		}
		Real uOffset = (type % SCORCH_PER_ROW) * 1.5f + 0.5f;
		Real radius = m_scorches[curScorch].radius;
		Vector3 loc = m_scorches[curScorch].location;
		Real vOffset = (type / SCORCH_PER_ROW) * 1.5f + 0.5f;

		Int minX = fast_float2long_round(bfmeFloorD((loc.X - radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		Int minY = fast_float2long_round(bfmeFloorD((loc.Y - radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		if (minX < -borderSize) minX = -borderSize;
		if (minY < -borderSize) minY = -borderSize;
		Int maxX = fast_float2long_round(bfmeCeilD((loc.X + radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		maxX++;
		Int maxY = fast_float2long_round(bfmeCeilD((loc.Y + radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		maxY++;
		if (maxX > m_map->getXExtent() - borderSize) {
			maxX = m_map->getXExtent() - borderSize;
		}
		if (maxY > m_map->getYExtent() - borderSize) {
			maxY = m_map->getYExtent() - borderSize;
		}
		Int startVertex = m_curNumScorchVertices;
		Int i, j;
		for (j = minY; j < maxY; j++) {
			Real Y = j * BFME_MAP_XY_FACTOR;
			for (i = minX; i < maxX; i++) {
				if (m_curNumScorchVertices >= MAX_SCORCH_VERTEX) {
					m_curNumScorchVertices = startVertex;
					return;
				}
				curVb->diffuse = diffuse;
				Real X = i * BFME_MAP_XY_FACTOR;
				curVb->u1 = (uOffset + (X - loc.X) / (2 * radius)) / (SCORCH_PER_ROW + 1);
				curVb->v1 = (vOffset + (Y - loc.Y) / (2 * radius)) / (SCORCH_PER_ROW + 1);
				curVb->x = X;
				curVb->y = Y;
				curVb->z = getClipHeight(i + borderSize, j + borderSize) * BFME_MAP_HEIGHT_SCALE + 1.0f;
				curVb++;
				m_curNumScorchVertices++;
			}
		}
		Int yOffset = maxX - minX;
		for (j = 0; j < maxY - minY - 1; j++) {
			Int yNdx = j + minY + borderSize;
			for (i = 0; i < maxX - minX - 1; i++) {
				if (m_curNumScorchIndices + 6 > MAX_SCORCH_INDEX) return;
				Int xNdx = i + minX + borderSize;
				Bool flipForBlend = reinterpret_cast<const Gen_0074B410 *>(m_map)->bfmeBitA(xNdx, yNdx);
				if (flipForBlend) {
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
					*curIb++ = startVertex + j * yOffset + i;
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + 1 + yOffset;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
				} else {
					*curIb++ = startVertex + j * yOffset + i;
					*curIb++ = startVertex + j * yOffset + i + 1 + yOffset;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
					*curIb++ = startVertex + j * yOffset + i;
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + 1 + yOffset;
				}
				m_curNumScorchIndices += 6;
			}
		}
	}
}
