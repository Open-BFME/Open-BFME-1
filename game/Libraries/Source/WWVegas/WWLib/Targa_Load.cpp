// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define TGA_USES_WWLIB_FILE_CLASSES
#include "targa.h"
#include "wwfile.h"
#include "ffactory.h"

#include <stdio.h>

// ?File_Read@Targa@@AAEHPAXH@Z absent-from-retail
inline int Targa::File_Read(void *buffer, int size)
{
	return TGAFile->Read(buffer, size);
}

// ?File_Seek@Targa@@AAEHHH@Z absent-from-retail
inline int Targa::File_Seek(int pos, int dir)
{
	return TGAFile->Seek(pos, dir);
}

inline void Targa::Close(void)
{
	if (TGAFile) {
		TGAFile->Close();
		_TheFileFactory->Return_File(TGAFile);
		TGAFile = NULL;
	}
}

// ?Load@Targa@@QAEJPBDPAD1_N@Z
long Targa::Load(const char* name, char* palette, char* image, bool invert_image)
{
	long size;
	long depth;
	long error = 0;

	if (Open(name, TGA_READMODE) == NULL) {
		if (Header.ColorMapType == 1) {
			depth = (Header.CMapDepth >> 3);
			size = (Header.CMapLength * depth);
			if ((palette != NULL) && (Header.CMapLength > 0)) {
				palette += (Header.CMapStart * depth);
				if (File_Read(palette, size) != size) {
					error = TGAERR_READ;
				}
			} else {
				if (File_Seek(size, SEEK_CUR) == -1) {
					error = TGAERR_READ;
				}
			}
		}

		if (!error && (image != NULL)) {
			depth = TGA_BytesPerPixel(Header.PixelDepth);
			size = ((Header.Width * Header.Height) * depth);
			switch (Header.ImageType) {
			case TGA_CMAPPED:
				if (File_Read(image, size) != size) {
					error = TGAERR_READ;
				}
				break;
			case TGA_TRUECOLOR:
				if (File_Read(image, size) == size) {
					if (invert_image) InvertImage();
				} else {
					error = TGAERR_READ;
				}
				break;
			case TGA_MONO:
				if (File_Read(image, size) != size) {
					error = TGAERR_READ;
				}
				break;
			case TGA_CMAPPED_ENCODED:
				error = DecodeImage();
				break;
			case TGA_TRUECOLOR_ENCODED:
				if ((error = DecodeImage()) == NULL) {
					if (invert_image) InvertImage();
				}
				break;
			default:
				error = TGAERR_NOTSUPPORTED;
				break;
		}

			if (!error) {
				if (Header.ImageDescriptor & TGAIDF_XORIGIN) {
					XFlip();
					Header.ImageDescriptor &= ~TGAIDF_XORIGIN;
				}
				if (Header.ImageDescriptor & TGAIDF_YORIGIN) {
					YFlip();
					Header.ImageDescriptor &= ~TGAIDF_YORIGIN;
				}
			}
		}
		Close();
	} else {
		error = TGAERR_OPEN;
	}
	return error;
}
