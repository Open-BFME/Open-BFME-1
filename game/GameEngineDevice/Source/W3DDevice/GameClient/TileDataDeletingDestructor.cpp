// cl: /O2

// The exact constructor at 0x006D68A0 identifies this 30-byte scalar-deleting destructor.
class TileData
{
public:
	virtual ~TileData();
};

void forceTileDataDeletingDestructor()
{
	TileData value;
}
