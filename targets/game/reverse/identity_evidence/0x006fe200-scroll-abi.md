# 0x006FE200 scroll body and ABI evidence

The source reconstructs the complete 349-byte body at RVA 0x006FE200 under the opaque owner Rva006FE200Owner. The tested base is 91d7b17f67449f1ff3e8a2f90d197e7057a08bcb. No retail class or method identity is asserted by this name.

## Boundary and calling contract

Every instruction in the claimed extent decodes. Both early exits at +0x0C and +0x3C, the zero-delta path at +0x66, the manager-null path at +0xE4 and both clamp branches stay inside the body. They reach the single epilogue at +0x156 and ret 8 at +0x15A. There is no outgoing conditional branch, tail jump, exception frame or hidden return buffer in the target. ECX is the unadjusted receiver, the first stack argument points to two four-byte floats, and the second is consumed by fmul as one four-byte float. No result register or x87 return value is established.

The complete incoming caller 0x005B4D40 supplies those two arguments at +0x316 and +0x31B before call [edx+0x14] at +0x31C. Its alternate rotation path stores the computed float at [esp] at +0x36F, pushes the coordinate-pair address at +0x372 and calls the same slot at +0x373. Both paths reload the receiver and invoke another virtual without caller cleanup for the scroll arguments, agreeing with ret 8. All caller returns and branches are included below. Its receiver is read from VA 0x012F7048. The complete base constructor 0x0060A000 writes its unchanged receiver to that global at +0x94. The complete derived constructor 0x006FC970 calls that base through ILT 0x0000B89D and installs VA 0x011207C0 at +0x23. Slot 5 contains VA 0x0042BB39, whose five-byte jump reaches the assigned body. This establishes the indirect caller route without naming the owner.

## Fields and callees

The target reads floats at receiver offsets +0xA8 and +0xAC and preserves the four raw bytes at +0xB0 in a three-field local. Its virtual call at +0xD9 receives the address of that local in one stack slot with ECX unchanged. Table slot 25 contains VA 0x004493B4, whose five-byte jump reaches 0x006FD2E0. The complete 174-byte callee copies argument fields +0, +4 and +8 into receiver fields +0xA8, +0xAC and +0xB0 and returns with ret 4. It conditionally clamps x/y after a separate tactical-view virtual, whose target is not needed to infer the scroll argument representation. The canonical Coord3D header supplies exactly those three floats. The source retains the bank's m_facing and m_gateMetric labels; the method name setPosition describes the witnessed three-field store rather than asserting a named retail member.

The REL32 call at target +0xFB reaches ILT 0x0002AE00 and then the independently matched 126-byte BfmeLivingWorldManager::rva00615a70 body at 0x00615A70. Retail loads the receiver from VA 0x012F706C and supplies the coordinate-pair address. The canonical data row identifies that singleton as TheLivingWorldManager; the source uses that existing declaration rather than the bank's invented debug-consumer name. The complete manager body forwards the unchanged argument through ILT 0x000307EC to 0x0061C2F0 and returns with ret 4. The complete guarded helper forwards it through ILT 0x000457A5 to the complete Region2D::isInside body at 0x0061BA90, which reads four-byte x/y values at +0/+4. The source does not introduce or retype the manager's STL map or any constructor cleanup.

The read-only constants at VA 0x0107533C, 0x01075350 and 0x01083B6C hold 0.5f, 0.0f and 0.25f. They are written as literals. VA 0x012F8274 and the two distinct writable globals at VA 0x012BAC54 and 0x012BAC50 remain extern float objects. No pin is invented. The three-component rotation temporary retains the witnessed local-frame shape; only x/y are read or written, and its unused third component establishes no original local-variable type identity.

## Retry, measurements and refutation

The old bank asserted an unproven BfmeFacingBody owner, treated +0xB0 as speed, omitted the virtual argument, reversed the gate, used less-than instead of zero equality and called a free debug routine without the observed manager receiver. The checked virtual callee and incoming caller independently refute those ABI and field hypotheses. The corrected source retains an address-derived owner and the bank's descriptive angle and gate labels.

The new hypothesis was that the native coordinate copy and aggregate rotation lifetime supply the frame and x87 shape the earlier skeleton lacked. It would be refuted by a complete caller or callee disagreeing on field widths, pointer order, receiver adjustment or cleanup, or by unchanged measured instruction shape after the corrections. The first corrected body and the subsequent aggregate experiments improved the measured distance. The two-component rotation local left only frame and stack-displacement differences; the three-component local removed them. Substituting canonical coordinate headers and explicit field-wise copying preserved the exact probe result. The original Zero Hour W3DView::scrollBy donor was read; its screen-to-world conversion differs, so no donor identity is transplanted.

| Trial | Source under build/rva006fe200 | Emitted bytes | Non-relocation differences | Probe quality |
|---|---|---:|---:|---:|
| Saved body | 00_saved.cpp | 317 | 212 | 0.2092 |
| Corrected ABI and comparisons | 01_corrected.cpp | 345 | 177 | 0.4699 |
| Field-wise native coordinate copy | 02_set.cpp | 347 | 154 | 0.5473 |
| Two-component rotation aggregate | 03_aggregate.cpp | 349 | 14 | 0.9599 |
| Three-component rotation aggregate | 04_rotation3.cpp | 349 | 0 | 1.0 |
| Canonical headers and field-wise stores | 05_canonical.cpp | 349 | 0 | 1.0 |

The quality metric ranks experiments; only the strict scoped gate resolves relocations and validates byte equality. Every trial source and unedited compiler probe is retained under build/rva006fe200. The owner's original identity remains unknown and is not a blocker for its complete address-derived ABI. A named owner, a different dynamic table on the verified receiver route, a callee reading a different field representation or a differing strict relocation target would refute this reconstruction.

## Raw decoded evidence

The following are the unedited decoder outputs for the target and the complete bodies used as ABI evidence. Labels inherited from generated rows are lookup aids, not identity proof.

### retail_target.log

