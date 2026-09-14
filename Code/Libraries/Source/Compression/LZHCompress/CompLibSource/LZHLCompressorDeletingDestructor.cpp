// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: LZHLCompressor scalar-deleting destructor at retail
// 0x00823150 (30 bytes).  The matched LZHLCompressor constructor at
// 0x008254C0 and complete destructor at 0x00825550 establish the identity.

class LZHLCompressor
{
public:
	~LZHLCompressor();
};

void forceLZHLCompressorDeletingDestructor(LZHLCompressor *value)
{
	delete value;
}
