//
// Created by sami on 18/01/18.
//



void configADC(gpio_pin_id_t gpioPin){
    adc_configure(
            ADC_CONFIG_OPTION_SAMPLING_SINGLE_STEP
            |ADC_CONFIG_OPTION_SAMPLING_MODE_SINGLE_ENDED
            |ADC_CONFIG_OPTION_RESULT_JUSTIFICATION_RIGHT
            |ADC_CONFIG_OPTION_RESOLUTION_10_BITS
            |ADC_CONFIG_OPTION_REF_SELECT_VDD);
    adc_set_input_channel(gpioPin);
    adc_start_single_conversion(gpioPin);
}

uint16_t readADC(gpio_pin_id_t gpioPin){
    uint16_t resultat = adc_start_single_conversion_get_value(gpioPin);
    return resultat;
}


void configI2C(){

    w2_configure( W2_CONFIG_OPTION_ENABLE |
                  W2_CONFIG_OPTION_MODE_MASTER |
                  W2_CONFIG_OPTION_CLOCK_FREQ_400_KHZ	);
}

void configOPT3001(){
    w2_send_start_condition();
    w2_send_byte(10001010);
    w2_send_byte(00000001);
    w2_send_byte(11001010);
    w2_send_byte(00010000);
    w2_send_stop_condition();
}


uint16_t readOPT3001(){
    w2_send_start_condition();
    w2_send_byte(10001011);
    uint16_t bright= w2_get_rxed_byte();
    bright<< = 8;
    bright=w2_get_rxed_byte();
    w2_send_stop_condition();
    return bright;
}