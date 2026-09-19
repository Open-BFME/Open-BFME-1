// cl: /DNDEBUG /MD /EHsc
// Retail 0x0002FA6D is a five-byte tail jump to the matched
// ControlBar::setLowControlBarConfig body at 0x0049E120.

class ControlBarSetLowConfigShim
{
public:
	void apply();
};

class Rva0002FA6DControlBarThunk
{
public:
	void forward();
};

void Rva0002FA6DControlBarThunk::forward()
{
	ControlBarSetLowConfigShim *bar = (ControlBarSetLowConfigShim *)this;
	bar->apply();
}
