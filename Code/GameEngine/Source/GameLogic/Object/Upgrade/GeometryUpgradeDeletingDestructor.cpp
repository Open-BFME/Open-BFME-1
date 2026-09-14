// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: GeometryUpgrade scalar-deleting destructor at retail RVA
// 0x002D58D0 (30 bytes).  Its call through ILT 0x0001C1D4 reaches the
// matched complete destructor at 0x002D5900.  The matched constructor at
// 0x002D5790, typed module factories, and the module-name getter establish
// the GeometryUpgrade identity independently of the generated placeholder.

class GeometryUpgrade
{
public:
	virtual ~GeometryUpgrade();
};

void forceGeometryUpgradeDeletingDestructor()
{
	GeometryUpgrade value;
}
