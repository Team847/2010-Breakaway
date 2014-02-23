#include "Manipulator.h"
#define extendDelay 0.25
Manipulator::Manipulator()
{
	extendTest = false;
	firstPassTest = true;
}
Manipulator::~Manipulator() {
}
void Manipulator::UseManip(bool triggerManip) {
	if (triggerManip == true) {
		if (extendTest == false) {
			if (failSafeTimer.Get() >= 2.0 || firstPassTest == true) {
				failSafeTimer.Stop();
				failSafeTimer.Reset();
				Hardware::GetInstance()->GetKicker2()->Set(false);
				Hardware::GetInstance()->GetKicker1()->Set(true);
				extendTest = true;
				firingPauseTimer.Start();
				firstPassTest = false;
			}
		}
	}
	if (firingPauseTimer.Get() >= extendDelay) {
		Hardware::GetInstance()->GetKicker1()->Set(false);
		Hardware::GetInstance()->GetKicker2()->Set(true);
		extendTest = false;
		firingPauseTimer.Stop();
		firingPauseTimer.Reset();
		failSafeTimer.Start();
	}
}
