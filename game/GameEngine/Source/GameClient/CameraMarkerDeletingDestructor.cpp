// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor of the node in View's +0x80 marker
// list, retail RVA 0x0045C870 (30 bytes). View's matched find, remove and clear
// paths (targets/game/reverse/identity_evidence/0045c9e0.md) establish the owned node type
// and call its destructor through ILT 0x00028984. This wrapper reproduces that
// destructor call followed by conditional delete.

class Rva0045C9E0CameraMarker
{
public:
	~Rva0045C9E0CameraMarker();
};

void forceRva0045C9E0CameraMarkerDelete(Rva0045C9E0CameraMarker *marker)
{
	delete marker;
}
