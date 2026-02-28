static void lis3dh_initfn(Object *obj)
{
    object_property_add(obj, "accel-x", "int",
                        lis3dh_get_accel_x,
                        lis3dh_set_accel_x, NULL, NULL);
    object_property_add(obj, "accel-y", "int",
                        lis3dh_get_accel_y, 
                        lis3dh_set_accel_y, NULL, NULL);
    object_property_add(obj, "accel-z", "int",
                        lis3dh_get_accel_z,
                        lis3dh_set_accel_z, NULL, NULL);
    object_property_add(obj, "temp", "int",
                        lis3dh_get_temp,
                        lis3dh_set_temp, NULL, NULL);
}