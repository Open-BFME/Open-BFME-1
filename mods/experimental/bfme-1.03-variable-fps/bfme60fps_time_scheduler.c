/* BFME 1.03 local variable-FPS proxy.  The 5-Hz active-simulation scheduler
   remains independent from the visual clock.  Animation and interpolation
   consume measured render time, scaled only below 15 FPS. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <unknwn.h>
#include <stdio.h>
#include "scheduler_math.h"
typedef HRESULT (WINAPI *DirectInput8CreateProc)(HINSTANCE,DWORD,REFIID,LPVOID *,LPUNKNOWN);
typedef int (__fastcall *GetFramesProc)(void *,void *);
enum { UPDATE_RVA=0x6E910, RESET_RVA=0x6E7A0, LOGIC_UPDATE_RVA=0x38DA10,
       UPDATE_SCHED_OFF=0xC7, RESET_CLOCK_OFF=0xA2,
       HLOD_SET_RVA=0x97A220,
       CLIENT_UPDATE_RVA=0x6B910, CLIENT_UPDATE_N=7, DELTA_PROVIDER_RVA=0x6957E0, DELTA_PROVIDER_N=10,
       STATE3_SET_RVA=0x97A250, STATE3_SET_N=8, STATE3_PARENT_N=16,
       D1_CALL_RVA=0x982B44, D1_TARGET_RVA=0x91FB90, D81_RVA=0x981E80, D546_RVA=0x9546B0,
       B5_TIMER_RVA=0x75C9F0, B5_TIMER_N=6, HLOD_STATE3_SET_ADDRESS=0x00D7A250,
       SYNC_RVA=0x8FD310, SYNC_N=14, SYNC_CLOCKS=5,
       W3D_RATE_SET_RVA=0x6FB9C0, W3D_FRAME_MS_RVA=0xEBB1CC,
       FLOAT_TEXT_RVA=0x43F328, FLOAT_TEXT_N=10, FLOAT_TO_INT_RVA=0x9F6E38,
       PARTICLE_RENDER_RVA=0x6FA9B0, PARTICLE_RENDER_N=7,
       PARTICLE_GET0_RVA=0x5C30A0, PARTICLE_GET1_RVA=0x5C30C0,
       PARTICLE_GET2_RVA=0x5C30E0, PARTICLE_GET3_RVA=0x5C3100,
       PARTICLE_GET4_RVA=0x5C3120, PARTICLE_ALPHA_RVA=0x5C3160,
       PARTICLE_MANAGER_RVA=0xEF64BC,
       PARTICLE_UPDATE_CALL_RVA=0x6EB55D, PARTICLE_UPDATE_CALL_N=11,
       PARTICLE_GET_N=6, PARTICLE_STATE_N=8192, PARTICLE_PATCH_N=16384,
       UPDATE_N=5, SCHED_N=13, RESET_CLOCK_N=18, LOGIC_UPDATE_N=7,
       HLOD_N=11, D1_N=5, D81_N=9, STATE_N=512,
       MANUAL_CALLER=0x00B5CA51, STATE3_CLOCK_CALLER=0x00AF4142 };
typedef struct { DWORD object,motion,lastTick; float input,output; int frames,mode; BOOL valid; } FrameState;
typedef struct { DWORD object,motion,lastTick; float frame; int mode; BOOL valid; } ObjectAnimState;
typedef struct { DWORD object,a1,a2,lastTick; float raw,output,inc,absolute; BYTE phase,kind; BOOL valid; } Mode3State;
typedef struct { DWORD tick,self,state,fc,vtfc,v118,a1,a2,a3,a4,a5,a6; } D81Event;
typedef struct { DWORD object,a1,a2,a4,lastTick; float raw3,out3,raw5,out5,raw6,out6; BOOL valid; } RenderState;
typedef struct { DWORD tick,receiver,a1,a2,a3,a4,a5,a6; } D546Event;
typedef struct { DWORD caller,raw,out; double remainder; BOOL valid; } SyncClock;
typedef struct { DWORD magic,patched,timerCalls,timerWrites,renderCalls,renderWrites,lastRaw,lastOut; } ProofRecord;
typedef struct { DWORD magic,patched,calls[SYNC_CLOCKS],raw[SYNC_CLOCKS],out[SYNC_CLOCKS]; } SyncProof;
typedef struct { DWORD self,animation,lastTick; float raw,out,total; BOOL valid; } TimerState;
typedef struct {
  DWORD particle,system,lastSeen,positionTick,scalarTick[6];
  float previousPosition[3],currentPosition[3];
  float previousScalar[6],currentScalar[6];
  BYTE scalarValid[6];
} ParticleVisualState;
typedef struct { float *position; float raw[3]; } ParticlePositionPatch;
typedef float (__fastcall *ParticleFloatGetter)(void *,void *);
typedef void (__fastcall *ParticleRenderProc)(void *,void *,void *);
typedef void (__fastcall *ParticleUpdateProc)(void *,void *);
typedef struct { float x,y; } CameraScrollDelta;
typedef void (__fastcall *CameraScrollProc)(void *,void *,CameraScrollDelta *);
static HMODULE g_di; static DirectInput8CreateProc g_create; static volatile LONG g_started;
static FrameState g_states[STATE_N];
static ObjectAnimState g_objectAnims[STATE_N];
static Mode3State g_mode3[STATE_N];
static HANDLE g_d81Events; static volatile LONG g_d81Count;
static RenderState g_render[STATE_N];
static HANDLE g_d546Events; static volatile LONG g_d546Count;
static SyncClock g_syncClocks[SYNC_CLOCKS];
static DWORD g_state3ClockRemainder;
static volatile LONG g_patchApplied,g_syncCalls,g_targetCalls,g_syncCounts[SYNC_CLOCKS];
static volatile LONG g_clientTargetCaptured;
static volatile LONG g_clientDispatchCalls,g_clientManagersCaptured;
static volatile LONG g_deltaProviderCalls;
static DWORD g_deltaStartTick;
static volatile DWORD g_state3Parents[STATE3_PARENT_N];
static volatile LONG g_state3ParentCounts[STATE3_PARENT_N],g_state3TotalCalls;
static BYTE *g_image;
static volatile DWORD g_lastTargetRaw,g_lastTargetOut;
static TimerState g_timerStates[STATE_N];
static volatile LONG g_timerCalls,g_timerWrites,g_renderCalls,g_renderWrites;
static volatile DWORD g_lastTimerRaw,g_lastTimerOut;
static volatile DWORD g_w3dOld,g_w3dNew;
static ParticleVisualState g_particleStates[PARTICLE_STATE_N];
static ParticlePositionPatch g_particlePatches[PARTICLE_PATCH_N];
static ParticleFloatGetter g_particleGetters[6];
static ParticleRenderProc g_particleRenderOriginal;
static CameraScrollProc g_cameraScrollOriginal;
static volatile LONG g_cameraScrollCalls;
static volatile LONG g_particleRenderContext;
static volatile LONG g_particleRenderCalls,g_particleInterpolated;
static DWORD g_particleRenderSerial;
static float g_particleRenderPhase;
typedef struct {
  BfmeFixedFrameClock clock;
  DWORD ticks,dispatches,skipped,bursts;
  float phase;
} FxTiming;
static FxTiming g_fx={{0.0},0,0,0,0,1.0f};
typedef struct {
  double realRenderDelta,animationDelta,frameMsRemainder;
  float slowdown,frameScale,visualPeriod,phase;
  LONG active,heldPeriod;
} VisualTiming;
static VisualTiming g_visual={0.0,0.0,0.0,1.0f,1.0f,6.0f,0.0f,0,2};
typedef enum { ACTIVE_SIMULATION, PAUSED, LOADING_TRANSITION,
               SUSPENDED_LARGE_GAP, NETWORK_BLOCKED,
               LOW_FPS_SLOWDOWN } TimingClass;
typedef struct {
  LARGE_INTEGER frequency,lastQpc;
  BfmeSchedulerMath clock;
  double activeSeconds,fps,measuredHz,windowStart;
  DWORD visualFrames,logicCalls,logicTicks,dueAttempts,networkBlocks;
  DWORD windowTicks,lastLogMs;
  int initialized,lastMode,lastClass;
  void *lastLogic;
} TimingState;
static TimingState g_timing;
static HANDLE g_timingLog=INVALID_HANDLE_VALUE;
static volatile LONG g_dueDecision,g_dueInFlight,g_phaseDecision;
static volatile LONG g_w3dClockFrozen;
static volatile LONG g_legacyPhaseCalls;
static LONG g_lastForeground=-1;
static const BYTE kUpdate[]={0x51,0x53,0x56,0x8B,0xF1};
static const BYTE kClientUpdate[]={0x6A,0xFF,0x68,0xD8,0x2A,0xFF,0x00};
static const BYTE kDeltaProvider[]={0x51,0x56,0x8B,0xF1,0x8B,0x86,0x04,0x06,0x00,0x00};
static const BYTE kState3Set[]={0x8B,0x44,0x24,0x14,0x8B,0x54,0x24,0x0C};
static const BYTE kUpdateA[]={0x8B,0x46,0x30,0x83,0xF8,0x06,0x75,0x0E,0x8A,0x4E,0x3C,0x84,0xC9,0x74,0x07,0x89,0x46,0x34,0xC6,0x46,0x3C,0x00};
static const BYTE kUpdateB[]={0xD8,0x15,0x34,0x53,0x07,0x01,0xDF,0xE0,0xF6,0xC4,0x41,0x75,0x08,0xDD,0xD8,0xD9,0x05,0x34,0x53,0x07,0x01,0x83,0xF9,0x06,0xD9,0x5E,0x38,0x57,0x0F,0x8E};
static const BYTE kReset[]={0xC6,0x47,0x3C,0x00,0xC7,0x47,0x34,0x06,0x00,0x00,0x00,0xC7,0x47,0x40,0x00,0x00,0xC0,0x40,0x89,0x6F,0x44};
static const BYTE kSched[]={0x83,0xF9,0x06,0xD9,0x5E,0x38,0x57,0x0F,0x8E,0x98,0x00,0x00,0x00};
static const BYTE kLogicUpdate[]={0x6A,0xFF,0x68,0x80,0xBE,0x01,0x01};
static const BYTE kHlod[]={0x8B,0x44,0x24,0x0C,0x8B,0x54,0x24,0x04,0x56,0x8B,0xF1};
static const BYTE kW3DSetRate[]={0xD9,0x44,0x24,0x04,0xE8,0x6F,0xB4,0x2F,0x00,0xA3,0xCC,0xB1,0x2B,0x01,0xC2,0x04,0x00};
static const BYTE kFloatText[]={0xDA,0x71,0x34,0xDE,0xE9,0xE8,0x06,0x7B,0x5B,0x00};
static const BYTE kParticleRender[]={0x6A,0xFF,0x68,0x58,0xBE,0x04,0x01};
static const BYTE kParticleGet0[]={0x8B,0x89,0x94,0x00,0x00,0x00};
static const BYTE kParticleGet1[]={0x8B,0x89,0x94,0x00,0x00,0x00};
static const BYTE kParticleGet2[]={0x8B,0x89,0x94,0x00,0x00,0x00};
static const BYTE kParticleGet3[]={0x8B,0x89,0x94,0x00,0x00,0x00};
static const BYTE kParticleGet4[]={0x8B,0x89,0x94,0x00,0x00,0x00};
static const BYTE kParticleAlpha[]={0x8B,0x89,0x90,0x00,0x00,0x00};
static const BYTE kParticleUpdateCall[]={0x8B,0x0D,0xBC,0x64,0x2F,0x01,0x8B,0x11,0xFF,0x52,0x14};
static const BYTE kD1Call[]={0xE8,0x47,0xD0,0xF9,0xFF};
static const BYTE kD81[]={0x56,0x8B,0xF1,0x8B,0x8E,0xFC,0x00,0x00,0x00};
static const BYTE kSync[]={0xA1,0x20,0xF4,0x33,0x01,0x8B,0x4C,0x24,0x04,0xA3,0x24,0xF4,0x33,0x01};
static const BYTE kB5Timer[]={0x8B,0xC1,0x8B,0x4C,0x24,0x04};
static BOOL match(const BYTE*a,const BYTE*b,SIZE_T n){SIZE_T i;for(i=0;i<n;i++)if(a[i]!=b[i])return FALSE;return TRUE;}
static void cp(BYTE*d,const BYTE*s,SIZE_T n){SIZE_T i;for(i=0;i<n;i++)d[i]=s[i];}
static void b(BYTE**p,BYTE x){*(*p)++=x;} static void d(BYTE**p,DWORD x){cp(*p,(BYTE*)&x,4);*p+=4;}
static float visual_frame_scale(void){float s=g_visual.frameScale;return s>=0.0f&&s<=2.0f?s:1.0f;}
/* Keyboard, screen-edge and RMB camera scroll all converge on View vslot
   0x48.  Retail applies the supplied delta once per 30-Hz visual frame, so
   scale the local copy by elapsed authored-frame time.  This is client-only:
   it never changes a message, replay record, or authoritative position. */