```text
; ?d_006fe200@@YAXXZ rva=0x006FE200 size=349
+0000 8b 44 24 04              mov     eax, dword ptr [esp + 4]                 
+0004 83 ec 20                 sub     esp, 0x20                                
+0007 85 c0                    test    eax, eax                                 
+0009 56                       push    esi                                      
+000a 8b f1                    mov     esi, ecx                                 
+000c 0f 84 44 01 00 00        je      0xafe356                                 
+0012 d9 00                    fld     dword ptr [eax]                          
+0014 d8 0d 3c 53 07 01        fmul    dword ptr [0x107533c]                    ;?g_bfmeK1253@@3MB
+001a d9 5c 24 04              fstp    dword ptr [esp + 4]                      
+001e d9 40 04                 fld     dword ptr [eax + 4]                      
+0021 d8 0d 3c 53 07 01        fmul    dword ptr [0x107533c]                    ;?g_bfmeK1253@@3MB
+0027 d9 5c 24 08              fstp    dword ptr [esp + 8]                      
+002b d9 86 e4 00 00 00        fld     dword ptr [esi + 0xe4]                   
+0031 d8 1d 74 82 2f 01        fcomp   dword ptr [0x12f8274]                    
+0037 df e0                    fnstsw  ax                                       
+0039 f6 c4 41                 test    ah, 0x41                                 
+003c 0f 84 14 01 00 00        je      0xafe356                                 
+0042 d9 05 50 53 07 01        fld     dword ptr [0x1075350]                    ;g_bfmeDefaultBR
+0048 d9 44 24 04              fld     dword ptr [esp + 4]                      
+004c da e9                    fucompp                                          
+004e df e0                    fnstsw  ax                                       
+0050 f6 c4 44                 test    ah, 0x44                                 
+0053 7a 17                    jp      0xafe26c                                 
+0055 d9 05 50 53 07 01        fld     dword ptr [0x1075350]                    ;g_bfmeDefaultBR
+005b d9 44 24 08              fld     dword ptr [esp + 8]                      
+005f da e9                    fucompp                                          
+0061 df e0                    fnstsw  ax                                       
+0063 f6 c4 44                 test    ah, 0x44                                 
+0066 0f 8b 94 00 00 00        jnp     0xafe300                                 
+006c d9 86 a8 00 00 00        fld     dword ptr [esi + 0xa8]                   
+0072 8b 86 b0 00 00 00        mov     eax, dword ptr [esi + 0xb0]              
+0078 d9 86 ac 00 00 00        fld     dword ptr [esi + 0xac]                   
+007e 8b 16                    mov     edx, dword ptr [esi]                     
+0080 d9 86 cc 00 00 00        fld     dword ptr [esi + 0xcc]                   
+0086 89 44 24 14              mov     dword ptr [esp + 0x14], eax              
+008a d9 e0                    fchs                                             
+008c 8d 44 24 0c              lea     eax, [esp + 0xc]                         
+0090 d9 c0                    fld     st(0)                                    
+0092 50                       push    eax                                      
+0093 d9 fe                    fsin                                             
+0095 8b ce                    mov     ecx, esi                                 
+0097 d9 c9                    fxch    st(1)                                    
+0099 d9 ff                    fcos                                             
+009b d9 44 24 08              fld     dword ptr [esp + 8]                      
+009f d8 c9                    fmul    st(1)                                    
+00a1 d9 c2                    fld     st(2)                                    
+00a3 d8 4c 24 0c              fmul    dword ptr [esp + 0xc]                    
+00a7 de e9                    fsubp   st(1)                                    
+00a9 d9 5c 24 1c              fstp    dword ptr [esp + 0x1c]                   
+00ad d8 4c 24 0c              fmul    dword ptr [esp + 0xc]                    
+00b1 d9 c9                    fxch    st(1)                                    
+00b3 d8 4c 24 08              fmul    dword ptr [esp + 8]                      
+00b7 de c1                    faddp   st(1)                                    
+00b9 d9 44 24 1c              fld     dword ptr [esp + 0x1c]                   
+00bd d8 0d 6c 3b 08 01        fmul    dword ptr [0x1083b6c]                    
+00c3 d8 c3                    fadd    st(3)                                    
+00c5 d9 5c 24 10              fstp    dword ptr [esp + 0x10]                   
+00c9 d8 0d 6c 3b 08 01        fmul    dword ptr [0x1083b6c]                    
+00cf d8 e9                    fsubr   st(1)                                    
+00d1 d9 5c 24 14              fstp    dword ptr [esp + 0x14]                   
+00d5 dd d8                    fstp    st(0)                                    
+00d7 dd d8                    fstp    st(0)                                    
+00d9 ff 52 64                 call    dword ptr [edx + 0x64]                   
+00dc 8b 0d 6c 70 2f 01        mov     ecx, dword ptr [0x12f706c]               ;?g_bfmeGameCW@@3PAVBfmeGameCW@@A
+00e2 85 c9                    test    ecx, ecx                                 
+00e4 74 1a                    je      0xafe300                                 
+00e6 8b 54 24 0c              mov     edx, dword ptr [esp + 0xc]               
+00ea 8b 44 24 10              mov     eax, dword ptr [esp + 0x10]              
+00ee 89 54 24 04              mov     dword ptr [esp + 4], edx                 
+00f2 8d 54 24 04              lea     edx, [esp + 4]                           
+00f6 52                       push    edx                                      
+00f7 89 44 24 0c              mov     dword ptr [esp + 0xc], eax               
+00fb e8 00 cb 92 ff           call    0x42ae00                                 ;?j_0002ae00@@YAXXZ
+0100 d9 05 54 ac 2b 01        fld     dword ptr [0x12bac54]                    
+0106 d8 4c 24 2c              fmul    dword ptr [esp + 0x2c]                   
+010a d8 86 cc 00 00 00        fadd    dword ptr [esi + 0xcc]                   
+0110 d9 96 cc 00 00 00        fst     dword ptr [esi + 0xcc]                   
+0116 d9 05 50 ac 2b 01        fld     dword ptr [0x12bac50]                    
+011c d9 e0                    fchs                                             
+011e d9 5c 24 28              fstp    dword ptr [esp + 0x28]                   
+0122 d8 5c 24 28              fcomp   dword ptr [esp + 0x28]                   
+0126 df e0                    fnstsw  ax                                       
+0128 f6 c4 05                 test    ah, 5                                    
+012b 7a 0a                    jp      0xafe337                                 
+012d 8b 44 24 28              mov     eax, dword ptr [esp + 0x28]              
+0131 89 86 cc 00 00 00        mov     dword ptr [esi + 0xcc], eax              
+0137 d9 86 cc 00 00 00        fld     dword ptr [esi + 0xcc]                   
+013d d8 1d 50 ac 2b 01        fcomp   dword ptr [0x12bac50]                    
+0143 df e0                    fnstsw  ax                                       
+0145 f6 c4 41                 test    ah, 0x41                                 
+0148 75 0c                    jne     0xafe356                                 
+014a 8b 0d 50 ac 2b 01        mov     ecx, dword ptr [0x12bac50]               
+0150 89 8e cc 00 00 00        mov     dword ptr [esi + 0xcc], ecx              
+0156 5e                       pop     esi                                      
+0157 83 c4 20                 add     esp, 0x20                                
+015a c2 08 00                 ret     8
```

### retail_virtual.log

```text
; ?setCursorWorldPosition@Rva006FD2E0Mouse@@QAEXPBUCoord3D@@@Z rva=0x006FD2E0 size=174
+0000 8b 44 24 04              mov     eax, dword ptr [esp + 4]                 
+0004 53                       push    ebx                                      
+0005 56                       push    esi                                      
+0006 8b f1                    mov     esi, ecx                                 
+0008 8b 08                    mov     ecx, dword ptr [eax]                     
+000a 57                       push    edi                                      
+000b 89 8e a8 00 00 00        mov     dword ptr [esi + 0xa8], ecx              
+0011 8b 50 04                 mov     edx, dword ptr [eax + 4]                 
+0014 8d be a8 00 00 00        lea     edi, [esi + 0xa8]                        
+001a 89 96 ac 00 00 00        mov     dword ptr [esi + 0xac], edx              
+0020 8b 40 08                 mov     eax, dword ptr [eax + 8]                 
+0023 8d 9e ac 00 00 00        lea     ebx, [esi + 0xac]                        
+0029 89 86 b0 00 00 00        mov     dword ptr [esi + 0xb0], eax              
+002f 8b 0d 00 16 2f 01        mov     ecx, dword ptr [0x12f1600]               ;?TheTacticalView@@3PAVView@@A
+0035 8b 11                    mov     edx, dword ptr [ecx]                     
+0037 ff 52 20                 call    dword ptr [edx + 0x20]                   
+003a 84 c0                    test    al, al                                   
+003c 74 6a                    je      0xafd388                                 
+003e d9 07                    fld     dword ptr [edi]                          
+0040 8d 8e dc 00 00 00        lea     ecx, [esi + 0xdc]                        
+0046 d8 19                    fcomp   dword ptr [ecx]                          
+0048 df e0                    fnstsw  ax                                       
+004a f6 c4 05                 test    ah, 5                                    
+004d 8b c7                    mov     eax, edi                                 
+004f 7b 02                    jnp     0xafd333                                 
+0051 8b c1                    mov     eax, ecx                                 
+0053 8b 00                    mov     eax, dword ptr [eax]                     
+0055 89 07                    mov     dword ptr [edi], eax                     
+0057 d9 03                    fld     dword ptr [ebx]                          
+0059 d8 9e e0 00 00 00        fcomp   dword ptr [esi + 0xe0]                   
+005f 8d 8e e0 00 00 00        lea     ecx, [esi + 0xe0]                        
+0065 df e0                    fnstsw  ax                                       
+0067 f6 c4 05                 test    ah, 5                                    
+006a 7a 02                    jp      0xafd34e                                 
+006c 8b cb                    mov     ecx, ebx                                 
+006e 8b 09                    mov     ecx, dword ptr [ecx]                     
+0070 89 0b                    mov     dword ptr [ebx], ecx                     
+0072 d9 07                    fld     dword ptr [edi]                          
+0074 d8 9e d4 00 00 00        fcomp   dword ptr [esi + 0xd4]                   
+007a 8d 8e d4 00 00 00        lea     ecx, [esi + 0xd4]                        
+0080 df e0                    fnstsw  ax                                       
+0082 f6 c4 41                 test    ah, 0x41                                 
+0085 75 02                    jne     0xafd369                                 
+0087 8b cf                    mov     ecx, edi                                 
+0089 8b 11                    mov     edx, dword ptr [ecx]                     
+008b 89 17                    mov     dword ptr [edi], edx                     
+008d d9 03                    fld     dword ptr [ebx]                          
+008f d8 9e d8 00 00 00        fcomp   dword ptr [esi + 0xd8]                   
+0095 8d 8e d8 00 00 00        lea     ecx, [esi + 0xd8]                        
+009b df e0                    fnstsw  ax                                       
+009d f6 c4 41                 test    ah, 0x41                                 
+00a0 75 02                    jne     0xafd384                                 
+00a2 8b cb                    mov     ecx, ebx                                 
+00a4 8b 01                    mov     eax, dword ptr [ecx]                     
+00a6 89 03                    mov     dword ptr [ebx], eax                     
+00a8 5f                       pop     edi                                      
+00a9 5e                       pop     esi                                      
+00aa 5b                       pop     ebx                                      
+00ab c2 04 00                 ret     4
```

