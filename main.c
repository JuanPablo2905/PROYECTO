#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"

#define SENSORABAJO1 12
#define SENSORARRIBA1 20
#define SENSORABAJO2 13
#define SENSORARRIBA2 21
#define MOTOR_PIN_1 0  // Conecta a IN1 del driver ULN2003A
#define MOTOR_PIN_2 1  // Conecta a IN2 del driver ULN2003A
#define MOTOR_PIN_3 4  // Conecta a IN3 del driver ULN2003A
#define MOTOR_PIN_4 5  // Conecta a IN4 del driver ULN2003A
#define MOTOR_PIN_5 6  // Conecta a IN1 del driver ULN2003A
#define MOTOR_PIN_6 7  // Conecta a IN2 del driver ULN2003A
#define MOTOR_PIN_7 8  // Conecta a IN3 del driver ULN2003A
#define MOTOR_PIN_8 9  // Conecta a IN4 del driver ULN2003A
#define LDR_PIN 26
#define LDR_PIN2 27


int umbral_luminosidad1 = 450;
int umbral_luminosidad2 = 450;



void girar_horario() {

  int secuencia_horaria[] = {1, 2, 4, 8};

  for (int i = 0; i < 4; i++) {
    gpio_put(0, (secuencia_horaria[i] & 0x01));
    gpio_put(1, (secuencia_horaria[i] & 0x02));
    gpio_put(4, (secuencia_horaria[i] & 0x04));
    gpio_put(5, (secuencia_horaria[i] & 0x08));

    gpio_put(6, (secuencia_horaria[i] & 0x01));
    gpio_put(7, (secuencia_horaria[i] & 0x02));
    gpio_put(8, (secuencia_horaria[i] & 0x04));
    gpio_put(9, (secuencia_horaria[i] & 0x08));



    sleep_ms(3); // Puedes ajustar la velocidad aquí

  }
}

void girar_antihorario() {

 int secuencia_antihoraria[] = {8, 4, 2, 1};

  for (int i = 0; i < 4; i++) {
    gpio_put(0, (secuencia_antihoraria[i] & 0x01));
    gpio_put(1, (secuencia_antihoraria[i] & 0x02));
   gpio_put(4, (secuencia_antihoraria[i] & 0x04));
    gpio_put(5, (secuencia_antihoraria[i] & 0x08));

    gpio_put(6, (secuencia_antihoraria[i] & 0x01));
    gpio_put(7, (secuencia_antihoraria[i] & 0x02));
   gpio_put(8, (secuencia_antihoraria[i] & 0x04));
    gpio_put(9, (secuencia_antihoraria[i] & 0x08));


    sleep_ms(3); // Puedes ajustar la velocidad aquí

  }
}


void detener_motor1() {
   //Detiene el motor estableciendo todas las señales de control en 0
  gpio_put(0, 0);
  gpio_put(1, 0);
  gpio_put(4, 0);
  gpio_put(5, 0);
}

void detener_motor2() {
  // Detiene el motor estableciendo todas las señales de control en 0
  gpio_put(6, 0);
  gpio_put(7, 0);
  gpio_put(8, 0);
  gpio_put(9, 0);
}



int main() {


  stdio_init_all();
  adc_init();
  adc_gpio_init(26);
  adc_gpio_init(27);



  gpio_init(0);
  gpio_init(1);
  gpio_init(4);
  gpio_init(5);
  gpio_init(6);
  gpio_init(7);
  gpio_init(8);
  gpio_init(9);


  gpio_set_dir(0, GPIO_OUT);
  gpio_set_dir(1, GPIO_OUT);
  gpio_set_dir(4, GPIO_OUT);
  gpio_set_dir(5, GPIO_OUT);
  gpio_set_dir(6, GPIO_OUT);
  gpio_set_dir(7, GPIO_OUT);
  gpio_set_dir(8, GPIO_OUT);
  gpio_set_dir(9, GPIO_OUT);




  gpio_init (12);
  gpio_init (20);
  gpio_init (13); 
  gpio_init (21);


  gpio_set_dir(12, GPIO_IN);
  gpio_set_dir(20, GPIO_IN);
  gpio_set_dir(13, GPIO_IN);
  gpio_set_dir(21, GPIO_IN);




  while (true) {

    adc_select_input(0);
    uint16_t ldr_value1 = adc_read();

    adc_select_input(1);
    uint16_t ldr_value2 = adc_read();




    bool sensabajo1 = (gpio_get(12));
    bool sensarriba1 = (gpio_get(20));
    bool sensabajo2 = (gpio_get(13));
    bool sensarriba2 = (gpio_get(21));

    // comienza el codigo del motor 1

    if (ldr_value1 < umbral_luminosidad1 && sensabajo1 == 1) {

      girar_antihorario(); // baja cortina1
    }
    if (ldr_value1 < umbral_luminosidad1 && sensabajo1 == 0){

      detener_motor1(); // se detiene el motor 1
    }
if(ldr_value1 > umbral_luminosidad1 && sensarriba1 == 0){

      girar_horario(); // sube la cortina 1
    }

// comienza el codigo del motor 2

    if (ldr_value2 < umbral_luminosidad2 && sensabajo2 == 1) {

      girar_antihorario(); // baja cortina2
    }
    if (ldr_value2 < umbral_luminosidad2 && sensabajo2 == 0){

      detener_motor2(); // se detiene el motor 2
    }
if(ldr_value2 > umbral_luminosidad2 && sensarriba2 == 0){

      girar_horario(); // sube la cortina 2
    }


}
}
