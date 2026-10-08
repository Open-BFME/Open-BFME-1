# d3dx9 (Summer 2003) owns the JPEG/libpng bodies in its region: 56 rows re-pointed, 36 double claims retired

Library-version audit follow-up, 2026-10-08 (`_impl/reports/libaudit-microsoft.md`, `libaudit-compression.md`).

## Why these bytes are Microsoft's and not the game's own libpng/jpeg

- Every row below sits inside the run `inputs/vendor/d3dx9/d3dx9.lib` owns, RVA 0x009F9B82-0x00AD5401
  (`inputs/vendor/d3dx9/PROVENANCE.txt`), 98.5% of which is already attached to that archive's members.
- Retail carries the strings `libpng version 1.0.5 - October 15, 1999` and IJG `6b  27-Mar-1998` once each,
  exactly as `d3dx9.lib` does; BFME2's `game.dat`, which loads `d3dx9_27.dll` dynamically, has no libpng or
  jpeg code or strings at all. The game never linked its own copy.
- The count-agreement standard refuses a class whenever retail holds MORE copies of a body than the archive
  supplies, so a second (game-compiled) copy of any of these bodies would have surfaced as oversubscription.
  None did.

## Method: the repo's own placement standard, re-derived

`tools/lib_window_sweep.py` (retired in f23366a748; read back from `f23366a748^` and run as an untracked
scratch copy, never re-added) decides a lib placement under COUNT-AGREEMENT: in-window, no more retail copies
than archive instances, archive-order assignment, then four refutations (ledger anchors, REL32 callee
targets, DIR32 bases, Ghidra names), and twin naming when more than one symbol survives. One change for this
run: a placement may supersede a HELD game-source row only at exactly that row's start and size (or the row's
size when the member's own trailing 0xCC padding fills it, as `dump-padded` already allowed). Of the 374
held rows in the window, 56 pass; every other row is refused with a reason recorded in
`_impl/reports/libaudit-fix-bfme1.md` (below 16-byte needle floor, callee contradiction, DIR32
contradiction, oversubscribed, archive order contradicts an attached row, or the COMDAT is already attached).

Each re-pointed row keeps its exact retail extent; `./build.sh` extracts the named member and byte-compares
the COMDAT against retail with relocation sites masked (`concrete` = bytes compared), the same test every
`vendored=d3dx9-summer2003` row passes.

## The 56 re-pointed rows

`pl` = in-window placements of the body, `inst` = archive instances, `anc` = already-attached rows that
anchor the order, `calls` = REL32 callees found at the archive-named body, `bases` = DIR32 globals resolving
to a base an attached row pins, `cand` = symbols surviving every test (2 = twin, named `?d3dx9_twin_<rva>`).

