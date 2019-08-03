#include "Ds18b20.h"
#include "stm32l1xx_gpio.h"

#define DS_PIN	  10

/**@brief Function for reading bit.
 */
Sensor::Temperature::Temperature(port_t port, pin_t pin, resolution_t resolution){
    m_port = port;
    m_pin = pin;

    if(setResolution(resolution) == TEMP_SENS_OK){
#ifdef DEBUG_LOG
    printf("Ds18b20.cpp. Resolution Is SET\n");
#endif
    } else {
#ifdef DEBUG_LOG
    printf("Ds18b20.cpp. Resolution Is NOT SET\n");
#endif
    }
}

/**@brief Function for reading bit.
 */  
Sensor::Temperature::~Temperature(){

}

/**@brief Function for reading bit.
 */
void Sensor::Temperature::write_bit(uint8_t bit){

    GPIO_ResetBits(GPIOC, DS_PIN);
    


    nrf_gpio_cfg_output(portMap);
    nrf_gpio_pin_clear(portMap);

    nrf_delay_us(5);

    if(bit)
    {
        nrf_gpio_pin_set(portMap);
    }

    nrf_delay_us(80);
    nrf_gpio_pin_set(portMap);   
}

/**@brief Function for reading bit.
 */
uint8_t Sensor::Temperature::read_bit(void){

    uint8_t bit = 0;
    uint32_t portMap = NRF_GPIO_PIN_MAP(m_port, m_pin);

    nrf_gpio_cfg_output(portMap);
    nrf_gpio_pin_clear(portMap);

    nrf_delay_us(5);

    nrf_gpio_pin_set(portMap);

    nrf_delay_us(15);

    nrf_gpio_cfg_input(portMap, NRF_GPIO_PIN_NOPULL);

    if(nrf_gpio_pin_read(portMap))
    {
        bit = 1;
    }    

    return bit;
}

/**@brief Function for reading bit.
 */
void Sensor::Temperature::write_byte(uint8_t byte){
    uint8_t i = 8;
    while(i--)
    {
        write_bit(byte & 1);
        byte >>= 1;
    }
//    unsigned char i;
//    unsigned char x;
//    for(i=0;i<8;i++)
//    {
//      x = byte>>i;
//      x &= 0x01;
//      write_bit(x);
//    }
//    nrf_delay_us(100);
}

/**@brief Function for reading bit.
 */
uint8_t Sensor::Temperature::read_byte(void){
//    unsigned char i;
//    unsigned char data = 0;
//    for (i=0;i<8;i++)
//    {
//        if(read_bit()) data|=0x01<<i;
//        nrf_delay_us(15);
//    }
//    return(data);
    uint8_t i = 8, n = 0;
    while(i--)
    {
        n >>= 1;
        n |= (read_bit() << 7);
        nrf_delay_us(1);
    }
    return n;
}

uint8_t Sensor::Temperature::reset(void){
    uint8_t presence = NOT_PRESENT;

    uint32_t portMap = NRF_GPIO_PIN_MAP(m_port, m_pin);

    nrf_gpio_cfg_output(portMap);
    nrf_gpio_pin_clear(portMap);

    nrf_delay_us(500);
    nrf_gpio_pin_set(portMap);

    nrf_gpio_cfg_input(portMap, NRF_GPIO_PIN_NOPULL);
    nrf_delay_us(30);

    nrf_delay_us(470);

    if(nrf_gpio_pin_read(portMap) == 1)
    {
        presence = PRESENT;
    }

    return presence;
}

/**@brief Function for reading bit.
 */
Sensor::Temperature::state_t Sensor::Temperature::setResolution(uint8_t resolution){

    if(reset() == NOT_PRESENT){
        printf("Sensor is NOT Detected\n");
        return TEMP_SENS_ERROR;
    }

    write_byte(SKIP_ROM);
    write_byte(WRITE_SCRATCHPAD);
    
    write_byte(0);
    write_byte(100);
    switch(resolution)
    {
        case _9_BIT:
            write_byte(_9_BIT);
            m_resolution = _9_BIT;
            break;

        case _10_BIT:
            write_byte(_10_BIT);
            m_resolution = _10_BIT;
            break;

        case _11_BIT:
            write_byte(_11_BIT);
            m_resolution = _11_BIT;
            break;

        case _12_BIT:
        default:
            write_byte(_12_BIT);
            m_resolution = _12_BIT;
            break;
    }

    if(reset() == NOT_PRESENT){
        return TEMP_SENS_ERROR;
    }

    return TEMP_SENS_OK;
}

/**@brief Function for reading bit.
 */
Sensor::Temperature::state_t Sensor::Temperature::updateTemperature(void){

    uint8_t temp_l, temp_h;
    uint8_t attempt = 100;
    //m_temperature = 0;

    if(reset() == PRESENT){

        write_byte(SKIP_ROM);
        write_byte(CONVERT_TEMP);

        while(attempt--){
            if(read_bit()){
                break;
            }
        }

        if(reset() == PRESENT){
            write_byte(SKIP_ROM);
            write_byte(READ_SCRATCHPAD);

            temp_l = read_byte();
            temp_h = read_byte();

            //*value = ((temp_h << 8 ) + temp_l) * 0.0625;
            m_temperature = ((temp_h << 8 ) + temp_l) * 0.0625;
            if(m_temperature > 40){
                printf("");
            }
           return TEMP_SENS_OK;
        }
        return TEMP_SENS_ERROR;
    }
    return TEMP_SENS_ERROR;
}

float Sensor::Temperature::getTemerature(void){
    return m_temperature;
}
