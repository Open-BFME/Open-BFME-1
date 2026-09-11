// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean BFME body for WW3D::End_Render at retail RVA 0x008FD880.
//
// BFME writes the successful result through AL. The public decorated name
// retains the WW3DErrorType spelling, so this source uses a byte-sized ABI view.

typedef bool WW3DErrorType;
const WW3DErrorType WW3D_ERROR_OK = true;

class SortingRendererClass
{
public:
	static void Flush();
};

class DX8Wrapper
{
public:
	static void End_Scene(bool flip_frame);
	static void Invalidate_Cached_Render_States();
};

namespace Debug_Statistics
{
	void End_Statistics();
}

class WW3D
{
public:
	static WW3DErrorType End_Render(bool flip_frame);
	static void Activate_Snapshot(bool enabled) { SnapshotActivated = enabled; }

	static bool IsInitted;
	static bool IsRendering;
	static bool SnapshotActivated;
	static int FrameCount;
};

#define WWPROFILE(value)
#define WWASSERT(value)
#define SNAPSHOT_SAY(value)

WW3DErrorType WW3D::End_Render(bool flip_frame)
{
	if (!IsInitted) {
		return(WW3D_ERROR_OK);
	}

	WWPROFILE("WW3D::End_Render");
	WWASSERT(IsRendering);
	WWASSERT(IsInitted);

	SortingRendererClass::Flush();
	IsRendering = false;

	{
		WWPROFILE("DX8Wrapper::End_Scene");
		DX8Wrapper::End_Scene(flip_frame);
	}

	FrameCount++;

	{
		WWPROFILE("End_Statistics");
		Debug_Statistics::End_Statistics();
	}

	SNAPSHOT_SAY(("==========================================\r\n"));
	SNAPSHOT_SAY(("========== WW3D::End_Render ==============\r\n"));
	SNAPSHOT_SAY(("==========================================\r\n\r\n"));

	WW3D::Activate_Snapshot(false);
	DX8Wrapper::Invalidate_Cached_Render_States();

	return WW3D_ERROR_OK;
}
