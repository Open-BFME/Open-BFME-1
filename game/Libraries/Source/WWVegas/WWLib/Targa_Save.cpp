// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define TGA_USES_WWLIB_FILE_CLASSES
#include "targa.h"
#include "wwfile.h"
#include "ffactory.h"

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

// ?File_Write@Targa@@QAEXXZ absent-from-retail
int Targa::File_Write(void *buffer, int size)
	{
	return TGAFile->Write(buffer, size);
	}

// ?File_Seek@Targa@@QAEXXZ absent-from-retail
int Targa::File_Seek(int pos, int dir)
	{
	return TGAFile->Seek(pos, dir);
	}

void Targa::Close(void)
	{
	if (TGAFile) {
		TGAFile->Close();
		_TheFileFactory->Return_File(TGAFile);
		TGAFile = NULL;
	}
	}

long Targa::Save(const char* name, long flags, bool addextension)
	{
	long size;
	long depth;
	char *palette;
	char *temppal;
	char *ptr;
	long error = 0;
	TGA2Footer footer;

	/* Open the Targa for write. */
	if (Open(name, TGA_WRITEMODE) == NULL)
		{
		Header.IDLength = 0;

		/* Set the ImageType for compression. */
		if (flags & TGAF_COMPRESS)
			{
			switch (Header.ImageType)
				{
				case TGA_CMAPPED:
				case TGA_TRUECOLOR:
				case TGA_MONO:
					Header.ImageType += 8;
				break;

				case TGA_CMAPPED_ENCODED:
				case TGA_TRUECOLOR_ENCODED:
				case TGA_MONO_ENCODED:
				break;

				/* Turn off compression for unknown types. */
				default:
					flags &= ~TGAF_COMPRESS;
				break;
				}
			}

		/*-----------------------------------------------------------------------
		 * WRITE THE HEADER DATA SECTION
		 *---------------------------------------------------------------------*/
		if (File_Write(&Header, sizeof(TGAHeader)) != sizeof(TGAHeader))
			error = TGAERR_WRITE;

		/*-----------------------------------------------------------------------
		 * WRITE THE COLORMAP (PALETTE) DATA SECTION
		 *---------------------------------------------------------------------*/
		if (!error && (flags & TGAF_PAL) && (mPalette != NULL)
				&& (Header.CMapLength > 0))
			{
			/* Adjust palette to the starting color entry. */
			depth = (Header.CMapDepth >> 3);
			palette = mPalette + (Header.CMapStart * depth);
			size = (Header.CMapLength * depth);

			/* Allocate temporary buffer for palette manipulation. */
			if ((temppal = (char *)malloc(size)) != NULL)
				{
				memcpy(temppal, palette, size);
				ptr = temppal;

				/* Write the palette. */
				if (File_Write(temppal, size) != size)
					error = TGAERR_WRITE;

				/* Free temporary palette buffer. */
				free(temppal);
				}
			else
				error = TGAERR_NOMEM;
			}

		/*-----------------------------------------------------------------------
		 * WRITE THE IMAGE DATA SECTION
		 *---------------------------------------------------------------------*/
		if (!error && (flags & TGAF_IMAGE) && (mImage != NULL))
			{
			
			bool imageinverted;

			/* Invert truecolor data. */
			if ((Header.ImageType == TGA_TRUECOLOR) || (Header.ImageType == TGA_TRUECOLOR_ENCODED)) {
				InvertImage();
				imageinverted = true;
			} else {
				imageinverted = false;
			}

			/* Write the image. */
			if (flags & TGAF_COMPRESS)
				EncodeImage();
			else
				{
				depth = TGA_BytesPerPixel(Header.PixelDepth);
				size = (((Header.Width * Header.Height)) * depth);

				if (File_Write(mImage, size) != size)
					error = TGAERR_WRITE;
				}

			// Bug fix (IML) : If the image was inverted, invert it again to restore it to its prior state.
			if (imageinverted) InvertImage();
			}

		/*-----------------------------------------------------------------------
		 * WRITE THE EXTENSION DATA SECTION
		 *---------------------------------------------------------------------*/

		// Mod (IML) Optionally add an extension to the file.
		if (addextension) {
			if (!error) {

				mExtension.ExtSize = 495;
				strncpy(mExtension.SoftID, "Denzil's Targa Code", 41);
				mExtension.SoftVer.Number = (1 * 100);
				mExtension.SoftVer.Letter = 0;

				/* Save position of extension area. */
				if ((footer.Extension = File_Seek(0, SEEK_CUR)) == -1)
					error = TGAERR_WRITE;

				if (!error && (File_Write(&mExtension, sizeof(TGA2Extension))
						!= sizeof(TGA2Extension)))
					error = TGAERR_WRITE;
			}
		} else {
			footer.Extension = 0;
		}
			
		/*-----------------------------------------------------------------------
		 * WRITE THE FOOTER DATA SECTION
		 *---------------------------------------------------------------------*/
		if (!error)
			{
			footer.Developer = 0;
			strncpy(footer.Signature, TGA2_SIGNATURE, 16);
			footer.RsvdChar = '.';
			footer.BZST = 0;

			if (File_Write(&footer, sizeof(TGA2Footer)) != sizeof(TGA2Footer))
				error = TGAERR_WRITE;
			}

		/* Close targa file. */
		Close();
		}
	else
		error = TGAERR_OPEN;

	return (error);
	}
