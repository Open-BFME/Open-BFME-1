// ?updateScorches@BaseHeightMapRenderObjClass@@IAEXXZ
// partial score=0.78 date=2026-08-31
// ?updateScorches@BaseHeightMapRenderObjClass@@IAEXXZ
// Near-match body fragment banked from the BFME layout reconstruction.
void BaseHeightMapRenderObjClass::updateScorches(void)
{
	struct BFMEScorch {
		Vector3 location;
		Real radius;
		Int scorchType;
		Bool flag;
	};
	struct BFMEHeightMapState {
		UnsignedByte prefix[0xd0];
		DX8VertexBufferClass *vertexScorch;
		DX8IndexBufferClass *indexScorch;
		TextureClass *scorchTexture;
		Int curNumScorchVertices;
		Int curNumScorchIndices;
		BFMEScorch scorches[MAX_SCORCH_MARKS];
		Int numScorches;
		Int scorchesInBuffer;
		Int nextScorch;
		UnsignedByte betweenScorchesAndMap[0x24];
		WorldHeightMap *map;
	};
	struct BFMEGlobalDataView {
		UnsignedByte prefix[0x9bc];
		Real terrainAmbient[3];
		UnsignedByte betweenAmbientAndDiffuse[0x18];
		Real terrainDiffuse[3];
	};
	BFMEHeightMapState *state = reinterpret_cast<BFMEHeightMapState *>(this);
	if (state->scorchesInBuffer > 1) return;
	if (state->numScorches == 0) return;
	if (!state->indexScorch || !state->vertexScorch) return;
	state->scorchesInBuffer = 0;
	state->curNumScorchVertices = 0;
	state->curNumScorchIndices = 0;

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
	Int diffuse = (Int)shadeB | ((Int)shadeG << 8) | ((Int)shadeR << 16) | ((int)255 << 24);
	Int xextent = *reinterpret_cast<Int *>(reinterpret_cast<UnsignedByte *>(m_map) + 0x10);

	DX8IndexBufferClass::WriteLockClass lockIdxBuffer(state->indexScorch);
	UnsignedShort *curIb = lockIdxBuffer.Get_Index_Array();
	DX8VertexBufferClass::WriteLockClass lockVtxBuffer(state->vertexScorch);
	VertexFormatXYZDUV1 *curVb = (VertexFormatXYZDUV1 *)lockVtxBuffer.Get_Vertex_Array();

	for (curScorch = state->numScorches - 1; curScorch >= 0; curScorch--) {
		state->scorchesInBuffer++;
		if (state->scorches[curScorch].flag) continue;
		Real radius = state->scorches[curScorch].radius;
		Vector3 loc = state->scorches[curScorch].location;
		Int type = state->scorches[curScorch].scorchType;
		if (type < 0) type = 0;
		if (type >= SCORCH_MARKS_IN_TEXTURE) type = 0;
		Real amtToFloat = MAP_HEIGHT_SCALE / 10;
		Int minX = fast_float2long_round(floorf((loc.X - radius) / MAP_XY_FACTOR));
		Int minY = fast_float2long_round(floorf((loc.Y - radius) / MAP_XY_FACTOR));
		if (minX < -xextent) minX = -xextent;
		if (minY < -xextent) minY = -xextent;
		Int maxX = fast_float2long_round(ceilf((loc.X + radius) / MAP_XY_FACTOR));
		Int maxY = fast_float2long_round(ceilf((loc.Y + radius) / MAP_XY_FACTOR));
		maxX++;
		maxY++;
		if (maxX > m_map->getXExtent() - xextent) maxX = m_map->getXExtent() - xextent;
		if (maxY > m_map->getYExtent() - xextent) maxY = m_map->getYExtent() - xextent;
		Int startVertex = state->curNumScorchVertices;
		Int i, j;
		for (j = minY; j < maxY; j++) {
			for (i = minX; i < maxX; i++) {
				if (state->curNumScorchVertices >= MAX_SCORCH_VERTEX) return;
				curVb->diffuse = diffuse;
				Real theZ = amtToFloat + ((float)getClipHeight(i + xextent, j + xextent) * MAP_HEIGHT_SCALE);
				Real uOffset = (type % SCORCH_PER_ROW) * 1.5f;
				Real vOffset = (type / SCORCH_PER_ROW) * 1.5f;
				Real X = i * MAP_XY_FACTOR;
				Real Y = j * MAP_XY_FACTOR;
				curVb->u1 = (uOffset + 0.5f + (X - loc.X) / (2 * radius)) / (SCORCH_PER_ROW + 1);
				curVb->v1 = (vOffset + 0.5f + (Y - loc.Y) / (2 * radius)) / (SCORCH_PER_ROW + 1);
				curVb->x = X;
				curVb->y = Y;
				curVb->z = theZ;
				curVb++;
				state->curNumScorchVertices++;
			}
		}
		Int yOffset = maxX - minX;
		for (j = 0; j < maxY - minY - 1; j++) {
			for (i = 0; i < maxX - minX - 1; i++) {
				if (state->curNumScorchIndices + 6 > MAX_SCORCH_INDEX) return;
				Int xNdx = i + minX + xextent;
				Int yNdx = j + minY + xextent;
				Bool flipForBlend = m_map->getFlipState(xNdx, yNdx);
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
				state->curNumScorchIndices += 6;
			}
		}
	}
}
