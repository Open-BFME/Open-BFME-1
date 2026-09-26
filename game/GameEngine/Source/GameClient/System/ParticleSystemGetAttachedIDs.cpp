// cl: /O2
// Open-BFME: ParticleSystem attached-ID accessors, retail 0x00801140 and
// 0x00801150 (7 bytes each).  ParticleSys.h declares this adjacent pair, and
// the exact BFME attachToDrawable/attachToObject bodies independently place
// their ID fields at +0xB4 and +0xB8.

enum DrawableID { INVALID_DRAWABLE_ID = 0 };
enum ObjectID { INVALID_OBJECT_ID = 0 };

class ParticleSystem
{
public:
	DrawableID getAttachedDrawable();
	ObjectID getAttachedObject();

private:
	unsigned char m_beforeAttachedDrawableID[0xB4];
	DrawableID m_attachedToDrawableID;
	ObjectID m_attachedToObjectID;
};

DrawableID ParticleSystem::getAttachedDrawable()
{
	return m_attachedToDrawableID;
}

ObjectID ParticleSystem::getAttachedObject()
{
	return m_attachedToObjectID;
}
