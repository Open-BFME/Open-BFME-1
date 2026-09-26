class BfmeDisplayXW
{
public:
	virtual void bfmeD00XW();
	virtual void bfmeD01XW();
	virtual void bfmeD02XW();
	virtual void bfmeD03XW();
	virtual void bfmeD04XW();
	virtual void bfmeD05XW();
	virtual void bfmeD06XW();
	virtual void bfmeD07XW();
	virtual void bfmeD08XW();
	virtual void bfmeD09XW();
	virtual void bfmeD10XW();
	virtual void bfmeD11XW();
	virtual void bfmeD12XW();
	virtual void bfmeD13XW();
	virtual void bfmeD14XW();
	virtual void bfmeD15XW();
	virtual void bfmeD16XW();
	virtual void bfmeD17XW();
	virtual void bfmeD18XW();
	virtual void bfmeD19XW();
	virtual void bfmeD20XW();
	virtual void bfmeD21XW();
	virtual void bfmeD22XW();
	virtual void bfmeD23XW();
	virtual void bfmeD24XW();
	virtual void bfmeD25XW();
	virtual void bfmeD26XW();
	virtual void bfmeD27XW();
	virtual void bfmeD28XW();
	virtual void bfmeD29XW();
	virtual void bfmeD30XW();
	virtual void bfmeD31XW();
	virtual void bfmeD32XW();
	virtual void bfmeD33XW();
	virtual void bfmeD34XW();
	virtual void bfmeD35XW();
	virtual void bfmeD36XW();
	virtual void bfmeD37XW();
	virtual void bfmeD38XW();
	virtual void bfmeD39XW();
	virtual void bfmeD40XW();
	virtual void bfmeD41XW();
	virtual void bfmeD42XW();
	virtual void bfmeD43XW();
	virtual void bfmeBeginXW();
	virtual void bfmeD45XW();
	virtual void bfmeD46XW();
	virtual void bfmeD47XW();
	virtual void bfmeD48XW();
	virtual void bfmeD49XW();
	virtual void bfmeD50XW();
	virtual void bfmeD51XW();
	virtual void bfmeD52XW();
	virtual void bfmeRectXW(int a, float left, float top, float right, float bottom, int b, int c);
	virtual void bfmeD54XW();
	virtual void bfmeEndXW();
};

extern BfmeDisplayXW *TheBfmeDisplayXW;

void __stdcall bfmeDrawXW(int a1, int a2, int a3, int a4, int a5, int a6)
{
	BfmeDisplayXW *display = TheBfmeDisplayXW;

	TheBfmeDisplayXW->bfmeBeginXW();
	display->bfmeRectXW(a1, (float)a2, (float)a3, (float)a4, (float)a5, a6, 2);
	display->bfmeEndXW();
}
