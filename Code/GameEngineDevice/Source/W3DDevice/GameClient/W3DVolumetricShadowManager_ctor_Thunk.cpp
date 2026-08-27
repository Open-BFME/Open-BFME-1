// cl: /DNDEBUG /MD /EHsc

class W3DShadowGeometryManager { char m_storage[8]; public: W3DShadowGeometryManager(); };
class W3DBufferManager { char m_storage[0x4265c]; public: W3DBufferManager(); };
extern W3DBufferManager *TheW3DBufferManager;
struct ShadowPool { bool allocate(int, int); char m_storage[8]; int available; };
extern ShadowPool ShadowPoolA;
extern ShadowPool ShadowPoolB;
extern int ShadowPoolALimit;
extern int ShadowPoolBLimit;

class W3DVolumetricShadowManager {
	void *m_shadowList;
	void *m_dynamicShadowVolumesToRender;
	W3DShadowGeometryManager *m_W3DShadowGeometryManager;
public:
	W3DVolumetricShadowManager();
};

// ??0W3DVolumetricShadowManager@@QAE@XZ
W3DVolumetricShadowManager::W3DVolumetricShadowManager()
	: m_shadowList(0), m_dynamicShadowVolumesToRender(0),
	  m_W3DShadowGeometryManager(new W3DShadowGeometryManager)
{
	TheW3DBufferManager = new W3DBufferManager;
	if (ShadowPoolA.available < 1000 && ShadowPoolA.allocate(1000, 0) &&
		ShadowPoolA.available < ShadowPoolALimit)
		ShadowPoolALimit = ShadowPoolA.available;
	if (ShadowPoolB.available < 1000 && ShadowPoolB.allocate(1000, 0) &&
		ShadowPoolB.available < ShadowPoolBLimit)
		ShadowPoolBLimit = ShadowPoolB.available;
}
