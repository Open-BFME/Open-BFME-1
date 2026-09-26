// ?readTexClass@WorldHeightMap@@IAEXPAUTXTextureClass@@PAPAVTileData@@@Z
// partial score=0.55 date=2026-09-21
// NOT a standalone TU. Candidate identity note for retail RVA 0x0074BBB0.
//
// The real source already lives at
// Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp:2795
// as WorldHeightMap::readTexClass, tagged in-source:
//   "?readTexClass@WorldHeightMap@@IAEXPAUTXTextureClass@@PAPAVTileData@@@Z present-unmatched"
//
// Its callee sequence (TerrainTypeCollection::findTerrain, TerrainType::getTexture,
// sprintf with format 0x1075310 and dir constant 0x1121b3c, FileSystem::openFile
// mode 0x41, GDIFileStream+WorldHeightMap::countTiles, File::seek vtable slot 5,
// a width*width search loop, WorldHeightMap::readTiles, File::close vtable slot 2)
// matches retail 0x0074BBB0's disassembly instruction-for-instruction at the
// call-site level.
//
// `python3 tools/probe.py Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp
//   "?readTexClass@WorldHeightMap@@IAEXPAUTXTextureClass@@PAPAVTileData@@@Z" 0x0074BBB0 --size 270`
// compiles clean against the file's own `// cl:` line and gives ours=304 retail=270
// (34 bytes too long), diverging from the very first non-prologue instruction.
//
// Root cause isolated: this TU's real (reference-header) AsciiString copy
// constructor, used when passing `texClass->name` by value into
// `TheTerrainTypes->findTerrain(...)`, is inlined with an extra "is the source
// string's data pointer null" fast-path branch that retail's actual compiled
// body does not have -- ours reads texClass->name (this+0x14) twice (once for
// that null check, once for the real copy), retail reads it once. Whoever picks
// this up next should look at how AsciiString's copy constructor is declared for
// this TU (Common/AsciiString.h via the reference includes) and find the lever
// that drops the early-out branch, OR give findTerrain's parameter a shape that
// does not trigger it (e.g. passing by a raw pointer/reference through a small
// TU-local wrapper instead of relying on the production header's inlined ctor).
//
// Separately unverified: the width search loop is currently written as
// `for (width = 10; width >= 1; width--)` but retail's own literal at the
// mov eax, imm32 for that loop is 0x10 (16 decimal) -- check whether BFME
// actually widened the search to 16 once the copy-ctor shape is fixed; do not
// assume the reference's `10` is right for BFME without checking against the
// disassembly again.
