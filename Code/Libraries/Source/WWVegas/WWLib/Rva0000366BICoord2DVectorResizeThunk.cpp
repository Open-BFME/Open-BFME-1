// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// The carved boundary at 0x0000366B jumps to the matched ICoord2D vector
// resize body at 0x00453DF0.  This method keeps the proven resize ABI and
// lets MSVC emit the direct tail jump for the thunk.

namespace _STL
{
class ICoord2DVectorResizeShim
{
public:
	void resize(unsigned int newSize);
};
}

class Rva0000366BICoord2DVectorResizeThunk
{
public:
	void forward(unsigned int newSize);
};

void Rva0000366BICoord2DVectorResizeThunk::forward(unsigned int newSize)
{
	((_STL::ICoord2DVectorResizeShim *)this)->resize(newSize);
}
