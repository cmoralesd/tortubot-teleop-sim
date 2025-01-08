#pragma once

/*
beep(n): emite un pitido breve, n veces
*/
void beep(int n);

// función para leer los sensores de línea
bool* read_line_sensors(void);

// función para controlar la velocidad deseada
float*  my_controller(bool* sensors);

// función para mover los motores
int* set_motor_target_velocities(float linear_vel, float angular_vel);