#include <Arduino.h>
#include "tortubot-setup.h"
#include "tortubot-functions.h"

void setup() {
  // inicialización
  tortubot_monitor_setup(115200);
  tortubot_io_setup();
  beep(2);
  Serial.println("Tortubot se ha inicializado correctamente");
}

void loop() {
  // ciclo principal:
  float linear_velocity, angular_velocity;

  // serial_listener
  Serial.print("nueva instrucción: ");
  while(Serial.available() == 0){}
  String input_instruction;
  // Cuidado! el monitor serial de VSCode usa \n como final de línea
  // Tomaremos solo el primer caracter del String
  input_instruction = Serial.readString().charAt(0);
  input_instruction.toLowerCase();
  Serial.println(input_instruction);    
      
  if (input_instruction  == "i") {
    Serial.println(" -> forward");
    linear_velocity = 0.1;
    angular_velocity = 0;

  } else if (input_instruction  == "j") {
    Serial.println(" -> left");
    linear_velocity = 0;
    angular_velocity = 0.5;

  } else if (input_instruction == "l") {
    Serial.println(" -> right");
    linear_velocity = 0;
    angular_velocity = -0.5;

  } else if (input_instruction == "k"){
    Serial.println(" -> backward");
    linear_velocity = -0.1;
    angular_velocity = 0;

  } else {
    Serial.println(" -> null instruction");
    linear_velocity = 0;
    angular_velocity = 0;

  }  

  // fin serial_listener


  // Lee los sensores
  bool* line_sensors = read_line_sensors();

  /***************** TO DO *********************/
  // Procesar datos de los sensores.
  // Modificar las órdenes de velocidad de acuerdo con los datos de los sensores
  // Limpiar y organizar el código.
  /*********************************************/

  // convierte la velocidad del robot en velocidad de los motores
  int* motor_target_vel = set_motor_target_velocities(linear_velocity, angular_velocity);


  // DEBUG: Monitoreamos para verificar el estado del robot
  //Serial.printf("sensors (L C R): %d, %d, %d, linear_vel: %.2f, angular_vel: %.2f, pwm_1: %d, pwm_2: %d \n \r", 
  //  line_sensors[0], line_sensors[1], line_sensors[2], cmd_vel[0], cmd_vel[1], motor_target_vel[0], motor_target_vel[1]);
  
  
}

