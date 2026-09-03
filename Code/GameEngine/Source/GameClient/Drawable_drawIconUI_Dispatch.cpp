// BFME's five-way icon pass dispatch.  These are the surviving retail ILT
// entry points; the dispatch itself is the recovered clean C++ body.

class Drawable
{
public:
	void drawIconUI(int group);
	void drawIconUI2(int group);
	void drawIconUI3(int group);

private:
	void drawHealthBar();
	void drawEmoticon();
	void drawCaption();
	void drawConstructPercent();
	void drawHealing();
	void drawBombed();
	void drawEnthusiastic();
	void drawDemoralized();
	void drawDisabled();
	void drawAmmo();
	void drawContained();
	void drawVeterancy();
};

void Drawable::drawIconUI(int group)
{
	switch (group)
	{
	case 0:
		drawHealthBar();
		drawEmoticon();
		drawCaption();
		drawConstructPercent();
		break;
	case 1:
		drawHealing();
		drawBombed();
		drawEnthusiastic();
		drawDemoralized();
		break;
	case 2:
		drawDisabled();
		break;
	case 3:
	case 4:
		drawAmmo();
		break;
	}
}

typedef void (Drawable::*DrawableStage)();
extern void j_00005bd7();
extern void j_0003d3e8();
extern void j_00022a11();
extern void j_00034130();
extern void j_0003d514();
extern void j_0002f6e9();
extern void j_00038bae();
extern void j_00012e2c();
extern void j_00038aaa();
extern void j_00022782();

union DrawableStageValue
{
	void (*freeFunction)();
	DrawableStage memberFunction;
};

static DrawableStageValue const s_stage00 = { j_00005bd7 };
static DrawableStageValue const s_stage01 = { j_0003d3e8 };
static DrawableStageValue const s_stage02 = { j_00022a11 };
static DrawableStageValue const s_stage03 = { j_00034130 };
static DrawableStageValue const s_stage04 = { j_0003d514 };
static DrawableStageValue const s_stage05 = { j_0002f6e9 };
static DrawableStageValue const s_stage06 = { j_00038bae };
static DrawableStageValue const s_stage07 = { j_00012e2c };
static DrawableStageValue const s_stage08 = { j_00038aaa };
static DrawableStageValue const s_stage09 = { j_00022782 };

void Drawable::drawIconUI2(int group)
{
	switch (group)
	{
	case 0:
		(this->*s_stage00.memberFunction)(); (this->*s_stage01.memberFunction)(); (this->*s_stage02.memberFunction)(); (this->*s_stage03.memberFunction)(); break;
	case 1:
		(this->*s_stage04.memberFunction)(); (this->*s_stage05.memberFunction)(); (this->*s_stage06.memberFunction)(); (this->*s_stage07.memberFunction)(); break;
	case 2:
		(this->*s_stage08.memberFunction)(); break;
	case 3:
	case 4:
		(this->*s_stage09.memberFunction)(); break;
	}
}

__forceinline void __fastcall invokeDrawableStage(Drawable *self, void (*function)())
{
	if (self != 0)
		function();
}

void Drawable::drawIconUI3(int group)
{
	switch (group)
	{
	case 0:
		invokeDrawableStage(this, j_00005bd7);
		invokeDrawableStage(this, j_0003d3e8);
		invokeDrawableStage(this, j_00022a11);
		invokeDrawableStage(this, j_00034130);
		break;
	case 1:
		invokeDrawableStage(this, j_0003d514);
		invokeDrawableStage(this, j_0002f6e9);
		invokeDrawableStage(this, j_00038bae);
		invokeDrawableStage(this, j_00012e2c);
		break;
	case 2:
		invokeDrawableStage(this, j_00038aaa);
		break;
	case 3:
	case 4:
		invokeDrawableStage(this, j_00022782);
		break;
	}
}
