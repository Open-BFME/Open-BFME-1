// cl: /MD /Gz /Os /DPNG_NO_READ_USER_TRANSFORM /DPNG_NO_WRITE_USER_TRANSFORM /DPNG_NO_READ_bKGD /DPNG_NO_READ_BACKGROUND /DPNG_NO_CONSOLE_IO /DPNG_NO_READ_cHRM /Igame/Libraries/Source/Compression/ZLib /Igame/Libraries/Source/LibPNG
/* libpng 1.0.5: adapted from LibPNG/pngtrans.c; copyright and license in LibPNG/png.h. */
#include <stdio.h>
#include <setjmp.h>
#include "zlib.h"
#define PNG_INTERNAL
// The upstream header declares C linkage; the archive uses D3DX C++ linkage.
#define png_set_bgr png_set_bgr_header_declaration
#define png_set_swap png_set_swap_header_declaration
#define png_set_packing png_set_packing_header_declaration
#define png_set_shift png_set_shift_header_declaration
#define png_set_interlace_handling png_set_interlace_handling_header_declaration
#define png_set_filler png_set_filler_header_declaration
#define png_do_swap png_do_swap_header_declaration
#define png_do_bgr png_do_bgr_header_declaration
namespace D3DX {
#include "png.h"
#undef png_set_bgr
#undef png_set_swap
#undef png_set_packing
#undef png_set_shift
#undef png_set_interlace_handling
#undef png_set_filler
#undef png_do_swap
#undef png_do_bgr
void
png_set_bgr(png_structp png_ptr)
{
   png_debug(1, "in png_set_bgr\n");
   png_ptr->transformations |= PNG_BGR;
}
void
png_set_swap(png_structp png_ptr)
{
   png_debug(1, "in png_set_swap\n");
   if (png_ptr->bit_depth == 16)
      png_ptr->transformations |= PNG_SWAP_BYTES;
}
void
png_set_packing(png_structp png_ptr)
{
   png_debug(1, "in png_set_packing\n");
   if (png_ptr->bit_depth < 8)
   {
      png_ptr->transformations |= PNG_PACK;
      png_ptr->usr_bit_depth = 8;
   }
}
void
png_set_shift(png_structp png_ptr, png_color_8p true_bits)
{
   png_debug(1, "in png_set_shift\n");
   png_ptr->transformations |= PNG_SHIFT;
   png_ptr->shift = *true_bits;
}
int
png_set_interlace_handling(png_structp png_ptr)
{
   png_debug(1, "in png_set_interlace handling\n");
   if (png_ptr->interlaced)
   {
      png_ptr->transformations |= PNG_INTERLACE;
      return (7);
   }

   return (1);
}
void
png_set_filler(png_structp png_ptr, png_uint_32 filler, int filler_loc)
{
   png_debug(1, "in png_set_filler\n");
   png_ptr->transformations |= PNG_FILLER;
   png_ptr->filler = (png_byte)filler;
   if (filler_loc == PNG_FILLER_AFTER)
      png_ptr->flags |= PNG_FLAG_FILLER_AFTER;
   else
      png_ptr->flags &= ~PNG_FLAG_FILLER_AFTER;

   /* This should probably go in the "do_filler" routine.
    * I attempted to do that in libpng-1.0.1a but that caused problems
    * so I restored it in libpng-1.0.2a
   */

   if (png_ptr->color_type == PNG_COLOR_TYPE_RGB)
   {
      png_ptr->usr_channels = 4;
   }

   /* Also I added this in libpng-1.0.2a (what happens when we expand
    * a less-than-8-bit grayscale to GA? */

   if (png_ptr->color_type == PNG_COLOR_TYPE_GRAY && png_ptr->bit_depth >= 8)
   {
      png_ptr->usr_channels = 2;
   }
}
void
png_do_swap(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_swap\n");
   if (
#if defined(PNG_USELESS_TESTS_SUPPORTED)
       row != NULL && row_info != NULL &&
#endif
       row_info->bit_depth == 16)
   {
      png_bytep rp = row;
      png_uint_32 i;
      png_uint_32 istop= row_info->width * row_info->channels;

      for (i = 0; i < istop; i++, rp += 2)
      {
         png_byte t = *rp;
         *rp = *(rp + 1);
         *(rp + 1) = t;
      }
   }
}
void
png_do_bgr(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_bgr\n");
   if (
#if defined(PNG_USELESS_TESTS_SUPPORTED)
       row != NULL && row_info != NULL &&
#endif
       (row_info->color_type & PNG_COLOR_MASK_COLOR))
   {
      png_uint_32 row_width = row_info->width;
      if (row_info->bit_depth == 8)
      {
         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 3)
            {
               png_byte save = *rp;
               *rp = *(rp + 2);
               *(rp + 2) = save;
            }
         }
         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 4)
            {
               png_byte save = *rp;
               *rp = *(rp + 2);
               *(rp + 2) = save;
            }
         }
      }
      else if (row_info->bit_depth == 16)
      {
         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 6)
            {
               png_byte save = *rp;
               *rp = *(rp + 4);
               *(rp + 4) = save;
               save = *(rp + 1);
               *(rp + 1) = *(rp + 5);
               *(rp + 5) = save;
            }
         }
         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 8)
            {
               png_byte save = *rp;
               *rp = *(rp + 4);
               *(rp + 4) = save;
               save = *(rp + 1);
               *(rp + 1) = *(rp + 5);
               *(rp + 5) = save;
            }
         }
      }
   }
}
}
