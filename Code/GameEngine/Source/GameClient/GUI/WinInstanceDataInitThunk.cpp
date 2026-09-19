// Retail RVA 0x00021EC7 tail-jumps to WinInstanceData::init at 0x00499850.

class WinInstanceData
{
public:
	void init();
};

class WinInstanceDataInitThunk
{
public:
	void forward();
};

void WinInstanceDataInitThunk::forward()
{
	((WinInstanceData *)this)->init();
}
