/*
 * @file ApollonReanimator.c
 * @brief TODO
 * @author Sami KOUATLI
 * @date 17/11/17.
 * @version 1.0
 */

#include "ApollonReanimator.h"

#define RF_CONFIG_PWR_DOWN	0x00
// (15min/2sec)=900, refers to the number of times we have to free and refill the timer register before waking up.
#define COUNT15MIN = 900

/**
 * See ApollonReanimator.h
 */
extern void reanimatorInit()
{
    config = RF_CONFIG_PWR_UP;
    rf_write_register(RF_CONFIG,&config,1);
    rf_clear_ce();
    flush_fifo_irq();
}

/**
 * See ApollonReanimator.h
 */
extern void reanimatorDestroy()
{
    rf_clear_ce();
    flush_fifo_irq();
    config = RF_CONFIG_PWR_DOWN;
    rf_write_register(RF_CONFIG,&config,1);
}

/**
 * See ApollonReanimator.h
 */
extern void putActiveMode()
{
    config = RF_CONFIG_PWR_UP;
    rf_write_register(RF_CONFIG,&config,1);
    flush_fifo_irq();
    rf_set_ce();
}

/**
 * See ApollonReanimator.h
 */
extern void putSleepMode()
{
    flush_fifo_irq();
    config = RF_CONFIG_PWR_DOWN;
    rf_write_register(RF_CONFIG,&config,1);
    rf_clear_ce();
    rf_write_register(RF_CONFIG,&config,1);
    rtc2_configure(RTC2_CONFIG_OPTION_ENABLE | RTC2_CONFIG_OPTION_COMPARE_MODE_0_RESET_AT_IRQ);
    pwr_clk_mgmt_clklf_configure(PWR_CLK_MGMT_CLKLF_CONFIG_OPTION_CLK_SRC_RCOSC32K);
    pwr_clk_mgmt_wakeup_sources_configure(PWR_CLK_MGMT_WAKEUP_CONFIG_OPTION_WAKEUP_ON_RTC2_TICK_IF_INT_ENABLED);

    int count = 0;

    while(count < COUNT15MIN){
        rtc2_configure(RTC2_CONFIG_OPTION_ENABLE | RTC2_CONFIG_OPTION_COMPARE_MODE_0_RESET_AT_IRQ);
        rtc2_set_compare_val(uint16_t compare_value);
        interrupt_isr_rtc2();
        pwr_clk_mgmt_enter_pwr_mode_memory_ret_tmr_on();
        count++;
    }
}