static void __fastcall camera_scroll_hook(void*self,void*unused,CameraScrollDelta*delta){
  CameraScrollDelta scaled;float scale;(void)unused;
  if(!g_cameraScrollOriginal||!delta)return;
  if(g_visual.active)scale=(float)bfme_camera_frame_scale(g_visual.realRenderDelta);
  else scale=InterlockedCompareExchange(&g_w3dClockFrozen,0,0)!=0?0.0f:1.0f;
  scaled.x=delta->x*scale;scaled.y=delta->y*scale;
  InterlockedIncrement(&g_cameraScrollCalls);
  g_cameraScrollOriginal(self,0,&scaled);
}
static BOOL install_camera_scroll(BYTE *image){
  enum { TACTICAL_VIEW_VA=0x012F1600, SCROLL_VSLOT=0x48 };
  void *view;DWORD *vtable,*slot,old,back;CameraScrollProc original;
  if(!image)return FALSE;
  view=*(void**)(image+(TACTICAL_VIEW_VA-0x00400000));if(!view)return FALSE;
  vtable=*(DWORD**)view;if(!vtable)return FALSE;slot=(DWORD*)((BYTE*)vtable+SCROLL_VSLOT);
  original=(CameraScrollProc)(ULONG_PTR)*slot;
  if(original==camera_scroll_hook)return g_cameraScrollOriginal!=0;
  if((BYTE*)original<image+0x1000||(BYTE*)original>=image+0x1000000)return FALSE;
  if(!VirtualProtect(slot,sizeof(*slot),PAGE_EXECUTE_READWRITE,&old))return FALSE;
  g_cameraScrollOriginal=original;*slot=(DWORD)(ULONG_PTR)&camera_scroll_hook;
  FlushInstructionCache(GetCurrentProcess(),slot,sizeof(*slot));
  VirtualProtect(slot,sizeof(*slot),old,&back);return TRUE;
}
static void invalidate_state(DWORD object,DWORD motion){DWORD i;if(!object||!motion)return;for(i=0;i<STATE_N;i++)if(g_states[i].object==object&&g_states[i].motion==motion){g_states[i].valid=FALSE;}}
static float adjust_manual(DWORD caller,DWORD mode,DWORD bits,DWORD object,DWORD motion){
  enum { CONTINUOUS_DELTA_LIMIT=3 };
  union{DWORD b;float f;} in,out; DWORD i,slot=STATE_N,now; int frames=0; float delta; BOOL transition=FALSE;
  in.b=bits; out.f=in.f;
  (void)caller;if(!object||!motion)return out.f;
  if(!(in.f==in.f)||in.f>1000000.0f||in.f<-1000000.0f)return out.f;
  { DWORD vt=*(DWORD*)motion; if(vt)frames=((GetFramesProc)(*(DWORD*)(vt+0x10)))((void*)motion,0); }
  if(frames<2||frames>100000)return out.f;
  now=GetTickCount();
  for(i=0;i<STATE_N;i++){if(g_states[i].object==object&&g_states[i].motion==motion){slot=i;break;}if(slot==STATE_N&&g_states[i].object==0)slot=i;}
  if(slot==STATE_N)return out.f;
  if(g_states[slot].object!=object||g_states[slot].motion!=motion||g_states[slot].frames!=frames||g_states[slot].mode!=(int)mode||!g_states[slot].valid){g_states[slot].object=object;g_states[slot].motion=motion;g_states[slot].input=in.f;g_states[slot].output=in.f;g_states[slot].frames=frames;g_states[slot].mode=(int)mode;g_states[slot].lastTick=now;g_states[slot].valid=TRUE;return out.f;}
  /* Pause is a hard visual-time stop.  Consume the caller's changing raw
     value so it cannot become resume debt, but keep the rendered frame fixed
     for every HLOD animation mode and every caller. */
  if(!g_visual.active){out.f=g_states[slot].output;g_states[slot].input=in.f;g_states[slot].lastTick=now;return out.f;}
  if((DWORD)(now-g_states[slot].lastTick)>250){transition=TRUE;}
  delta=in.f-g_states[slot].input;
  /* Tiny negative steps are timestamp/float rounding.  A real reverse or
     state restart must be passed through; only an endpoint-to-start wrap is
     treated as the same looping clip.  Explicit setters invalidate this
     state before the next B5CA update, so selection/build/effect clips start
     at their requested frame instead of inheriting a previous loop phase. */
  if(!transition&&delta< -0.20f){
    if(g_states[slot].input>(float)frames*0.75f&&in.f<(float)frames*0.25f)delta+=(float)frames;
    else transition=TRUE;
  }
  if(!transition&&delta>(float)CONTINUOUS_DELTA_LIMIT)transition=TRUE;
  if(!transition&&delta<-(float)CONTINUOUS_DELTA_LIMIT)transition=TRUE;
  if(transition)out.f=in.f;
  else{
    /* The corrected W3D time already supplies the active rate.  Accumulating
       raw deltas at 1x preserves active playback and the pause-time offset. */
    out.f=g_states[slot].output+delta;
    while(out.f>=(float)frames)out.f-=(float)frames;
    while(out.f<0.0f)out.f+=(float)frames;
  }
  g_states[slot].input=in.f;g_states[slot].output=out.f;g_states[slot].lastTick=now;
  return out.f;
}
static ObjectAnimState *object_animation_state(DWORD object){
  DWORD i,slot=STATE_N;for(i=0;i<STATE_N;i++){if(g_objectAnims[i].object==object)return &g_objectAnims[i];if(slot==STATE_N&&g_objectAnims[i].object==0)slot=i;}
  if(slot==STATE_N)return 0;g_objectAnims[slot].object=object;return &g_objectAnims[slot];
}
static void __stdcall adjust_hlod_call(DWORD caller,DWORD object,DWORD *motionBits,DWORD *frameBits,DWORD *modeBits){
  union{DWORD b;float f;} frame;ObjectAnimState *state;DWORD incomingMotion,incomingMode;
  if(!object||!motionBits||!frameBits||!modeBits)return;
  incomingMotion=*motionBits;incomingMode=*modeBits;frame.b=*frameBits;
  frame.f=adjust_manual(caller,incomingMode,frame.b,object,incomingMotion);
  state=object_animation_state(object);
  if(g_visual.active){
    *frameBits=frame.b;
    if(state){state->motion=incomingMotion;state->frame=frame.f;state->mode=(int)incomingMode;state->lastTick=GetTickCount();state->valid=TRUE;}
    return;
  }
  /* Freeze the complete render-object animation state.  Holding only a frame
     is insufficient when two paused client paths alternate motion or mode. */
  if(state&&state->valid&&state->motion){union{float f;DWORD b;} held;held.f=state->frame;*motionBits=state->motion;*frameBits=held.b;*modeBits=0;state->lastTick=GetTickCount();}
  else{*frameBits=frame.b;*modeBits=0;if(state){state->motion=incomingMotion;state->frame=frame.f;state->mode=(int)incomingMode;state->lastTick=GetTickCount();state->valid=TRUE;}}
}
static BOOL hook_hlod(BYTE*s){
  BYTE*t=(BYTE*)VirtualAlloc(0,176,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD r,o,q;if(!t)return FALSE;p=t;
  b(&p,0x9c);b(&p,0x60);
  b(&p,0x8d);b(&p,0x44);b(&p,0x24);b(&p,0x30); /* &mode */
  b(&p,0x8d);b(&p,0x54);b(&p,0x24);b(&p,0x2c); /* &frame */
  b(&p,0x8d);b(&p,0x4c);b(&p,0x24);b(&p,0x28); /* &motion */
  b(&p,0x8b);b(&p,0x5c);b(&p,0x24);b(&p,0x18); /* object/this */
  b(&p,0x8b);b(&p,0x7c);b(&p,0x24);b(&p,0x24); /* caller */
  b(&p,0x50);b(&p,0x52);b(&p,0x51);b(&p,0x53);b(&p,0x57);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&adjust_hlod_call);b(&p,0xff);b(&p,0xd0);
  b(&p,0x61);b(&p,0x9d);cp(p,kHlod,HLOD_N);p+=HLOD_N;b(&p,0xe9);r=(DWORD)(ULONG_PTR)(s+HLOD_N)-((DWORD)(ULONG_PTR)p+4);d(&p,r);FlushInstructionCache(GetCurrentProcess(),t,p-t);
  if(!VirtualProtect(s,HLOD_N,PAGE_EXECUTE_READWRITE,&o))return FALSE;s[0]=0xe9;r=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&r,4);for(r=5;r<HLOD_N;r++)s[r]=0x90;FlushInstructionCache(GetCurrentProcess(),s,HLOD_N);VirtualProtect(s,HLOD_N,o,&q);return TRUE;
}
/* d1fb90 is the actual state-3 progression update.  Correct its result in
   the controller itself, before d81e80 consumes it.  The older candidates
   changed only an argument at the final draw call, leaving this field at
   60-FPS speed and causing the visible one-shot glitches. */
