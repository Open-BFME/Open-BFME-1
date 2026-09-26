// ?updateScorches@BaseHeightMapScorchUpdater@@QAEXXZ
// partial score=0.8 date=2026-09-07
// Retail 0x006C7E90 ends at ret +0x600 and spans 1,537 bytes. The matched
// drawScorches caller invokes ILT 0x00032966 through BaseHeightMapScorchUpdater,
// which proves the method identity.
//
// The draft matches the prologue through +0x21, guards, color packing, lock
// order, scorch checks, type clamp, floor and ceil calls, height read, and
// flip-state call. Retail keeps `this` in EBP at +0x22. The draft uses EDI or
// EBX, reads type at +0xF4 before flag at +0xF8, and uses a different shade
// spill at [esp+0x40].
// The full translation unit declares floor and ceil with dllimport. Its
// REAL_TO_INT macros call fast_float2long_round.
struct BFMEScorchEntry {
	Vector3 location;
	Real radius;
	Int scorchType;
	UnsignedByte flag;
};
// Retail-exact mirror of the scorch storage; the updater alias reaches the
// same bytes as BaseHeightMapRenderObjClass ([this+0xd0]..[this+0x2ff4]).
class BaseHeightMapScorchUpdater
{
public:
	void updateScorches();

private:
	UnsignedByte m_pad00[0xd0];
	DX8VertexBufferClass *m_vertexScorch;
	DX8IndexBufferClass *m_indexScorch;
	TextureClass *m_scorchTexture;
	Int m_curNumScorchVertices;
	Int m_curNumScorchIndices;
	BFMEScorchEntry m_scorches[500];
	Int m_numScorches;
	Int m_scorchesInBuffer;
	Int m_nextScorch;
	UnsignedByte m_pad2fd0[0x24];
	WorldHeightMap *m_map;
};

