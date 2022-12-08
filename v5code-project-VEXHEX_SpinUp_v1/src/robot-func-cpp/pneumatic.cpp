#include "vex.h"
#include "robot-func/pneumatic.h"

bool ButtonR2Boolean = false;

void endgameActivation() {
  ButtonR2Boolean = !ButtonR2Boolean;
  endgame.set(ButtonR2Boolean);
}