static float wrap01(float x){while(x>=1.0f)x-=1.0f;while(x<0.0f)x+=1.0f;return x;}
static BOOL forward_delta(float from,float to,float *delta){float d=to-from;if(d<-0.50f)d+=1.0f;else if(d<0.0f)return FALSE;if(d>0.50f)return FALSE;*delta=d;return TRUE;}
static float circle_distance(float a,float b){float d=a-b;if(d<0.0f)d=-d;if(d>0.50f)d=1.0f-d;return d;}
static void __stdcall adjust_mode3(DWORD self,DWORD beforeBits){
  union { DWORD b; float f; } before,after,out; DWORD i,slot=STATE_N,now,a1,a2; float di,da,predInc,predAbs,scale,probe;
  Mode3State *st;
  if(!self||*(DWORD*)((BYTE*)(ULONG_PTR)self+0x104)!=3)return;
  before.b=beforeBits;after.b=*(DWORD*)((BYTE*)(ULONG_PTR)self+0x118);
  if(!(before.f==before.f)||!(after.f==after.f)||before.f<0.0f||after.f<0.0f||before.f>1.05f||after.f>1.05f)return;
  now=GetTickCount();scale=visual_frame_scale();probe=0.125f*scale;a1=*(DWORD*)((BYTE*)(ULONG_PTR)self+0x108);a2=*(DWORD*)((BYTE*)(ULONG_PTR)self+0x10c);
  for(i=0;i<STATE_N;i++){if(g_mode3[i].object==self){slot=i;break;}if(slot==STATE_N&&g_mode3[i].object==0)slot=i;}
  if(slot==STATE_N)return;st=&g_mode3[slot];
  /* A new controller, an explicit clip change, or a long pause starts a new
     normalized phase.  The first corrected sample is still half-rate. */
  if(st->object!=self||!st->valid||st->a1!=a1||st->a2!=a2||(DWORD)(now-st->lastTick)>250){
    st->object=self;st->a1=a1;st->a2=a2;st->raw=after.f;st->phase=0;st->kind=0;st->lastTick=now;st->valid=TRUE;
    if(forward_delta(before.f,after.f,&di))st->output=wrap01(before.f+di*scale);else st->output=after.f;
    out.f=st->output;*(DWORD*)((BYTE*)(ULONG_PTR)self+0x118)=out.b;return;
  }
  if(st->phase==0){
    BOOL hi=forward_delta(before.f,after.f,&di),ha=forward_delta(st->raw,after.f,&da);
    if(!hi&&!ha){st->valid=FALSE;return;}if(!hi)di=da;if(!ha)da=di;
    /* On the next sample a tiny probe tells whether the engine reads the
       previous field (incremental) or recomputes from its absolute clock. */
    st->inc=di;st->absolute=da;st->output=wrap01(st->output+(di+da)*(0.5f*scale));st->raw=after.f;st->phase=1;st->lastTick=now;
    out.f=wrap01(st->output+probe);*(DWORD*)((BYTE*)(ULONG_PTR)self+0x118)=out.b;return;
  }
  if(st->phase==1){
    predInc=wrap01(wrap01(st->output+probe)+st->inc);predAbs=wrap01(st->raw+st->absolute);
    st->kind=(circle_distance(after.f,predInc)<=circle_distance(after.f,predAbs))?1:2;st->phase=2;
  }
  if(st->kind==1){if(!forward_delta(before.f,after.f,&di)){st->valid=FALSE;return;}}
  else {if(!forward_delta(st->raw,after.f,&di)){st->valid=FALSE;return;}}
  st->output=wrap01(st->output+di*scale);st->raw=after.f;st->lastTick=now;out.f=st->output;*(DWORD*)((BYTE*)(ULONG_PTR)self+0x118)=out.b;
}
static BOOL hook_d1call(BYTE*s,BYTE*target){
  BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD r,o,q;
  if(!t)return FALSE;p=t;
  /* preserve ECX/self and the pre-update position, then call the original */
  b(&p,0x51);b(&p,0x8b);b(&p,0x81);d(&p,0x118);b(&p,0x50);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)target);b(&p,0xff);b(&p,0xd0);
  /* Keep all original post-call registers and flags intact around helper. */
  b(&p,0x9c);b(&p,0x60);b(&p,0x8b);b(&p,0x44);b(&p,0x24);b(&p,0x28);b(&p,0x8b);b(&p,0x54);b(&p,0x24);b(&p,0x24);b(&p,0x52);b(&p,0x50);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&adjust_mode3);b(&p,0xff);b(&p,0xd0);b(&p,0x61);b(&p,0x9d);b(&p,0x83);b(&p,0xc4);b(&p,0x08);b(&p,0xc3);
  FlushInstructionCache(GetCurrentProcess(),t,p-t);
  if(!VirtualProtect(s,D1_N,PAGE_EXECUTE_READWRITE,&o))return FALSE;s[0]=0xe8;r=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&r,4);FlushInstructionCache(GetCurrentProcess(),s,D1_N);VirtualProtect(s,D1_N,o,&q);return TRUE;
}
/* d81e80 is the renderer feeder.  Its fifth argument is the current frame
   and its sixth is the normalized phase.  Both must use the same half-rate
   progression; changing only the phase leaves the visible animation fast. */
static void __stdcall adjust_render(DWORD self,DWORD a1,DWORD a2,DWORD a4,DWORD *p3,DWORD *p5,DWORD *p6){
  union { DWORD b; float f; } in3,in5,in6,out; DWORD i,slot=STATE_N,now; float d3,d5,d6;
  RenderState *st;
  if(!self||!p3||!p5||!p6)return;
  in3.b=*p3;in5.b=*p5;in6.b=*p6;
  if(!(in3.f==in3.f)||!(in5.f==in5.f)||!(in6.f==in6.f)||in3.f<-1.0f||in3.f>100000.0f||in5.f<-1.0f||in5.f>100000.0f||in6.f<-0.05f||in6.f>1.05f)return;
  InterlockedIncrement(&g_renderCalls);
  now=GetTickCount();
  for(i=0;i<STATE_N;i++){if(g_render[i].object==self){slot=i;break;}if(slot==STATE_N&&g_render[i].object==0)slot=i;}
  if(slot==STATE_N)return;st=&g_render[slot];
  if(st->object!=self||!st->valid||st->a1!=a1||st->a2!=a2||st->a4!=a4||(DWORD)(now-st->lastTick)>250){
    st->object=self;st->a1=a1;st->a2=a2;st->a4=a4;st->raw3=st->out3=in3.f;st->raw5=st->out5=in5.f;st->raw6=st->out6=in6.f;st->lastTick=now;st->valid=TRUE;InterlockedIncrement(&g_renderWrites);return;
  }
  d3=in3.f-st->raw3;
  d5=in5.f-st->raw5;
  d6=in6.f-st->raw6;if(d6<-0.50f)d6+=1.0f;
  if(d3<0.0f||d3>12.0f)st->out3=in3.f;else st->out3+=d3*visual_frame_scale();
  if(d5<0.0f||d5>12.0f)st->out5=in5.f;else st->out5+=d5*visual_frame_scale();
  if(d6<0.0f||d6>0.50f)st->out6=in6.f;else st->out6=wrap01(st->out6+d6*visual_frame_scale());
  st->raw3=in3.f;st->raw5=in5.f;st->raw6=in6.f;st->lastTick=now;
  out.f=st->out3;*p3=out.b;out.f=st->out5;*p5=out.b;out.f=st->out6;*p6=out.b;InterlockedIncrement(&g_renderWrites);
}
static BOOL hook_d81(BYTE*s){
  BYTE*t=(BYTE*)VirtualAlloc(0,192,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD r,o,q;
  if(!t)return FALSE;p=t;
  b(&p,0x9c);b(&p,0x60);b(&p,0x8b);b(&p,0xec); /* pushfd, pushad, mov ebp,esp */
  b(&p,0x8d);b(&p,0x45);b(&p,0x3c);b(&p,0x50); /* &sixth */
  b(&p,0x8d);b(&p,0x45);b(&p,0x38);b(&p,0x50); /* &fifth */
  b(&p,0x8d);b(&p,0x45);b(&p,0x30);b(&p,0x50); /* &third */
  b(&p,0xff);b(&p,0x75);b(&p,0x34);b(&p,0xff);b(&p,0x75);b(&p,0x2c);b(&p,0xff);b(&p,0x75);b(&p,0x28);b(&p,0x8b);b(&p,0x45);b(&p,0x18);b(&p,0x50);
  b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&adjust_render);b(&p,0xff);b(&p,0xd0);b(&p,0x61);b(&p,0x9d);cp(p,kD81,D81_N);p+=D81_N;b(&p,0xe9);r=(DWORD)(ULONG_PTR)(s+D81_N)-((DWORD)(ULONG_PTR)p+4);d(&p,r);FlushInstructionCache(GetCurrentProcess(),t,p-t);
  if(!VirtualProtect(s,D81_N,PAGE_EXECUTE_READWRITE,&o))return FALSE;s[0]=0xe9;r=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&r,4);for(r=5;r<D81_N;r++)s[r]=0x90;FlushInstructionCache(GetCurrentProcess(),s,D81_N);VirtualProtect(s,D81_N,o,&q);return TRUE;
}
static BYTE *find_d546_call(BYTE *start,BYTE *target){
  DWORD i;LONG rel;
  for(i=0;i<1024-5;i++)if(start[i]==0xe8){rel=*(LONG*)(start+i+1);if(start+i+5+rel==target)return start+i;}
  return 0;
}
static BOOL hook_d546call(BYTE*s,BYTE*target){
  BYTE*t=(BYTE*)VirtualAlloc(0,160,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD r,o,q;
  if(!t)return FALSE;p=t;
  b(&p,0x9c);b(&p,0x60);b(&p,0x8b);b(&p,0xec);
  b(&p,0x8d);b(&p,0x45);b(&p,0x3c);b(&p,0x50);b(&p,0x8d);b(&p,0x45);b(&p,0x38);b(&p,0x50);b(&p,0x8d);b(&p,0x45);b(&p,0x30);b(&p,0x50);
  b(&p,0xff);b(&p,0x75);b(&p,0x34);b(&p,0xff);b(&p,0x75);b(&p,0x2c);b(&p,0xff);b(&p,0x75);b(&p,0x28);b(&p,0x8b);b(&p,0x45);b(&p,0x18);b(&p,0x50);
  b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&adjust_render);b(&p,0xff);b(&p,0xd0);b(&p,0x61);b(&p,0x9d);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)target);b(&p,0xff);b(&p,0xe0);FlushInstructionCache(GetCurrentProcess(),t,p-t);
  if(!VirtualProtect(s,5,PAGE_EXECUTE_READWRITE,&o))return FALSE;s[0]=0xe8;r=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&r,4);FlushInstructionCache(GetCurrentProcess(),s,5);VirtualProtect(s,5,o,&q);return TRUE;
}
/*
   B5CA computes state-3 phase as 1 - remaining/total, then dispatches the
   D7A250 virtual which installs it in an HLOD controller.  At 60 FPS the
   game decrements remaining by roughly 1.0 every rendered update, giving a
   five-update clip.  On the first active update, double both the countdown
   total and remaining time while retaining half the first-frame phase.  The
   native timer then decrements normally for ten 60-Hz updates and reaches its
   genuine final phase instead of being cut off halfway.  D7A250 always creates
   state 3; mode-2 walk clips never pass this filter.
*/
static void __stdcall adjust_state3_timer(DWORD self,DWORD drawable){
  union { DWORD b; float f; } raw,total,out; DWORD i,slot=STATE_N,now,animation,driver,vt,target; TimerState *st;float scale,oldTotal,phase;
  if(!self||!drawable)return;
  animation=*(DWORD*)((BYTE*)(ULONG_PTR)self+0xf8);driver=*(DWORD*)((BYTE*)(ULONG_PTR)self+0xdc);
  if(!animation||!driver)return;
  vt=*(DWORD*)(ULONG_PTR)drawable;if(!vt)return;target=*(DWORD*)((BYTE*)(ULONG_PTR)vt+0xac);
  if(target!=HLOD_STATE3_SET_ADDRESS)return;
  InterlockedIncrement(&g_timerCalls);
  raw.b=*(DWORD*)((BYTE*)(ULONG_PTR)self+0x74);total.b=*(DWORD*)((BYTE*)(ULONG_PTR)self+0x78);
  if(!(raw.f==raw.f)||!(total.f==total.f)||total.f<=0.05f||total.f>100000.0f||raw.f<-1.0f||raw.f>total.f+1.0f)return;
  now=GetTickCount();
  for(i=0;i<STATE_N;i++){if(g_timerStates[i].self==self){slot=i;break;}if(slot==STATE_N&&g_timerStates[i].self==0)slot=i;}
  if(slot==STATE_N)return;st=&g_timerStates[slot];
  if(st->self!=self||!st->valid||st->animation!=animation||st->total!=total.f||(DWORD)(now-st->lastTick)>250||raw.f>st->out+0.20f){
    /* Convert the legacy per-render countdown to the measured fraction of a
       30-Hz frame.  This is 2x duration at 60 FPS, 1x at 30, and 0.5x at
       15/below, matching animationDelta rather than a fixed 60-FPS rule. */
    scale=visual_frame_scale();if(scale<0.001f)return;oldTotal=total.f;phase=(1.0f-raw.f/oldTotal)*scale;
    if(phase<0.0f)phase=0.0f;if(phase>1.0f)phase=1.0f;
    total.f=oldTotal/scale;out.f=total.f*(1.0f-phase);
    st->total=total.f;st->raw=raw.f;st->out=out.f;st->lastTick=now;st->valid=TRUE;
    *(DWORD*)((BYTE*)(ULONG_PTR)self+0x78)=total.b;
  }else{
    /* The engine now owns the expanded countdown and advances it normally. */
    out.f=raw.f;st->raw=raw.f;st->out=out.f;st->lastTick=now;
  }
  *(DWORD*)((BYTE*)(ULONG_PTR)self+0x74)=out.b;
  g_lastTimerRaw=raw.b;g_lastTimerOut=out.b;InterlockedIncrement(&g_timerWrites);
}
static BOOL hook_state3_timer(BYTE*s){
  BYTE*t=(BYTE*)VirtualAlloc(0,128,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*tr=(BYTE*)VirtualAlloc(0,48,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD r,o,q;
  if(!t||!tr)return FALSE;
  p=tr;cp(p,kB5Timer,B5_TIMER_N);p+=B5_TIMER_N;b(&p,0xe9);r=(DWORD)(ULONG_PTR)(s+B5_TIMER_N)-((DWORD)(ULONG_PTR)p+4);d(&p,r);FlushInstructionCache(GetCurrentProcess(),tr,B5_TIMER_N+5);
  p=t;b(&p,0x9c);b(&p,0x60);
  /* [esp+0x28] is B5CA's drawable argument; [esp+0x18] is its this pointer. */
  b(&p,0x8b);b(&p,0x44);b(&p,0x24);b(&p,0x28);b(&p,0x8b);b(&p,0x4c);b(&p,0x24);b(&p,0x18);
  b(&p,0x50);b(&p,0x51);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&adjust_state3_timer);b(&p,0xff);b(&p,0xd0);
  b(&p,0x61);b(&p,0x9d);b(&p,0xe9);r=(DWORD)(ULONG_PTR)tr-((DWORD)(ULONG_PTR)p+4);d(&p,r);FlushInstructionCache(GetCurrentProcess(),t,p-t);
  if(!VirtualProtect(s,B5_TIMER_N,PAGE_EXECUTE_READWRITE,&o))return FALSE;s[0]=0xe9;r=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&r,4);s[5]=0x90;FlushInstructionCache(GetCurrentProcess(),s,B5_TIMER_N);VirtualProtect(s,B5_TIMER_N,o,&q);return TRUE;
}
/* WW3D receives an absolute millisecond clock.  Scale only its delta, retain
   fractional milliseconds, and freeze it while client/game time is frozen. */
