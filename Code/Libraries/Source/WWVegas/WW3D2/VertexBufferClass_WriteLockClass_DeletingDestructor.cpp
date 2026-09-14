// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: VertexBufferClass::WriteLockClass scalar-deleting destructor at
// retail 0x007C1500 (30 bytes).  The matched nested-class constructor at
// 0x0091DD70 and complete destructor at 0x0091DE10 establish the identity;
// this TU emits the compiler-owned deleting wrapper.

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		~WriteLockClass();
	};
};

void Force_VertexBuffer_WriteLockClass_Deleting_Destructor(
	VertexBufferClass::WriteLockClass *value)
{
	delete value;
}