### retail_manager.log

```text
; ?rva00615a70@BfmeLivingWorldManager@@QAEXABUCoord2D@@@Z rva=0x00615A70 size=126
+0000 83 ec 08                 sub     esp, 8                                   
+0003 57                       push    edi                                      
+0004 8d 44 24 04              lea     eax, [esp + 4]                           
+0008 50                       push    eax                                      
+0009 81 c1 94 01 00 00        add     ecx, 0x194                               
+000f e8 dd 3a 9f ff           call    0x409561                                 ;?j_00009561@@YAXXZ
+0014 8b 7c 24 04              mov     edi, dword ptr [esp + 4]                 
+0018 85 ff                    test    edi, edi                                 
+001a 74 5b                    je      0xa15ae7                                 
+001c 53                       push    ebx                                      
+001d 8b 5c 24 14              mov     ebx, dword ptr [esp + 0x14]              
+0021 56                       push    esi                                      
+0022 8b 74 24 10              mov     esi, dword ptr [esp + 0x10]              
+0026 8b 4f 08                 mov     ecx, dword ptr [edi + 8]                 
+0029 53                       push    ebx                                      
+002a e8 4d ad a1 ff           call    0x4307ec                                 ;?j_000307ec@@YAXXZ
+002f 8b 07                    mov     eax, dword ptr [edi]                     
+0031 85 c0                    test    eax, eax                                 
+0033 74 04                    je      0xa15aa9                                 
+0035 8b f8                    mov     edi, eax                                 
+0037 eb 38                    jmp     0xa15ae1                                 
+0039 8b 4e 08                 mov     ecx, dword ptr [esi + 8]                 
+003c 2b 4e 04                 sub     ecx, dword ptr [esi + 4]                 
+003f c1 f9 02                 sar     ecx, 2                                   
+0042 51                       push    ecx                                      
+0043 83 c7 04                 add     edi, 4                                   
+0046 57                       push    edi                                      
+0047 8b ce                    mov     ecx, esi                                 
+0049 e8 bc 0d 9f ff           call    0x40687a                                 ;?j_0000687a@@YAXXZ
+004e 8b 4e 08                 mov     ecx, dword ptr [esi + 8]                 
+0051 2b 4e 04                 sub     ecx, dword ptr [esi + 4]                 
+0054 c1 f9 02                 sar     ecx, 2                                   
+0057 33 d2                    xor     edx, edx                                 
+0059 8d a4 24 00 00 00 00     lea     esp, [esp]                               
+0060 40                       inc     eax                                      
+0061 3b c1                    cmp     eax, ecx                                 
+0063 73 0a                    jae     0xa15adf                                 
+0065 8b 56 04                 mov     edx, dword ptr [esi + 4]                 
+0068 8b 14 82                 mov     edx, dword ptr [edx + eax*4]             
+006b 85 d2                    test    edx, edx                                 
+006d 74 f1                    je      0xa15ad0                                 
+006f 8b fa                    mov     edi, edx                                 
+0071 85 ff                    test    edi, edi                                 
+0073 75 b1                    jne     0xa15a96                                 
+0075 5e                       pop     esi                                      
+0076 5b                       pop     ebx                                      
+0077 5f                       pop     edi                                      
+0078 83 c4 08                 add     esp, 8                                   
+007b c2 04 00                 ret     4
```

### retail_point_helper.log

```text
; ?bfmeUpdateBFromPointGuardedNA@BfmeThingNA@@QAEXABVCoord2D@@@Z rva=0x0061C2F0 size=109
+0000 53                       push    ebx                                      
+0001 56                       push    esi                                      
+0002 8b f1                    mov     esi, ecx                                 
+0004 8b 5e 18                 mov     ebx, dword ptr [esi + 0x18]              
+0007 f6 c3 02                 test    bl, 2                                    
+000a 74 06                    je      0xa1c302                                 
+000c c6 46 31 00              mov     byte ptr [esi + 0x31], 0                 
+0010 eb 24                    jmp     0xa1c326                                 
+0012 f6 c3 05                 test    bl, 5                                    
+0015 75 06                    jne     0xa1c30d                                 
+0017 c6 46 31 01              mov     byte ptr [esi + 0x31], 1                 
+001b eb 19                    jmp     0xa1c326                                 
+001d 8b 44 24 0c              mov     eax, dword ptr [esp + 0xc]               
+0021 50                       push    eax                                      
+0022 8d 4e 1c                 lea     ecx, [esi + 0x1c]                        
+0025 e8 8b 94 a2 ff           call    0x4457a5                                 ;?j_000457a5@@YAXXZ
+002a 84 c0                    test    al, al                                   
+002c 88 46 31                 mov     byte ptr [esi + 0x31], al                
+002f 74 05                    je      0xa1c326                                 
+0031 f6 c3 04                 test    bl, 4                                    
+0034 75 32                    jne     0xa1c358                                 
+0036 8a 46 31                 mov     al, byte ptr [esi + 0x31]                
+0039 84 c0                    test    al, al                                   
+003b 74 1f                    je      0xa1c34c                                 
+003d 8a 46 32                 mov     al, byte ptr [esi + 0x32]                
+0040 84 c0                    test    al, al                                   
+0042 74 18                    je      0xa1c34c                                 
+0044 f6 c3 10                 test    bl, 0x10                                 
+0047 74 07                    je      0xa1c340                                 
+0049 8a 46 30                 mov     al, byte ptr [esi + 0x30]                
+004c 84 c0                    test    al, al                                   
+004e 75 18                    jne     0xa1c358                                 
+0050 8b ce                    mov     ecx, esi                                 
+0052 e8 e3 68 9e ff           call    0x402c2a                                 ;?j_00002c2a@@YAXXZ
+0057 5e                       pop     esi                                      
+0058 5b                       pop     ebx                                      
+0059 c2 04 00                 ret     4                                        
+005c f6 c3 20                 test    bl, 0x20                                 
+005f 75 07                    jne     0xa1c358                                 
+0061 8b ce                    mov     ecx, esi                                 
+0063 e8 8c ec a1 ff           call    0x43afe4                                 ;?j_0003afe4@@YAXXZ
+0068 5e                       pop     esi                                      
+0069 5b                       pop     ebx                                      
+006a c2 04 00                 ret     4
```

### retail_region.log

