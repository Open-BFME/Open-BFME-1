#ifndef BFME60FPS_SCHEDULER_MATH_H
#define BFME60FPS_SCHEDULER_MATH_H

typedef struct BfmeSchedulerMath
{
  double accumulator;
  double interval;
} BfmeSchedulerMath;

typedef struct BfmeFixedFrameClock
{
  double accumulator;
} BfmeFixedFrameClock;

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

static double bfme_w3d_clock_scale(int simulationVisualActive,
                                   int truePause,
                                   double visualSlowdown,
                                   int inputAlreadyScaled)
{
  /* Shell/loading movies use the retail real-time clock.  Only a true game
     pause freezes WW3D; merely having no active simulation is not a pause. */
  if (truePause)
    return 0.0;
  if (!simulationVisualActive || inputAlreadyScaled)
    return 1.0;
  if (visualSlowdown < 0.0)
    return 0.0;
  return visualSlowdown > 1.0 ? 1.0 : visualSlowdown;
}

static double bfme_camera_frame_scale(double realRenderDelta)
{
  /* Camera travel is real-time presentation and does not inherit the
     intentional below-15-FPS simulation/animation slowdown. */
  double scale = realRenderDelta > 0.0 ? 30.0 * realRenderDelta : 0.0;
  return scale > 2.0 ? 2.0 : scale;
}

static double bfme_legacy_frame_scale(double realRenderDelta, double visualFps)
{
  /* Legacy animation paths add one 30-Hz-sized step per visual update. */
  double scale = 30.0 * bfme_animation_delta(realRenderDelta, visualFps);
  if (scale < 0.0)
    return 0.0;
  return scale > 2.0 ? 2.0 : scale;
}

static float bfme_visual_lerp(float previous, float current, float phase)
{
  if (!(phase >= 0.0f))
    phase = 0.0f;
  else if (phase > 1.0f)
    phase = 1.0f;
  return previous + (current - previous) * phase;
}

static int bfme_fixed_frame_advance(BfmeFixedFrameClock *clock,
                                    double animationDelta,
                                    double authoredHz,
                                    int maxUpdates)
{
  double interval;
  int updates = 0;
  if (!(authoredHz > 0.0) || maxUpdates < 1)
    return 0;
  interval = 1.0 / authoredHz;
  if (animationDelta > 0.0)
    clock->accumulator += animationDelta;
  while (clock->accumulator + 1.0e-9 >= interval && updates < maxUpdates) {
    clock->accumulator -= interval;
    updates++;
  }
  if (clock->accumulator < 0.0)
    clock->accumulator = 0.0;
  /* The outer render clock discards large process stalls.  This is only a
     final guard against turning an anomalous frame into future FX debt. */
  if (updates == maxUpdates && clock->accumulator >= interval)
    clock->accumulator = 0.0;
  return updates;
}

static float bfme_fixed_frame_phase(const BfmeFixedFrameClock *clock,
                                    double authoredHz)
{
  double phase;
  if (!(authoredHz > 0.0))
    return 1.0f;
  phase = clock->accumulator * authoredHz;
  if (!(phase >= 0.0))
    return 0.0f;
  return phase > 1.0 ? 1.0f : (float)phase;
}

/* Accumulate active simulation time without consuming a due interval.  Once
   a tick is pending, its interval is intentionally kept fixed until native
   BFME admission either executes it or a lifecycle boundary discards it. */
static int bfme_scheduler_offer(BfmeSchedulerMath *clock, double activeDelta,
                                double visualFps, int pending)
{
  double oldInterval = clock->interval;
  double interval;

  if (!pending)
  {
    interval = 1.0 / bfme_target_hz(visualFps);

    /* A low-FPS interval may leave more accumulated time than the recovered
       5 Hz interval.  Clamp that remainder so recovery can offer at most one
       tick and can never turn slowdown into catch-up debt. */
    if (oldInterval > 0.0 && interval < oldInterval &&
        clock->accumulator > interval)
      clock->accumulator = interval;

    clock->interval = interval;
  }
  else if (!(clock->interval > 0.0))
  {
    clock->interval = 1.0 / bfme_target_hz(visualFps);
  }

  if (activeDelta > 0.0)
    clock->accumulator += activeDelta;

  return !pending &&
         clock->accumulator + 1.0e-9 >= clock->interval;
}

/* Consume time only after the hooked GameLogic entry proves that BFME's
   native network gate admitted the pending tick.  A short delay retains its
   remainder; a delay of another whole interval or more drops stale debt. */
static void bfme_scheduler_complete(BfmeSchedulerMath *clock,
                                    double pendingInterval)
{
  if (!(pendingInterval > 0.0))
    pendingInterval = clock->interval;

  clock->accumulator -= pendingInterval;
  if (clock->accumulator < 0.0 ||
      clock->accumulator + 1.0e-9 >= pendingInterval)
    clock->accumulator = 0.0;
}

static int bfme_scheduler_advance(BfmeSchedulerMath *clock, double activeDelta,
                                  double visualFps)
{
  if (!bfme_scheduler_offer(clock, activeDelta, visualFps, 0))
    return 0;
  bfme_scheduler_complete(clock, clock->interval);
  return 1;
}

#endif
