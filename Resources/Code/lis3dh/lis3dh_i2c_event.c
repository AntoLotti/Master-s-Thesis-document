static int lis3dh_i2c_event(I2CSlave *i2c, enum i2c_event event)
{
    LIS3DHState *lis3dh = LIS3DH(i2c);
    
    switch (event) 
    {
        case I2C_START_SEND:    // Start of write operation
            /* Master is starting a WRITE operation 
            (sending data to the device) */
            lis3dh->i2c_params.ptr             = 0xFF;
			lis3dh->i2c_params.auto_increment  = false;
			lis3dh->i2c_params.address_phase   = true;
            break;
            
        case I2C_START_RECV:    // Start of read operation
            /* Master is starting a READ operation 
            (requesting data from the device) */
			if (lis3dh->i2c_params.ptr == 0xFF)
				lis3dh->i2c_params.ptr = LIS3DH_ADDR_WHO_AM_I;

			lis3dh->i2c_params.address_phase = false;
            break;
            
        case I2C_FINISH:        // Stop condition
            /* Master ends the transaction 
            (STOP condition) */
            break;
            
        case I2C_NACK:          // NACK received
            /* Master didn't acknowledge the data */
            break;
        
        default:               // Should never happen
            return -1;
    }

    return 0;
}