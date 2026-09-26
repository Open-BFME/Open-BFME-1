// cl: /DNDEBUG /MD /EHsc
// CameraShakeSystemClass::Add_Camera_Shake calls this five-byte incremental-link thunk.
// The thunk routes to ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass,256>::Allocate_Object_Memory.

class CameraShakeSystemClass
{
public:
	class CameraShakerClass;
};

template <class T, int BLOCK_SIZE>
class ObjectPoolClass
{
public:
	T *Allocate_Object_Memory(void);
};

class Rva00002603Thunk
{
public:
	CameraShakeSystemClass::CameraShakerClass *forward();
};

CameraShakeSystemClass::CameraShakerClass *Rva00002603Thunk::forward()
{
	return ((ObjectPoolClass<CameraShakeSystemClass::CameraShakerClass,256> *)this)
		->Allocate_Object_Memory();
}
