#ifndef SONAR_H_
#define SONAR_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Sonar {
   public:
    /**
     * @param triggerPin  Digital ben til styring af sensoren (output).
     * @param echoPin  Digitalt ben til modtagelse af data fra sensoren (input).
     */
      Sonar(int triggerPin, int echoPin);

    /**
     * Måler afstanden
     * @returns Afstanden i cm. Ved afstande længere end 400cm retuneres negativ værdi.
     */
      double distanceCM();

    /**
     * Måler afstanden
     * @returns Afstanden i cm. Ved afstande længere end 400cm retuneres negativ værdi.
     * @param temperatur  Temperatur i grades celcius
     */
      double distanceCM(float temperatur);
   private:
      int triggerPin;
      int echoPin;
};

#endif 