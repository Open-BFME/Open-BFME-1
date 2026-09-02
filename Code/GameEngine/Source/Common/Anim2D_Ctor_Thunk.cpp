// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of Anim2D::Anim2D.

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

class Anim2D;

class Anim2DTemplate
{
public:
	unsigned char m_unreconstructed_00[0x0C];
	const void *m_images;                         // retail this+0x0C
	UnsignedShort m_numFrames;                    // retail this+0x10
	UnsignedShort m_framesBetweenUpdates;         // retail this+0x12
	UnsignedInt m_animMode;                       // retail this+0x14
	Bool m_randomizeStartFrame;                   // retail this+0x18

	UnsignedShort getNumFrames() const { return m_numFrames; }
};

class Anim2DCollection
{
public:
	unsigned char m_unreconstructed_00[0x0C];
	Anim2D *m_instanceList;                       // retail this+0x0C
};

class Image
{
public:
	unsigned char m_unreconstructed_00[0x24];
	Int m_imageWidth;                             // retail this+0x24
	Int m_imageHeight;                            // retail this+0x28
};

class ClientFrameSubsystem
{
public:
	virtual void bfmeVirtualStub00();
	virtual void bfmeVirtualStub01();
	virtual void bfmeVirtualStub02();
	virtual void bfmeVirtualStub03();
	virtual void bfmeVirtualStub04();
	virtual void bfmeVirtualStub05();
	virtual void bfmeVirtualStub06();
	virtual void bfmeVirtualStub07();
	virtual void bfmeVirtualStub08();
	virtual void bfmeVirtualStub09();
	virtual void bfmeVirtualStub10();
	virtual void bfmeVirtualStub11();
	virtual void bfmeVirtualStub12();
	virtual void bfmeVirtualStub13();
	virtual void bfmeVirtualStub14();
	virtual void bfmeVirtualStub15();
	virtual void bfmeVirtualStub16();
	virtual void bfmeVirtualStub17();
	virtual void bfmeVirtualStub18();
	virtual void bfmeVirtualStub19();
	virtual void bfmeVirtualStub20();
	virtual void bfmeVirtualStub21();
	virtual void bfmeVirtualStub22();
	virtual void bfmeVirtualStub23();
	virtual void bfmeVirtualStub24();
	virtual void bfmeVirtualStub25();
	virtual UnsignedInt getFrame();
};

extern ClientFrameSubsystem *TheGameClientClientUpdate;
extern Int __cdecl GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);

class Snapshot
{
public:
	Snapshot() {}
	~Snapshot();


	protected:
	void *m_vtable;
};

class Anim2D : public Snapshot
{
public:
	Anim2D(Anim2DTemplate *, Anim2DCollection *);
	void reset();
	Int getCurrentFrameWidth() const;
	Int getCurrentFrameHeight() const;

private:
	UnsignedShort m_currentFrame;
	UnsignedShort m_unreconstructed_06;
	UnsignedInt m_lastUpdateFrame;
	Anim2DTemplate *m_template;
	UnsignedByte m_status;
	UnsignedByte m_unreconstructed_11;
	UnsignedShort m_minFrame;
	UnsignedShort m_maxFrame;
	UnsignedInt m_framesBetweenUpdates;
	float m_alpha;
	Anim2DCollection *m_collectionSystem;
	Anim2D *m_collectionSystemNext;
	Anim2D *m_collectionSystemPrev;
	Int m_cachedImageWidth;
	Int m_cachedImageHeight;
};

__forceinline Int Anim2D::getCurrentFrameWidth() const
{
	const UnsignedShort frame = m_currentFrame;
	Anim2DTemplate *templateValue = m_template;
	if (frame < templateValue->m_numFrames)
	{
		Image *image = ((Image **)templateValue->m_images)[frame];
		if (image)
			return image->m_imageWidth;
	}
	return 0;
}

__forceinline Int Anim2D::getCurrentFrameHeight() const
{
	const UnsignedShort frame = m_currentFrame;
	Anim2DTemplate *templateValue = m_template;
	if (frame < templateValue->m_numFrames)
	{
		Image *image = ((Image **)templateValue->m_images)[frame];
		if (image)
			return image->m_imageHeight;
	}
	return 0;
}

// ??0Anim2D@@QAE@PAVAnim2DTemplate@@PAVAnim2DCollection@@@Z
Anim2D::Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collectionSystem)
{
	const unsigned int zero = 0;

	m_vtable = (void *)0x0110F29C;
	m_currentFrame = zero;
	m_minFrame = zero;
	m_template = animTemplate;
	m_status = zero;
	m_alpha = 1.0f;

	if (m_template->m_randomizeStartFrame)
	{
		m_currentFrame = (UnsignedShort)GetGameClientRandomValue(
			0, m_template->getNumFrames() - 1, (char *)0x0110F228, 0x1AF);
		m_lastUpdateFrame = TheGameClientClientUpdate->getFrame();
	}
	else
	{
		reset();
	}

	m_maxFrame = m_template->m_numFrames - 1;
	m_framesBetweenUpdates = m_template->m_framesBetweenUpdates;
	m_collectionSystemNext = zero;
	m_collectionSystemPrev = zero;
	m_lastUpdateFrame = zero;
	m_collectionSystem = collectionSystem;

	if (collectionSystem)
	{
		m_collectionSystemPrev = zero;
		m_collectionSystemNext = collectionSystem->m_instanceList;
		if (collectionSystem->m_instanceList)
			collectionSystem->m_instanceList->m_collectionSystemPrev = this;
		collectionSystem->m_instanceList = this;
	}

	m_cachedImageHeight = getCurrentFrameHeight();
	m_cachedImageWidth = getCurrentFrameWidth();
}
