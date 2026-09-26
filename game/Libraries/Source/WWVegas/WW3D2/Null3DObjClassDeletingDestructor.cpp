// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Null3DObjClass scalar-deleting destructor at retail RVA
// 0x00972960.  Its matched constructors at 0x009726A0/0x009726E0 install
// vtable 0x0113E87C, whose Clone, Class_ID=22, Render, and bounding-volume
// slots identify Null3DObjClass; the empty complete destructor thunks to
// RenderObjClass at 0x00972980.

class Null3DObjClass
{
public:
	virtual ~Null3DObjClass();
};

void forceNull3DObjClassDeletingDestructor()
{
	Null3DObjClass value;
}
