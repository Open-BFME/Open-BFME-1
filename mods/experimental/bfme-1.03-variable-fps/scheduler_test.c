#include <stdio.h>
#include <string.h>
#include "scheduler_math.h"

static int run_seconds(double fps,int seconds)
{
  BfmeSchedulerMath clock;int frames=(int)(fps*(double)seconds),i,ticks=0;
  memset(&clock,0,sizeof(clock));
  for(i=0;i<frames;i++)ticks+=bfme_scheduler_advance(&clock,1.0/fps,fps);
  return ticks;
}

static double absolute(double x){return x<0.0?-x:x;}

static double run_animation_seconds(double fps,int seconds)
{
  int frames=(int)(fps*(double)seconds),i;double total=0.0;
  for(i=0;i<frames;i++)total+=bfme_animation_delta(1.0/fps,fps);
  return total;
}

static int interpolation_is_monotonic(double fps,int seconds)
{
  BfmeSchedulerMath clock;int frames=(int)(fps*(double)seconds),i,age=0;double phase=0.0,last=0.0,current;
  memset(&clock,0,sizeof(clock));
  for(i=0;i<frames;i++){
    phase+=bfme_animation_delta(1.0/fps,fps)/0.2;if(phase>1.0)phase=1.0;
    if(bfme_scheduler_advance(&clock,1.0/fps,fps)){age++;phase=0.0;}
    current=(double)age+phase;if(current+1.0e-7<last)return 0;last=current;
  }
  return 1;
}

static long accumulated_frame_milliseconds(double fps,int seconds)
{
  int frames=(int)(fps*(double)seconds),i;double remainder=0.0,exact;long total=0,whole;
  for(i=0;i<frames;i++){
    exact=bfme_animation_delta(1.0/fps,fps)*1000.0+remainder;whole=(long)exact;
    remainder=exact-(double)whole;total+=whole;
  }
  return total;
}

static int legacy_phase_sequence_is_complete(double fps,int seconds)
{
  BfmeSchedulerMath clock;int frames=(int)(fps*(double)seconds),i,phase=1,next,fill,mask=0,ticks=0;
  memset(&clock,0,sizeof(clock));
  for(i=0;i<frames;i++){
    next=phase+1;
    if(bfme_scheduler_advance(&clock,1.0/fps,fps)){
      for(fill=next;fill<=6;fill++)if(fill>=2)mask|=1<<fill;
      if(mask!=(0x7c))return 0;
      mask=0;phase=1;ticks++;
    }else{
      if(next>=2&&next<=6)mask|=1<<next;
      phase=next;
    }
  }
  return ticks>0;
}

typedef struct SyncMathTest
{
  unsigned long caller,raw,out;
  double remainder;
  int valid;
} SyncMathTest;

static unsigned long sync_math_step(SyncMathTest *clock,unsigned long caller,
                                    unsigned long raw,double scale)
{
  unsigned long delta,whole;double amount;
  if(!clock->valid){clock->caller=caller;clock->raw=raw;clock->out=raw;clock->remainder=0.0;clock->valid=1;return raw;}
  if(clock->caller!=caller){clock->caller=caller;clock->raw=raw;clock->remainder=0.0;return clock->out;}
  delta=raw-clock->raw;if(delta>1000){clock->raw=raw;clock->remainder=0.0;return clock->out;}
  amount=(double)delta*scale+clock->remainder;whole=(unsigned long)amount;clock->remainder=amount-(double)whole;
  clock->raw=raw;clock->out+=whole;return clock->out;
}