static DWORD __stdcall scaled_w3d_clock(DWORD caller,DWORD raw){
  DWORD delta,scaled,i,slot=SYNC_CLOCKS;double amount;float slowdown;BOOL frozen;
  SyncClock *clock;
  InterlockedIncrement(&g_syncCalls);
  for(i=0;i<SYNC_CLOCKS;i++){if(g_syncClocks[i].caller==caller){slot=i;break;}if(slot==SYNC_CLOCKS&&g_syncClocks[i].caller==0)slot=i;}
  if(slot==SYNC_CLOCKS)return raw;
  clock=&g_syncClocks[slot];
  if(!clock->caller)clock->caller=caller;
  InterlockedIncrement(&g_syncCounts[slot]);InterlockedIncrement(&g_targetCalls);g_lastTargetRaw=raw;
  frozen=InterlockedCompareExchange(&g_w3dClockFrozen,0,0)!=0;
  /* Before active simulation (including shell startup/loading), preserve the
     retail argument exactly.  Running it through per-caller transformed
     timelines can jump the one global WW3D clock and blank the shell map. */
  if(!g_visual.active&&!frozen){clock->raw=raw;clock->out=raw;clock->remainder=0.0;clock->valid=TRUE;g_lastTargetOut=raw;return raw;}
  if(!clock->valid){clock->raw=raw;clock->out=raw;clock->remainder=0.0;clock->valid=TRUE;g_lastTargetOut=raw;return raw;}
  delta=raw-clock->raw;
  /* Never convert a reset, suspend, or paused wall-clock gap into catch-up. */
  if(delta>1000){clock->raw=raw;clock->remainder=0.0;g_lastTargetOut=clock->out;return clock->out;}
  /* The main W3DDisplay caller already advances its synthetic input by the
     scaled TheW3DFrameLengthInMsec.  Other absolute-time callers still need
     the low-FPS slowdown during simulation.  Shell/loading clocks pass at
     retail speed; only the explicit pause state freezes WW3D. */
  slowdown=(float)bfme_w3d_clock_scale(g_visual.active,
    frozen,
    g_visual.slowdown,caller==STATE3_CLOCK_CALLER);
  amount=(double)delta*(double)slowdown+clock->remainder;scaled=(DWORD)amount;clock->remainder=amount-(double)scaled;
  clock->raw=raw;clock->out+=scaled;g_lastTargetOut=clock->out;
  return clock->out;
}
static BOOL hook_sync(BYTE*s){
  BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*tr=(BYTE*)VirtualAlloc(0,48,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD r,o,q;
  if(!t||!tr)return FALSE;
  p=tr;cp(p,kSync,SYNC_N);p+=SYNC_N;b(&p,0xe9);r=(DWORD)(ULONG_PTR)(s+SYNC_N)-((DWORD)(ULONG_PTR)p+4);d(&p,r);FlushInstructionCache(GetCurrentProcess(),tr,SYNC_N+5);
  p=t;b(&p,0x9c);b(&p,0x60); /* flags/registers */
  b(&p,0xff);b(&p,0x74);b(&p,0x24);b(&p,0x28); /* raw argument */
  b(&p,0xff);b(&p,0x74);b(&p,0x24);b(&p,0x28); /* caller return address after prior push */
  b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&scaled_w3d_clock);b(&p,0xff);b(&p,0xd0);
  b(&p,0x89);b(&p,0x44);b(&p,0x24);b(&p,0x28); /* replace original argument */
  b(&p,0x61);b(&p,0x9d);b(&p,0xe9);r=(DWORD)(ULONG_PTR)tr-((DWORD)(ULONG_PTR)p+4);d(&p,r);FlushInstructionCache(GetCurrentProcess(),t,p-t);
  if(!VirtualProtect(s,SYNC_N,PAGE_EXECUTE_READWRITE,&o))return FALSE;s[0]=0xe9;r=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&r,4);for(r=5;r<SYNC_N;r++)s[r]=0x90;FlushInstructionCache(GetCurrentProcess(),s,SYNC_N);VirtualProtect(s,SYNC_N,o,&q);return TRUE;
}
static const char *timing_class_name(TimingClass value){
  switch(value){
  case ACTIVE_SIMULATION:return "ACTIVE_SIMULATION";
  case PAUSED:return "PAUSED";
  case LOADING_TRANSITION:return "LOADING/TRANSITION";
  case SUSPENDED_LARGE_GAP:return "SUSPENDED/LARGE_GAP";
  case NETWORK_BLOCKED:return "NETWORK_BLOCKED";
  case LOW_FPS_SLOWDOWN:return "LOW_FPS_SLOWDOWN";
  }
  return "UNKNOWN";
}
static void open_timing_log(void){
  DWORD size,wrote;static const char header[]="wall_ms,active_s,visual_fps,logic_calls,logic_ticks,measured_hz,target_hz,interval_s,accumulator_s,animation_delta_s,slowdown,visual_phase,legacy_frame_scale,visual_period,pause,low_fps,network_present,network_admission,classification,game_mode,max_fps,use_fps_limit,limit_frame_rate,logic_time_scale,logic_frame_adjustment,frame_elapsed_ms,sleep_remaining_ms,sleep_total_ms,previous_frame_ms,w3d_frame_ms,engine_active,foreground\r\n";
  if(g_timingLog!=INVALID_HANDLE_VALUE)return;
  g_timingLog=CreateFileA("C:\\BFME1\\BFME_FOCUS_DIAGNOSTIC.csv",GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
  if(g_timingLog==INVALID_HANDLE_VALUE)g_timingLog=CreateFileA("BFME_FOCUS_DIAGNOSTIC.csv",GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
  if(g_timingLog==INVALID_HANDLE_VALUE)return;
  size=GetFileSize(g_timingLog,0);SetFilePointer(g_timingLog,0,0,FILE_END);
  if(size==0)WriteFile(g_timingLog,header,sizeof(header)-1,&wrote,0);
}
static void log_timing(TimingClass classification,const char *admission,BOOL force){
  char line[960];int n,maxFps=0,logicAdjust=0;DWORD wrote,now=GetTickCount(),network=0,frameElapsed=0,sleepRemaining=0,sleepTotal=0,previousFrame=0,w3dFrame=0,foregroundPid=0;double target;float logicScale=0.0f;BYTE useFps=0,limitRate=0,engineActive=0;LONG foreground;void *engine,*global;HWND foregroundWindow;
  foregroundWindow=GetForegroundWindow();if(foregroundWindow)GetWindowThreadProcessId(foregroundWindow,&foregroundPid);foreground=foregroundPid==GetCurrentProcessId();
  if(foreground!=g_lastForeground){g_lastForeground=foreground;force=TRUE;}
  if(!force&&classification==g_timing.lastClass&&(DWORD)(now-g_timing.lastLogMs)<1000)return;
  if(g_image){
    network=*(volatile DWORD*)(g_image+(0x012F7714-0x00400000));
    engine=*(void**)(g_image+(0x012ED524-0x00400000));global=*(void**)(g_image+(0x012ED5C8-0x00400000));
    if(engine){maxFps=*(volatile int*)((BYTE*)engine+8);engineActive=*(volatile BYTE*)((BYTE*)engine+0x0D);}
    if(global)useFps=*(volatile BYTE*)((BYTE*)global+0x1E);
    limitRate=*(volatile BYTE*)(g_image+(0x012ED520-0x00400000));logicScale=*(volatile float*)(g_image+(0x012A72A4-0x00400000));
    {int *adjust=*(int**)(g_image+(0x012A7244-0x00400000));if(adjust)logicAdjust=*adjust;}
    frameElapsed=*(volatile DWORD*)(g_image+(0x012ED514-0x00400000));sleepRemaining=*(volatile DWORD*)(g_image+(0x012ED510-0x00400000));sleepTotal=*(volatile DWORD*)(g_image+(0x012ED50C-0x00400000));previousFrame=*(volatile DWORD*)(g_image+(0x012ED518-0x00400000));w3dFrame=*(volatile DWORD*)(g_image+W3D_FRAME_MS_RVA);
  }
  target=bfme_target_hz(g_timing.fps);
  n=_snprintf(line,sizeof(line)-1,"%lu,%.6f,%.3f,%lu,%lu,%.3f,%.3f,%.6f,%.6f,%.6f,%.4f,%.4f,%.4f,%.4f,%d,%d,%d,%s,%s,%d,%d,%d,%d,%.6f,%d,%lu,%lu,%lu,%lu,%lu,%d,%d\r\n",
    (unsigned long)now,g_timing.activeSeconds,g_timing.fps,
    (unsigned long)g_timing.logicCalls,(unsigned long)g_timing.logicTicks,
    g_timing.measuredHz,target,g_timing.clock.interval,g_timing.clock.accumulator,g_visual.animationDelta,
    g_visual.slowdown,g_visual.phase,g_visual.frameScale,g_visual.visualPeriod,
    classification==PAUSED,classification==LOW_FPS_SLOWDOWN,network!=0,
    admission,timing_class_name(classification),g_timing.lastMode,
    maxFps,(int)useFps,(int)limitRate,logicScale,logicAdjust,
    (unsigned long)frameElapsed,(unsigned long)sleepRemaining,(unsigned long)sleepTotal,(unsigned long)previousFrame,(unsigned long)w3dFrame,(int)engineActive,(int)foreground);
  if(n<0||n>=(int)sizeof(line))n=sizeof(line)-1;line[n]=0;
  open_timing_log();if(g_timingLog!=INVALID_HANDLE_VALUE)WriteFile(g_timingLog,line,(DWORD)n,&wrote,0);
  g_timing.lastLogMs=now;g_timing.lastClass=classification;
}
static void update_measured_hz(void){
  double elapsed=g_timing.activeSeconds-g_timing.windowStart;
  if(elapsed>=1.0){g_timing.measuredHz=(double)(g_timing.logicTicks-g_timing.windowTicks)/elapsed;g_timing.windowStart=g_timing.activeSeconds;g_timing.windowTicks=g_timing.logicTicks;}
}
static void __stdcall reset_time_scheduler(void *engine){
  LARGE_INTEGER now;(void)engine;
  if(!g_timing.frequency.QuadPart)QueryPerformanceFrequency(&g_timing.frequency);
  QueryPerformanceCounter(&now);g_timing.lastQpc=now;g_timing.clock.accumulator=0.0;g_timing.clock.interval=0.2;
  g_timing.activeSeconds=0.0;g_timing.fps=0.0;g_timing.measuredHz=0.0;g_timing.windowStart=0.0;g_timing.windowTicks=g_timing.logicTicks;
  g_timing.initialized=1;g_timing.lastMode=-1;g_timing.lastLogic=0;g_timing.lastClass=-1;
  g_visual.realRenderDelta=0.0;g_visual.animationDelta=0.0;g_visual.frameMsRemainder=0.0;g_visual.slowdown=1.0f;g_visual.frameScale=0.0f;g_visual.visualPeriod=6.0f;g_visual.phase=0.0f;g_visual.active=0;g_visual.heldPeriod=2;
  ZeroMemory(g_states,sizeof(g_states));ZeroMemory(g_objectAnims,sizeof(g_objectAnims));ZeroMemory(g_particleStates,sizeof(g_particleStates));g_particleRenderSerial=0;
  ZeroMemory(&g_fx,sizeof(g_fx));g_fx.phase=1.0f;
  InterlockedExchange(&g_dueDecision,0);InterlockedExchange(&g_dueInFlight,0);InterlockedExchange(&g_phaseDecision,2);
  InterlockedExchange(&g_w3dClockFrozen,0);
  log_timing(LOADING_TRANSITION,"RESET_REBASE",TRUE);
}
static BOOL engine_time_frozen(void){
  typedef BOOL (__fastcall *BoolThisProc)(void*,void*);void *view,*script;DWORD vt;
  if(!g_image)return FALSE;
  view=*(void**)(g_image+(0x012F1600-0x00400000));
  if(view&&(vt=*(DWORD*)view)!=0){
    if(((BoolThisProc)(*(DWORD*)(vt+0xD4)))(view,0)&&!((BoolThisProc)(*(DWORD*)(vt+0x74)))(view,0))return TRUE;
  }
  script=*(void**)(g_image+(0x012F076C-0x00400000));
  if(script&&((BoolThisProc)(g_image+0x00336F20))(script,0))return TRUE;
  return FALSE;
}
static void hold_visual_phase(void *engine,LONG phase,BOOL rebase){
  if(rebase){g_visual.phase=0.0f;g_visual.frameMsRemainder=0.0;g_visual.heldPeriod=2;g_fx.clock.accumulator=0.0;g_fx.phase=1.0f;}
  else if(g_visual.active&&phase>=2&&phase<=6)g_visual.heldPeriod=phase;
  if(g_visual.heldPeriod<2||g_visual.heldPeriod>6)g_visual.heldPeriod=2;
  g_visual.active=0;g_visual.realRenderDelta=0.0;g_visual.animationDelta=0.0;g_visual.frameScale=0.0f;
  *(volatile LONG*)((BYTE*)engine+0x30)=g_visual.heldPeriod;
  *(volatile float*)((BYTE*)engine+0x38)=g_visual.phase;
  InterlockedExchange(&g_phaseDecision,g_visual.heldPeriod);
}
static void advance_visual_time(void *engine,double delta){
  double animationDelta,period,frameMsExact;LONG frameMs;
  g_visual.realRenderDelta=delta;
  g_visual.slowdown=(float)bfme_visual_slowdown(g_timing.fps);
  animationDelta=bfme_animation_delta(delta,g_timing.fps);g_visual.animationDelta=animationDelta;
  g_visual.frameScale=(float)bfme_legacy_frame_scale(delta,g_timing.fps);
  period=g_timing.fps/bfme_target_hz(g_timing.fps);if(period<1.0)period=1.0;if(period>240.0)period=240.0;
  g_visual.visualPeriod=(float)period;g_visual.phase+=(float)(animationDelta/0.2);
  if(g_visual.phase<0.0f)g_visual.phase=0.0f;if(g_visual.phase>1.0f)g_visual.phase=1.0f;
  g_visual.active=1;*(volatile float*)((BYTE*)engine+0x38)=g_visual.phase;
  frameMsExact=animationDelta*1000.0+g_visual.frameMsRemainder;frameMs=(LONG)frameMsExact;
  g_visual.frameMsRemainder=frameMsExact-(double)frameMs;if(frameMs<1)frameMs=1;if(frameMs>250)frameMs=250;
  if(g_image){InterlockedExchange((volatile LONG*)(g_image+W3D_FRAME_MS_RVA),frameMs);g_w3dNew=(DWORD)frameMs;}
}
static void complete_legacy_phases(void *engine,LONG firstPhase){
  typedef void (__fastcall *PhaseProc)(void*,void*,int);LONG phase;PhaseProc proc;
  if(!g_image||firstPhase>6)return;if(firstPhase<2)firstPhase=2;
  proc=(PhaseProc)(g_image+0x0006BAE0);
  /* The timer controls only phase 1.  When fewer than six visual frames fit
     in a 200-ms logic interval, finish the remaining legacy phase slices in
     order.  These phase 2..6 calls do not admit an authoritative tick. */
  for(phase=firstPhase;phase<=6;phase++){proc(engine,0,phase);InterlockedIncrement(&g_legacyPhaseCalls);}
}
static void __stdcall schedule_time_tick(void *engine,LONG newPeriod){
  LARGE_INTEGER now;double delta,instant,alpha;void *logic;int mode,loading,paused;TimingClass classification;BOOL due;
  InterlockedExchange(&g_dueDecision,0);InterlockedExchange(&g_phaseDecision,newPeriod);
  if(InterlockedExchange(&g_dueInFlight,0)!=0){++g_timing.networkBlocks;log_timing(NETWORK_BLOCKED,"BLOCKED",TRUE);}
  QueryPerformanceCounter(&now);
  if(!g_timing.initialized||!g_timing.frequency.QuadPart){reset_time_scheduler(engine);g_timing.lastQpc=now;hold_visual_phase(engine,newPeriod,TRUE);return;}
  delta=(double)(now.QuadPart-g_timing.lastQpc.QuadPart)/(double)g_timing.frequency.QuadPart;g_timing.lastQpc=now;++g_timing.visualFrames;
  if(!(delta>0.0)||delta>0.75){g_timing.clock.accumulator=0.0;hold_visual_phase(engine,newPeriod,TRUE);log_timing(SUSPENDED_LARGE_GAP,"DISCARDED_GAP",TRUE);return;}
  instant=1.0/delta;if(instant<1.0)instant=1.0;if(instant>240.0)instant=240.0;
  if(!(g_timing.fps>0.0))g_timing.fps=instant;else{alpha=delta/(0.5+delta);g_timing.fps+=(instant-g_timing.fps)*alpha;}
  logic=*(void**)(g_image+(0x012F0898-0x00400000));
  if(!logic){InterlockedExchange(&g_w3dClockFrozen,0);g_timing.lastLogic=0;g_timing.lastMode=-1;g_timing.clock.accumulator=0.0;hold_visual_phase(engine,newPeriod,TRUE);log_timing(LOADING_TRANSITION,"NO_LOGIC",FALSE);return;}
  mode=*(volatile int*)((BYTE*)logic+0x10C);loading=(*(volatile BYTE*)((BYTE*)logic+0x69)!=0)||(*(volatile BYTE*)((BYTE*)logic+0x6A)!=0)||(*(volatile BYTE*)((BYTE*)logic+0x9D)!=0);
  if(logic!=g_timing.lastLogic||mode!=g_timing.lastMode){InterlockedExchange(&g_w3dClockFrozen,0);g_timing.clock.accumulator=0.0;g_timing.lastLogic=logic;g_timing.lastMode=mode;hold_visual_phase(engine,newPeriod,TRUE);log_timing(LOADING_TRANSITION,"LIFECYCLE_REBASE",TRUE);return;}
  if(loading){InterlockedExchange(&g_w3dClockFrozen,0);g_timing.clock.accumulator=0.0;hold_visual_phase(engine,newPeriod,TRUE);log_timing(LOADING_TRANSITION,"INACTIVE",FALSE);return;}
  paused=*(volatile BYTE*)((BYTE*)logic+0x11C)!=0;
  if(paused||engine_time_frozen()){
    InterlockedExchange(&g_w3dClockFrozen,1);
    hold_visual_phase(engine,newPeriod,FALSE);
    /* Preserve the retail pause contract: phase 1 enters
       _bfme_updateNetworkAndLogic's isGamePaused gate and suppresses the
       GameLogic/client slice.  dueDecision remains false, so this is not a
       scheduled logic tick and does not change the 5-Hz timer. */
    InterlockedExchange(&g_phaseDecision,1);
    log_timing(PAUSED,"NATIVE_PHASE1_PAUSE_GATE",FALSE);return;
  }
  InterlockedExchange(&g_w3dClockFrozen,0);
  g_timing.activeSeconds+=delta;advance_visual_time(engine,delta);classification=g_timing.fps<15.0?LOW_FPS_SLOWDOWN:ACTIVE_SIMULATION;
  due=bfme_scheduler_advance(&g_timing.clock,delta,g_timing.fps)!=0;update_measured_hz();
  if(due){
    LONG denominator=newPeriod>0?newPeriod:1;
    complete_legacy_phases(engine,newPeriod);
    *(volatile LONG*)((BYTE*)engine+0x34)=denominator;*(volatile BYTE*)((BYTE*)engine+0x3C)=0;
    ++g_timing.dueAttempts;InterlockedExchange(&g_dueInFlight,1);InterlockedExchange(&g_dueDecision,1);
    log_timing(classification,"TIMER_DUE",TRUE);
  }else log_timing(classification,"NOT_DUE",FALSE);
}
static void __stdcall record_logic_update(void){
  ++g_timing.logicCalls;
  if(InterlockedExchange(&g_dueInFlight,0)!=0){void *engine;g_visual.phase=0.0f;engine=g_image?*(void**)(g_image+(0x012ED524-0x00400000)):0;if(engine)*(volatile float*)((BYTE*)engine+0x38)=0.0f;++g_timing.logicTicks;update_measured_hz();log_timing(g_timing.fps<15.0?LOW_FPS_SLOWDOWN:ACTIVE_SIMULATION,"ALLOWED",TRUE);}
}
static ParticleVisualState *particle_visual_state(DWORD particle,DWORD system,BOOL create){
  DWORD i,slot,oldestSlot,oldestAge,serial;
  ParticleVisualState *state;
  if(!particle)return 0;
  slot=((particle>>4)*2654435761u)&(PARTICLE_STATE_N-1);oldestSlot=slot;oldestAge=0;serial=g_particleRenderSerial;
  for(i=0;i<32;i++){
    state=&g_particleStates[(slot+i)&(PARTICLE_STATE_N-1)];
    if(state->particle==particle){
      if(system&&state->system!=system){ZeroMemory(state,sizeof(*state));state->particle=particle;state->system=system;}
      return state;
    }
    if(!state->particle){
      if(!create)return 0;
      ZeroMemory(state,sizeof(*state));state->particle=particle;state->system=system;return state;
    }
    if((DWORD)(serial-state->lastSeen)>=oldestAge){oldestAge=serial-state->lastSeen;oldestSlot=(slot+i)&(PARTICLE_STATE_N-1);}
  }
  if(!create)return 0;
  state=&g_particleStates[oldestSlot];ZeroMemory(state,sizeof(*state));state->particle=particle;state->system=system;return state;
}
static float particle_phase(void){
  float phase;
  if(!g_visual.active&&InterlockedCompareExchange(&g_w3dClockFrozen,0,0)==0)return 1.0f;
  phase=g_fx.phase;if(!(phase>=0.0f))return 0.0f;return phase>1.0f?1.0f:phase;
}
static DWORD prepare_particle_positions(void){
  BYTE *manager,*sentinel,*node,*system,*particle;DWORD systems=0,count=0,tick=g_fx.ticks;float *position,phase;ParticleVisualState *state;
  ++g_particleRenderSerial;phase=particle_phase();g_particleRenderPhase=phase;
  manager=g_image?*(BYTE**)(g_image+PARTICLE_MANAGER_RVA):0;if(!manager)return 0;
  sentinel=*(BYTE**)(manager+0x80);if(!sentinel)return 0;node=*(BYTE**)sentinel;
  while(node&&node!=sentinel&&systems++<8192){
    system=*(BYTE**)(node+8);particle=system?*(BYTE**)(system+0xA0):0;
    while(particle&&count<PARTICLE_PATCH_N){
      position=(float*)(particle+0x1C);state=particle_visual_state((DWORD)(ULONG_PTR)particle,(DWORD)(ULONG_PTR)system,TRUE);
      if(!state->positionTick){
        state->previousPosition[0]=state->currentPosition[0]=position[0];state->previousPosition[1]=state->currentPosition[1]=position[1];state->previousPosition[2]=state->currentPosition[2]=position[2];state->positionTick=tick+1;
      }else if(state->positionTick!=tick+1){
        state->previousPosition[0]=state->currentPosition[0];state->previousPosition[1]=state->currentPosition[1];state->previousPosition[2]=state->currentPosition[2];
        state->currentPosition[0]=position[0];state->currentPosition[1]=position[1];state->currentPosition[2]=position[2];state->positionTick=tick+1;
      }else{
        state->currentPosition[0]=position[0];state->currentPosition[1]=position[1];state->currentPosition[2]=position[2];
      }
      state->lastSeen=g_particleRenderSerial;
      if(phase<1.0f){
        g_particlePatches[count].position=position;g_particlePatches[count].raw[0]=position[0];g_particlePatches[count].raw[1]=position[1];g_particlePatches[count].raw[2]=position[2];
        position[0]=bfme_visual_lerp(state->previousPosition[0],state->currentPosition[0],phase);
        position[1]=bfme_visual_lerp(state->previousPosition[1],state->currentPosition[1],phase);
        position[2]=bfme_visual_lerp(state->previousPosition[2],state->currentPosition[2],phase);++count;
      }
      particle=*(BYTE**)(particle+0x3C);
    }
    node=*(BYTE**)node;
  }
  return count;
}
static void restore_particle_positions(DWORD count){
  DWORD i;float *position;for(i=0;i<count;i++){position=g_particlePatches[i].position;position[0]=g_particlePatches[i].raw[0];position[1]=g_particlePatches[i].raw[1];position[2]=g_particlePatches[i].raw[2];}
}
static float interpolate_particle_scalar(void *particle,float raw,DWORD index){
  ParticleVisualState *state;DWORD tick;
  if(index>=6||InterlockedCompareExchange(&g_particleRenderContext,0,0)==0)return raw;
  state=particle_visual_state((DWORD)(ULONG_PTR)particle,0,FALSE);if(!state)return raw;tick=g_fx.ticks+1;
  if(!state->scalarValid[index]){state->previousScalar[index]=state->currentScalar[index]=raw;state->scalarTick[index]=tick;state->scalarValid[index]=1;return raw;}
  if(state->scalarTick[index]!=tick){state->previousScalar[index]=state->currentScalar[index];state->currentScalar[index]=raw;state->scalarTick[index]=tick;}
  else state->currentScalar[index]=raw;
  return bfme_visual_lerp(state->previousScalar[index],state->currentScalar[index],g_particleRenderPhase);
}
static float __fastcall particle_get0_hook(void*self,void*unused){(void)unused;return interpolate_particle_scalar(self,g_particleGetters[0](self,0),0);}
static float __fastcall particle_get1_hook(void*self,void*unused){(void)unused;return interpolate_particle_scalar(self,g_particleGetters[1](self,0),1);}
static float __fastcall particle_get2_hook(void*self,void*unused){(void)unused;return interpolate_particle_scalar(self,g_particleGetters[2](self,0),2);}
static float __fastcall particle_get3_hook(void*self,void*unused){(void)unused;return interpolate_particle_scalar(self,g_particleGetters[3](self,0),3);}
static float __fastcall particle_get4_hook(void*self,void*unused){(void)unused;return interpolate_particle_scalar(self,g_particleGetters[4](self,0),4);}
static float __fastcall particle_alpha_hook(void*self,void*unused){(void)unused;return interpolate_particle_scalar(self,g_particleGetters[5](self,0),5);}
static void __fastcall particle_render_hook(void*self,void*unused,void*rinfo){DWORD count;(void)unused;count=prepare_particle_positions();InterlockedIncrement(&g_particleRenderCalls);InterlockedExchange(&g_particleInterpolated,(LONG)count);InterlockedExchange(&g_particleRenderContext,1);g_particleRenderOriginal(self,0,rinfo);InterlockedExchange(&g_particleRenderContext,0);restore_particle_positions(count);}
static BOOL patch_jump(BYTE *site,DWORD count,BYTE *target){DWORD old,back,rel,i;if(count<5||!VirtualProtect(site,count,PAGE_EXECUTE_READWRITE,&old))return FALSE;site[0]=0xE9;rel=(DWORD)(ULONG_PTR)target-((DWORD)(ULONG_PTR)site+5);cp(site+1,(BYTE*)&rel,4);for(i=5;i<count;i++)site[i]=0x90;FlushInstructionCache(GetCurrentProcess(),site,count);VirtualProtect(site,count,old,&back);return TRUE;}
static void __stdcall dispatch_particle_updates(void){
  BYTE *manager;DWORD vtable,i;int updates;ParticleUpdateProc update;
  ++g_fx.dispatches;manager=g_image?*(BYTE**)(g_image+PARTICLE_MANAGER_RVA):0;if(!manager)return;
  vtable=*(DWORD*)manager;if(!vtable)return;update=(ParticleUpdateProc)(*(DWORD*)(vtable+0x14));if(!update)return;
  if(InterlockedCompareExchange(&g_w3dClockFrozen,0,0)!=0){++g_fx.skipped;return;}
  /* Before an active simulation clock exists (loading/shell setup), preserve
     retail dispatch. Active gameplay uses the INIs' authored 30-Hz frame
     cadence, independently of the 5-Hz authoritative scheduler. */
  if(!g_visual.active||!(g_visual.animationDelta>0.0)){
    update(manager,0);++g_fx.ticks;g_fx.phase=1.0f;g_fx.clock.accumulator=0.0;return;
  }
  updates=bfme_fixed_frame_advance(&g_fx.clock,g_visual.animationDelta,30.0,8);
  if(updates>1)++g_fx.bursts;
  g_fx.phase=g_timing.fps>30.0?bfme_fixed_frame_phase(&g_fx.clock,30.0):1.0f;
  if(!updates)++g_fx.skipped;
  for(i=0;i<(DWORD)updates;i++){update(manager,0);++g_fx.ticks;}
}
static BOOL hook_particle_update_call(BYTE *site){
  BYTE*t=(BYTE*)VirtualAlloc(0,64,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel;if(!t)return FALSE;p=t;
  b(&p,0x9C);b(&p,0x60);b(&p,0xB8);d(&p,(DWORD)(ULONG_PTR)&dispatch_particle_updates);b(&p,0xFF);b(&p,0xD0);b(&p,0x61);b(&p,0x9D);
  b(&p,0xE9);rel=(DWORD)(ULONG_PTR)(site+PARTICLE_UPDATE_CALL_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);
  FlushInstructionCache(GetCurrentProcess(),t,p-t);return patch_jump(site,PARTICLE_UPDATE_CALL_N,t);
}
static BOOL make_particle_trampoline(BYTE *site,DWORD count,BYTE *hook,BYTE **original){BYTE*t=(BYTE*)VirtualAlloc(0,count+16,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel;if(!t)return FALSE;p=t;cp(p,site,count);p+=count;b(&p,0xE9);rel=(DWORD)(ULONG_PTR)(site+count)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);FlushInstructionCache(GetCurrentProcess(),t,p-t);*original=t;return patch_jump(site,count,hook);}
static BOOL install_particle_interpolation(BYTE *render,BYTE **getters){
  if(!make_particle_trampoline(render,PARTICLE_RENDER_N,(BYTE*)&particle_render_hook,(BYTE**)&g_particleRenderOriginal))return FALSE;
  if(!make_particle_trampoline(getters[0],PARTICLE_GET_N,(BYTE*)&particle_get0_hook,(BYTE**)&g_particleGetters[0]))return FALSE;
  if(!make_particle_trampoline(getters[1],PARTICLE_GET_N,(BYTE*)&particle_get1_hook,(BYTE**)&g_particleGetters[1]))return FALSE;
  if(!make_particle_trampoline(getters[2],PARTICLE_GET_N,(BYTE*)&particle_get2_hook,(BYTE**)&g_particleGetters[2]))return FALSE;
  if(!make_particle_trampoline(getters[3],PARTICLE_GET_N,(BYTE*)&particle_get3_hook,(BYTE**)&g_particleGetters[3]))return FALSE;
  if(!make_particle_trampoline(getters[4],PARTICLE_GET_N,(BYTE*)&particle_get4_hook,(BYTE**)&g_particleGetters[4]))return FALSE;
  if(!make_particle_trampoline(getters[5],PARTICLE_GET_N,(BYTE*)&particle_alpha_hook,(BYTE**)&g_particleGetters[5]))return FALSE;
  return TRUE;
}
static BOOL hook_floating_text(BYTE *site){
  BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel;if(!t)return FALSE;p=t;
  b(&p,0xD9);b(&p,0x05);d(&p,(DWORD)(ULONG_PTR)&g_visual.phase);                 /* fld phase */
  b(&p,0xD8);b(&p,0x8B);d(&p,0x12A0);                                         /* fmul [ebx+12a0] */
  b(&p,0xDE);b(&p,0xC1);                                                       /* faddp */
  b(&p,0xD8);b(&p,0x35);d(&p,(DWORD)(ULONG_PTR)&g_visual.visualPeriod);         /* fdiv period */
  b(&p,0xDE);b(&p,0xE9);b(&p,0xB8);d(&p,(DWORD)(ULONG_PTR)(g_image+FLOAT_TO_INT_RVA));b(&p,0xFF);b(&p,0xD0);
  b(&p,0xE9);rel=(DWORD)(ULONG_PTR)(site+FLOAT_TEXT_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);
  FlushInstructionCache(GetCurrentProcess(),t,p-t);return patch_jump(site,FLOAT_TEXT_N,t);
}
static BOOL hook_scheduler_decision(BYTE *site){
  BYTE*t=(BYTE*)VirtualAlloc(0,160,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel;if(!t)return FALSE;p=t;
  b(&p,0xD9);b(&p,0x5E);b(&p,0x38);b(&p,0x57);b(&p,0x9C);b(&p,0x60);b(&p,0x51);b(&p,0x56);b(&p,0xB8);d(&p,(DWORD)(ULONG_PTR)&schedule_time_tick);b(&p,0xFF);b(&p,0xD0);b(&p,0x61);b(&p,0x9D);
  b(&p,0x50);b(&p,0xB8);d(&p,(DWORD)(ULONG_PTR)&g_phaseDecision);b(&p,0x8B);b(&p,0x08);b(&p,0xB8);d(&p,(DWORD)(ULONG_PTR)&g_dueDecision);b(&p,0x83);b(&p,0x38);b(&p,0x00);b(&p,0x58);
  b(&p,0x0F);b(&p,0x85);rel=(DWORD)(ULONG_PTR)(site+SCHED_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);
  b(&p,0xE9);rel=(DWORD)(ULONG_PTR)(site+0xA5)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);
  FlushInstructionCache(GetCurrentProcess(),t,p-t);return patch_jump(site,SCHED_N,t);
}
static BOOL hook_reset_clock(BYTE *site){
  BYTE*t=(BYTE*)VirtualAlloc(0,128,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel;if(!t)return FALSE;p=t;cp(p,kReset,RESET_CLOCK_N);p+=RESET_CLOCK_N;
  b(&p,0x9C);b(&p,0x60);b(&p,0x57);b(&p,0xB8);d(&p,(DWORD)(ULONG_PTR)&reset_time_scheduler);b(&p,0xFF);b(&p,0xD0);b(&p,0x61);b(&p,0x9D);b(&p,0xE9);rel=(DWORD)(ULONG_PTR)(site+RESET_CLOCK_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);
  FlushInstructionCache(GetCurrentProcess(),t,p-t);return patch_jump(site,RESET_CLOCK_N,t);
}
static BOOL hook_logic_update(BYTE *site){
  BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel;if(!t)return FALSE;p=t;
  b(&p,0x9C);b(&p,0x60);b(&p,0xB8);d(&p,(DWORD)(ULONG_PTR)&record_logic_update);b(&p,0xFF);b(&p,0xD0);b(&p,0x61);b(&p,0x9D);cp(p,kLogicUpdate,LOGIC_UPDATE_N);p+=LOGIC_UPDATE_N;b(&p,0xE9);rel=(DWORD)(ULONG_PTR)(site+LOGIC_UPDATE_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);
  FlushInstructionCache(GetCurrentProcess(),t,p-t);return patch_jump(site,LOGIC_UPDATE_N,t);
}
static BOOL install_time_scheduler(BYTE *u,BYTE *r,BYTE *logic){reset_time_scheduler(0);if(!hook_logic_update(logic))return FALSE;if(!hook_reset_clock(r+RESET_CLOCK_OFF))return FALSE;if(!hook_scheduler_decision(u+UPDATE_SCHED_OFF))return FALSE;return TRUE;}
static void write_scheduler_proof(void){
  DWORD rec[10],wrote;HANDLE f;rec[0]=0x31534354;rec[1]=1;rec[2]=(DWORD)(ULONG_PTR)(g_image+UPDATE_RVA+UPDATE_SCHED_OFF);rec[3]=(DWORD)(ULONG_PTR)(g_image+RESET_RVA+RESET_CLOCK_OFF);rec[4]=(DWORD)(ULONG_PTR)(g_image+LOGIC_UPDATE_RVA);rec[5]=(DWORD)g_timing.frequency.LowPart;rec[6]=(DWORD)g_timing.frequency.HighPart;rec[7]=g_w3dOld;rec[8]=g_w3dNew;rec[9]=5;
  f=CreateFileA("C:\\BFME1\\BFME_60FPS_TIME_SCHEDULER_PROOF.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,rec,sizeof(rec),&wrote,0);CloseHandle(f);
}
static void write_particle_proof(void){union{float f;DWORD d;}phase;DWORD rec[18],wrote;HANDLE f;phase.f=g_fx.phase;rec[0]=0x32584650;rec[1]=(DWORD)InterlockedCompareExchange(&g_patchApplied,0,0);rec[2]=(DWORD)InterlockedCompareExchange(&g_particleRenderCalls,0,0);rec[3]=(DWORD)InterlockedCompareExchange(&g_particleInterpolated,0,0);rec[4]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_RENDER_RVA);rec[5]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_GET0_RVA);rec[6]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_GET1_RVA);rec[7]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_GET2_RVA);rec[8]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_GET3_RVA);rec[9]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_GET4_RVA);rec[10]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_ALPHA_RVA);rec[11]=g_timing.logicTicks;rec[12]=(DWORD)(ULONG_PTR)(g_image+PARTICLE_UPDATE_CALL_RVA);rec[13]=g_fx.dispatches;rec[14]=g_fx.ticks;rec[15]=g_fx.skipped;rec[16]=g_fx.bursts;rec[17]=phase.d;f=CreateFileA("C:\\BFME1\\BFME_60FPS_PARTICLE_PROOF.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,rec,sizeof(rec),&wrote,0);CloseHandle(f);}
static void write_sync_proof(void){HANDLE f;DWORD wrote,i;SyncProof p;p.magic=0x31434E53;p.patched=(DWORD)InterlockedCompareExchange(&g_patchApplied,0,0);for(i=0;i<SYNC_CLOCKS;i++){p.calls[i]=(DWORD)InterlockedCompareExchange(&g_syncCounts[i],0,0);p.raw[i]=g_syncClocks[i].raw;p.out[i]=g_syncClocks[i].out;}f=CreateFileA("BFME_60FPS_ALL_SYNC_PROOF.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,&p,sizeof(p),&wrote,0);CloseHandle(f);}
static void write_proof(void){HANDLE f;DWORD wrote;ProofRecord p;p.magic=0x314D4F43;p.patched=(DWORD)InterlockedCompareExchange(&g_patchApplied,0,0);p.timerCalls=(DWORD)InterlockedCompareExchange(&g_timerCalls,0,0);p.timerWrites=(DWORD)InterlockedCompareExchange(&g_timerWrites,0,0);p.renderCalls=(DWORD)InterlockedCompareExchange(&g_renderCalls,0,0);p.renderWrites=(DWORD)InterlockedCompareExchange(&g_renderWrites,0,0);p.lastRaw=g_lastTimerRaw;p.lastOut=g_lastTimerOut;f=CreateFileA("BFME_60FPS_STATE3_COMBINED_PROOF.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,&p,sizeof(p),&wrote,0);CloseHandle(f);}
static void dump_d1_code(BYTE *image){HANDLE f;DWORD wrote,header[2];f=CreateFileA("BFME_60FPS_D1FB90_CODE.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;header[0]=(DWORD)(ULONG_PTR)(image+D1_TARGET_RVA);header[1]=0x2000;WriteFile(f,header,sizeof(header),&wrote,0);WriteFile(f,image+D1_TARGET_RVA,0x2000,&wrote,0);CloseHandle(f);}
static void dump_region(const char *name,BYTE *data,DWORD size){HANDLE f;DWORD wrote;f=CreateFileA(name,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,data,size,&wrote,0);CloseHandle(f);}
static void dump_renderer_code(BYTE *image){dump_region("BFME_60FPS_D546B0_CODE.bin",image+D546_RVA,0x6000);dump_region("BFME_60FPS_D81E80_CODE.bin",image+D81_RVA,0x1000);dump_region("BFME_60FPS_D7A220_CODE.bin",image+HLOD_SET_RVA,0x1000);dump_region("BFME_60FPS_B5C9F0_CODE.bin",image+B5_TIMER_RVA,0x1000);}
static void dump_client_scheduler_code(BYTE *image){dump_region("BFME_60FPS_CLIENT_UPDATE_BODY.bin",image+CLIENT_UPDATE_RVA,0x8000);dump_region("BFME_60FPS_GAMEENGINE_UPDATE_CODE.bin",image+UPDATE_RVA,0x5000);dump_region("BFME_60FPS_GAMEENGINE_RESET_CODE.bin",image+RESET_RVA,0x1000);}
typedef struct { DWORD kind,source,object,vtable,slot,target; } ClientManagerRecord;
static void add_direct(ClientManagerRecord *r,DWORD source,DWORD target){r->kind=1;r->source=source;r->object=0;r->vtable=0;r->slot=0;r->target=(DWORD)(ULONG_PTR)(g_image+(target-0x00400000));}
static BOOL read32(DWORD address,DWORD *value){SIZE_T got=0;*value=0;return ReadProcessMemory(GetCurrentProcess(),(void*)(ULONG_PTR)address,value,4,&got)&&got==4;}
static DWORD resolve_jump(DWORD target){DWORD i,disp,next;BYTE op;SIZE_T got;for(i=0;i<8;i++){got=0;if(!ReadProcessMemory(GetCurrentProcess(),(void*)(ULONG_PTR)target,&op,1,&got)||got!=1||op!=0xE9)break;if(!read32(target+1,&disp))break;next=target+5+(LONG)disp;if(next<(DWORD)(ULONG_PTR)g_image||next>=(DWORD)(ULONG_PTR)(g_image+0x1000000)||next==target)break;target=next;}return target;}
static void add_virtual(ClientManagerRecord *r,DWORD global,DWORD add,DWORD slot){DWORD object=0;r->kind=2;r->source=global;r->object=0;r->vtable=0;r->slot=slot;r->target=0;if(!read32((DWORD)(ULONG_PTR)(g_image+(global-0x00400000)),&object)||!object)return;r->object=object+add;if(!read32(r->object,&r->vtable)||!r->vtable)return;read32(r->vtable+slot,&r->target);}
static void __stdcall capture_client_managers(void){
  ClientManagerRecord r[19]; HANDLE f; DWORD wrote,i,count;
  count=(DWORD)InterlockedIncrement(&g_clientDispatchCalls);(void)count;if(InterlockedCompareExchange(&g_clientManagersCaptured,1,0)!=0||!g_image)return;
  add_direct(&r[0],0x0046B930,0x00440791);add_direct(&r[1],0x0046B96D,0x004358EB);add_direct(&r[2],0x0046B9A7,0x0040180C);
  add_direct(&r[3],0x0046B9D4,0x0042AE96);add_direct(&r[4],0x0046B9D9,0x00436921);add_direct(&r[5],0x0046BA06,0x00445A1B);
  add_direct(&r[6],0x0046BA11,0x00445A1B);add_direct(&r[7],0x0046BA23,0x0043D578);add_direct(&r[8],0x0046BA62,0x00441ED9);
  add_virtual(&r[9],0x012F1464,0,0x14);add_virtual(&r[10],0x012F1464,0,0x24);add_virtual(&r[11],0x012F1464,0,0x68);
  add_virtual(&r[12],0x012F19E8,0,0x14);add_virtual(&r[13],0x012EF0E4,4,0x14);add_virtual(&r[14],0x012F4C50,0,0x14);
  add_virtual(&r[15],0x012ED668,0,0x14);add_virtual(&r[16],0x012ED84C,0,0x14);add_virtual(&r[17],0x012F7714,0,0x24);
  add_virtual(&r[18],0x012ED668,0,0x18c);
  for(i=0;i<19;i++)if(r[i].target)r[i].target=resolve_jump(r[i].target);
  f=CreateFileA("BFME_60FPS_CLIENT_MANAGERS.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;
  {DWORD header[3];header[0]=0x31474D43;header[1]=19;header[2]=(DWORD)(ULONG_PTR)g_image;WriteFile(f,header,sizeof(header),&wrote,0);}
  WriteFile(f,r,sizeof(r),&wrote,0);for(i=0;i<19;i++)if(r[i].target>=(DWORD)(ULONG_PTR)g_image&&r[i].target<(DWORD)(ULONG_PTR)(g_image+0x1000000))WriteFile(f,(BYTE*)(ULONG_PTR)r[i].target,0x2000,&wrote,0);CloseHandle(f);
}
static BOOL hook_client_dispatch(BYTE*s){BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel,old,back;if(!t)return FALSE;p=t;b(&p,0x9c);b(&p,0x60);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&capture_client_managers);b(&p,0xff);b(&p,0xd0);b(&p,0x61);b(&p,0x9d);cp(p,kClientUpdate,CLIENT_UPDATE_N);p+=CLIENT_UPDATE_N;b(&p,0xe9);rel=(DWORD)(ULONG_PTR)(s+CLIENT_UPDATE_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);FlushInstructionCache(GetCurrentProcess(),t,p-t);if(!VirtualProtect(s,CLIENT_UPDATE_N,PAGE_EXECUTE_READWRITE,&old))return FALSE;s[0]=0xe9;rel=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&rel,4);for(rel=5;rel<CLIENT_UPDATE_N;rel++)s[rel]=0x90;FlushInstructionCache(GetCurrentProcess(),s,CLIENT_UPDATE_N);VirtualProtect(s,CLIENT_UPDATE_N,old,&back);return TRUE;}
static void __stdcall count_delta_provider(void){InterlockedIncrement(&g_deltaProviderCalls);}
static BOOL hook_delta_provider_count(BYTE*s){BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel,old,back,i;if(!t)return FALSE;p=t;b(&p,0x9c);b(&p,0x60);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&count_delta_provider);b(&p,0xff);b(&p,0xd0);b(&p,0x61);b(&p,0x9d);cp(p,kDeltaProvider,DELTA_PROVIDER_N);p+=DELTA_PROVIDER_N;b(&p,0xe9);rel=(DWORD)(ULONG_PTR)(s+DELTA_PROVIDER_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);FlushInstructionCache(GetCurrentProcess(),t,p-t);if(!VirtualProtect(s,DELTA_PROVIDER_N,PAGE_EXECUTE_READWRITE,&old))return FALSE;s[0]=0xe9;rel=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&rel,4);for(i=5;i<DELTA_PROVIDER_N;i++)s[i]=0x90;FlushInstructionCache(GetCurrentProcess(),s,DELTA_PROVIDER_N);VirtualProtect(s,DELTA_PROVIDER_N,old,&back);return TRUE;}
static void write_delta_proof(void){HANDLE f;DWORD wrote,rec[6];rec[0]=0x31504C44;rec[1]=(DWORD)InterlockedCompareExchange(&g_deltaProviderCalls,0,0);rec[2]=g_deltaStartTick;rec[3]=GetTickCount();rec[4]=0x42055555;rec[5]=(DWORD)(ULONG_PTR)(g_image+DELTA_PROVIDER_RVA);f=CreateFileA("BFME_60FPS_DISPLAY_DELTA_PROOF.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,rec,sizeof(rec),&wrote,0);CloseHandle(f);}
static void __stdcall record_state3_parent(DWORD parent){DWORD i;InterlockedIncrement(&g_state3TotalCalls);for(i=0;i<STATE3_PARENT_N;i++){DWORD seen=g_state3Parents[i];if(seen==parent){InterlockedIncrement(&g_state3ParentCounts[i]);return;}if(!seen&&InterlockedCompareExchange((volatile LONG*)&g_state3Parents[i],(LONG)parent,0)==0){InterlockedIncrement(&g_state3ParentCounts[i]);return;}}}
static BOOL hook_state3_parent(BYTE*s){BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel,old,back,i;if(!t)return FALSE;p=t;b(&p,0x9c);b(&p,0x60);b(&p,0x8b);b(&p,0x44);b(&p,0x24);b(&p,0x48);b(&p,0x50);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&record_state3_parent);b(&p,0xff);b(&p,0xd0);b(&p,0x61);b(&p,0x9d);cp(p,kState3Set,STATE3_SET_N);p+=STATE3_SET_N;b(&p,0xe9);rel=(DWORD)(ULONG_PTR)(s+STATE3_SET_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);FlushInstructionCache(GetCurrentProcess(),t,p-t);if(!VirtualProtect(s,STATE3_SET_N,PAGE_EXECUTE_READWRITE,&old))return FALSE;s[0]=0xe9;rel=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&rel,4);for(i=5;i<STATE3_SET_N;i++)s[i]=0x90;FlushInstructionCache(GetCurrentProcess(),s,STATE3_SET_N);VirtualProtect(s,STATE3_SET_N,old,&back);return TRUE;}
static void write_state3_parents(void){HANDLE f;DWORD wrote,i,header[3],pair[2],parent;header[0]=0x31503353;header[1]=(DWORD)InterlockedCompareExchange(&g_state3TotalCalls,0,0);header[2]=STATE3_PARENT_N;f=CreateFileA("BFME_60FPS_STATE3_PARENTS.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,header,sizeof(header),&wrote,0);for(i=0;i<STATE3_PARENT_N;i++){pair[0]=g_state3Parents[i];pair[1]=(DWORD)InterlockedCompareExchange(&g_state3ParentCounts[i],0,0);WriteFile(f,pair,sizeof(pair),&wrote,0);}for(i=0;i<STATE3_PARENT_N;i++){parent=g_state3Parents[i];if(parent>=(DWORD)(ULONG_PTR)(g_image+0x1000)&&parent<(DWORD)(ULONG_PTR)(g_image+0x1000000))WriteFile(f,(BYTE*)(ULONG_PTR)(parent-0x1000),0x2000,&wrote,0);}CloseHandle(f);}
static void capture_w3d_frame_rate_slot(void){
  DWORD object=0,vtable=0,entry=0,target=0,wrote,rec[8],slots[46];
  HANDLE f; SIZE_T got=0;
  if(!g_image)return;
  if(!read32((DWORD)(ULONG_PTR)(g_image+(0x012F1464-0x00400000)),&object)||!object)return;
  if(!read32(object,&vtable)||!vtable)return;
  if(!ReadProcessMemory(GetCurrentProcess(),(void*)(ULONG_PTR)vtable,slots,sizeof(slots),&got)||got!=sizeof(slots))return;
  entry=slots[45]; target=resolve_jump(entry);
  rec[0]=0x31524657; /* WFR1 */ rec[1]=(DWORD)(ULONG_PTR)g_image; rec[2]=object; rec[3]=vtable;
  rec[4]=45; rec[5]=entry; rec[6]=target; rec[7]=0xB4;
  f=CreateFileA("BFME_60FPS_W3D_FRAMERATE_SLOT.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
  if(f==INVALID_HANDLE_VALUE)return;
  WriteFile(f,rec,sizeof(rec),&wrote,0); WriteFile(f,slots,sizeof(slots),&wrote,0);
  if(target>=(DWORD)(ULONG_PTR)(g_image+0x1000)&&target<(DWORD)(ULONG_PTR)(g_image+0x1000000))
    WriteFile(f,(void*)(ULONG_PTR)target,0x1000,&wrote,0);
  CloseHandle(f);
}
static void write_w3d_clock_proof(void){
  DWORD rec[8],wrote; HANDLE f;
  rec[0]=0x314B4357; /* WCK1 */ rec[1]=(DWORD)InterlockedCompareExchange(&g_patchApplied,0,0);
  rec[2]=g_w3dOld; rec[3]=g_w3dNew; rec[4]=*(volatile DWORD*)(g_image+W3D_FRAME_MS_RVA);
  rec[5]=(DWORD)(ULONG_PTR)(g_image+W3D_RATE_SET_RVA); rec[6]=(DWORD)(ULONG_PTR)(g_image+W3D_FRAME_MS_RVA); rec[7]=60;
  f=CreateFileA("C:\\BFME1\\BFME_60FPS_W3D_CLOCK_PROOF.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
  if(f==INVALID_HANDLE_VALUE)return; WriteFile(f,rec,sizeof(rec),&wrote,0); CloseHandle(f);
}
static void __stdcall capture_client_target(DWORD self){DWORD vt,target,rec[3];HANDLE f;DWORD wrote;if(!self||InterlockedCompareExchange(&g_clientTargetCaptured,1,0)!=0)return;vt=*(DWORD*)(ULONG_PTR)self;if(!vt){InterlockedExchange(&g_clientTargetCaptured,0);return;}target=*(DWORD*)((BYTE*)(ULONG_PTR)vt+0x80);rec[0]=self;rec[1]=vt;rec[2]=target;f=CreateFileA("BFME_60FPS_CLIENT_TARGET.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return;WriteFile(f,rec,sizeof(rec),&wrote,0);if(target>=0x00400000&&target<0x02000000)WriteFile(f,(BYTE*)(ULONG_PTR)target,0x4000,&wrote,0);CloseHandle(f);}
static BOOL hook_client_capture(BYTE*s){BYTE*t=(BYTE*)VirtualAlloc(0,96,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE),*p;DWORD rel,old,back;if(!t)return FALSE;p=t;b(&p,0x9c);b(&p,0x60);b(&p,0x51);b(&p,0xb8);d(&p,(DWORD)(ULONG_PTR)&capture_client_target);b(&p,0xff);b(&p,0xd0);b(&p,0x61);b(&p,0x9d);cp(p,kUpdate,UPDATE_N);p+=UPDATE_N;b(&p,0xe9);rel=(DWORD)(ULONG_PTR)(s+UPDATE_N)-((DWORD)(ULONG_PTR)p+4);d(&p,rel);FlushInstructionCache(GetCurrentProcess(),t,p-t);if(!VirtualProtect(s,UPDATE_N,PAGE_EXECUTE_READWRITE,&old))return FALSE;s[0]=0xe9;rel=(DWORD)(ULONG_PTR)t-((DWORD)(ULONG_PTR)s+5);cp(s+1,(BYTE*)&rel,4);FlushInstructionCache(GetCurrentProcess(),s,UPDATE_N);VirtualProtect(s,UPDATE_N,old,&back);return TRUE;}
static BOOL apply(void){
  BYTE*im=(BYTE*)GetModuleHandleA(0),*u,*r,*c,*rate,*logic,*sync,*floating,*particleRender,*particleUpdateCall,*particleGetters[6];volatile LONG*frameMs;DWORD old;
  if(!im)return FALSE;
  u=im+UPDATE_RVA;r=im+RESET_RVA;c=im+CLIENT_UPDATE_RVA;rate=im+W3D_RATE_SET_RVA;logic=im+LOGIC_UPDATE_RVA;sync=im+SYNC_RVA;floating=im+FLOAT_TEXT_RVA;particleRender=im+PARTICLE_RENDER_RVA;particleUpdateCall=im+PARTICLE_UPDATE_CALL_RVA;
  particleGetters[0]=im+PARTICLE_GET0_RVA;particleGetters[1]=im+PARTICLE_GET1_RVA;particleGetters[2]=im+PARTICLE_GET2_RVA;particleGetters[3]=im+PARTICLE_GET3_RVA;particleGetters[4]=im+PARTICLE_GET4_RVA;particleGetters[5]=im+PARTICLE_ALPHA_RVA;
  frameMs=(volatile LONG*)(im+W3D_FRAME_MS_RVA);
  if(!match(u,kUpdate,5)||!match(u+0x71,kUpdateA,sizeof(kUpdateA))||!match(u+0xB2,kUpdateB,sizeof(kUpdateB))||!match(u+UPDATE_SCHED_OFF,kSched,sizeof(kSched))||!match(r+RESET_CLOCK_OFF,kReset,sizeof(kReset))||!match(logic,kLogicUpdate,sizeof(kLogicUpdate))||!match(c,kClientUpdate,sizeof(kClientUpdate))||!match(rate,kW3DSetRate,sizeof(kW3DSetRate))||!match(sync,kSync,sizeof(kSync))||!match(floating,kFloatText,sizeof(kFloatText))||!match(particleRender,kParticleRender,sizeof(kParticleRender))||!match(particleUpdateCall,kParticleUpdateCall,sizeof(kParticleUpdateCall))||!match(particleGetters[0],kParticleGet0,sizeof(kParticleGet0))||!match(particleGetters[1],kParticleGet1,sizeof(kParticleGet1))||!match(particleGetters[2],kParticleGet2,sizeof(kParticleGet2))||!match(particleGetters[3],kParticleGet3,sizeof(kParticleGet3))||!match(particleGetters[4],kParticleGet4,sizeof(kParticleGet4))||!match(particleGetters[5],kParticleAlpha,sizeof(kParticleAlpha)))return FALSE;
  old=(DWORD)InterlockedCompareExchange(frameMs,0,0);if(old!=33)return FALSE;g_image=im;g_w3dOld=old;g_w3dNew=old;
  /* Install the runtime-identified W3DView vslot before modifying code bytes,
     so an early startup retry cannot leave a partially installed patch. */
  if(!install_camera_scroll(im))return FALSE;
  if(!hook_sync(sync))return FALSE;if(!hook_floating_text(floating))return FALSE;if(!install_time_scheduler(u,r,logic))return FALSE;if(!hook_particle_update_call(particleUpdateCall))return FALSE;if(!install_particle_interpolation(particleRender,particleGetters))return FALSE;
  InterlockedExchange(&g_patchApplied,1);write_w3d_clock_proof();write_scheduler_proof();write_particle_proof();return TRUE;
}
static DWORD WINAPI worker(LPVOID u){DWORD i,j;(void)u;for(i=0;i<1200;i++){if(apply()){for(j=0;j<12;j++){Sleep(5000);write_w3d_clock_proof();write_particle_proof();}return 0;}Sleep(25);}InterlockedExchange(&g_patchApplied,-1);return 0;}
static BOOL load(void){char p[MAX_PATH];UINT n;HMODULE m;if(g_di)return TRUE;n=GetSystemDirectoryA(p,sizeof(p));if(!n||n>=sizeof(p)-13)return FALSE;lstrcatA(p,"\\dinput8.dll");m=LoadLibraryA(p);if(!m)return FALSE;g_create=(DirectInput8CreateProc)GetProcAddress(m,"DirectInput8Create");if(!g_create)return FALSE;g_di=m;return TRUE;}
HRESULT WINAPI DirectInput8Create(HINSTANCE a,DWORD b,REFIID c,LPVOID*d,LPUNKNOWN e){HANDLE h;if(!load())return E_FAIL;if(InterlockedCompareExchange(&g_started,1,0)==0){h=CreateThread(0,0,worker,0,0,0);if(h)CloseHandle(h);}return g_create(a,b,c,d,e);}
BOOL WINAPI DllMain(HINSTANCE a,DWORD b,LPVOID c){(void)a;(void)b;(void)c;return TRUE;}
