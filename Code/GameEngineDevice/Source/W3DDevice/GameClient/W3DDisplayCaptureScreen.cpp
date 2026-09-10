/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Open-BFME: real C++ reconstruction of W3DDisplay::captureScreen.
//
// The retail body is reached by the matched W3DDisplay::takeScreenShot
// caller.  The local COM declaration preserves the D3D9 surface slots used
// by the front-buffer copy without changing a shared WW3D header.
// Full501B ends after ret8 at0x006EAA82 through0x006EAA85 exclusive.
// Device guard calls existing903090/905B10; frontbuffer904FF0 returns
// the D3D9 surface whose GetDesc/LockRect/Release slots are30/34/08.

#include <windows.h>

typedef unsigned int UnsignedInt;

class BfmeAwakenLog;

class IDirect3DSurface9
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual unsigned long __stdcall Release(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual long __stdcall GetDesc(void *desc);
	virtual long __stdcall LockRect(void *locked_rect, const RECT *rect, unsigned long flags);
};

class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer(void);
};

class BfmeAwakenLog
{
public:
	virtual BfmeAwakenLog *slot00(int value);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual BfmeAwakenLog *slot38(const char *value);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual BfmeAwakenLog *slot4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual BfmeAwakenLog *slot6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);
extern HWND ApplicationHWnd;

class BfmeRadarCaptureGuard
{
public:
	BfmeRadarCaptureGuard(void) { W3DRadarResetLock(); }
	~BfmeRadarCaptureGuard(void) { bfmeUnlock1179(); }
};

static __forceinline void BfmeCaptureErrorCode(int result)
{
	if (result != 0)
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")
			->slot00(result)->slot4c(1);
	}
}

class W3DDisplay
{
protected:
	void captureScreen(char *image, UnsignedInt rowBytes);
};

// ?captureScreen@W3DDisplay@@IAEXPADI@Z
void W3DDisplay::captureScreen(char *image, UnsignedInt rowBytes)
{
	Sleep(500);
	BfmeRadarCaptureGuard guard;

	IDirect3DSurface9 *fb = DX8Wrapper::_Get_DX8_Front_Buffer();
	char desc[32];
	fb->GetDesc(desc);

	RECT bounds;
	POINT point;
	GetClientRect(ApplicationHWnd, &bounds);
	point.x = bounds.left;
	point.y = bounds.top;
	ClientToScreen(ApplicationHWnd, &point);
	bounds.left = point.x;
	bounds.top = point.y;
	point.x = bounds.right;
	point.y = bounds.bottom;
	ClientToScreen(ApplicationHWnd, &point);
	bounds.right = point.x;
	bounds.bottom = point.y;

	struct BfmeLockedRect
	{
		long pitch;
		void *bits;
	} locked;

	BfmeCaptureErrorCode(fb->LockRect(&locked, &bounds, 0x10));

	unsigned int x, y, index, index2, width, height;
	width = bounds.right - bounds.left;
	height = bounds.bottom - bounds.top;

	for (y = 0; y < height; ++y)
	{
		for (x = 0; x < width; ++x)
		{
			index = 3 * x + y * rowBytes;
			index2 = y * locked.pitch + 4 * x;
			image[index] = *((char *)locked.bits + index2 + 0);
			image[index + 1] = *((char *)locked.bits + index2 + 1);
			image[index + 2] = *((char *)locked.bits + index2 + 2);
		}
	}

	fb->Release();
}