| rva | size | old row (name, source) | member | symbol | pl | inst | anc | calls | bases | cand | concrete |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 0x00A56226 | 88 | `?QueryInterface@CConstantTable@D3DXShader@@UAGJABU_GUID@@PAPAX@Z` (CConstantTableQueryInterface.cpp) | cconstanttable.obj | `?QueryInterface@CConstantTable@D3DXShader@@UAGJABU_GUID@@PAPAX@Z` | 3 | 3 | 2 | 0 | 2 | 1 | 76 |
| 0x00A62100 | 51 | `_jpeg_set_linear_quality@12` (jcparam.c) | jcparam.obj | `?jpeg_set_linear_quality@D3DX@@YGXPAUjpeg_compress_struct@1@HH@Z` | 1 | 1 | 0 | 2 | 2 | 1 | 35 |
| 0x00A62140 | 62 | `_jpeg_quality_scaling@4` (jcparam.c) | jcparam.obj | `?jpeg_quality_scaling@D3DX@@YGHH@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 62 |
| 0x00A62180 | 108 | `_jpeg_set_quality@12` (jcparam.c) | jcparam.obj | `?jpeg_set_quality@D3DX@@YGXPAUjpeg_compress_struct@1@HH@Z` | 1 | 1 | 0 | 2 | 2 | 1 | 92 |
| 0x00A625E0 | 39 | `_fill_a_scan@24` (jcparam.c) | jcparam.obj | `?fill_a_scan@D3DX@@YGPAUjpeg_scan_info@1@PAU21@HHHHH@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 39 |
| 0x00A62B80 | 137 | `_png_format_buffer@12` (pngerror.c) | pngerror.obj | `?png_format_buffer@D3DX@@YGXPAUpng_struct_def@1@PADPBD@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 129 |
| 0x00A62C18 | 28 | `_png_set_error_fn@16` (pngerror.c) | pngerror.obj | `?png_set_error_fn@D3DX@@YGXPAUpng_struct_def@1@PAXP6AX0PBD@Z3@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 28 |
| 0x00A62C73 | 36 | `_png_chunk_error@8` (pngerror_ChunkError_Thunk.cpp) | pngerror.obj | `?png_chunk_error@D3DX@@YGXPAUpng_struct_def@1@PBD@Z` | 2 | 2 | 0 | 2 | 0 | 1 | 28 |
| 0x00A62C97 | 36 | `_png_chunk_warning@8` (pngerror.c) | pngerror.obj | `?png_chunk_warning@D3DX@@YGXPAUpng_struct_def@1@PBD@Z` | 2 | 2 | 0 | 2 | 0 | 1 | 28 |
| 0x00A62CC3 | 45 | `_png_set_sig_bytes@8` (png.c) | png.obj | `?png_set_sig_bytes@D3DX@@YGXPAUpng_struct_def@1@H@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 37 |
| 0x00A62CF0 | 75 | `_png_sig_cmp@12` (png.c) | png.obj | `?png_sig_cmp@D3DX@@YGHPAEII@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 71 |
| 0x00A62DAA | 23 | `_png_reset_crc@4` (png.c) | png.obj | `?png_reset_crc@D3DX@@YGXPAUpng_struct_def@1@@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 19 |
| 0x00A62DC1 | 63 | `_png_calculate_crc@12` (png.c) | png.obj | `?png_calculate_crc@D3DX@@YGXPAUpng_struct_def@1@PAEI@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 59 |
| 0x00A630EA | 23 | `_png_set_flush@8` (pngwrite.c) | pngwrite.obj | `?png_set_flush@D3DX@@YGXPAUpng_struct_def@1@H@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 23 |
| 0x00A63101 | 166 | `_png_write_flush@4` (pngwrite.c) | pngwrite.obj | `?png_write_flush@D3DX@@YGXPAUpng_struct_def@1@@Z` | 1 | 1 | 0 | 5 | 0 | 1 | 142 |
| 0x00A63288 | 452 | `_png_set_filter@12` (pngwrite.c) | pngwrite.obj | `?png_set_filter@D3DX@@YGXPAUpng_struct_def@1@HH@Z` | 1 | 1 | 0 | 9 | 0 | 1 | 396 |
| 0x00A6365B | 21 | `_png_set_compression_level@8` (pngwrite.c) | pngwrite.obj | `?png_set_compression_level@D3DX@@YGXPAUpng_struct_def@1@H@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 21 |
| 0x00A63670 | 21 | `_png_set_compression_mem_level@8` (pngwrite.c) | pngwrite.obj | `?png_set_compression_mem_level@D3DX@@YGXPAUpng_struct_def@1@H@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 21 |
| 0x00A63685 | 21 | `_png_set_compression_strategy@8` (pngwrite.c) | pngwrite.obj | `?png_set_compression_strategy@D3DX@@YGXPAUpng_struct_def@1@H@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 21 |
| 0x00A6369A | 53 | `_png_set_compression_window_bits@8` (pngwrite.c) | pngwrite.obj | `?png_set_compression_window_bits@D3DX@@YGXPAUpng_struct_def@1@H@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 41 |
| 0x00A636CF | 41 | `_png_set_compression_method@8` (pngwrite.c) | pngwrite.obj | `?png_set_compression_method@D3DX@@YGXPAUpng_struct_def@1@H@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 33 |
| 0x00A636F8 | 17 | `_png_set_write_status_fn@8` (pngwrite.c) | pngwrite.obj | `?png_set_write_status_fn@D3DX@@YGXPAUpng_struct_def@1@P6AX0KH@Z@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 17 |
| 0x00A637FD | 36 | `_png_write_rows@12` (pngwrite.c) | pngwrite.obj | `?png_write_rows@D3DX@@YGXPAUpng_struct_def@1@PAPAEK@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 32 |
| 0x00A63821 | 71 | `_png_write_image@8` (pngwrite.c) | pngwrite.obj | `?png_write_image@D3DX@@YGXPAUpng_struct_def@1@PAPAE@Z` | 1 | 1 | 0 | 2 | 0 | 1 | 63 |
| 0x00A63926 | 29 | `_png_set_gAMA@16` (pngset.c) | pngset.obj | `?png_set_gAMA@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@N@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 29 |
| 0x00A639E4 | 38 | `_png_set_PLTE@16` (pngset.c) | pngset.obj | `?png_set_PLTE@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@PAUpng_color_struct@1@H@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 38 |
| 0x00A63A0A | 29 | `_png_set_sRGB@12` (pngset.c) | pngset.obj | `?png_set_sRGB@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@H@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 29 |
| 0x00A63DD8 | 31 | `_png_read_update_info@8` (pngread.c) | pngread.obj | `?png_read_update_info@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@@Z` | 1 | 1 | 0 | 2 | 0 | 1 | 23 |
| 0x00A63DF7 | 19 | `_png_start_read_image@4` (pngread.c) | pngread.obj | `?png_start_read_image@D3DX@@YGXPAUpng_struct_def@1@@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 15 |
| 0x00A6418D | 115 | `_png_read_rows@16` (pngread.c) | pngread.obj | `?png_read_rows@D3DX@@YGXPAUpng_struct_def@1@PAPAE1K@Z` | 1 | 1 | 0 | 3 | 0 | 1 | 103 |
| 0x00A64200 | 75 | `_png_read_image@8` (pngread.c) | pngread.obj | `?png_read_image@D3DX@@YGXPAUpng_struct_def@1@PAPAE@Z` | 1 | 1 | 0 | 2 | 0 | 1 | 67 |
| 0x00A64458 | 17 | `_png_set_read_status_fn@8` (pngread.c) | pngread.obj | `?png_set_read_status_fn@D3DX@@YGXPAUpng_struct_def@1@P6AX0KH@Z@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 17 |
| 0x00A644E6 | 29 | `_png_get_valid@12` (pngget.c) | pngget.obj | `?png_get_valid@D3DX@@YGKPAUpng_struct_def@1@PAUpng_info_struct@1@K@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 29 |
| 0x00A64503 | 25 | `_png_get_rowbytes@8` (pngget.c) | pngget.obj | `?png_get_rowbytes@D3DX@@YGKPAUpng_struct_def@1@PAUpng_info_struct@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 25 |
| 0x00A6451C | 25 | `_png_get_channels@8` (pngget.c) | pngget.obj | `?png_get_channels@D3DX@@YGEPAUpng_struct_def@1@PAUpng_info_struct@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 25 |
| 0x00A64535 | 25 | `_png_get_signature@8` (pngget.c) | pngget.obj | `?png_get_signature@D3DX@@YGPAEPAUpng_struct_def@1@PAUpng_info_struct@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 25 |
| 0x00A6454E | 44 | `_png_get_gAMA@12` (pngget.c) | pngget.obj | `?png_get_gAMA@D3DX@@YGKPAUpng_struct_def@1@PAUpng_info_struct@1@PAN@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 44 |
| 0x00A6457A | 46 | `_png_get_sRGB@12` (pngget.c) | pngget.obj | `?png_get_sRGB@D3DX@@YGKPAUpng_struct_def@1@PAUpng_info_struct@1@PAH@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 46 |
| 0x00A645A8 | 209 | `_png_get_IHDR@36` (pngget.c) | pngget.obj | `?png_get_IHDR@D3DX@@YGKPAUpng_struct_def@1@PAUpng_info_struct@1@PAK2PAH3333@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 201 |
| 0x00A64679 | 54 | `_png_get_PLTE@16` (pngget.c) | pngget.obj | `?png_get_PLTE@D3DX@@YGKPAUpng_struct_def@1@PAUpng_info_struct@1@PAPAUpng_color_struct@1@PAH@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 54 |
| 0x00A64723 | 20 | `_png_set_swap@4` (pngtrans.c) | pngtrans.obj | `?png_set_swap@D3DX@@YGXPAUpng_struct_def@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 20 |
| 0x00A64737 | 27 | `_png_set_packing@4` (pngtrans.c) | pngtrans.obj | `?png_set_packing@D3DX@@YGXPAUpng_struct_def@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 27 |
| 0x00A64752 | 27 | `_png_set_shift@8` (pngtrans.c) | pngtrans.obj | `?png_set_shift@D3DX@@YGXPAUpng_struct_def@1@PAUpng_color_8_struct@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 27 |
| 0x00A6476D | 28 | `_png_set_interlace_handling@4` (pngtrans.c) | pngtrans.obj | `?png_set_interlace_handling@D3DX@@YGHPAUpng_struct_def@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 28 |
| 0x00A64789 | 79 | `_png_set_filler@12` (pngtrans.c) | pngtrans.obj | `?png_set_filler@D3DX@@YGXPAUpng_struct_def@1@KH@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 79 |
| 0x00A647D8 | 47 | `_png_do_swap@8` (pngtrans.c) | pngtrans.obj | `?png_do_swap@D3DX@@YGXPAUpng_row_info_struct@1@PAE@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 47 |
| 0x00A64807 | 193 | `_png_do_bgr@8` (pngtrans.c) | pngtrans.obj | `?png_do_bgr@D3DX@@YGXPAUpng_row_info_struct@1@PAE@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 193 |
| 0x00A648C8 | 127 | `_png_set_crc_action@12` (pngrtran.c) | pngrtran.obj | `?png_set_crc_action@D3DX@@YGXPAUpng_struct_def@1@HH@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 119 |
| 0x00A64F90 | 56 | `_png_set_gamma@20` (pngrtran.c) | pngrtran.obj | `?png_set_gamma@D3DX@@YGXPAUpng_struct_def@1@NN@Z` | 1 | 1 | 0 | 0 | 1 | 1 | 48 |
| 0x00A6536B | 70 | `_png_do_chop@8` (pngrtran.c) | pngrtran.obj | `?png_do_chop@D3DX@@YGXPAUpng_row_info_struct@1@PAE@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 70 |
| 0x00A655EA | 98 | `_png_build_grayscale_palette@8` (pngrtran.c) | pngrtran.obj | `?png_build_grayscale_palette@D3DX@@YGXHPAUpng_color_struct@1@@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 98 |
| 0x00A6564C | 848 | `_png_do_gamma@20` (pngrtran.c) | pngrtran.obj | `?png_do_gamma@D3DX@@YGXPAUpng_row_info_struct@1@PAE1PAPAGH@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 848 |
| 0x00A65EF8 | 271 | `_png_do_dither@16` (pngrtran.c) | pngrtran.obj | `?png_do_dither@D3DX@@YGXPAUpng_row_info_struct@1@PAE11@Z` | 1 | 1 | 0 | 0 | 0 | 1 | 271 |
| 0x00A6630A | 276 | `_png_init_read_transformations@4` (pngrtran.c) | pngrtran.obj | `?png_init_read_transformations@D3DX@@YGXPAUpng_struct_def@1@@Z` | 1 | 1 | 0 | 1 | 0 | 1 | 272 |
| 0x00A9AEF9 | 16 | `?dup_00a9aef9@@YAXXZ` (DamageFX.cpp) | createmesh.obj | `??0CBone@@QAE@XZ / ??0CStringStack@D3DXCore@@QAE@XZ` | 2 | 2 | 1 | 0 | 0 | 2 | 16 |
| 0x00AC7FB0 | 24 | `_jpeg_free_small@12` (jmemwin32.cpp) | jmemansi.obj | `?jpeg_free_large@D3DX@@YGXPAUjpeg_common_struct@1@PAXI@Z / ?jpeg_free_small@D3DX@@YGXPAUjpeg_common_struct@1@PAXI@Z` | 2 | 2 | 1 | 0 | 0 | 2 | 20 |

