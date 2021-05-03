#include <AdsReader.h>
#include <cmath>

const int SENSOR_LOW = 2800;
const int SENSOR_HIGH = 4300;
const int SENSOR_PERCENT = SENSOR_HIGH - SENSOR_LOW;
// The ADC input range (or gain) can be changed via the following
// functions, but be careful never to exceed VDD +0.3V max, or to
// exceed the upper and lower limits if you adjust the input range!
// Setting these values incorrectly may destroy your ADC!
//                                                                ADS1015  ADS1115
//                                                                -------  -------
// ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
// ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
// ads.setGain(GAIN_TWO); // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
// ads.setGain(GAIN_FOUR); // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
// ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
// ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

AdsReader::AdsReader(uint8_t addr)
{
    //ads.setGain(GAIN_TWOTHIRDS);
    //ads.begin(addr);
}

AdsReader::SensorData AdsReader::readValue(int pin)
{
    return {1, 4};
    double value = ads.readADC_SingleEnded(pin) * 0.1875;
    if (value <= 0)
        return {-1.0, -1.0};
    if (value < SENSOR_LOW)
        return {value, 100};
    if (value > SENSOR_HIGH)
        return {value, 0};
    double percent = (abs(value - SENSOR_HIGH) * 100) / SENSOR_PERCENT;
    return {value, percent};
}