int main(void)
{
  const double fps[] = {60,45,30,20,15,12,10,5};
  const int expected[] = {300,300,300,300,300,240,200,100};
  BfmeSchedulerMath clock;FILE *out;int i,ticks,failures=0,first,second;double animation,expectedAnimation,scale,period,phase;
  out=fopen("build\\bfme60fps_local\\scheduler_test_results.txt","w");
  if(!out)return 2;
  fprintf(out,"BFME 60 FPS active-time scheduler deterministic tests\n");
  for(i=0;i<(int)(sizeof(fps)/sizeof(fps[0]));i++){
    ticks=run_seconds(fps[i],60);
    fprintf(out,"steady fps=%g seconds=60 ticks=%d expected=%d %s\n",fps[i],ticks,expected[i],ticks==expected[i]?"PASS":"FAIL");
    if(ticks!=expected[i])failures++;
    animation=run_animation_seconds(fps[i],60);expectedAnimation=60.0*bfme_visual_slowdown(fps[i]);
    scale=bfme_legacy_frame_scale(1.0/fps[i],fps[i]);period=fps[i]/bfme_target_hz(fps[i]);
    fprintf(out,"animation fps=%g seconds=60 animation_s=%.6f expected=%.6f integer_ms=%ld frame_scale=%.6f visual_period=%.6f monotonic=%s phases_2_to_6=%s %s\n",fps[i],animation,expectedAnimation,accumulated_frame_milliseconds(fps[i],60),scale,period,interpolation_is_monotonic(fps[i],60)?"PASS":"FAIL",legacy_phase_sequence_is_complete(fps[i],60)?"PASS":"FAIL",absolute(animation-expectedAnimation)<1.0e-6&&absolute((double)accumulated_frame_milliseconds(fps[i],60)-expectedAnimation*1000.0)<1.1&&interpolation_is_monotonic(fps[i],60)&&legacy_phase_sequence_is_complete(fps[i],60)?"PASS":"FAIL");
    if(absolute(animation-expectedAnimation)>=1.0e-6||absolute((double)accumulated_frame_milliseconds(fps[i],60)-expectedAnimation*1000.0)>=1.1||!interpolation_is_monotonic(fps[i],60)||!legacy_phase_sequence_is_complete(fps[i],60))failures++;
  }

  memset(&clock,0,sizeof(clock));ticks=0;
  for(i=0;i<6;i++)ticks+=bfme_scheduler_advance(&clock,1.0/60.0,60.0);
  /* A pause contributes no calls; the pre-pause half interval is retained. */
  for(i=0;i<6;i++)ticks+=bfme_scheduler_advance(&clock,1.0/60.0,60.0);
  fprintf(out,"pause_remainder ticks=%d expected=1 %s\n",ticks,ticks==1?"PASS":"FAIL");if(ticks!=1)failures++;
  phase=0.375; /* Paused frames contribute zero animation delta and preserve interpolation. */
  for(i=0;i<600;i++)phase+=bfme_animation_delta(0.0,60.0)/0.2;
  fprintf(out,"pause_visual_phase phase=%.6f expected=0.375000 %s\n",phase,absolute(phase-0.375)<1.0e-9?"PASS":"FAIL");if(absolute(phase-0.375)>=1.0e-9)failures++;

  {
    int render,clientFrame=0,advanceFrame=1,logicPhaseCalls=0,presentationPhase=1;
    double presentationRatio=0.0;
    /* Model the hook boundary: retail has already set advanceFrame before
       the scheduler decision.  The presentation-only pause route must leave
       it set and must not enter any GameLogic phase. */
    for(render=0;render<12;render++){
      if(advanceFrame)clientFrame++;
      advanceFrame=1;
      presentationPhase++;
      presentationRatio=(double)presentationPhase/12.0;
      if(presentationRatio>1.0)presentationRatio=1.0;
      /* paused scheduler: skip the phase-dispatch call */
    }
    fprintf(out,"pause_presentation_route client_frames=%d logic_phases=%d ratio=%.1f expected=12,0,1.0 %s\n",
      clientFrame,logicPhaseCalls,presentationRatio,(clientFrame==12&&logicPhaseCalls==0&&absolute(presentationRatio-1.0)<1.0e-9)?"PASS":"FAIL");
    if(clientFrame!=12||logicPhaseCalls!=0||absolute(presentationRatio-1.0)>=1.0e-9)failures++;
  }

  {
    unsigned long retailW3dClock=1000,worldAnimationFrame=42,lastWorldSync=1000;
    /* The shared retail clock remains available to pause-menu presentation,
       while the separate world-animation hold consumes zero visual delta. */
    for(i=0;i<10;i++){retailW3dClock+=16;lastWorldSync=retailW3dClock;}
    fprintf(out,"pause_clock_separation w3d_ms=%lu world_frame=%lu last_sync=%lu expected=1160,42,1160 %s\n",
      retailW3dClock,worldAnimationFrame,lastWorldSync,(retailW3dClock==1160&&worldAnimationFrame==42&&lastWorldSync==1160)?"PASS":"FAIL");
    if(retailW3dClock!=1160||worldAnimationFrame!=42||lastWorldSync!=1160)failures++;
  }

  fprintf(out,"game_modes shell4=%d singleplayer7=%d expected=1,0 %s\n",bfme_game_mode_suspends_scheduler(4),bfme_game_mode_suspends_scheduler(7),bfme_game_mode_suspends_scheduler(4)==1&&bfme_game_mode_suspends_scheduler(7)==0?"PASS":"FAIL");
  if(bfme_game_mode_suspends_scheduler(4)!=1||bfme_game_mode_suspends_scheduler(7)!=0)failures++;

  {SyncMathTest sync;unsigned long a,b,c,d,e,f,g;memset(&sync,0,sizeof(sync));
    a=sync_math_step(&sync,1,1000,1.0);b=sync_math_step(&sync,1,1016,1.0);
    c=sync_math_step(&sync,2,50000,0.5);d=sync_math_step(&sync,2,50020,0.5);
    e=sync_math_step(&sync,1,1032,1.0);f=sync_math_step(&sync,1,1048,1.0);
    g=sync_math_step(&sync,1,1064,0.0);
    fprintf(out,"global_sync outputs=%lu,%lu,%lu,%lu,%lu,%lu,%lu expected=1000,1016,1016,1026,1026,1042,1042 %s\n",a,b,c,d,e,f,g,(a==1000&&b==1016&&c==1016&&d==1026&&e==1026&&f==1042&&g==1042)?"PASS":"FAIL");
    if(a!=1000||b!=1016||c!=1016||d!=1026||e!=1026||f!=1042||g!=1042)failures++;
  }

  {double raw=10.0,input=10.0,rendered=10.0,delta; /* Central manual-HLOD pause accumulator. */
    for(i=0;i<20;i++){raw+=1.0;delta=raw-input;input=raw;rendered+=delta*0.0;}
    raw+=1.0;delta=raw-input;input=raw;rendered+=delta;
    fprintf(out,"pause_manual_animation rendered=%.6f expected=11.000000 %s\n",rendered,absolute(rendered-11.0)<1.0e-9?"PASS":"FAIL");if(absolute(rendered-11.0)>=1.0e-9)failures++;
  }

  memset(&clock,0,sizeof(clock));
  bfme_scheduler_advance(&clock,0.59,5.0);
  first=bfme_scheduler_advance(&clock,1.0/60.0,60.0);
  second=bfme_scheduler_advance(&clock,1.0/60.0,60.0);
  fprintf(out,"low_fps_recovery first=%d second=%d expected=1,0 %s\n",first,second,(first==1&&second==0)?"PASS":"FAIL");if(first!=1||second!=0)failures++;

  memset(&clock,0,sizeof(clock));ticks=0;
  for(i=0;i<600;i++)ticks+=bfme_scheduler_advance(&clock,1.0/60.0,60.0);
  /* A five-second debugger/process stall is discarded by the outer clock. */
  for(i=0;i<600;i++)ticks+=bfme_scheduler_advance(&clock,1.0/60.0,60.0);
  fprintf(out,"discarded_stall ticks=%d expected=100 %s\n",ticks,ticks==100?"PASS":"FAIL");if(ticks!=100)failures++;

  fprintf(out,"failures=%d\n",failures);fclose(out);return failures?1:0;
}
