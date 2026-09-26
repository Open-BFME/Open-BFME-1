// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Anim2D protected scalar-deleting destructor at retail RVA
// 0x005BB020 (30 bytes). The matched constructor at 0x005BA4D0 and matched
// complete destructor at 0x005BA670 both install vtable 0x0110F29C. Its slot
// zero routes here; the wrapper calls the destructor through ILT 0x00004DBD.

class Anim2D
{
	friend void forceAnim2DDeletingDestructor();

protected:
	virtual ~Anim2D();
};

void forceAnim2DDeletingDestructor()
{
	Anim2D value;
}
