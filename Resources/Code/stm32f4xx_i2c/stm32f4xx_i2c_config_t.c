/* stm32f4xx I2C parameters used in the internal logic */
typedef struct stm32f4xx_i2c_config_s
{
    uint8_t addr;
    stm32f4xx_opt_t ops;
    bool flg_sb;
    bool flg_start;
    bool flg_stop;
    bool flg_swrst;
    bool flg_addr;
}stm32f4xx_i2c_config_t;