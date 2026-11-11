// Twenty-one 22-byte bodies with one shape:
//
//     mov eax, [esp + 4]
//     push eax
//     push ecx
//     call <helper>
//     add esp, 8
//     mov eax, 1
//     ret 4
//
// this is pushed as the FIRST argument (pushed last) and the caller cleans
// eight bytes, so the helper is __cdecl taking this and the argument in that
// order. mov eax,1 rather than mov al,1 makes the return int-width, the same
// distinction Player::iterateObjects turned on.
//
// The ledger had every one of these split in two: fourteen bytes ending in
// add esp,8 with no ret, and the return-TRUE tail claimed separately as an
// alias of W3DShadowGeometry::init. Those aliases were retracted in the
// previous commit.
//
class GameWindow;
class WinInstanceData;
void W3DGadgetCheckBoxDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetCheckBoxImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetComboBoxDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetComboBoxImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetHorizontalSliderDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetHorizontalSliderImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetListBoxDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetListBoxImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetProgressBarDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetPushButtonDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetPushButtonImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetRadioButtonDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetRadioButtonImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetStaticTextDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetStaticTextImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetTabControlDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetTabControlImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetTextEntryDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetTextEntryImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetVerticalSliderDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetVerticalSliderImageDraw(GameWindow *window, WinInstanceData *instData);

class Gen_00790310
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00790330
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00790b60
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00790b80
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_007916f0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00791710
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00792f60
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00792f80
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00793a70
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00795ec0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00795fd0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_007969c0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_007969e0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00797000
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00797020
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_007983b0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_007983d0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_007995e0
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00799600
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00799c90
{
public:
	int bfmeSubmit(void *argument);
};

class Gen_00799cb0
{
public:
	int bfmeSubmit(void *argument);
};

// ?bfmeSubmit@Gen_00790310@@QAEHPAX@Z
int Gen_00790310::bfmeSubmit(void *argument)
{
	W3DGadgetCheckBoxDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00790330@@QAEHPAX@Z
int Gen_00790330::bfmeSubmit(void *argument)
{
	W3DGadgetCheckBoxImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00790b60@@QAEHPAX@Z
int Gen_00790b60::bfmeSubmit(void *argument)
{
	W3DGadgetComboBoxDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00790b80@@QAEHPAX@Z
int Gen_00790b80::bfmeSubmit(void *argument)
{
	W3DGadgetComboBoxImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_007916f0@@QAEHPAX@Z
int Gen_007916f0::bfmeSubmit(void *argument)
{
	W3DGadgetHorizontalSliderDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00791710@@QAEHPAX@Z
int Gen_00791710::bfmeSubmit(void *argument)
{
	W3DGadgetHorizontalSliderImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00792f60@@QAEHPAX@Z
int Gen_00792f60::bfmeSubmit(void *argument)
{
	W3DGadgetListBoxDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00792f80@@QAEHPAX@Z
int Gen_00792f80::bfmeSubmit(void *argument)
{
	W3DGadgetListBoxImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00793a70@@QAEHPAX@Z
int Gen_00793a70::bfmeSubmit(void *argument)
{
	W3DGadgetProgressBarDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00795ec0@@QAEHPAX@Z
int Gen_00795ec0::bfmeSubmit(void *argument)
{
	W3DGadgetPushButtonDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00795fd0@@QAEHPAX@Z
int Gen_00795fd0::bfmeSubmit(void *argument)
{
	W3DGadgetPushButtonImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_007969c0@@QAEHPAX@Z
int Gen_007969c0::bfmeSubmit(void *argument)
{
	W3DGadgetRadioButtonDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_007969e0@@QAEHPAX@Z
int Gen_007969e0::bfmeSubmit(void *argument)
{
	W3DGadgetRadioButtonImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00797000@@QAEHPAX@Z
int Gen_00797000::bfmeSubmit(void *argument)
{
	W3DGadgetStaticTextDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00797020@@QAEHPAX@Z
int Gen_00797020::bfmeSubmit(void *argument)
{
	W3DGadgetStaticTextImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_007983b0@@QAEHPAX@Z
int Gen_007983b0::bfmeSubmit(void *argument)
{
	W3DGadgetTabControlDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_007983d0@@QAEHPAX@Z
int Gen_007983d0::bfmeSubmit(void *argument)
{
	W3DGadgetTabControlImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_007995e0@@QAEHPAX@Z
int Gen_007995e0::bfmeSubmit(void *argument)
{
	W3DGadgetTextEntryDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00799600@@QAEHPAX@Z
int Gen_00799600::bfmeSubmit(void *argument)
{
	W3DGadgetTextEntryImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00799c90@@QAEHPAX@Z
int Gen_00799c90::bfmeSubmit(void *argument)
{
	W3DGadgetVerticalSliderDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}

// ?bfmeSubmit@Gen_00799cb0@@QAEHPAX@Z
int Gen_00799cb0::bfmeSubmit(void *argument)
{
	W3DGadgetVerticalSliderImageDraw((GameWindow *)this, (WinInstanceData *)argument);

	return 1;
}
