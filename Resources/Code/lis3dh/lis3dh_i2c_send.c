static int lis3dh_i2c_send(I2CSlave *i2c, uint8_t data)
{
    LIS3DHState *lis3dh = LIS3DH(i2c);

	if (lis3dh->i2c_params.ptr == 0xFF && lis3dh->i2c_params.address_phase)
	{
		lis3dh->i2c_params.ptr = data & LIS3DH_SUB_REG_MASK;
		lis3dh->i2c_params.auto_increment =  (data & LIS3DH_SUB_AUTO_INC_MASK) != 0x00 ? true : false;
		lis3dh->i2c_params.address_phase = false;
	}else
	{
		lis3dh_write_register( lis3dh, lis3dh->i2c_params.ptr, data);
		if (lis3dh->i2c_params.auto_increment)
			lis3dh->i2c_params.ptr++;
	}
	return 0;
}