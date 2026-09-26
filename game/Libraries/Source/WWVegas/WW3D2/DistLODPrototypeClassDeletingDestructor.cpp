// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: DistLODPrototypeClass scalar-deleting destructor at retail RVA
// 0x0014AAE0 (30 bytes). The exact constructor at 0x00149E30 installs vtable
// 0x010956B0, whose slot zero routes through ILT 0x000169F5 to this wrapper.
// The DistLOD loader's concrete allocation corroborates identity; the complete
// destructor is called through ILT 0x00012B16.

class DistLODPrototypeClass
{
public:
	virtual ~DistLODPrototypeClass();
};

void forceDistLODPrototypeClassDeletingDestructor()
{
	DistLODPrototypeClass value;
}
