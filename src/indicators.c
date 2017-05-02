#ifndef _indicators
#define _indicators

int indMode[2] = {0, 0};
/* various modes for indicators, might not all be used
 * 0: off
 * 1: on
 * 2: slow blink
 * 3: fast blink
 * 4: dim (PWM, i.e., very very fast blink)
 */

// indirection: indicator lamps
int ind[2] = {ind0, ind1};

// counter used for indicator timing
int indicatorTick = 0;

// refreshes the indicator LEDs, updating them if necessary
void doIndicateTick() {
  // speed of flashing (in ticks)
  int flashSpeed;
  // iterate through each LED
  for (int i = 0; i < 2; ++i) {
    flashSpeed = 4096;
    switch (indMode[i]) {
      case 1:
        // led is on
        turnLEDOn(ind[i]);
        break;
      case 2:
        // led is flashing slowly
        flashSpeed *= 2;
        /* falls through */
      case 3:
        // led is flashing quickly
        if ((indicatorTick % flashSpeed) > (flashSpeed / 2))
          turnLEDOn(ind[i]);
        else
          turnLEDOff(ind[i]);
        break;
      case 4:
        // led is dim
        if (!(indicatorTick % 4))
          turnLEDOn(ind[i]);
        else
          turnLEDOff(ind[i]);
        break;
      default:
        // led is off
        turnLEDOff(ind[i]);
        break;
    }
  }
  // increment the tick, and loop around if appropriate.
  indicatorTick++;
  if (indicatorTick > flashSpeed * 2) indicatorTick = 0;
}

#endif