// 040-horplus — BFME tactical-camera Hor+ modernization.
//
// This payload is intentionally one small C++ translation unit. It is linked
// with /NODEFAULTLIB and placed in .bfmemod by tools/modbuild.py; there is no
// loader or CRT behind it. The only floating-point math here is multiply and
// divide. The retail CameraClass::Set_View_Plane routine at RVA 0x00931780
// supplies the tangent operation, after which this payload scales the native
// view-plane half-extents by the display aspect relative to the 4:3 reference.
// MSVC 7.1 emits its floating-point presence marker for these operations, so
// the local definition below satisfies that marker without providing a runtime
// library function. modbuild.py accepts this one self-defined compiler marker;
// every other unresolved external remains fatal.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" const int _fltused = 0;

enum {
	DISPLAY_GET_WIDTH_SLOT = 0x2C / 4,
	DISPLAY_GET_HEIGHT_SLOT = 0x30 / 4,
	VIEW_WIDTH = 0x18,
	VIEW_FOV = 0x6C,
	VIEW_CAMERA = 0x104,
	CAMERA_VIEW_PLANE_MIN_X = 0xDC,
	CAMERA_VIEW_PLANE_MIN_Y = 0xE0,
	CAMERA_VIEW_PLANE_MAX_X = 0xE4,
	CAMERA_VIEW_PLANE_MAX_Y = 0xE8,
	CAMERA_FRUSTUM_VALID = 0x100
};

// BFME globals confirmed by the reconstructed Display/ControlBar sources:
// TheDisplay is 0x012F1270 and TheTacticalView is 0x012F1600. BFME's
// W3DView layout puts m_3DCamera at +0x104. TheDisplay's getWidth/getHeight
// are vtable slots +0x2C/+0x30, as shown by the matched setWidth assembly.
#define TheDisplay (*(void **)0x012F1270)
#define TheTacticalView (*(void **)0x012F1600)

// MSVC 7.1 rejects __thiscall in this project. These are the documented
// __fastcall spellings: this in ECX, unused EDX, and no explicit stack args.
typedef UnsignedInt(__fastcall *DisplayDimension)(void *self, void *edx);
typedef void(__fastcall *SetViewPlane)(void *self, void *edx, Real hfov, Real vfov);

// CameraClass::Set_View_Plane(float,float), reverse/functions.csv RVA
// 0x00931780, matched against Code/Libraries/.../WW3D2/camera.cpp. Payload
// calls use the fixed retail VA (RVA + the 0x00400000 image base). Passing
// vfov=-1 preserves the retail behavior of deriving the vertical extent from
// the camera's current tactical viewport aspect.
#define c_set_view_plane ((SetViewPlane)0x00D31780)

static void *field_pointer(void *base, int offset)
{
	return *(void **)((unsigned char *)base + offset);
}

static Int field_int(void *base, int offset)
{
	return *(Int *)((unsigned char *)base + offset);
}

static Real *field_real(void *base, int offset)
{
	return (Real *)((unsigned char *)base + offset);
}

static UnsignedInt display_dimension(void *display, UnsignedInt slot)
{
	DisplayDimension function = (DisplayDimension)(*(void ***)display)[slot];
	return function(display, 0);
}

static void apply_hor_plus(void *view)
{
	if (view == 0 || view != TheTacticalView || TheDisplay == 0)
		return;

	void *camera = field_pointer(view, VIEW_CAMERA);
	UnsignedInt display_width = display_dimension(TheDisplay, DISPLAY_GET_WIDTH_SLOT);
	UnsignedInt display_height = display_dimension(TheDisplay, DISPLAY_GET_HEIGHT_SLOT);
	Int width = field_int(view, VIEW_WIDTH);
	if (camera == 0 || display_width == 0 || display_height == 0 || width <= 0)
		return;

	// Re-run the retail tangent calculation for the current zoom/FOV and the
	// current view-width fraction. The camera's AspectRatio has already been
	// set by the retail caller when this runs.
	Real horizontal_fov = *field_real(view, VIEW_FOV) * (Real)width / (Real)display_width;
	c_set_view_plane(camera, 0, horizontal_fov, -1.0f);

	// Scaling both native half-extents by displayAspect/(4/3) is equivalent to
	// the reference-plane construction: it keeps the 4:3 vertical extent and
	// reveals the additional horizontal world at wider display ratios. No table
	// or clamp.
	Real display_scale = ((Real)display_width / (Real)display_height) * 0.75f;
	*field_real(camera, CAMERA_VIEW_PLANE_MIN_X) *= display_scale;
	*field_real(camera, CAMERA_VIEW_PLANE_MIN_Y) *= display_scale;
	*field_real(camera, CAMERA_VIEW_PLANE_MAX_X) *= display_scale;
	*field_real(camera, CAMERA_VIEW_PLANE_MAX_Y) *= display_scale;
	*(unsigned char *)((unsigned char *)camera + CAMERA_FRUSTUM_VALID) = 0;
}

// BFME W3DView::setWidth epilogue at RVA 0x0073DDF8: ESI still holds the
// W3DView after the retail Set_View_Plane call and before pop esi.
extern "C" __declspec(dllexport) void __cdecl horplus_set_width_tail(void *view)
{
	apply_hor_plus(view);
}

// CameraClass::Set_Aspect_Ratio return at RVA 0x00931365. ECX remains the
// camera through this no-call retail body; the pointer gate excludes all other
// camera instances and leaves the 2D/UI/cinematic cameras alone.
extern "C" __declspec(dllexport) void __cdecl horplus_set_aspect_return(void *camera)
{
	void *view = TheTacticalView;
	if (view != 0 && field_pointer(view, VIEW_CAMERA) == camera)
		apply_hor_plus(view);
}

// CameraClass::Set_Transform epilogue at RVA 0x00931304: ESI is the camera
// saved by the retail body. This runs after buildCameraTransform has updated
// m_FOV, covering real zoom and the shared scripted/slaved camera path.
extern "C" __declspec(dllexport) void __cdecl horplus_set_transform_tail(void *camera)
{
	void *view = TheTacticalView;
	if (view != 0 && field_pointer(view, VIEW_CAMERA) == camera)
		apply_hor_plus(view);
}
