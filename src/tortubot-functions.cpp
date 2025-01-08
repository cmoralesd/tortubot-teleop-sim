#include <Arduino.h>
#include "tortubot-setup.h"
#include "tortubot-functions.h"

/*
* beep(n): emite un pitido breve, n veces
*/
void beep(int n){
  for(int i=0; i<=n; i++){
    tone(BUZZER, 1000);
    delay(50);
    noTone(BUZZER);
    delay(200);
  }

}


/*
* Función para leer los sensores de línea
*/
bool* read_line_sensors(void){
    static bool sensor_values[3];
    sensor_values[0] = digitalRead(SENSOR_L);
    sensor_values[1] = digitalRead(SENSOR_C);
    sensor_values[2] = digitalRead(SENSOR_R);
    return sensor_values;
}

// función para controlar la velocidad deseada
float* my_controller(bool* sensors){
    // lee los valores de los sensores
    bool sensor_L_value = !sensors[0];
    bool sensor_C_value = !sensors[1];
    bool sensor_R_value = !sensors[2];

    // inicializa las velocidades del robot
    static float robot_velocity[2];

    // Funcionalidad básica: El robot se avanza hasta detenerse al fin del camino.
    // Si los tres sensores detectan, el robot se mueve en dirección hacia adelante.
    // Si el sensor central deja de detectar, el robot se detiene.
    // Si un sensor lateral deja de detectar, el robot retrocede girando en la misma dirección.
    
    float linear_vel, angular_vel;
    if (sensor_C_value){
      if (sensor_L_value && sensor_R_value){
        // Los tres sensores detectan: el robot se mueve en dirección hacia adelante.
        linear_vel = 0.1; // 0.1 m/s
        angular_vel = 0;
      }
      if (!sensor_L_value){
        // Sensor izquierdo no detecta: retrocede girando.
        linear_vel = -0.1;
        angular_vel = -1.57; // 90 grados por segundo
      }
      if (!sensor_R_value){
        // Sensor derecho no detecta: retrocede girando.
        linear_vel = -0.1;
        angular_vel = 1.57;
      }
    }else{
      // El sensor central no detecta: el robot se detiene.
      linear_vel = 0;
      angular_vel = 0;
    }
    
    // determina las velocidades a partir de los datos de los sensores
    robot_velocity[0] = linear_vel; // determina velocidad lineal 
    robot_velocity[1] = angular_vel; // determina velocidad angular

    return robot_velocity;

}


/*
* Función para activar los motores a partir del cálculo de cinemática inversa.
*/
int* set_motor_target_velocities(float linear_vel, float angular_vel){
    // calcula la cinemática inversa
    static float R = 0.021;  // radio de la rueda
    static float L = 0.082;  // distancia entre ruedas
    float right_velocity = (2 * linear_vel - angular_vel * L) / (2 * R);
    float left_velocity = (2 / R) * linear_vel - right_velocity;

    //Serial.printf("right_velocity: %f, left_velocity: %f /n /r", right_velocity, left_velocity);
    
    // Factor de escala (se ajusta según la necesidad)
    float scale = 4.0; 

    // Obtiene los valores de velocidad PWM a partir de la velocidad de las ruedas.
    // pwm_vel[0] <- rueda izquierda
    // pwm_vel[1] <- rueda derecha
    static int pwm_vel[2];
    pwm_vel[0] = map(int(left_velocity * scale), -100, 100, -255, 255); 
    pwm_vel[1] = map(int(right_velocity * scale), -100, 100, -255, 255); 

    // Envía las órdenes de velocidad a los motores, dependiendo del sentido de giro.
    // Para el motor izquierdo:
    if (pwm_vel[0] >=0){
      analogWrite(MOTOR1_FW, pwm_vel[0]);
      analogWrite(MOTOR1_BW, 0);
    }else{
      analogWrite(MOTOR1_FW, 0);
      analogWrite(MOTOR1_BW, -pwm_vel[0]);
    }

    // Para el motor derecho:
    if (pwm_vel[1] >=0){
      analogWrite(MOTOR2_FW, pwm_vel[1]);
      analogWrite(MOTOR2_BW, 0);
    }else{
      analogWrite(MOTOR2_FW, 0);
      analogWrite(MOTOR2_BW, -pwm_vel[1]);
    }

    // retorna el valor de velocidad
    return pwm_vel;

}