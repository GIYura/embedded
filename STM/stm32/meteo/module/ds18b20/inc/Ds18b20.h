#ifndef _DS18B20_H
#define _DS18B20_H

#include <stdint.h>

namespace Sensor{
    class Temperature{

        private:

            void write_bit(uint8_t bit);
            uint8_t read_bit(void);

            void write_byte(uint8_t byte);
            uint8_t read_byte(void);

            uint8_t reset(void);

            enum cmd_t{
                SKIP_ROM          = 0xCC,
                WRITE_SCRATCHPAD  = 0x4E,
                READ_SCRATCHPAD   = 0xBE,
                CONVERT_TEMP      = 0x44
            };

            enum status_t{
                NOT_PRESENT = 0,
                PRESENT
            };

        public:

            enum resolution_t{
                _9_BIT            = 0x1F,
                _10_BIT           = 0x3F,
                _11_BIT           = 0x5F,
                _12_BIT           = 0x7F
            };

            enum port_t{
                kPortA  = 0,
                kPortB,
                kPortC,
                kPortD
            };

            enum pin_t{
                kPin0 = 0,
                kPin1,
                kPin2,
                kPin3,
                kPin4,
                kPin5,
                kPin6,
                kPin7,
                kPin8,
                kPin9,
                kPin10,
                kPin11,
                kPin12,
                kPin13,
                kPin14,
                kPin15,
                kPin16,
                kPin17,
                kPin18,
                kPin19,
                kPin20,
                kPin21,
                kPin22,
                kPin23,
                kPin24,
                kPin25,
                kPin26,
                kPin27,
                kPin28,
                kPin29,
                kPin30,
                kPin31
            };

        private:
    
            port_t m_port;
            pin_t m_pin;
            resolution_t m_resolution;

        public:

            enum state_t{
                TEMP_SENS_OK      = 0,
                TEMP_SENS_ERROR
            };
            
            state_t updateTemperature(void);
            state_t setResolution(uint8_t resolution);
         
            Temperature(port_t port, pin_t pin, resolution_t resolution);
            ~Temperature();

            float getTemerature(void);

            float m_temperature;

    };
}
#endif