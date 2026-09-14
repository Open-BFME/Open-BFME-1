// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: IndexBufferClass::WriteLockClass scalar-deleting destructor at
// retail 0x007C1530 (30 bytes).  The matched nested-class constructor at
// 0x0091CE50 and complete destructor at 0x0091CEF0 establish the identity;
// this TU emits the compiler-owned deleting wrapper.

class IndexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		~WriteLockClass();
	};
};

void Force_IndexBuffer_WriteLockClass_Deleting_Destructor(
	IndexBufferClass::WriteLockClass *value)
{
	delete value;
}
