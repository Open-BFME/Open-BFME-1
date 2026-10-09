// ?rva0081E650MaxCompressedSize@@YAHHW4CompressionType@@@Z
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /MD /EHs-c-
extern "C" __declspec(dllimport) double __cdecl ceil(double);
unsigned int __cdecl __identifier("?j_0081eb70@@YAXXZ")(unsigned int);

enum CompressionType
{
    COMPRESSION_NONE = 0, COMPRESSION_REFPACK, COMPRESSION_NOXLZH,
    COMPRESSION_ZLIB1, COMPRESSION_ZLIB2, COMPRESSION_ZLIB3,
    COMPRESSION_ZLIB4, COMPRESSION_ZLIB5, COMPRESSION_ZLIB6,
    COMPRESSION_ZLIB7, COMPRESSION_ZLIB8, COMPRESSION_ZLIB9,
    COMPRESSION_BTREE, COMPRESSION_HUFF
};

// Open BFME 2: Code/Libraries/Source/Compression/CompressionManager_decompressData.cpp.
int rva0081E650MaxCompressedSize(int uncompressedLen, CompressionType compType)
{
    switch (compType)
    {
        case COMPRESSION_NOXLZH:
            return __identifier("?j_0081eb70@@YAXXZ")(uncompressedLen) + 8;
        case COMPRESSION_BTREE:
        case COMPRESSION_HUFF:
        case COMPRESSION_REFPACK:
            return uncompressedLen + 8;
        case COMPRESSION_ZLIB1:
        case COMPRESSION_ZLIB2:
        case COMPRESSION_ZLIB3:
        case COMPRESSION_ZLIB4:
        case COMPRESSION_ZLIB5:
        case COMPRESSION_ZLIB6:
        case COMPRESSION_ZLIB7:
        case COMPRESSION_ZLIB8:
        case COMPRESSION_ZLIB9:
            return (int)(ceil(uncompressedLen * 1.1 + 12 + 8));
    }
    return 0;
}