Two rows are twins: at 0x00A9AEF9 the 16-byte body is masked-identical in two createmesh.obj symbols and at
0x00AC7FB0 `jpeg_free_small`/`jpeg_free_large` are the same 20 bytes (plus 4 bytes of the member's padding
retail kept); the image witnesses neither, so the name asserts none and `object-symbol=` carries the COMDAT.

## The 36 retired double claims (one owner per address)

At each address below a `vendored=d3dx9-summer2003` row was ALREADY attached (its member places there under
the same standard; the sweep's verdict for the game row is `comdat-already-consumed`) and a second,
game-source row claimed the identical extent. The game row is retired; the archive row stays.

| rva | retired row (name, source) | owner kept (name, member) | size |
|---|---|---|---|
| 0x00A61790 | `_emit_message@8` (jerror.c) | `?emit_message@D3DX@@YGXPAUjpeg_common_struct@1@H@Z` (jerror.obj) | 52 |
| 0x00A618A0 | `_jpeg_std_error@4` (jerror.c) | `?jpeg_std_error@D3DX@@YGPAUjpeg_error_mgr@1@PAU21@@Z` (jerror.obj) | 78 |
| 0x00AAA8C0 | `_self_destruct@4` (jmemmgr.c) | `?self_destruct@D3DX@@YGXPAUjpeg_common_struct@1@@Z` (jmemmgr.obj) | 56 |
| 0x00AAAA00 | `_jpeg_destroy@4` (jcomapi.c) | `?jpeg_destroy@D3DX@@YGXPAUjpeg_common_struct@1@@Z` (jcomapi.obj) | 30 |
| 0x00AAAA60 | `_jdiv_round_up@8` (jutils.c) | `?jdiv_round_up@D3DX@@YGJJJ@Z` (jutils.obj) | 18 |
| 0x00AAAA80 | `_jround_up@8` (jutils.c) | `?jround_up@D3DX@@YGJJJ@Z` (jutils.obj) | 26 |
| 0x00AAAAA0 | `_jcopy_sample_rows@24` (jutils.c) | `?jcopy_sample_rows@D3DX@@YGXPAPAEH0HHI@Z` (jutils.obj) | 72 |
| 0x00AAAAF0 | `_jcopy_block_row@12` (jutils.c) | `?jcopy_block_row@D3DX@@YGXPAY0EA@F0I@Z` (jutils.obj) | 36 |
| 0x00AAAB20 | `_jzero_far@8` (jutils.c) | `?jzero_far@D3DX@@YGXPAXI@Z` (jutils.obj) | 29 |
| 0x00AABF2A | `_png_memcpy_check@16` (pngmem.c) | `?png_memcpy_check@D3DX@@YGPAXPAUpng_struct_def@1@PAX1K@Z` (pngmem.obj) | 37 |
| 0x00AABF4F | `_png_memset_check@16` (pngmem.c) | `?png_memset_check@D3DX@@YGPAXPAUpng_struct_def@1@PAXHK@Z` (pngmem.obj) | 51 |
| 0x00AAC07D | `_png_save_uint_32@8` (pngwutil.c) | `?png_save_uint_32@D3DX@@YGXPAEK@Z` (pngwutil.obj) | 37 |
| 0x00AAC0A2 | `_png_save_uint_16@8` (pngwutil.c) | `?png_save_uint_16@D3DX@@YGXPAEI@Z` (pngwutil.obj) | 21 |
| 0x00AAC0B7 | `_png_write_chunk_start@12` (pngwutil.c) | `?png_write_chunk_start@D3DX@@YGXPAUpng_struct_def@1@PAEK@Z` (pngwutil.obj) | 64 |
| 0x00AAC0F7 | `_png_write_chunk_data@12` (pngwutil.c) | `?png_write_chunk_data@D3DX@@YGXPAUpng_struct_def@1@PAEI@Z` (pngwutil.obj) | 39 |
| 0x00AAC11E | `_png_write_chunk_end@4` (pngwutil.c) | `?png_write_chunk_end@D3DX@@YGXPAUpng_struct_def@1@@Z` (pngwutil.obj) | 39 |
| 0x00AAC145 | `_png_write_sig@4` (pngwutil.c) | `?png_write_sig@D3DX@@YGXPAUpng_struct_def@1@@Z` (pngwutil.obj) | 33 |
| 0x00AAC569 | `_png_write_chunk@16` (pngwutil.c) | `?png_write_chunk@D3DX@@YGXPAUpng_struct_def@1@PAE1I@Z` (pngwutil.obj) | 43 |
| 0x00AAC834 | `_png_write_IDAT@12` (pngwutil.c) | `?png_write_IDAT@D3DX@@YGXPAUpng_struct_def@1@PAEI@Z` (pngwutil.obj) | 32 |
| 0x00AAC870 | `_png_write_finish_row@4` (pngwutil.c) | `?png_write_finish_row@D3DX@@YGXPAUpng_struct_def@1@@Z` (pngwutil.obj) | 383 |
| 0x00AAC9EF | `_png_write_filtered_row@8` (pngwutil.c) | `?png_write_filtered_row@D3DX@@YGXPAUpng_struct_def@1@PAE@Z` (pngwutil.obj) | 170 |
| 0x00AAEEC6 | `_png_get_int_32@4` (pngrutil.c) | `?png_get_uint_32@D3DX@@YGKPAE@Z` (pngrutil.obj) | 37 |
| 0x00AAEEEB | `_png_get_uint_16@4` (pngrutil.c) | `?png_get_uint_16@D3DX@@YGGPAE@Z` (pngrutil.obj) | 21 |
| 0x00AAEF00 | `_png_crc_read@12` (pngrutil.c) | `?png_crc_read@D3DX@@YGXPAUpng_struct_def@1@PAEI@Z` (pngrutil.obj) | 23 |
| 0x00AAEF17 | `_png_crc_error@4` (pngrutil.c) | `?png_crc_error@D3DX@@YGHPAUpng_struct_def@1@@Z` (pngrutil.obj) | 92 |
| 0x00AAEF73 | `_png_check_chunk_name@8` (pngrutil.c) | `?png_check_chunk_name@D3DX@@YGXPAUpng_struct_def@1@PAE@Z` (pngrutil.obj) | 98 |
| 0x00AAF7C9 | `_png_crc_finish@8` (pngrutil.c) | `?png_crc_finish@D3DX@@YGHPAUpng_struct_def@1@K@Z` (pngrutil.obj) | 133 |
| 0x00AAF84E | `_png_handle_IHDR@12` (pngrutil.c) | `?png_handle_IHDR@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@K@Z` (pngrutil.obj) | 480 |
| 0x00AAFB47 | `_png_handle_IEND@12` (pngrutil.c) | `?png_handle_IEND@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@K@Z` (pngrutil.obj) | 70 |
| 0x00AAFB8D | `_png_handle_gAMA@12` (pngrutil.c) | `?png_handle_gAMA@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@K@Z` (pngrutil.obj) | 257 |
| 0x00AAFC8E | `_png_handle_sRGB@12` (pngrutil.c) | `?png_handle_sRGB@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@K@Z` (pngrutil.obj) | 226 |
| 0x00AAFD70 | `_png_handle_tRNS@12` (pngrutil.c) | `?png_handle_tRNS@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@K@Z` (pngrutil.obj) | 417 |
| 0x00AAFF11 | `_png_handle_unknown@12` (pngrutil.c) | `?png_handle_unknown@D3DX@@YGXPAUpng_struct_def@1@PAUpng_info_struct@1@K@Z` (pngrutil.obj) | 70 |
| 0x00AAFF57 | `_png_read_finish_row@4` (pngrutil.c) | `?png_read_finish_row@D3DX@@YGXPAUpng_struct_def@1@@Z` (pngrutil.obj) | 528 |
| 0x00ACB810 | `_expand_bottom_edge@16` (jcprepct.c) | `?expand_bottom_edge@D3DX@@YGXPAPAEIHH@Z` (jcprepct.obj) | 42 |
| 0x00ACBE60 | `_expand_right_edge@16` (jcsample.c) | `?expand_right_edge@D3DX@@YGXPAPAEHII@Z` (jcsample.obj) | 90 |

## What this does NOT claim

The 318 other held rows in the window stay where they are. 208 are under the 16-byte floor at which the
standard refuses to place by needle; 48 size-optimised deleting destructors call a folded destructor the
archive's twin does not; the `SetAlloc` pair and the `??_GC*Program` rotation resolve a global to a base an
attached row contradicts; three real-name game rows (`Get_Processor_Manufacturer_Name`, `decalmsh` operator[],
`dup_a05018`) also double-claim an attached archive row but are outside this file's JPEG/libpng scope and are
listed for a separate decision.
