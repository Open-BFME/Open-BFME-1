// BFME W3DView drawable callback at retail RVA 0x0073AD50.
// The W3DView update call passes this callback and the view as user data.
// cl: /DNDEBUG /MD

class View;
class Drawable
{
public:
	void draw(View *view);
};

void drawDrawable(Drawable *draw, void *userData)
{
	draw->draw((View *)userData);
}
