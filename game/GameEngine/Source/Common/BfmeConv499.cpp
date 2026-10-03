extern "C" unsigned char bfmeTagBNH[];

class BfmeThingBNH;
class BFMEWaterTrackTextureHandle;

BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *name, int mipCount, int format);
typedef void (__cdecl *BfmeGetWaterTrackTextureOutput)(void *result, char *name, int mipCount, int format);

class BfmeThingBNH
{
public:
	BfmeThingBNH *bfmeGoBNH(void *what);
};

BfmeThingBNH *BfmeThingBNH::bfmeGoBNH(void *what)
{
	((BfmeGetWaterTrackTextureOutput)BFMEGetWaterTrackTexture)(this, (char *)bfmeTagBNH, 0, 0);
	return this;
}
