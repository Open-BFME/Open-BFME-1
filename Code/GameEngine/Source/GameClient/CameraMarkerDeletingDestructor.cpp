// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: CameraMarker scalar-deleting destructor at retail RVA 0x0045C870
// (30 bytes). CameraMarkerList's exact find, remove, and clear paths establish
// the owned node type and call its matched destructor through ILT 0x00028984.
// This wrapper reproduces that destructor call followed by conditional delete.

class CameraMarker
{
public:
	~CameraMarker();
};

void forceCameraMarkerDelete(CameraMarker *marker)
{
	delete marker;
}
