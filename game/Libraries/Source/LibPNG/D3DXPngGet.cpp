// cl: /MD /Gz /Os /Igame/Libraries/Source/Compression/ZLib /Igame/Libraries/Source/LibPNG
/* libpng 1.0.5: adapted from pngget.c; copyright and license in LibPNG/png.h. */
#include "D3DXPngConfig.h"
#include <stdio.h>
#include <setjmp.h>
#include "zlib.h"
#define PNG_INTERNAL
#define png_get_valid png_get_valid_header_declaration
#define png_get_rowbytes png_get_rowbytes_header_declaration
#define png_get_channels png_get_channels_header_declaration
#define png_get_signature png_get_signature_header_declaration
#define png_get_gAMA png_get_gAMA_header_declaration
#define png_get_sRGB png_get_sRGB_header_declaration
#define png_get_IHDR png_get_IHDR_header_declaration
#define png_get_PLTE png_get_PLTE_header_declaration
#define png_get_tRNS png_get_tRNS_header_declaration
#define png_warning png_warning_header_declaration
namespace D3DX {
#include "png.h"
// Stock allocation sizes must survive changes to the shared feature profile.
typedef char png_struct_native_size[sizeof(png_struct) == 0x19c ? 1 : -1];
typedef char png_info_native_size[sizeof(png_info) == 0x40 ? 1 : -1];
typedef char png_row_info_native_size[sizeof(png_row_info) == 0xc ? 1 : -1];
typedef char png_callbacks_native_abi[
   D3DXPngSameType<png_error_ptr, void (__cdecl *)(png_structp, png_const_charp)>::value &&
   D3DXPngSameType<png_rw_ptr, void (__cdecl *)(png_structp, png_bytep, png_size_t)>::value &&
   D3DXPngSameType<png_flush_ptr, void (__cdecl *)(png_structp)>::value &&
   D3DXPngSameType<png_read_status_ptr, void (__cdecl *)(png_structp, png_uint_32, int)>::value &&
   D3DXPngSameType<png_write_status_ptr, void (__cdecl *)(png_structp, png_uint_32, int)>::value ? 1 : -1];
#undef png_get_valid
#undef png_get_rowbytes
#undef png_get_channels
#undef png_get_signature
#undef png_get_gAMA
#undef png_get_sRGB
#undef png_get_IHDR
#undef png_get_PLTE
#undef png_get_tRNS
#undef png_warning
void png_warning(png_structp, png_const_charp);
png_uint_32
png_get_valid(png_structp png_ptr, png_infop info_ptr, png_uint_32 flag)
{
   if (png_ptr != NULL && info_ptr != NULL)
      return(info_ptr->valid & flag);
   else
      return(0);
}
png_uint_32
png_get_rowbytes(png_structp png_ptr, png_infop info_ptr)
{
   if (png_ptr != NULL && info_ptr != NULL)
      return(info_ptr->rowbytes);
   else
      return(0);
}
png_byte
png_get_channels(png_structp png_ptr, png_infop info_ptr)
{
   if (png_ptr != NULL && info_ptr != NULL)
      return(info_ptr->channels);
   else
      return (0);
}
png_bytep
png_get_signature(png_structp png_ptr, png_infop info_ptr)
{
   if (png_ptr != NULL && info_ptr != NULL)
      return(info_ptr->signature);
   else
      return (NULL);
}
png_uint_32
png_get_gAMA(png_structp png_ptr, png_infop info_ptr, double *file_gamma)
{
   if (png_ptr != NULL && info_ptr != NULL && (info_ptr->valid & PNG_INFO_gAMA)
      && file_gamma != NULL)
   {
      png_debug1(1, "in %s retrieval function\n", "gAMA");
      *file_gamma = (double)info_ptr->gamma;
      return (PNG_INFO_gAMA);
   }
   return (0);
}
png_uint_32
png_get_sRGB(png_structp png_ptr, png_infop info_ptr, int *file_srgb_intent)
{
   if (png_ptr != NULL && info_ptr != NULL && (info_ptr->valid & PNG_INFO_sRGB)
      && file_srgb_intent != NULL)
   {
      png_debug1(1, "in %s retrieval function\n", "sRGB");
      *file_srgb_intent = (int)info_ptr->srgb_intent;
      return (PNG_INFO_sRGB);
   }
   return (0);
}
png_uint_32
png_get_IHDR(png_structp png_ptr, png_infop info_ptr,
   png_uint_32 *width, png_uint_32 *height, int *bit_depth,
   int *color_type, int *interlace_type, int *compression_type,
   int *filter_type)

{
   if (png_ptr != NULL && info_ptr != NULL && width != NULL && height != NULL &&
      bit_depth != NULL && color_type != NULL)
   {
      int pixel_depth, channels;
      png_uint_32 rowbytes_per_pixel;

      png_debug1(1, "in %s retrieval function\n", "IHDR");
      *width = info_ptr->width;
      *height = info_ptr->height;
      *bit_depth = info_ptr->bit_depth;
      *color_type = info_ptr->color_type;
      if (compression_type != NULL)
         *compression_type = info_ptr->compression_type;
      if (filter_type != NULL)
         *filter_type = info_ptr->filter_type;
      if (interlace_type != NULL)
         *interlace_type = info_ptr->interlace_type;

      /* check for potential overflow of rowbytes */
      if (*color_type == PNG_COLOR_TYPE_PALETTE)
         channels = 1;
      else if (*color_type & PNG_COLOR_MASK_COLOR)
         channels = 3;
      else
         channels = 1;
      if (*color_type & PNG_COLOR_MASK_ALPHA)
         channels++;
      pixel_depth = *bit_depth * channels;
      rowbytes_per_pixel = (pixel_depth + 7) >> 3;
      if ((*width > PNG_MAX_UINT/rowbytes_per_pixel))
      {
         png_warning(png_ptr,
            "Width too large for libpng to process image data.");
      }
      return (1);
   }
   return (0);
}
png_uint_32
png_get_PLTE(png_structp png_ptr, png_infop info_ptr, png_colorp *palette,
   int *num_palette)
{
   if (png_ptr != NULL && info_ptr != NULL && info_ptr->valid & PNG_INFO_PLTE &&
       palette != NULL)
   {
      png_debug1(1, "in %s retrieval function\n", "PLTE");
      *palette = info_ptr->palette;
      *num_palette = info_ptr->num_palette;
      png_debug1(3, "num_palette = %d\n", *num_palette);
      return (PNG_INFO_PLTE);
   }
   return (0);
}
png_uint_32
png_get_tRNS(png_structp png_ptr, png_infop info_ptr,
   png_bytep *trans, int *num_trans, png_color_16p *trans_values)
{
   png_uint_32 retval = 0;
   if (png_ptr != NULL && info_ptr != NULL && info_ptr->valid & PNG_INFO_tRNS)
   {
      png_debug1(1, "in %s retrieval function\n", "tRNS");
      if (info_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
      {
          if (trans != NULL)
          {
             *trans = info_ptr->trans;
             retval |= PNG_INFO_tRNS;
          }
          if (trans_values != NULL)
             *trans_values = &(info_ptr->trans_values);
      }
      else /* if (info_ptr->color_type != PNG_COLOR_TYPE_PALETTE) */
      {
          if (trans_values != NULL)
          {
             *trans_values = &(info_ptr->trans_values);
             retval |= PNG_INFO_tRNS;
          }
          if(trans != NULL)
             *trans = NULL;
      }
      if(num_trans != NULL)
      {
         *num_trans = info_ptr->num_trans;
         retval |= PNG_INFO_tRNS;
      }
   }
   return (retval);
}
}
