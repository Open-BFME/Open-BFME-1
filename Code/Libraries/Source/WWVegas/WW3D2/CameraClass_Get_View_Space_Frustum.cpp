// cl: /DNDEBUG /MD /EHsc

// The reference header defines this as an inline CameraClass accessor.  BFME
// emits a standalone copy at 0x00942F20; keeping the class layout local lets
// this TU reproduce that copy without changing the shared vendored header.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/frustum.h
class FrustumClass {
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class CameraClass {
public:
	const FrustumClass &Get_View_Space_Frustum(void) const;

protected:
	void Update_Frustum(void) const;

	char _camera_prefix[0x194];
	FrustumClass ViewSpaceFrustum;
};

const FrustumClass &CameraClass::Get_View_Space_Frustum(void) const
{
	Update_Frustum();
	return ViewSpaceFrustum;
}
