// cl: /DNDEBUG /MD /GX- /Igame/Libraries/Source/Compression/LZHCompress/CompLibHeader
// Retail RVA 0x00823230, 27 bytes.
// Matched DecompressFile (0x0081E9A0) and DecompressMemory (0x0081EB80)
// call LZHLDestroyDecompressor with the handle from LZHLCreateDecompressor.
// Retail takes one cdecl pointer argument and calls the nonvirtual destructor
// at 0x008267E0, then operator delete. The vendored _lz.h declaration and
// Huff.cpp destructor independently establish the LZHLDecompressor type.
// Formerly Rva00823230(Gen008267E0*); no anonymous class or local layout needed.
#define LZHLINTERNAL
#include "_huff.h"
#include "_lz.h"

void LZHLDestroyDecompressor(void *handle)
{
    delete static_cast<LZHLDecompressor *>(handle);
}

// Retail RVA 0x00823210, 27 bytes. Matched CompressFile at 0x0081EC50
// calls this API with its compressor handle; retail calls the nonvirtual
// LZHLCompressor destructor at 0x00825550 and then operator delete.
void LZHLDestroyCompressor(void *handle)
{
    delete static_cast<LZHLCompressor *>(handle);
}

// Matched CompressFile names these API calls at RVAs 0x00823110 and
// 0x00823200. The factory allocates sizeof(LZHLCompressor)==0x18 and
// tail-calls its matched constructor; the bound is the canonical inline.
void *LZHLCreateCompressor()
{
    return new LZHLCompressor;
}

unsigned int LZHLCompressorCalcMaxBuf(unsigned int rawSize)
{
    return LZHLCompressor::calcMaxBuf(rawSize);
}

// Retail 0x00823130: matched CompressFile calls this named API.
// The member at 0x00825680 takes dst/src/size with ECX=handle, returns
// LZHLEncoder::flush in EAX, and pops 12 argument bytes. Its named
// LZBuffer/encoder callees and canonical declaration prove the identity;
// the vendored member body itself remains present-unmatched.
unsigned int LZHLCompress(void *handle, void *destination, void *source, unsigned int sourceSize)
{
    return static_cast<LZHLCompressor *>(handle)->compress(
        static_cast<BYTE *>(destination), static_cast<const BYTE *>(source), sourceSize);
}
