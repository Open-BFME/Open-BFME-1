// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for W3DShroudMaterialPassClass.
// Vtable 0x00D209C8 slots name this class (?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ); its slot zero routes
// through ILT 0x0003CA15 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00016DC9 reaches cleanup body 0x00933420.

// ??1W3DShroudMaterialPassClass@@UAE@XZ (retail 0x00702580, 5 B) is the
// implicit destructor: a bare `jmp ??1MaterialPassClass@@UAE@XZ` (0x00933420)
// with no vtable re-seat, so the class declares no destructor of its own and
// derives from MaterialPassClass, whose virtual destructor is matched in
// MaterialPassClassDestructor.cpp.
class MaterialPassClass
{
public:
	virtual ~MaterialPassClass();
};

class W3DShroudMaterialPassClass : public MaterialPassClass
{
private:
	friend void forceW3DShroudMaterialPassClassDeletingDestructor();
};

void forceW3DShroudMaterialPassClassDeletingDestructor()
{
	W3DShroudMaterialPassClass value;
}
