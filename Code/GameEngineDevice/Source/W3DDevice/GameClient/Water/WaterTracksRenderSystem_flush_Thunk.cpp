class RenderInfoClass;

class WaterTracksRenderSystem
{
public:
	void flush(RenderInfoClass &rinfo);
};

class Rva00014C45WaterTracksFlushThunk
{
public:
	void forward(RenderInfoClass &rinfo);
};

void Rva00014C45WaterTracksFlushThunk::forward(RenderInfoClass &rinfo)
{
	((WaterTracksRenderSystem *)this)->flush(rinfo);
}
