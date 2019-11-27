MPU9250 mpu;

void getMPUData()
{
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        mpu.update();
        Serial.print("Roll: ");
        Serial.println(mpu.getRoll());

        Serial.print("Pitch: ");
        Serial.println(mpu.getPitch());

        Serial.print("Yaw: ");
        Serial.println(mpu.getYaw());
        prev_ms = millis();
    }
}