```text
; ?isInside@Region2D@@QBE_NABVCoord2D@@@Z rva=0x0061BA90 size=66
+0000 8b 54 24 04              mov     edx, dword ptr [esp + 4]                 
+0004 d9 02                    fld     dword ptr [edx]                          
+0006 d8 19                    fcomp   dword ptr [ecx]                          
+0008 df e0                    fnstsw  ax                                       
+000a f6 c4 41                 test    ah, 0x41                                 
+000d 75 2e                    jne     0xa1bacd                                 
+000f d9 02                    fld     dword ptr [edx]                          
+0011 d8 59 08                 fcomp   dword ptr [ecx + 8]                      
+0014 df e0                    fnstsw  ax                                       
+0016 f6 c4 05                 test    ah, 5                                    
+0019 7a 22                    jp      0xa1bacd                                 
+001b d9 42 04                 fld     dword ptr [edx + 4]                      
+001e d8 59 04                 fcomp   dword ptr [ecx + 4]                      
+0021 df e0                    fnstsw  ax                                       
+0023 f6 c4 41                 test    ah, 0x41                                 
+0026 75 15                    jne     0xa1bacd                                 
+0028 d9 42 04                 fld     dword ptr [edx + 4]                      
+002b d8 59 0c                 fcomp   dword ptr [ecx + 0xc]                    
+002e df e0                    fnstsw  ax                                       
+0030 f6 c4 05                 test    ah, 5                                    
+0033 7a 08                    jp      0xa1bacd                                 
+0035 b8 01 00 00 00           mov     eax, 1                                   
+003a c2 04 00                 ret     4                                        
+003d 33 c0                    xor     eax, eax                                 
+003f c2 04 00                 ret     4
```

### retail_scroll_caller.log

