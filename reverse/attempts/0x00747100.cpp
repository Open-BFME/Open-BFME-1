// ?readTiles@WorldHeightMap@@SA_NPAVInputStream@@PAPAVTileData@@H@Z
// partial score=0.96 date=2026-09-21
// Banked reconstruction for retail RVA 0x00747100.
Bool WorldHeightMap::readTiles(InputStream *pStr, TileData **tiles, Int numRows)
{
	TTargaHeader hdr;
	pStr->read(&hdr, sizeof(hdr));
	Int tileWidth = hdr.imageWidth/TILE_PIXEL_EXTENT;
	Int tileHeight = hdr.imageHeight/TILE_PIXEL_EXTENT;

	if (hdr.imageHeight==TILE_PIXEL_EXTENT/2) {
		tileHeight = 1;
	}
	if (hdr.imageWidth==TILE_PIXEL_EXTENT/2) {
		tileWidth = 1;
	}

	if (tileWidth<numRows && tileHeight<numRows) {
		return(false);
	}
	if (hdr.imageType & 0x08) return(false);
	if (hdr.imageWidth > 0x400) return(false);
	int bytesPerPixel = (hdr.pixelDepth+7)/8;
	if (bytesPerPixel < 3) return(false);
	if (bytesPerPixel > 4) return(false);
	for (int i=0; i<numRows*numRows; i++) {
		if (tiles[i] == NULL)
			tiles[i] = MSGNEW("WorldHeightMap_readTiles") TileData;
	}
	for (int row = 0; row < numRows*TILE_PIXEL_EXTENT; row++) {
		UnsignedByte *source = (UnsignedByte *)0x01303808;
		++source;
		if (row < hdr.imageHeight) {
			pStr->read((void *)0x01303808, hdr.imageWidth*bytesPerPixel);
		}
		for (int column=0; column<hdr.imageWidth && column<numRows*TILE_PIXEL_EXTENT; column++) {
			UnsignedByte r, g, b, a;
			if (row < hdr.imageHeight) {
				g = source[0];
				r = source[1];
				b = source[-1];
				if (bytesPerPixel==4) {
					a = source[2];
				} else {
					a = 255;
				}
				source += bytesPerPixel;
			} else {
				r = g = b = a = 0;
			}
			int tileNdx = (column/TILE_PIXEL_EXTENT) + numRows*(row/TILE_PIXEL_EXTENT);
			int pixelNdx = (column%TILE_PIXEL_EXTENT) + TILE_PIXEL_EXTENT*(row%TILE_PIXEL_EXTENT);
			UnsignedByte *pixel = tiles[tileNdx]->getDataPtr();
			pixel += pixelNdx*TILE_BYTES_PER_PIXEL;
			*pixel++ = b;
			*pixel++ = g;
			*pixel++ = r;
			*pixel = a;
		}
	}
	for (int i=0; i<numRows*numRows; i++) {
		tiles[i]->updateMips();
	}
	return(true);
}
