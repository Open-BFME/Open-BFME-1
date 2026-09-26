// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define TGA_USES_WWLIB_FILE_CLASSES
#include "targa.h"
#include "wwfile.h"
#include "ffactory.h"

#include <stdlib.h>

inline void Targa::Close(void)
{
	if (TGAFile) {
		TGAFile->Close();
		_TheFileFactory->Return_File(TGAFile);
		TGAFile = NULL;
	}
}

// ?Load@Targa@@QAEJPBDJ_N@Z
long Targa::Load(const char* name, long flags, bool invert_image)
{
	long size;
	long error = 0;

	if (Open(name, TGA_READMODE) == 0) {
		if ((flags & TGAF_PAL) && (Header.ColorMapType == 1)) {
			if ((mPalette != NULL) && (mFlags & TGAF_PAL)) {
				free(mPalette);
				mPalette = NULL;
				mFlags &= ~TGAF_PAL;
			}
			if ((mPalette == NULL) && !(mFlags & TGAF_PAL)) {
				size = (Header.CMapLength * (Header.CMapDepth >> 3));
				if (size != 0) {
					if ((mPalette = (char *)malloc(size)) != NULL) {
						mFlags |= TGAF_PAL;
					} else {
						error = TGAERR_NOMEM;
					}
				}
			}
		}
		if (!error && (flags & TGAF_IMAGE)) {
			if ((mImage != NULL) && (mFlags & TGAF_IMAGE)) {
				free(mImage);
				mImage = NULL;
				mFlags &= ~TGAF_IMAGE;
			}
			if ((mImage == NULL) && !(mFlags & TGAF_IMAGE)) {
				size = ((Header.Width * Header.Height) * TGA_BytesPerPixel(Header.PixelDepth));
				if (size != 0) {
					if ((mImage = (char *)malloc(size)) != NULL) {
						mFlags |= TGAF_IMAGE;
					} else {
						error = TGAERR_NOMEM;
					}
				}
			}
		}
		if (!error) {
			error = Load(name, mPalette, mImage, invert_image);
		}
		Close();
	} else {
		error = TGAERR_OPEN;
	}
	return error;
}
