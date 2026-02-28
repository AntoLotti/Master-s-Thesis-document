static void stm32f4xx_i2c_write(void *opaque, hwaddr addr, uint64_t value, unsigned size) {
    STM32F4XXI2CState *s = opaque;
    
    s->config.ops = ops_w;      // Record operation type
    s->config.addr = addr;      // Record register offset
    
    switch (addr) {
        case STM32F4_I2C_CR1_ADDR:  stm32f4xx_i2c_write_cr1(s, value); break;
        case STM32F4_I2C_CR2_ADDR:  stm32f4xx_i2c_write_cr2(s, value); break;
        case STM32F4_I2C_DR_ADDR:   stm32f4xx_i2c_write_dr(s, value); break;
        // Other registers updated directly
    }
}