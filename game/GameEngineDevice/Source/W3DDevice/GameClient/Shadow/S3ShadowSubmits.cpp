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
// Each body reaches a different helper; all twenty-one are known by address
// alone and are pinned here.

class Gen_00790310;
void bfmeHandle_00790310(Gen_00790310 *owner, void *argument);		// ILT 0x0003883E

class Gen_00790330;
void bfmeHandle_00790330(Gen_00790330 *owner, void *argument);		// ILT 0x000011A4

class Gen_00790b60;
void bfmeHandle_00790b60(Gen_00790b60 *owner, void *argument);		// ILT 0x0000C036

class GameWindow;
class WinInstanceData;
void W3DGadgetComboBoxImageDraw(GameWindow *window, WinInstanceData *instData);

class Gen_007916f0;
void bfmeHandle_007916f0(Gen_007916f0 *owner, void *argument);		// ILT 0x000148BC

class Gen_00791710;
void bfmeHandle_00791710(Gen_00791710 *owner, void *argument);		// ILT 0x0001E137

class Gen_00792f60;
void bfmeHandle_00792f60(Gen_00792f60 *owner, void *argument);		// ILT 0x00038311

class Gen_00792f80;
void bfmeHandle_00792f80(Gen_00792f80 *owner, void *argument);		// ILT 0x0003BB15

class Gen_00793a70;
void bfmeHandle_00793a70(Gen_00793a70 *owner, void *argument);		// ILT 0x0000CF45

class Gen_00795ec0;
void bfmeHandle_00795ec0(Gen_00795ec0 *owner, void *argument);		// ILT 0x00033E1F

class Gen_00795fd0;
void bfmeHandle_00795fd0(Gen_00795fd0 *owner, void *argument);		// ILT 0x0001D6B0

class Gen_007969c0;
void bfmeHandle_007969c0(Gen_007969c0 *owner, void *argument);		// ILT 0x00037E98

class Gen_007969e0;
void bfmeHandle_007969e0(Gen_007969e0 *owner, void *argument);		// ILT 0x00018327

class Gen_00797000;
void bfmeHandle_00797000(Gen_00797000 *owner, void *argument);		// ILT 0x00011847

class Gen_00797020;
void bfmeHandle_00797020(Gen_00797020 *owner, void *argument);		// ILT 0x00008C2E

class Gen_007983b0;
void bfmeHandle_007983b0(Gen_007983b0 *owner, void *argument);		// ILT 0x0003A684

class Gen_007983d0;
void bfmeHandle_007983d0(Gen_007983d0 *owner, void *argument);		// ILT 0x00039E55

class Gen_007995e0;
void bfmeHandle_007995e0(Gen_007995e0 *owner, void *argument);		// ILT 0x0003201F

class Gen_00799600;
void bfmeHandle_00799600(Gen_00799600 *owner, void *argument);		// ILT 0x00023056

class Gen_00799c90;
void bfmeHandle_00799c90(Gen_00799c90 *owner, void *argument);		// ILT 0x0002C7AA

class Gen_00799cb0;
void bfmeHandle_00799cb0(Gen_00799cb0 *owner, void *argument);		// ILT 0x0003DC7B

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
	bfmeHandle_00790310(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00790330@@QAEHPAX@Z
int Gen_00790330::bfmeSubmit(void *argument)
{
	bfmeHandle_00790330(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00790b60@@QAEHPAX@Z
int Gen_00790b60::bfmeSubmit(void *argument)
{
	bfmeHandle_00790b60(this, argument);

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
	bfmeHandle_007916f0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00791710@@QAEHPAX@Z
int Gen_00791710::bfmeSubmit(void *argument)
{
	bfmeHandle_00791710(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00792f60@@QAEHPAX@Z
int Gen_00792f60::bfmeSubmit(void *argument)
{
	bfmeHandle_00792f60(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00792f80@@QAEHPAX@Z
int Gen_00792f80::bfmeSubmit(void *argument)
{
	bfmeHandle_00792f80(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00793a70@@QAEHPAX@Z
int Gen_00793a70::bfmeSubmit(void *argument)
{
	bfmeHandle_00793a70(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00795ec0@@QAEHPAX@Z
int Gen_00795ec0::bfmeSubmit(void *argument)
{
	bfmeHandle_00795ec0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00795fd0@@QAEHPAX@Z
int Gen_00795fd0::bfmeSubmit(void *argument)
{
	bfmeHandle_00795fd0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_007969c0@@QAEHPAX@Z
int Gen_007969c0::bfmeSubmit(void *argument)
{
	bfmeHandle_007969c0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_007969e0@@QAEHPAX@Z
int Gen_007969e0::bfmeSubmit(void *argument)
{
	bfmeHandle_007969e0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00797000@@QAEHPAX@Z
int Gen_00797000::bfmeSubmit(void *argument)
{
	bfmeHandle_00797000(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00797020@@QAEHPAX@Z
int Gen_00797020::bfmeSubmit(void *argument)
{
	bfmeHandle_00797020(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_007983b0@@QAEHPAX@Z
int Gen_007983b0::bfmeSubmit(void *argument)
{
	bfmeHandle_007983b0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_007983d0@@QAEHPAX@Z
int Gen_007983d0::bfmeSubmit(void *argument)
{
	bfmeHandle_007983d0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_007995e0@@QAEHPAX@Z
int Gen_007995e0::bfmeSubmit(void *argument)
{
	bfmeHandle_007995e0(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00799600@@QAEHPAX@Z
int Gen_00799600::bfmeSubmit(void *argument)
{
	bfmeHandle_00799600(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00799c90@@QAEHPAX@Z
int Gen_00799c90::bfmeSubmit(void *argument)
{
	bfmeHandle_00799c90(this, argument);

	return 1;
}

// ?bfmeSubmit@Gen_00799cb0@@QAEHPAX@Z
int Gen_00799cb0::bfmeSubmit(void *argument)
{
	bfmeHandle_00799cb0(this, argument);

	return 1;
}