void BaseHeightMapScorchUpdater::updateScorches()
{
	struct BFMEWorldHeightMapView {
		UnsignedByte prefix[8];
		Int xExtent;
		Int yExtent;
		Int borderSize;
		UnsignedByte mid[0x10];
		UnsignedShort *heightData;
	};
	struct BFMEGlobalDataView {
		UnsignedByte prefix[0x9bc];
		Real terrainAmbient[3];
		UnsignedByte betweenAmbientAndDiffuse[0x18];
		Real terrainDiffuse[3];
	};
	if (m_scorchesInBuffer > 1) {
		return;
	}
	if (m_numScorches == 0) {
		return;
	}
	if (m_indexScorch == NULL || m_vertexScorch == NULL) {
		return;
	}
	m_scorchesInBuffer = 0;
	m_curNumScorchVertices = 0;
	m_curNumScorchIndices = 0;

	Int curScorch;
	Real shadeR, shadeG, shadeB;
	const BFMEGlobalDataView *global = reinterpret_cast<const BFMEGlobalDataView *>(TheGlobalData);
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
	WorldHeightMap *map = m_map;
	Int borderSize = reinterpret_cast<BFMEWorldHeightMapView *>(map)->borderSize;
	DX8IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexScorch);
	UnsignedShort *ib = lockIdxBuffer.Get_Index_Array();
	UnsignedShort *curIb = ib;

	DX8VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexScorch);
	VertexFormatXYZDUV1 *vb = (VertexFormatXYZDUV1 *)lockVtxBuffer.Get_Vertex_Array();
	VertexFormatXYZDUV1 *curVb = vb;

	const Real MAP_XY_FACTOR_INV = 1.0f / MAP_XY_FACTOR;
	for (curScorch = m_numScorches - 1; curScorch >= 0; curScorch--) {
		if (m_scorches[curScorch].flag != 0) {
			continue;
		}
		m_scorchesInBuffer++;
		Int type = m_scorches[curScorch].scorchType;
		if (type < 0) {
			type = 0;
		}
		if (type >= 9 /*SCORCH_MARKS_IN_TEXTURE*/) {
			type = 0;
		}
		Real uOffset = (type % 3 /*SCORCH_PER_ROW*/) * 1.5f;
		Real vOffset = (type / 3 /*SCORCH_PER_ROW*/) * 1.5f;
		Real radius = m_scorches[curScorch].radius;
		Real locX = m_scorches[curScorch].location.X;
		Real locY = m_scorches[curScorch].location.Y;
		Real amtToFloat = 0;
		amtToFloat = MAP_HEIGHT_SCALE / 10;

		Int minX = REAL_TO_INT_FLOOR((locX - radius) * MAP_XY_FACTOR_INV);
		Int minY = REAL_TO_INT_FLOOR((locY - radius) * MAP_XY_FACTOR_INV);
		if (minX < -borderSize) minX = -borderSize;
		if (minY < -borderSize) minY = -borderSize;
		Int maxX = REAL_TO_INT_CEIL((locX + radius) * MAP_XY_FACTOR_INV);
		Int maxY = REAL_TO_INT_CEIL((locY + radius) * MAP_XY_FACTOR_INV);
		maxX++; maxY++;
		Int width = reinterpret_cast<BFMEWorldHeightMapView *>(m_map)->xExtent;
		if (maxX > width - borderSize) {
			maxX = width - borderSize;
		}
		Int height = reinterpret_cast<BFMEWorldHeightMapView *>(m_map)->yExtent;
		if (maxY > height - borderSize) {
			maxY = height - borderSize;
		}
		Int startVertex = m_curNumScorchVertices;
		Int i, j;
		for (j = minY; j < maxY; j++) {
			for (i = minX; i < maxX; i++) {
				if (m_curNumScorchVertices >= 8194 /*MAX_SCORCH_VERTEX*/) return;
				curVb->diffuse = diffuse;
				Int xNdx = i + borderSize;
				Int yNdx = j + borderSize;
				Int xExtent = reinterpret_cast<BFMEWorldHeightMapView *>(m_map)->xExtent;
				Int yExtent = reinterpret_cast<BFMEWorldHeightMapView *>(m_map)->yExtent;
				if (xNdx < 0) xNdx = 0;
				else if (xNdx >= xExtent) xNdx = xExtent - 1;
				if (yNdx < 0) yNdx = 0;
				else if (yNdx >= yExtent) yNdx = yExtent - 1;
				UnsignedShort heightSample = reinterpret_cast<BFMEWorldHeightMapView *>(m_map)->heightData[yNdx * xExtent + xNdx];
				Real theZ;
				theZ = amtToFloat + ((Real)heightSample * MAP_HEIGHT_SCALE);
				Real X = i * MAP_XY_FACTOR;
				Real Y = j * MAP_XY_FACTOR;
				curVb->u1 = (uOffset + 0.5f + (X - locX) / (2 * radius)) / (3 + 1 /*SCORCH_PER_ROW+1*/);
				curVb->v1 = (vOffset + 0.5f + (Y - locY) / (2 * radius)) / (3 + 1 /*SCORCH_PER_ROW+1*/);
				curVb->x = X;
				curVb->y = Y;
				curVb->z = theZ;
				curVb++;
				m_curNumScorchVertices++;
			}
		}
		Int yOffset = maxX - minX;
		for (j = 0; j < maxY - minY - 1; j++) {
			for (i = 0; i < maxX - minX - 1; i++) {
				if (m_curNumScorchIndices + 6 > 49164 /*MAX_SCORCH_INDEX*/) return;
				Int xNdx = i + minX + borderSize;
				Int yNdx = j + minY + borderSize;
				Bool flipForBlend = map->getFlipState(xNdx, yNdx);
				if (flipForBlend) {
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
					*curIb++ = startVertex + j * yOffset + i;
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + 1 + yOffset;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
				}
				else
				{
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
