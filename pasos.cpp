#include<Arduino.h>
#include<Wire.h>

const int MPU_addr = 0x68; // I2C address of the MPU-6050

long tiempo_prev;
float dt;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;

//valor para calculo de paso

float nuevo_pasos;
float viejo_pasos;
int pre_incre;
int pre_decre;
int pre_decre_a;
int pre_incre_a;
int fin_pasos;
int constador_pasos;
double time1_pasos;
double time_final_pasos;
double time2_pasos;

//------------------------------------------------------------------//
//Toma de datos
//------------------------------------------------------------------//

void setup_movimiento() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
//  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);

}

int* lectura_movimiento() {

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers

  int datos[7] = {0, 0, 0};
  datos[0] = Wire.read() << 8 | Wire.read();
  datos[1] = Wire.read() << 8 | Wire.read();
  datos[2] = Wire.read() << 8 | Wire.read();

  return datos;
}


//lectura de datos


int analisis_alta(float valor, float nuevo, float viejo, float media, float superior, float diferencia, int pre_decre, int pre_incre, int pre_a, int contador, int fin , double time1, double time_final,double time_valido) {
  float Umbral = (superior - media ) + superior;

  if (valor > media and valor < Umbral and (superior - media) > diferencia and (superior - media) < (diferencia * 20) ) {
    viejo = nuevo;
    nuevo = valor;

    contador++;

    if (contador > 1) {
      fin = 0;
      if (nuevo > viejo) {
        pre_incre++;
        if (pre_a = 1) {
          pre_decre = 0;
        } else {
          if (pre_incre > 10) {
            fin = 2;
            time_final = micros();
            contador = 0;
          }
        }
      }
      if (nuevo < viejo) {
        pre_decre++;
        if (pre_a = 0) {
          pre_incre = 0;
        }
        else {
          if (pre_decre > 3) {
            pre_a = 0;
          }
        }
      }
    } else {
      time1 = micros();
      fin = -1;
    }
  } else if (fin == -1) {
    fin = 2;
    time_final = micros();
    contador = 0;

    
  }
  else if (fin == 1) {
    fin = 0;

  }
  if (fin == 2 and time_valido >  (time_final - time1) and (time_valido*130) <  (time_final - time1)  ){
    fin =1;
    }
    return fin;
}
