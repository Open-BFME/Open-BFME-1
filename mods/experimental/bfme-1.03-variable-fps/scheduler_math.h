#ifndef BFME60FPS_SCHEDULER_MATH_H
#define BFME60FPS_SCHEDULER_MATH_H

typedef struct BfmeSchedulerMath
{
  double accumulator;
  double interval;
} BfmeSchedulerMath;

static int bfme_game_mode_suspends_scheduler(int mode)
{
  /* BFME mode 4 is the shell.  Mode 7 is also single-player and must run. */
  return mode == 4;
}

static double bfme_target_hz(double visualFps)
{
  if (!(visualFps > 0.0) || visualFps > 1000.0)
    visualFps = 15.0;
  return visualFps >= 15.0 ? 5.0 : 5.0 * (visualFps / 15.0);
}

static double bfme_visual_slowdown(double visualFps)
{
  if (!(visualFps > 0.0) || visualFps > 1000.0)
    visualFps = 15.0;
  return visualFps >= 15.0 ? 1.0 : visualFps / 15.0;
}

static double bfme_animation_delta(double realRenderDelta, double visualFps)
{
  return realRenderDelta > 0.0
             ? realRenderDelta * bfme_visual_slowdown(visualFps)
             : 0.0;
}

static double bfme_legacy_frame_scale(double realRenderDelta, double visualFps)
{
  /* Legacy animation paths add one 30-Hz-sized step per visual update. */
  double scale = 30.0 * bfme_animation_delta(realRenderDelta, visualFps);
  if (scale < 0.0)
    return 0.0;
  return scale > 2.0 ? 2.0 : scale;
}

static int bfme_scheduler_advance(BfmeSchedulerMath *clock, double activeDelta,
                                  double visualFps)
{
  double oldInterval = clock->interval;
  double targetHz = bfme_target_hz(visualFps);
  double interval = 1.0 / targetHz;

  /* A low-FPS interval may leave more accumulated time than the recovered
     5 Hz interval.  Clamp that remainder so recovery can emit at most one
     tick and can never turn slowdown into catch-up debt. */
  if (oldInterval > 0.0 && interval < oldInterval &&
      clock->accumulator > interval)
    clock->accumulator = interval;

  clock->interval = interval;
  if (activeDelta > 0.0)
    clock->accumulator += activeDelta;

  if (clock->accumulator + 1.0e-9 < interval)
    return 0;

  clock->accumulator -= interval;
  if (clock->accumulator < 0.0 || clock->accumulator + 1.0e-9 >= interval)
    clock->accumulator = 0.0;
  return 1;
}

#endif