```text
; ?rva005B4D40@Calls004329D0@@QAEXXZ rva=0x005B4D40 size=902
+0000 a1 28 10 2f 01           mov     eax, dword ptr [0x12f1028]               ;?Glo012F1028@@3PAVGlo012F1028Type@@A
+0005 83 ec 14                 sub     esp, 0x14                                
+0008 85 c0                    test    eax, eax                                 
+000a 56                       push    esi                                      
+000b 8b f1                    mov     esi, ecx                                 
+000d 0f 84 6e 03 00 00        je      0x9b50c1                                 
+0013 8a 48 2c                 mov     cl, byte ptr [eax + 0x2c]                
+0016 84 c9                    test    cl, cl                                   
+0018 0f 84 63 03 00 00        je      0x9b50c1                                 
+001e 8b 0d 98 08 2f 01        mov     ecx, dword ptr [0x12f0898]               ;?TheBfmeGameLogic@@3PAURva00367E30Logic@@A
+0024 e8 2d df a6 ff           call    0x422c96                                 ;?j_00022c96@@YAXXZ
+0029 84 c0                    test    al, al                                   
+002b 0f 85 50 03 00 00        jne     0x9b50c1                                 
+0031 a1 28 10 2f 01           mov     eax, dword ptr [0x12f1028]               ;?Glo012F1028@@3PAVGlo012F1028Type@@A
+0036 c6 40 1c 00              mov     byte ptr [eax + 0x1c], 0                 
+003a 8a 46 2c                 mov     al, byte ptr [esi + 0x2c]                
+003d 84 c0                    test    al, al                                   
+003f c7 44 24 10 00 00 00 00  mov     dword ptr [esp + 0x10], 0                
+0047 c7 44 24 14 00 00 00 00  mov     dword ptr [esp + 0x14], 0                
+004f c7 44 24 04 00 00 00 00  mov     dword ptr [esp + 4], 0                   
+0057 0f 84 d3 02 00 00        je      0x9b5070                                 
+005d 8b 0d 48 70 2f 01        mov     ecx, dword ptr [0x12f7048]               ;?g_bfmeStateDF@@3PAVBfmeHostESM@@A
+0063 e8 a5 3e a9 ff           call    0x448c4d                                 ;?j_00048c4d@@YAXXZ
+0068 84 c0                    test    al, al                                   
+006a 74 24                    je      0x9b4dd0                                 
+006c 8b 46 04                 mov     eax, dword ptr [esi + 4]                 
+006f a8 01                    test    al, 1                                    
+0071 74 04                    je      0x9b4db7                                 
+0073 48                       dec     eax                                      
+0074 89 46 04                 mov     dword ptr [esi + 4], eax                 
+0077 8b 46 04                 mov     eax, dword ptr [esi + 4]                 
+007a 85 c0                    test    eax, eax                                 
+007c 7d 0c                    jge     0x9b4dca                                 
+007e c7 46 04 00 00 00 00     mov     dword ptr [esi + 4], 0                   
+0085 8b 46 04                 mov     eax, dword ptr [esi + 4]                 
+0088 85 c0                    test    eax, eax                                 
+008a 75 04                    jne     0x9b4dd0                                 
+008c c6 46 2c 00              mov     byte ptr [esi + 0x2c], 0                 
+0090 8a 46 2c                 mov     al, byte ptr [esi + 0x2c]                
+0093 84 c0                    test    al, al                                   
+0095 0f 84 95 02 00 00        je      0x9b5070                                 
+009b f6 46 04 01              test    byte ptr [esi + 4], 1                    
+009f 57                       push    edi                                      
+00a0 0f 84 ef 00 00 00        je      0x9b4ed5                                 
+00a6 8b 0d 8c 14 2f 01        mov     ecx, dword ptr [0x12f148c]               ;?TheInGameUI@@3PAVInGameUI@@A
+00ac 8a 81 bd 12 00 00        mov     al, byte ptr [ecx + 0x12bd]              
+00b2 84 c0                    test    al, al                                   
+00b4 74 54                    je      0x9b4e4a                                 
+00b6 8b 0d 70 12 2f 01        mov     ecx, dword ptr [0x12f1270]               ;?TheDisplay@@3PAVDisplay@@A
+00bc 8b 11                    mov     edx, dword ptr [ecx]                     
+00be 55                       push    ebp                                      
+00bf ff 52 2c                 call    dword ptr [edx + 0x2c]                   
+00c2 8b 0d 70 12 2f 01        mov     ecx, dword ptr [0x12f1270]               ;?TheDisplay@@3PAVDisplay@@A
+00c8 8b f8                    mov     edi, eax                                 
+00ca 8b 01                    mov     eax, dword ptr [ecx]                     
+00cc d1 ef                    shr     edi, 1                                   
+00ce ff 50 30                 call    dword ptr [eax + 0x30]                   
+00d1 8b 4e 14                 mov     ecx, dword ptr [esi + 0x14]              
+00d4 8b 56 0c                 mov     edx, dword ptr [esi + 0xc]               
+00d7 8d 2c 39                 lea     ebp, [ecx + edi]                         
+00da d1 e8                    shr     eax, 1                                   
+00dc 3b ea                    cmp     ebp, edx                                 
+00de 7d 05                    jge     0x9b4e25                                 
+00e0 89 6e 0c                 mov     dword ptr [esi + 0xc], ebp               
+00e3 eb 09                    jmp     0x9b4e2e                                 
+00e5 2b cf                    sub     ecx, edi                                 
+00e7 3b ca                    cmp     ecx, edx                                 
+00e9 7e 03                    jle     0x9b4e2e                                 
+00eb 89 4e 0c                 mov     dword ptr [esi + 0xc], ecx               
+00ee 8b 4e 18                 mov     ecx, dword ptr [esi + 0x18]              
+00f1 8b 56 10                 mov     edx, dword ptr [esi + 0x10]              
+00f4 8d 3c 01                 lea     edi, [ecx + eax]                         
+00f7 3b fa                    cmp     edi, edx                                 
+00f9 5d                       pop     ebp                                      
+00fa 7d 05                    jge     0x9b4e41                                 
+00fc 89 7e 10                 mov     dword ptr [esi + 0x10], edi              
+00ff eb 09                    jmp     0x9b4e4a                                 
+0101 2b c8                    sub     ecx, eax                                 
+0103 3b ca                    cmp     ecx, edx                                 
+0105 7e 03                    jle     0x9b4e4a                                 
+0107 89 4e 10                 mov     dword ptr [esi + 0x10], ecx              
+010a 8b 56 0c                 mov     edx, dword ptr [esi + 0xc]               
+010d 8b 4e 14                 mov     ecx, dword ptr [esi + 0x14]              
+0110 8b 3d c8 d5 2e 01        mov     edi, dword ptr [0x12ed5c8]               ;?TheWritableGlobalData@@3PAURva006C9270GlobalData@@A
+0116 8b 46 10                 mov     eax, dword ptr [esi + 0x10]              
+0119 2b ca                    sub     ecx, edx                                 
+011b 8b 56 18                 mov     edx, dword ptr [esi + 0x18]              
+011e 89 4c 24 0c              mov     dword ptr [esp + 0xc], ecx               
+0122 db 44 24 0c              fild    dword ptr [esp + 0xc]                    
+0126 2b d0                    sub     edx, eax                                 
+0128 89 54 24 0c              mov     dword ptr [esp + 0xc], edx               
+012c d8 8f 64 0b 00 00        fmul    dword ptr [edi + 0xb64]                  
+0132 8d 4c 24 0c              lea     ecx, [esp + 0xc]                         
+0136 d9 54 24 14              fst     dword ptr [esp + 0x14]                   
+013a db 44 24 0c              fild    dword ptr [esp + 0xc]                    
+013e d8 8f 68 0b 00 00        fmul    dword ptr [edi + 0xb68]                  
+0144 d9 54 24 18              fst     dword ptr [esp + 0x18]                   
+0148 d9 c9                    fxch    st(1)                                    
+014a d9 5c 24 0c              fstp    dword ptr [esp + 0xc]                    
+014e d9 5c 24 10              fstp    dword ptr [esp + 0x10]                   
+0152 e8 78 16 a5 ff           call    0x40650f                                 ;?j_0000650f@@YAXXZ
+0157 d9 87 bc 0b 00 00        fld     dword ptr [edi + 0xbbc]                  
+015d d9 c0                    fld     st(0)                                    
+015f d8 8f 64 0b 00 00        fmul    dword ptr [edi + 0xb64]                  
+0165 d8 c9                    fmul    st(1)                                    
+0167 d8 4c 24 0c              fmul    dword ptr [esp + 0xc]                    
+016b d8 44 24 14              fadd    dword ptr [esp + 0x14]                   
+016f d9 5c 24 14              fstp    dword ptr [esp + 0x14]                   
+0173 dd d8                    fstp    st(0)                                    
+0175 d9 87 bc 0b 00 00        fld     dword ptr [edi + 0xbbc]                  
+017b d9 c0                    fld     st(0)                                    
+017d d8 8f 68 0b 00 00        fmul    dword ptr [edi + 0xb68]                  
+0183 d8 c9                    fmul    st(1)                                    
+0185 d8 4c 24 10              fmul    dword ptr [esp + 0x10]                   
+0189 d8 44 24 18              fadd    dword ptr [esp + 0x18]                   
+018d d9 5c 24 18              fstp    dword ptr [esp + 0x18]                   
+0191 dd d8                    fstp    st(0)                                    
+0193 eb 06                    jmp     0x9b4edb                                 
+0195 8b 3d c8 d5 2e 01        mov     edi, dword ptr [0x12ed5c8]               ;?TheWritableGlobalData@@3PAURva006C9270GlobalData@@A
+019b 8b 46 04                 mov     eax, dword ptr [esi + 4]                 
+019e a8 02                    test    al, 2                                    
+01a0 74 18                    je      0x9b4efa                                 
+01a2 8b 4e 24                 mov     ecx, dword ptr [esi + 0x24]              
+01a5 2b 4e 1c                 sub     ecx, dword ptr [esi + 0x1c]              
+01a8 89 4c 24 0c              mov     dword ptr [esp + 0xc], ecx               
+01ac db 44 24 0c              fild    dword ptr [esp + 0xc]                    
+01b0 d8 0d 4c 7f 0e 01        fmul    dword ptr [0x10e7f4c]                    
+01b6 d9 5c 24 08              fstp    dword ptr [esp + 8]                      
+01ba a8 04                    test    al, 4                                    
+01bc 0f 84 84 00 00 00        je      0x9b4f86                                 
+01c2 8a 4e 2d                 mov     cl, byte ptr [esi + 0x2d]                
+01c5 84 c9                    test    cl, cl                                   
+01c7 74 1a                    je      0x9b4f23                                 
+01c9 d9 87 bc 0b 00 00        fld     dword ptr [edi + 0xbbc]                  
+01cf d8 8f 68 0b 00 00        fmul    dword ptr [edi + 0xb68]                  
+01d5 d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+01db d8 6c 24 18              fsubr   dword ptr [esp + 0x18]                   
+01df d9 5c 24 18              fstp    dword ptr [esp + 0x18]                   
+01e3 8a 4e 2e                 mov     cl, byte ptr [esi + 0x2e]                
+01e6 84 c9                    test    cl, cl                                   
+01e8 74 1a                    je      0x9b4f44                                 
+01ea d9 87 bc 0b 00 00        fld     dword ptr [edi + 0xbbc]                  
+01f0 d8 8f 68 0b 00 00        fmul    dword ptr [edi + 0xb68]                  
+01f6 d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+01fc d8 44 24 18              fadd    dword ptr [esp + 0x18]                   
+0200 d9 5c 24 18              fstp    dword ptr [esp + 0x18]                   
+0204 8a 4e 2f                 mov     cl, byte ptr [esi + 0x2f]                
+0207 84 c9                    test    cl, cl                                   
+0209 74 1a                    je      0x9b4f65                                 
+020b d9 87 bc 0b 00 00        fld     dword ptr [edi + 0xbbc]                  
+0211 d8 8f 64 0b 00 00        fmul    dword ptr [edi + 0xb64]                  
+0217 d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+021d d8 6c 24 14              fsubr   dword ptr [esp + 0x14]                   
+0221 d9 5c 24 14              fstp    dword ptr [esp + 0x14]                   
+0225 8a 4e 30                 mov     cl, byte ptr [esi + 0x30]                
+0228 84 c9                    test    cl, cl                                   
+022a 74 1a                    je      0x9b4f86                                 
+022c d9 87 bc 0b 00 00        fld     dword ptr [edi + 0xbbc]                  
+0232 d8 8f 64 0b 00 00        fmul    dword ptr [edi + 0xb64]                  
+0238 d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+023e d8 44 24 14              fadd    dword ptr [esp + 0x14]                   
+0242 d9 5c 24 14              fstp    dword ptr [esp + 0x14]                   
+0246 a8 08                    test    al, 8                                    
+0248 0f 84 bc 00 00 00        je      0x9b504a                                 
+024e 8b 0d 70 12 2f 01        mov     ecx, dword ptr [0x12f1270]               ;?TheDisplay@@3PAVDisplay@@A
+0254 8b 11                    mov     edx, dword ptr [ecx]                     
+0256 ff 52 30                 call    dword ptr [edx + 0x30]                   
+0259 8b 0d 70 12 2f 01        mov     ecx, dword ptr [0x12f1270]               ;?TheDisplay@@3PAVDisplay@@A
+025f 8b f8                    mov     edi, eax                                 
+0261 8b 01                    mov     eax, dword ptr [ecx]                     
+0263 ff 50 2c                 call    dword ptr [eax + 0x2c]                   
+0266 8b 4e 18                 mov     ecx, dword ptr [esi + 0x18]              
+0269 83 f9 03                 cmp     ecx, 3                                   
+026c 8b 15 c8 d5 2e 01        mov     edx, dword ptr [0x12ed5c8]               ;?TheWritableGlobalData@@3PAURva006C9270GlobalData@@A
+0272 7d 20                    jge     0x9b4fd4                                 
+0274 d9 82 bc 0b 00 00        fld     dword ptr [edx + 0xbbc]                  
+027a d8 8a 6c 0b 00 00        fmul    dword ptr [edx + 0xb6c]                  
+0280 d8 8a 68 0b 00 00        fmul    dword ptr [edx + 0xb68]                  
+0286 d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+028c d8 6c 24 18              fsubr   dword ptr [esp + 0x18]                   
+0290 d9 5c 24 18              fstp    dword ptr [esp + 0x18]                   
+0294 83 c7 fd                 add     edi, -3                                  
+0297 3b cf                    cmp     ecx, edi                                 
+0299 72 20                    jb      0x9b4ffb                                 
+029b d9 82 bc 0b 00 00        fld     dword ptr [edx + 0xbbc]                  
+02a1 d8 8a 6c 0b 00 00        fmul    dword ptr [edx + 0xb6c]                  
+02a7 d8 8a 68 0b 00 00        fmul    dword ptr [edx + 0xb68]                  
+02ad d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+02b3 d8 44 24 18              fadd    dword ptr [esp + 0x18]                   
+02b7 d9 5c 24 18              fstp    dword ptr [esp + 0x18]                   
+02bb 8b 76 14                 mov     esi, dword ptr [esi + 0x14]              
+02be 83 fe 03                 cmp     esi, 3                                   
+02c1 7d 20                    jge     0x9b5023                                 
+02c3 d9 82 bc 0b 00 00        fld     dword ptr [edx + 0xbbc]                  
+02c9 d8 8a 6c 0b 00 00        fmul    dword ptr [edx + 0xb6c]                  
+02cf d8 8a 64 0b 00 00        fmul    dword ptr [edx + 0xb64]                  
+02d5 d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+02db d8 6c 24 14              fsubr   dword ptr [esp + 0x14]                   
+02df d9 5c 24 14              fstp    dword ptr [esp + 0x14]                   
+02e3 83 c0 fd                 add     eax, -3                                  
+02e6 3b f0                    cmp     esi, eax                                 
+02e8 72 20                    jb      0x9b504a                                 
+02ea d9 82 bc 0b 00 00        fld     dword ptr [edx + 0xbbc]                  
+02f0 d8 8a 6c 0b 00 00        fmul    dword ptr [edx + 0xb6c]                  
+02f6 d8 8a 64 0b 00 00        fmul    dword ptr [edx + 0xb64]                  
+02fc d8 0d 44 de 10 01        fmul    dword ptr [0x110de44]                    
+0302 d8 44 24 14              fadd    dword ptr [esp + 0x14]                   
+0306 d9 5c 24 14              fstp    dword ptr [esp + 0x14]                   
+030a 8b 44 24 08              mov     eax, dword ptr [esp + 8]                 
+030e 8b 0d 48 70 2f 01        mov     ecx, dword ptr [0x12f7048]               ;?g_bfmeStateDF@@3PAVBfmeHostESM@@A
+0314 8b 11                    mov     edx, dword ptr [ecx]                     
+0316 50                       push    eax                                      
+0317 8d 44 24 18              lea     eax, [esp + 0x18]                        
+031b 50                       push    eax                                      
+031c ff 52 14                 call    dword ptr [edx + 0x14]                   
+031f 8b 0d 48 70 2f 01        mov     ecx, dword ptr [0x12f7048]               ;?g_bfmeStateDF@@3PAVBfmeHostESM@@A
+0325 8b 11                    mov     edx, dword ptr [ecx]                     
+0327 5f                       pop     edi                                      
+0328 ff 52 34                 call    dword ptr [edx + 0x34]                   
+032b 5e                       pop     esi                                      
+032c 83 c4 14                 add     esp, 0x14                                
+032f c3                       ret                                              
+0330 8a 46 31                 mov     al, byte ptr [esi + 0x31]                
+0333 84 c0                    test    al, al                                   
+0335 74 13                    je      0x9b508a                                 
+0337 a1 c8 d5 2e 01           mov     eax, dword ptr [0x12ed5c8]               ;?TheWritableGlobalData@@3PAURva006C9270GlobalData@@A
+033c d9 80 c8 0c 00 00        fld     dword ptr [eax + 0xcc8]                  
+0342 d8 0d 40 de 10 01        fmul    dword ptr [0x110de40]                    
+0348 eb 18                    jmp     0x9b50a2                                 
+034a 8a 46 32                 mov     al, byte ptr [esi + 0x32]                
+034d 84 c0                    test    al, al                                   
+034f 74 25                    je      0x9b50b6                                 
+0351 a1 c8 d5 2e 01           mov     eax, dword ptr [0x12ed5c8]               ;?TheWritableGlobalData@@3PAURva006C9270GlobalData@@A
+0356 d9 80 c8 0c 00 00        fld     dword ptr [eax + 0xcc8]                  
+035c d8 0d f0 88 08 01        fmul    dword ptr [0x10888f0]                    
+0362 8b 0d 48 70 2f 01        mov     ecx, dword ptr [0x12f7048]               ;?g_bfmeStateDF@@3PAVBfmeHostESM@@A
+0368 8b 11                    mov     edx, dword ptr [ecx]                     
+036a 51                       push    ecx                                      
+036b 8d 44 24 14              lea     eax, [esp + 0x14]                        
+036f d9 1c 24                 fstp    dword ptr [esp]                          
+0372 50                       push    eax                                      
+0373 ff 52 14                 call    dword ptr [edx + 0x14]                   
+0376 8b 0d 48 70 2f 01        mov     ecx, dword ptr [0x12f7048]               ;?g_bfmeStateDF@@3PAVBfmeHostESM@@A
+037c 8b 11                    mov     edx, dword ptr [ecx]                     
+037e ff 52 34                 call    dword ptr [edx + 0x34]                   
+0381 5e                       pop     esi                                      
+0382 83 c4 14                 add     esp, 0x14                                
+0385 c3                       ret
```

