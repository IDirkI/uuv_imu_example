#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

///Available ADC channels to read from.
enum class AdcChannel {
  Ch0,
  Ch1,
  Ch2,
  Ch3,
};

///Controllable PWM output channels.
enum class PwmChannel {
  Ch1,
  Ch2,
  Ch3,
  Ch4,
  Ch5,
  Ch6,
  Ch7,
  Ch8,
  Ch9,
  Ch10,
  Ch11,
  Ch12,
  Ch13,
  Ch14,
  Ch15,
  Ch16,
  All,
};

///Onboard user-controllable LEDs.
enum class UserLed {
  Led1,
  Led2,
  Led3,
};

///An array of readings from the different ADC channels.
struct ADCData {
  float channel[4];
};

///Board-oriented direction axes (x is forwards, y is right, z is down).
struct AxisData {
  float x;
  float y;
  float z;
};

extern "C" {

///Sets the size of the navigator led strip (1 is the default), should be called before `init`.
void set_rgb_led_strip_size(uintptr_t size);

///Initializes the Navigator module with default settings.
void init();

///Runs some tests on available sensors, then returns the result.
bool self_test();

///Sets the state of the selected onboard LED.
void set_led(UserLed select, bool state);

///Gets the selected onboard LED output state.
bool get_led(UserLed select);

///Toggle the output of the selected LED.
void set_led_toggle(UserLed select);

///Sets all user LEDs to the desired state ( Blue, Green, and Red ).
void set_led_all(bool state);

///Set the color brightnesses of a connected NeoPixel LED array.
void set_neopixel(const uint8_t (*rgb_array)[3], uintptr_t length);

///Set the color brightnesses of a connected NeoPixel LED array.
void set_neopixel_rgbw(const uint8_t (*rgb_array)[4], uintptr_t length);

///Reads the ADC channel values (from the ADS1115 chip).
ADCData read_adc_all();

///Reads a specific ADC channel (from the ADS1115 chip).
float read_adc(AdcChannel channel);

///Reads the current pressure (from the onboard BMP280 chip).
float read_pressure();

///Reads the current temperature (from the onboard BMP280 chip).
float read_temp();

///Reads the local magnetic field strengths (from the onboard Ak09915 magnetometer).
AxisData read_mag();

///Reads the current acceleration values (from the ICM20689 chip's accelerometer).
AxisData read_accel();

///Reads the current angular velocity (from the ICM20689 chip's gyroscope).
AxisData read_gyro();

///Reads the state of leak detector pin from Navigator.
bool read_leak();

///Enables or disables the PWM chip (PCA9685), using the firmware and OE_pin.
void set_pwm_enable(bool state);

///Get the PWM chip (PCA9685)'s OE_pin state
bool get_pwm_enable();

///LOW_LEVEL: Sets the PWM frequency of the PCA9685 chip. All channels use the same frequency.
void set_pwm_freq_prescale(uint8_t value);

///Sets the PWM frequency of the PCA9685 chip. All channels use the same frequency.
void set_pwm_freq_hz(float freq);

///Sets the duty cycle (the proportion of ON time) for the selected PWM channel.
void set_pwm_channel_value(PwmChannel channel, uint16_t value);

///Sets the duty cycle (the proportion of ON time) for the selected PWM channel.
void set_pwm_channel_duty_cycle(PwmChannel channel, float duty_cycle);

///Sets the duty cycle (based on OFF counter from 0 to 4096) for a list of multiple PWM channels.
void set_pwm_channels_value(const PwmChannel *channels, uint16_t value, uintptr_t length);

///Sets the duty cycle (from 0.0 to 1.0) for a list of multiple PWM channels.
void set_pwm_channels_duty_cycle(const PwmChannel *channels, float duty_cycle, uintptr_t length);

///Sets the duty cycle (from 0 to 4096) for a list of multiple channels with multiple values.
void set_pwm_channels_values(const PwmChannel *channels, const uint16_t *values, uintptr_t length);

///Sets the duty cycle (from 0.0 to 1.0) for a list of multiple channels with multiple values.
void set_pwm_channels_duty_cycle_values(const PwmChannel *channels,
                                        const float *duty_cycle,
                                        uintptr_t length);

} // extern "C"
