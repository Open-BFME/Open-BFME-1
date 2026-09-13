// cl: /DNDEBUG /MD /EHsc

// Two independent confirmations, which is what this identification needs.
//
// Position: the slots below this one are ??_GCameraClass and
// Clone@CameraClass, and rendobj.h declares destructor, Clone, then Class_ID --
// so this slot is Class_ID of CameraClass.
//
// Value: the body returns 8, and counting rendobj.h's ClassID enum from
// CLASSID_MESH = 0 puts CLASSID_CAMERA at 8.
//
// Either alone would be weak. A body returning a small constant is common, and
// forty of them in this image return a value that happens to land inside that
// enum; only a handful sit in a vtable whose named slots agree.
class RenderObjClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class CameraClass
{
public:
	virtual ~CameraClass();
	virtual RenderObjClass *Clone(void) const;
	virtual int Class_ID(void) const;
};

// ?Class_ID@CameraClass@@UBEHXZ
int CameraClass::Class_ID(void) const
{
	return 8;
}
