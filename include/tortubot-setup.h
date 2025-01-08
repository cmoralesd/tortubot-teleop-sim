#pragma once

// Conexiones físicas de los dispositivos
#define SENSOR_L 18
#define SENSOR_C 19
#define SENSOR_R 23

#define MOTOR1_FW 32
#define MOTOR1_BW 27
#define MOTOR2_FW 25
#define MOTOR2_BW 26

#define BUZZER 2

// declaración de funciones
void tortubot_io_setup(void);
void tortubot_monitor_setup(int baudrate);
void tortubot_wifi_setup(String ssid, String password);