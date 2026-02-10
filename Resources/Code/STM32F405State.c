typedef struct STM32F405State {
    SysBusDevice parent_obj;

    /* ARM Cortex-M4 CPU */
    ARMv7MState armv7m;

    /* Existing peripherals */
    STM32RccState rcc;
    STM32F4xxSyscfgState syscfg;
    STM32F4xxExtiState exti;
    STM32F2XXUsartState usart[STM_NUM_USARTS];
    STM32F2XXTimerState timer[STM_NUM_TIMERS];
    OrIRQState adc_irqs;
    STM32F2XXADCState adc[STM_NUM_ADCS];
    STM32F2XXSPIState spi[STM_NUM_SPIS];
    STM32GPIOState gpio[STM_NUM_GPIOS];
    
    /* Newly added I2C controllers */
    STM32F4XXI2CState i2c[STM_NUM_I2CS];

    MemoryRegion ccm;
    MemoryRegion sram;
    MemoryRegion flash;
    MemoryRegion flash_alias;

    Clock *sysclk;
    Clock *refclk;
} STM32F405State;