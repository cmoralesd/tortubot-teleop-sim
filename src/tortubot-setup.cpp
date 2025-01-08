#include <Arduino.h>
#include <WiFi.h>
#include "tortubot-setup.h"


// función para configuración de entradas y salidas
void tortubot_io_setup(void) {
  pinMode(SENSOR_L, INPUT);
  pinMode(SENSOR_C, INPUT);
  pinMode(SENSOR_R, INPUT);
  
  pinMode(MOTOR1_FW, OUTPUT);
  pinMode(MOTOR1_BW, OUTPUT);
  pinMode(MOTOR2_FW, OUTPUT);
  pinMode(MOTOR2_BW, OUTPUT);
}

// inicializa la comunicación serial
void tortubot_monitor_setup(int baudrate) {
    Serial.begin(baudrate);
    Serial.printf("Puerto serie inicializado a %d", baudrate);
    Serial.println("");
}