### retail_base_constructor.log

```text
; ??0Rva006092D0State@@QAE@XZ rva=0x0060A000 size=237
+0000 6a ff                    push    -1                                       
+0002 68 ab da 03 01           push    0x103daab                                ;eh_00c3daab
+0007 64 a1 00 00 00 00        mov     eax, dword ptr fs:[0]                    
+000d 50                       push    eax                                      
+000e 64 89 25 00 00 00 00     mov     dword ptr fs:[0], esp                    
+0015 83 ec 08                 sub     esp, 8                                   
+0018 53                       push    ebx                                      
+0019 56                       push    esi                                      
+001a 57                       push    edi                                      
+001b 8b f1                    mov     esi, ecx                                 
+001d 89 74 24 10              mov     dword ptr [esp + 0x10], esi              
+0021 33 db                    xor     ebx, ebx                                 
+0023 c7 06 d0 5a 11 01        mov     dword ptr [esi], 0x1115ad0               
+0029 89 5e 04                 mov     dword ptr [esi + 4], ebx                 
+002c 88 5e 08                 mov     byte ptr [esi + 8], bl                   
+002f 88 5e 09                 mov     byte ptr [esi + 9], bl                   
+0032 88 5e 0a                 mov     byte ptr [esi + 0xa], bl                 
+0035 88 5e 0b                 mov     byte ptr [esi + 0xb], bl                 
+0038 89 5e 0c                 mov     dword ptr [esi + 0xc], ebx               
+003b 89 5e 10                 mov     dword ptr [esi + 0x10], ebx              
+003e 88 5e 14                 mov     byte ptr [esi + 0x14], bl                
+0041 88 5e 15                 mov     byte ptr [esi + 0x15], bl                
+0044 8d 7e 18                 lea     edi, [esi + 0x18]                        
+0047 89 1f                    mov     dword ptr [edi], ebx                     
+0049 89 5f 04                 mov     dword ptr [edi + 4], ebx                 
+004c 89 5f 08                 mov     dword ptr [edi + 8], ebx                 
+004f 89 5f 0c                 mov     dword ptr [edi + 0xc], ebx               
+0052 89 5f 10                 mov     dword ptr [edi + 0x10], ebx              
+0055 8b 47 0c                 mov     eax, dword ptr [edi + 0xc]               
+0058 89 47 18                 mov     dword ptr [edi + 0x18], eax              
+005b 89 5f 28                 mov     dword ptr [edi + 0x28], ebx              
+005e 89 5f 24                 mov     dword ptr [edi + 0x24], ebx              
+0061 89 5f 20                 mov     dword ptr [edi + 0x20], ebx              
+0064 89 5f 1c                 mov     dword ptr [edi + 0x1c], ebx              
+0067 89 5e 44                 mov     dword ptr [esi + 0x44], ebx              
+006a 89 5e 48                 mov     dword ptr [esi + 0x48], ebx              
+006d 89 5e 4c                 mov     dword ptr [esi + 0x4c], ebx              
+0070 89 5e 50                 mov     dword ptr [esi + 0x50], ebx              
+0073 89 5e 54                 mov     dword ptr [esi + 0x54], ebx              
+0076 89 5e 58                 mov     dword ptr [esi + 0x58], ebx              
+0079 89 5e 5c                 mov     dword ptr [esi + 0x5c], ebx              
+007c 88 5e 60                 mov     byte ptr [esi + 0x60], bl                
+007f 89 5e 64                 mov     dword ptr [esi + 0x64], ebx              
+0082 89 5e 68                 mov     dword ptr [esi + 0x68], ebx              
+0085 89 5e 6c                 mov     dword ptr [esi + 0x6c], ebx              
+0088 8b 0d 6c 70 2f 01        mov     ecx, dword ptr [0x12f706c]               ;?g_bfmeGameCW@@3PAVBfmeGameCW@@A
+008e 3b cb                    cmp     ecx, ebx                                 
+0090 89 5c 24 1c              mov     dword ptr [esp + 0x1c], ebx              
+0094 89 35 48 70 2f 01        mov     dword ptr [0x12f7048], esi               ;?g_bfmeStateDF@@3PAVBfmeHostESM@@A
+009a 74 05                    je      0xa0a0a1                                 
+009c e8 6c f1 a1 ff           call    0x42920d                                 ;?j_0002920d@@YAXXZ
+00a1 8b 4e 20                 mov     ecx, dword ptr [esi + 0x20]              
+00a4 8b 46 24                 mov     eax, dword ptr [esi + 0x24]              
+00a7 53                       push    ebx                                      
+00a8 8d 54 24 13              lea     edx, [esp + 0x13]                        
+00ac 52                       push    edx                                      
+00ad 51                       push    ecx                                      
+00ae 50                       push    eax                                      
+00af 50                       push    eax                                      
+00b0 e8 f0 45 a1 ff           call    0x41e6a5                                 ;?j_0001e6a5@@YAXXZ
+00b5 83 c4 14                 add     esp, 0x14                                
+00b8 53                       push    ebx                                      
+00b9 53                       push    ebx                                      
+00ba 53                       push    ebx                                      
+00bb 53                       push    ebx                                      
+00bc 8b cf                    mov     ecx, edi                                 
+00be 89 46 24                 mov     dword ptr [esi + 0x24], eax              
+00c1 e8 d7 8d a2 ff           call    0x432e9d                                 ;?j_00032e9d@@YAXXZ
+00c6 53                       push    ebx                                      
+00c7 53                       push    ebx                                      
+00c8 68 00 00 80 3f           push    0x3f800000                               
+00cd 68 00 00 80 3f           push    0x3f800000                               
+00d2 8b cf                    mov     ecx, edi                                 
+00d4 e8 c4 8d a2 ff           call    0x432e9d                                 ;?j_00032e9d@@YAXXZ
+00d9 8b 4c 24 14              mov     ecx, dword ptr [esp + 0x14]              
+00dd 5f                       pop     edi                                      
+00de 8b c6                    mov     eax, esi                                 
+00e0 5e                       pop     esi                                      
+00e1 5b                       pop     ebx                                      
+00e2 64 89 0d 00 00 00 00     mov     dword ptr fs:[0], ecx                    
+00e9 83 c4 14                 add     esp, 0x14                                
+00ec c3                       ret
```

