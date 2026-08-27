#pragma once

// This is a modernization switch, not part of the retail byte-match path.
// Keep it easy to turn off while comparing the original camera behavior.
#ifndef BFME_ENABLE_HOR_PLUS_WIDESCREEN
#define BFME_ENABLE_HOR_PLUS_WIDESCREEN 1
#endif

// The retail tactical view is full display width, but its default control bar
// leaves only about 80% of the display height for the world.  The reference
// aspect is therefore the 4:3 display aspect adjusted for the current view's
// width and height fractions, rather than a hard-coded 4:3 camera aspect.
static const Real HOR_PLUS_REFERENCE_DISPLAY_ASPECT = 4.0f / 3.0f;

static inline Real calculateHorPlusReferenceViewportAspect(
	Real currentViewportAspect,
	Real currentDisplayAspect)
{
	if (currentViewportAspect <= 0.0f || currentDisplayAspect <= 0.0f)
		return HOR_PLUS_REFERENCE_DISPLAY_ASPECT;

	return currentViewportAspect * HOR_PLUS_REFERENCE_DISPLAY_ASPECT / currentDisplayAspect;
}

static inline Real calculateReferenceVerticalFov(
	Real referenceViewportAspect,
	Real referenceHorizontalFov)
{
	if (referenceViewportAspect <= 0.0f)
		return referenceHorizontalFov;

	return 2.0f * atan(tan(referenceHorizontalFov * 0.5f) / referenceViewportAspect);
}

static inline Real calculateHorPlusHorizontalFov(
	Real currentViewportAspect,
	Real referenceViewportAspect,
	Real referenceHorizontalFov)
{
	if (currentViewportAspect <= 0.0f || referenceViewportAspect <= 0.0f)
		return referenceHorizontalFov;

	Real referenceVerticalFov = calculateReferenceVerticalFov(
		referenceViewportAspect, referenceHorizontalFov);
	return 2.0f * atan(tan(referenceVerticalFov * 0.5f) * currentViewportAspect);
}
