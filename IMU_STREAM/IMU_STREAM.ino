#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.

   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3-5V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
   2015/AUG/27  - Added calibration and system status helpers
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

const uint8_t calibrationData[22]= {243,255,169,255,9,0,0,0,252,255,0,0,209,1,2,2,12,1,232,3,214,3};
uint8_t buf[6];

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);

  /* Initialise the sensor */
  if(!bno.begin(bno.adafruit_bno055_opmode_t::OPERATION_MODE_IMUPLUS))
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("error");
    while(1);
  }

  delay(1000);

  bno.setSensorOffsets(calibrationData);

}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{

  memset (buf, 0, 6);
  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)bno.adafruit_vector_type_t::VECTOR_EULER, buf, 6);
  Serial.write(0);
  Serial.write(0);
  Serial.write(0);
  Serial.write(buf,6);
//  Serial.println(" ");
//  Serial.print((unsigned int)buffer[0]);
//  Serial.print(" ");
//  Serial.print((unsigned int)buffer[1]);
//  Serial.print(" ");
//  Serial.print((unsigned int)buffer[2]);
//  Serial.print(" ");
//  Serial.print((unsigned int)buffer[3]);
//  Serial.print(" ");
//  Serial.print((unsigned int)buffer[4]);
//  Serial.print(" ");
//  Serial.print((unsigned int)buffer[5]);
  /* Wait the specified delay before requesting nex data */
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
