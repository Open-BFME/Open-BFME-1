# WorldHeightMap::getUVData at 0x0074CF30

Retail 0x0074CF30 (82 B, previously the placeholder ?sample@BfmeMapWU@@QAEEHHHHH@Z
in BfmeGrokMapSamp.cpp) is Zero Hour's WorldHeightMap::getUVData.

- Its only call (callees.py 0x74CF30 82) goes ILT 0x9FC5 -> 0x0074BEB0, the
  matched ?getUVForTileIndex@WorldHeightMap@@IAE_NHFQAM0_N@Z
  (WorldHeightMapGetUVForTileIndex.cpp). getUVForTileIndex is protected, so
  the caller is a WorldHeightMap member.
- The body is exactly ZH WorldHeightMap.cpp getUVData: ndx =
  (yIndex + m_drawOriginY) * m_width + xIndex + m_drawOriginX; if
  ndx < m_dataSize and m_tileNdxes is non-null, return
  getUVForTileIndex(ndx, m_tileNdxes[ndx], U, V, fullTile) (movsx of the
  short tile index, three stack args passed through); else return false.
  It ends `ret 0x14` (five dword args: Int, Int, float*, float*, Bool).
- Offsets: m_width +0x08, m_dataSize +0x20, m_tileNdxes +0x8C,
  m_drawOriginX/Y +0x120E0/+0x120E4 (BfmeGrokMapSamp.cpp's view).

BfmeGrokMapSamp.cpp's body is renamed to the real member (bytes unchanged);
WorldHeightMap.cpp's present-unmatched ZH copy (which does not byte-match) is
removed so only the retail-proven definition remains.
