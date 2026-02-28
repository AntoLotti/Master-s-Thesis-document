/* stm32f4xx I2C fsm structure */
typedef struct stm32f4xx_i2c_fsm_s
{
	int act_st;	// State where the fsm is 
	stm32f4xx_i2c_fsm_trans_t *trans_table;	// Transition table
}stm32f4xx_i2c_fsm_t;