### retail_constructor.log

```text
; ??0Rva006FC970@@QAE@XZ rva=0x006FC970 size=239
+0000 56                       push    esi                                      
+0001 57                       push    edi                                      
+0002 8b f1                    mov     esi, ecx                                 
+0004 e8 24 ef 90 ff           call    0x40b89d                                 ;?j_0000b89d@@YAXXZ
+0009 33 c0                    xor     eax, eax                                 
+000b 89 46 70                 mov     dword ptr [esi + 0x70], eax              
+000e 89 46 74                 mov     dword ptr [esi + 0x74], eax              
+0011 89 46 78                 mov     dword ptr [esi + 0x78], eax              
+0014 89 46 7c                 mov     dword ptr [esi + 0x7c], eax              
+0017 89 86 80 00 00 00        mov     dword ptr [esi + 0x80], eax              
+001d 89 86 84 00 00 00        mov     dword ptr [esi + 0x84], eax              
+0023 c7 06 c0 07 12 01        mov     dword ptr [esi], 0x11207c0               
+0029 ba 00 00 80 3f           mov     edx, 0x3f800000                          
+002e 89 96 88 00 00 00        mov     dword ptr [esi + 0x88], edx              
+0034 89 96 8c 00 00 00        mov     dword ptr [esi + 0x8c], edx              
+003a 89 86 90 00 00 00        mov     dword ptr [esi + 0x90], eax              
+0040 89 86 94 00 00 00        mov     dword ptr [esi + 0x94], eax              
+0046 89 86 98 00 00 00        mov     dword ptr [esi + 0x98], eax              
+004c b9 66 66 66 3f           mov     ecx, 0x3f666666                          
+0051 89 8e 9c 00 00 00        mov     dword ptr [esi + 0x9c], ecx              
+0057 89 8e a0 00 00 00        mov     dword ptr [esi + 0xa0], ecx              
+005d 89 8e a4 00 00 00        mov     dword ptr [esi + 0xa4], ecx              
+0063 89 86 a8 00 00 00        mov     dword ptr [esi + 0xa8], eax              
+0069 89 86 ac 00 00 00        mov     dword ptr [esi + 0xac], eax              
+006f 89 86 b0 00 00 00        mov     dword ptr [esi + 0xb0], eax              
+0075 89 86 b4 00 00 00        mov     dword ptr [esi + 0xb4], eax              
+007b 89 86 b8 00 00 00        mov     dword ptr [esi + 0xb8], eax              
+0081 89 86 bc 00 00 00        mov     dword ptr [esi + 0xbc], eax              
+0087 89 86 c0 00 00 00        mov     dword ptr [esi + 0xc0], eax              
+008d 89 86 c4 00 00 00        mov     dword ptr [esi + 0xc4], eax              
+0093 89 86 c8 00 00 00        mov     dword ptr [esi + 0xc8], eax              
+0099 89 86 cc 00 00 00        mov     dword ptr [esi + 0xcc], eax              
+009f 89 86 e8 00 00 00        mov     dword ptr [esi + 0xe8], eax              
+00a5 89 86 38 01 00 00        mov     dword ptr [esi + 0x138], eax             
+00ab 89 86 3c 01 00 00        mov     dword ptr [esi + 0x13c], eax             
+00b1 89 86 40 01 00 00        mov     dword ptr [esi + 0x140], eax             
+00b7 89 86 44 01 00 00        mov     dword ptr [esi + 0x144], eax             
+00bd 89 86 48 01 00 00        mov     dword ptr [esi + 0x148], eax             
+00c3 8d be 58 01 00 00        lea     edi, [esi + 0x158]                       
+00c9 c7 86 d0 00 00 00 00 00 20 41 mov     dword ptr [esi + 0xd0], 0x41200000       
+00d3 89 96 e4 00 00 00        mov     dword ptr [esi + 0xe4], edx              
+00d9 c7 86 ec 00 00 00 92 0a 06 3f mov     dword ptr [esi + 0xec], 0x3f060a92       
+00e3 b9 c4 09 00 00           mov     ecx, 0x9c4                               
+00e8 f3 ab                    rep stosd dword ptr es:[edi], eax                  
+00ea 5f                       pop     edi                                      
+00eb 8b c6                    mov     eax, esi                                 
+00ed 5e                       pop     esi                                      
+00ee c3                       ret
```

### vtable.log

