// cl: /DNDEBUG /MD /EHsc

// Slot 9 of GridCullSystemClass's vtable, the first unclaimed one after Save at
// slot 8. gridcull.h declares Get_Object_Count immediately after Save, inline, as
// `{ return ObjCount; }` -- and the body here is a four-byte getter returning the
// int member at +0x54. Slots 10 and 11 sit past the end of the reference's
// declaration list and are BFME additions, so they are left alone.
class CullableClass;
class Vector3;
class AABoxClass;
class OBBoxClass;
class FrustumClass;
class ChunkLoadClass;
class ChunkSaveClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/gridcull.h
class GridCullSystemClass
{
public:
	virtual ~GridCullSystemClass();
	virtual void Collect_Objects(const Vector3 &point);
	virtual void Collect_Objects(const AABoxClass &box);
	virtual void Collect_Objects(const OBBoxClass &box);
	virtual void Collect_Objects(const FrustumClass &frustum);
	virtual void Re_Partition(const Vector3 &min, const Vector3 &max, float objdim);
	virtual void Update_Culling(CullableClass *obj);
	virtual void Load(ChunkLoadClass &cload);
	virtual void Save(ChunkSaveClass &csave);
	virtual int Get_Object_Count(void) const;

private:
	unsigned char m_base[0x50];
	int m_objCount;
};

// ?Get_Object_Count@GridCullSystemClass@@UBEHXZ
int GridCullSystemClass::Get_Object_Count(void) const
{
	return m_objCount;
}
