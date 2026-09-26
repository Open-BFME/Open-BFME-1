// cl: /MD /Gz /Os /DPNG_NO_READ_USER_TRANSFORM /DPNG_NO_WRITE_USER_TRANSFORM /DPNG_NO_READ_bKGD /DPNG_NO_READ_BACKGROUND /DPNG_NO_CONSOLE_IO /DPNG_NO_READ_cHRM /Igame/Libraries/Source/Compression/ZLib
/* Isolated re-claim of png_chunk_error, whose real definition lives in
   pngerror.c (libpng 1.0.5) alongside png_format_buffer/png_error.
   In that shared TU the optimizer can see straight through png_error's
   body to png_default_error's terminal longjmp() and proves the whole
   call chain never returns, so it drops png_chunk_error's own epilogue --
   a real code-size difference from retail, whose png_chunk_error keeps
   its return path. Declaring png_error here as a plain extern, with no
   visible definition anywhere in this TU, keeps that interprocedural
   proof out of reach and reproduces retail's epilogue.
   png_format_buffer, by contrast, must stay a genuine local `static`
   definition (a byte-identical copy of pngerror.c's) rather than an
   extern prototype: it's internal-linkage in the real file, so the
   optimizer is free to pick its own register-passing ABI for it (the
   buffer argument travels in ECX, never pushed) -- externing it here
   would force a stack-passed call and desync the call site's bytes.
   Struct layout must still track pngerror.c's own PNG_NO_* set (those
   flags move field offsets), so this file mirrors them verbatim. */

#define PNG_INTERNAL
#include "png.h"

extern "C" {

#define isnonalpha(c) ((c) < 41 || (c) > 122 || ((c) > 90 && (c) < 97))
static PNG_CONST char png_digit[16] = {
   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

// png_format_buffer present-unmatched
static void
png_format_buffer(png_structp png_ptr, png_charp buffer, png_const_charp message)
{
   int iout = 0, iin = 0;

   while (iin < 4) {
      int c = png_ptr->chunk_name[iin++];
      if (isnonalpha(c)) {
         buffer[iout++] = '[';
         buffer[iout++] = png_digit[(c & 0xf0) >> 4];
         buffer[iout++] = png_digit[c & 0xf];
         buffer[iout++] = ']';
      } else {
         buffer[iout++] = (png_byte)c;
      }
   }

   if (message == NULL)
      buffer[iout] = 0;
   else {
      buffer[iout++] = ':';
      buffer[iout++] = ' ';
      png_memcpy(buffer+iout, message, 64);
      buffer[iout+63] = 0;
   }
}

void
png_chunk_error(png_structp png_ptr, png_const_charp message)
{
	char msg[16+64];
	png_format_buffer(png_ptr, msg, message);
	png_error(png_ptr, msg);
}

}
