// ?drawIconUI@Drawable@@QAEXH@Z
// partial score=0.9 date=2026-09-03
// BFME Drawable icon-dispatch helper.  The retail ILT callees are legacy
// entry points whose ABI consumes this in ECX although their generated C++
// declarations are cdecl-shaped.

struct DrawableIconStage
{
	void stage00(); void stage01(); void stage02(); void stage03(); void stage04();
	void stage05(); void stage06(); void stage07(); void stage08(); void stage09();
};

class Drawable
{
public:
	void drawIconUI(int group);
	void stage00(); void stage01(); void stage02(); void stage03(); void stage04();
	void stage05(); void stage06(); void stage07(); void stage08(); void stage09();
};

void Drawable::drawIconUI(int group)
{
	switch (group)
	{
	case 0:
		stage00(); stage01(); stage02(); stage03();
		break;
	case 1:
		stage04(); stage05(); stage06(); stage07();
		break;
	case 2:
		stage08();
		break;
	case 3:
	case 4:
		stage09();
		break;
	}
}
