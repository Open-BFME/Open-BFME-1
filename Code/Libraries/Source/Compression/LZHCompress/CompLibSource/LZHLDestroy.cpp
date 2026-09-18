// cl: /DNDEBUG /MD /ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader
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
