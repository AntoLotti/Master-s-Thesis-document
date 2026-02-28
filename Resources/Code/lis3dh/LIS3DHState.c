typedef struct LIS3DHState 
{
    /* Parent object */
    I2CSlave i2c;

    lis3dh_config_t *config;    /**< Operating mode, scale, ODR */
    lis3dh_params_t *params;    /**< Sensitivity, range, shifts */
    lis3dh_i2c_params_t i2c;    /**< Address pointer, auto-inc  */
    
    /* GPIO outputs */
    qemu_irq int1;               /**< INT1 output line */
    qemu_irq int2;               /**< INT2 output line */

    /* Registers */
    uint8_t status_reg_aux; // Status Register
    uint8_t adc_1_l;    // 1-Axis Acceleration Data Low Register
    uint8_t adc_1_h;    // 1-Axis Acceleration Data High Register
    uint8_t adc_2_l;    // 2-Axis Acceleration Data Low Register
    uint8_t adc_2_h;    // 2-Axis Acceleration Data High Register
    uint8_t adc_3_l;    // 3-Axis Acceleration Data Low Register
    uint8_t adc_3_h;    // 3-Axis Acceleration Data High Register
    :
    :
    :
    :
    uint8_t act_ths;
    uint8_t act_dur;    
    
} LIS3DHState;