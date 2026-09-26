class BfmeDisplayXL
{
public:
	virtual void bfmeD00XL();
	virtual void bfmeD01XL();
	virtual void bfmeD02XL();
	virtual void bfmeD03XL();
	virtual void bfmeD04XL();
	virtual void bfmeD05XL();
	virtual void bfmeD06XL();
	virtual void bfmeD07XL();
	virtual void bfmeD08XL();
	virtual void bfmeD09XL();
	virtual void bfmeD10XL();
	virtual void bfmeD11XL();
	virtual void bfmeD12XL();
	virtual void bfmeD13XL();
	virtual void bfmeD14XL();
	virtual void bfmeD15XL();
	virtual void bfmeD16XL();
	virtual void bfmeD17XL();
	virtual void bfmeD18XL();
	virtual void bfmeD19XL();
	virtual void bfmeD20XL();
	virtual void bfmeD21XL();
	virtual void bfmeD22XL();
	virtual void bfmeD23XL();
	virtual void bfmeD24XL();
	virtual void bfmeD25XL();
	virtual void bfmeD26XL();
	virtual void bfmeD27XL();
	virtual void bfmeD28XL();
	virtual void bfmeD29XL();
	virtual void bfmeD30XL();
	virtual void bfmeD31XL();
	virtual void bfmeD32XL();
	virtual void bfmeD33XL();
	virtual void bfmeD34XL();
	virtual void bfmeD35XL();
	virtual void bfmeD36XL();
	virtual void bfmeD37XL();
	virtual void bfmeD38XL();
	virtual void bfmeD39XL();
	virtual void bfmeD40XL();
	virtual void bfmeD41XL();
	virtual void bfmeD42XL();
	virtual void bfmeD43XL();
	virtual void bfmeBeginXL();
	virtual void bfmeD45XL();
	virtual void bfmeRectXL(float left, float top, float right, float bottom, int a, int b);
	virtual void bfmeD47XL();
	virtual void bfmeD48XL();
	virtual void bfmeD49XL();
	virtual void bfmeD50XL();
	virtual void bfmeD51XL();
	virtual void bfmeD52XL();
	virtual void bfmeD53XL();
	virtual void bfmeD54XL();
	virtual void bfmeEndXL();
};

extern BfmeDisplayXL *TheBfmeDisplayXL;

void __stdcall bfmeDrawXL(int a1, int a2, int a3, int a4, int a5, int a6)
{
	BfmeDisplayXL *display = TheBfmeDisplayXL;

	TheBfmeDisplayXL->bfmeBeginXL();
	display->bfmeRectXL((float)a3, (float)a4, (float)a5, (float)a6, a2, a1);
	display->bfmeEndXL();
}
