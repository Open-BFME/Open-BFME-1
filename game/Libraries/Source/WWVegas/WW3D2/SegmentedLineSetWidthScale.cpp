// cl: /DNDEBUG /MD /EHsc
// BFME adds a second, clamped line-renderer value to Set_Width.

class SegmentedLineClass
{
public:
	void Set_Width(float width, float scale);
};

// ?Set_Width@SegmentedLineClass@@QAEXMM@Z
void SegmentedLineClass::Set_Width(float width, float scale)
{
	*(float *)((char *)this + 0xe8) = width > 0.0f ? width : 0.0f;
	*(float *)((char *)this + 0xfc) = scale > 0.0f ? scale : 0.0f;
	*(unsigned int *)((char *)this + 0x10) &= ~0x20000u;
}
