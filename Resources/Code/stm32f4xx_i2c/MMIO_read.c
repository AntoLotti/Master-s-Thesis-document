static uint64_t stm32f4xx_i2c_read(void *opaque, hwaddr addr, unsigned size)
{
    STM32F4XXI2CState *s = opaque;
    uint64_t result = 0x00UL;
    
    s->config.ops = ops_r;
    s->config.addr = addr;

    if ( s->config.flg_addr && addr != STM32F4_I2C_SR2_ADDR)
        s->config.flg_addr = false;

    if ( s->config.flg_sb )
        s->config.flg_sb = false;

    switch (addr) 
    {
        case STM32F4_I2C_CR1_ADDR:   result = s->i2c_cr1;        break;
        case STM32F4_I2C_CR2_ADDR:   result = s->i2c_cr2;        break;
        case STM32F4_I2C_OAR1_ADDR:  result = s->i2c_oar1;       break;
        case STM32F4_I2C_OAR2_ADDR:  result = s->i2c_oar2;       break;
        case STM32F4_I2C_DR_ADDR:    result = stm32f4xx_i2c_read_dr(s);  break;
        case STM32F4_I2C_SR1_ADDR:   result = stm32f4xx_i2c_read_sr1(s); break;
        case STM32F4_I2C_SR2_ADDR:   result = stm32f4xx_i2c_read_sr2(s); break;
        case STM32F4_I2C_CCR_ADDR:   result = s->i2c_ccr;        break;
        case STM32F4_I2C_TRISE_ADDR: result = s->i2c_trise;      break;
        case STM32F4_I2C_FLTR_ADDR:  result = s->i2c_fltr;       break;

        default:
            qemu_log_mask(LOG_GUEST_ERROR, "STM32 I2C: Bad read offset 0x%lx\n", addr);
    }

    STM32_DEBUG("Value readed: 0x%02x", (uint32_t)result);

    s->config.ops = ops_na;
    s->config.addr = 0xFF;

    return result;
}