static uint8_t lis3dh_i2c_recv(I2CSlave *i2c)
{
    LIS3DHState *lis3dh = LIS3DH(i2c);

    uint8_t value = lis3dh_read_register( lis3dh );

    if (lis3dh->i2c_params.auto_increment)
    {
        lis3dh->i2c_params.ptr++;
    }

	return value;
}