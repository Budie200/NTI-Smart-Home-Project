#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    unsigned int temperatureADC;
    unsigned int lightADC;
    unsigned int temperature;


    // ================= PORT CONFIGURATION =================

    // PORTC all output
    DDRC = 0b11111111;

    // PORTA all input
    DDRA = 0b00000000;


    // ================= ADC CONFIGURATION =================

    // AVCC as reference voltage
    // ADC0 selected
    ADMUX = 0b01000000;

    // Enable ADC
    // Prescaler = 8
    ADCSRA = 0b10000111;


    // ================= MAIN LOOP =================

    while(1)
    {
        // Select ADC0
        ADMUX = 0b01000000;

        // Start ADC conversion
        ADCSRA = ADCSRA | 0b01000000;

        // Wait until conversion finishes
        while((ADCSRA & 0b00010000) == 0)
        {
        }

        // Read ADC result
        temperatureADC = ADCL;

        temperatureADC = temperatureADC |
                         (ADCH << 8);

        // Clear ADC flag
        ADCSRA = ADCSRA | 0b00010000;


        // Convert ADC value to Celsius
        temperature = (temperatureADC * 500UL) / 1024;
        // Select ADC1
        ADMUX = 0b01000001;

        // Start ADC conversion
        ADCSRA = ADCSRA | 0b01000000;

        // Wait until conversion finishes
        while((ADCSRA & 0b00010000) == 0)
        {
        }

        // Read ADC result
        lightADC = ADCL;

        lightADC = lightADC |
                   (ADCH << 8);

        // Clear ADC flag
        ADCSRA = ADCSRA | 0b00010000;
      
        if(temperature >= 30)
        {
            PORTC = PORTC | 0b00000100;
        }

        else
        {
            PORTC = PORTC & 0b11111011;
        }

        if(lightADC < 400)
        {
            // Living Room Light ON
            PORTC = PORTC | 0b00000001;

            // Bedroom Light ON
            PORTC = PORTC | 0b00000010;
        }

        else
        {
            // Living Room Light OFF
            PORTC = PORTC & 0b11111110;

            // Bedroom Light OFF
            PORTC = PORTC & 0b11111101;
        }


        _delay_ms(500);
    }
}
