// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for W3DShroudMaterialPassClass.
// Vtable 0x00D209C8 slots name this class (?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ); its slot zero routes
// through ILT 0x0003CA15 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00016DC9 reaches cleanup body 0x00933420.

class W3DShroudMaterialPassClass
{
protected:
	virtual ~W3DShroudMaterialPassClass();
private:
	friend void forceW3DShroudMaterialPassClassDeletingDestructor();
};

void forceW3DShroudMaterialPassClassDeletingDestructor()
{
	W3DShroudMaterialPassClass value;
}
