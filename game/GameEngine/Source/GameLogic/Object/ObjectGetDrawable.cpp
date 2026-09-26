// BFME Object::getDrawable, retail 0x001BE440.  Unlike the Zero Hour inline
// accessor, BFME exposes this through Object vtable 0x0109EE58 slot +0x28.

class Drawable;

class Object
{
public:
	virtual Drawable *getDrawable() const;

private:
	unsigned char m_pad[ 0x7C ];
	Drawable *m_drawable;
};

Drawable *Object::getDrawable() const
{
	return m_drawable;
}
