/* STM32 I2C State struct requirements */
typedef struct STM32F4XXI2CState
{
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion iomem;
    I2CBus *bus;
    qemu_irq irq_event;
    qemu_irq irq_error;
    
    char *bus_name;

    /* for internall logic */
    stm32f4xx_i2c_config_t config;
    stm32f4xx_i2c_fsm_t *fsm;

   /* Registers*/ 
    uint32_t i2c_cr1;
    :
    :
    :
    uint32_t i2c_fltr;
}STM32F4XXI2CState;
