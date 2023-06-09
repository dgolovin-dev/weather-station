#include "./scheduler.h"

class PotentiometerModule {
  public: 
    struct Args {
      bool reversed;
      float minValue;
      float maxValue;
      float* outValue;
      uint8_t pin;
      Scheduler* timer;
      unsigned long updatePeriod;
    };

    PotentiometerModule(Args args) {
      this->args = args;
      args.timer->schedule(args.updatePeriod, true, &this->update, this);
    }

  private:
    Args args;
    bool initialized; 

    bool update() {
      auto signal = analogRead(this->args.pin);
      if(args.reversed) {
        signal = 1023 - signal;
      }
      *(this->args.outValue) = this->args.minValue + (this->args.maxValue - this->args.minValue) * (float)signal/1023.0;      
      return true;
    }
};