```text
=== vtable 0x011207c0 (rva 0x00d207c0) ===
  -- retail slots --
  slot   0 +0x000 -> 0x0043dd6b ?j_0003dd6b@@YAXXZ  [gthunks_069.cpp]
  slot   1 +0x004 -> 0x0041905b ?j_0001905b@@YAXXZ  [gthunks_027.cpp]
  slot   2 +0x008 -> 0x0042127e ?j_0002127e@@YAXXZ  [gthunks_036.cpp]
  slot   3 +0x00c -> 0x0042ba44 ?j_0002ba44@@YAXXZ  [gthunks_048.cpp]
  slot   4 +0x010 -> 0x004169f0 ?j_000169f0@@YAXXZ  [gthunks_024.cpp]
  slot   5 +0x014 -> 0x0042bb39 ?j_0002bb39@@YAXXZ  [gthunks_048.cpp]
  slot   6 +0x018 -> 0x0042e67c ?j_0002e67c@@YAXXZ  [gthunks_051.cpp]
  slot   7 +0x01c -> 0x00446155 ?j_00046155@@YAXXZ  [gthunks_078.cpp]
  slot   8 +0x020 -> 0x0042266a ?j_0002266a@@YAXXZ  [gthunks_038.cpp]
  slot   9 +0x024 -> 0x0042a18a ?j_0002a18a@@YAXXZ  [gthunks_046.cpp]
  slot  10 +0x028 -> 0x0041dd9a ?j_0001dd9a@@YAXXZ  [gthunks_032.cpp]
  slot  11 +0x02c -> 0x0042d330 ?j_0002d330@@YAXXZ  [gthunks_050.cpp]
  slot  12 +0x030 -> 0x004349a5 ?j_000349a5@@YAXXZ  [gthunks_058.cpp]
  slot  13 +0x034 -> 0x004348f1 ?j_000348f1@@YAXXZ  [gthunks_058.cpp]
  slot  14 +0x038 -> 0x004067ee ?j_000067ee@@YAXXZ  [gthunks_006.cpp]
  slot  15 +0x03c -> 0x0043d28a ?j_0003d28a@@YAXXZ  [gthunks_068.cpp]
  slot  16 +0x040 -> 0x00426efe ?j_00026efe@@YAXXZ  [gthunks_043.cpp]
  slot  17 +0x044 -> 0x0043e829 ?j_0003e829@@YAXXZ  [gthunks_069.cpp]
  slot  18 +0x048 -> 0x0040439a ?j_0000439a@@YAXXZ  [gthunks_003.cpp]
  slot  19 +0x04c -> 0x00409985 ?j_00009985@@YAXXZ  [gthunks_009.cpp]
  slot  20 +0x050 -> 0x004481cb ?j_000481cb@@YAXXZ  [gthunks_080.cpp]
  slot  21 +0x054 -> 0x004335dc ?j_000335dc@@YAXXZ  [gthunks_057.cpp]
  slot  22 +0x058 -> 0x0043607a ?j_0003607a@@YAXXZ  [gthunks_060.cpp]
  slot  23 +0x05c -> 0x0042ab67 ?j_0002ab67@@YAXXZ  [gthunks_047.cpp]
  slot  24 +0x060 -> 0x00412b7f ?j_00012b7f@@YAXXZ  [gthunks_020.cpp]
  slot  25 +0x064 -> 0x004493b4 ?j_000493b4@@YAXXZ  [gthunks_082.cpp]
  slot  26 +0x068 -> 0x0041780f ?j_0001780f@@YAXXZ  [gthunks_025.cpp]
  slot  27 +0x06c -> 0x0040fba0 ?j_0000fba0@@YAXXZ  [gthunks_016.cpp]
  slot  28 +0x070 -> 0x004225c0 ?j_000225c0@@YAXXZ  [gthunks_037.cpp]
  -- .text functions carrying the constant (ctors/dtors install it; a cmp is a type check) --
  0x006fc970   239B ??0Rva006FC970@@QAE@XZ  [Rva006FC970Constructor.cpp]
  0x006fd550   294B ?destruct@Rva006FD550@@QAEXXZ  [Rva006FD550Destructor.cpp]
  -- ledger notes mentioning it --
   ?build@Rva006FD990CameraCorners@@QAEXPAVVector3@@@Z,,0x006FD990,622,game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD990CameraCorners.cpp,mat
   ?build@Rva006FE3C0CameraRay@@QAEXPBURva006FE3C0ScreenPoint@@PAVVector3@@1@Z,,0x006FE3C0,340,game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FE
   ?destruct@Rva006FD550@@QAEXXZ,,0x006FD550,294,game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD550Destructor.cpp,matched,Base destructor of t
```

### checked_target.log

```text
0x2ae00 -> 0x615a70  x1  ?j_0002ae00@@YAXXZ

1 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### checked_virtual.log

```text
0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### checked_manager.log

```text
0x687a -> 0x611ca0  x1  ?j_0000687a@@YAXXZ
  0x9561 -> 0x6115a0  x1  ?j_00009561@@YAXXZ
  0x307ec -> 0x61c2f0  x1  ?j_000307ec@@YAXXZ

3 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### checked_point_helper.log

```text
0x2c2a -> 0x61c060  x1  ?j_00002c2a@@YAXXZ
  0x3afe4 -> 0x61bb50  x1  ?j_0003afe4@@YAXXZ
  0x457a5 -> 0x61ba90  x1  ?j_000457a5@@YAXXZ

3 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### checked_region.log

```text
0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### checked_scroll_caller.log

```text
0x650f -> 0x14ff40  x1  ?j_0000650f@@YAXXZ
  0x22c96 -> 0x383480  x1  ?j_00022c96@@YAXXZ
  0x48c4d -> 0x609320  x1  ?j_00048c4d@@YAXXZ

3 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### checked_base_constructor.log

```text
0x1e6a5 -> 0xb98f0  x1  ?j_0001e6a5@@YAXXZ
  0x2920d -> 0x6157c0  x1  ?j_0002920d@@YAXXZ
  0x32e9d -> 0x6ab10  x2  ?j_00032e9d@@YAXXZ

3 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### checked_constructor.log

```text
0xb89d -> 0x60a000  x1  ?j_0000b89d@@YAXXZ

1 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```

### constants.log

```text
0107533C: 0000003f float=0.5
012F8274: 2a389238 float=6.972283881623298e-05
01075350: 00000000 float=0.0
01083B6C: 0000803e float=0.25
012BAC54: 0000803f float=1.0
012BAC50: 0000803f float=1.0
```

### retail_thunks.log

```text
; ?j_0002bb39@@YAXXZ rva=0x0002BB39 size=5
+0000 e9 c2 26 6d 00           jmp     0xafe200                                 ;?Rva006FE200@Rva006FE200Owner@@QAEXPBUCoord2D@@M@Z

0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

External JMP instructions in the decoded extent:
  0x0002BB39 -> 0x006FE200
Verify tail-call target identity and ABI separately; these are not included in the direct CALL inventory.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
; ?j_000493b4@@YAXXZ rva=0x000493B4 size=5
+0000 e9 27 3f 6b 00           jmp     0xafd2e0                                 ;?setCursorWorldPosition@Rva006FD2E0Mouse@@QAEXPBUCoord3D@@@Z

0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

External JMP instructions in the decoded extent:
  0x000493B4 -> 0x006FD2E0
Verify tail-call target identity and ABI separately; these are not included in the direct CALL inventory.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
; ?j_0002ae00@@YAXXZ rva=0x0002AE00 size=5
+0000 e9 6b ac 5e 00           jmp     0xa15a70                                 ;?rva00615a70@BfmeLivingWorldManager@@QAEXABUCoord2D@@@Z

0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

External JMP instructions in the decoded extent:
  0x0002AE00 -> 0x00615A70
Verify tail-call target identity and ABI separately; these are not included in the direct CALL inventory.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
; ?j_000307ec@@YAXXZ rva=0x000307EC size=5
+0000 e9 ff ba 5e 00           jmp     0xa1c2f0                                 ;?bfmeUpdateBFromPointGuardedNA@BfmeThingNA@@QAEXABVCoord2D@@@Z

0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

External JMP instructions in the decoded extent:
  0x000307EC -> 0x0061C2F0
Verify tail-call target identity and ABI separately; these are not included in the direct CALL inventory.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
; ?j_000457a5@@YAXXZ rva=0x000457A5 size=5
+0000 e9 e6 62 5d 00           jmp     0xa1ba90                                 ;?isInside@Region2D@@QBE_NABVCoord2D@@@Z

0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

External JMP instructions in the decoded extent:
  0x000457A5 -> 0x0061BA90
Verify tail-call target identity and ABI separately; these are not included in the direct CALL inventory.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
; ?j_0000b89d@@YAXXZ rva=0x0000B89D size=5
+0000 e9 5e e7 5f 00           jmp     0xa0a000                                 ;??0Rva006092D0State@@QAE@XZ

0 distinct call target(s), 0 unnamed in function ledger
  Every direct call target above has a ledger name, not necessarily a proven signature.
  Ledger names, especially generated/thunk placeholders, are not ABI proof. Verify full callee bodies and typed declarations before adding or reusing pins.

External JMP instructions in the decoded extent:
  0x0000B89D -> 0x0060A000
Verify tail-call target identity and ABI separately; these are not included in the direct CALL inventory.

Decoding the requested extent does not prove the function boundary, indirect targets, identity, or ABI.
```
