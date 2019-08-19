#include<Arduino.h>
#include <LowPower.h>
#include "Globales.h"
#include "funciones.h"
#include "envio.h"
#include "loop.h"
#include "pasos.h"
#include "rumia.h"

#define SAMPLING_FREQUENCY_TOMA 1000 // Hz
#define SAMPLING_FREQUENCY_ENVIO 15 //minutos

//----------------------------------- //
//------------------------------------//
//|     FUNCIONES DE CONTROL          //
//|----------------------------------- //
//    funcion para el control          //
//|----------------------------------- //


//------------------------------------//
//  FUNCION modificacion de variables //
//----------------------------------- //

double lectura_c = 0 ;
double envio_c = 0;
void setup_modificaciones() {
  lectura_c = round(1000000 * (1 / SAMPLING_FREQUENCY_TOMA));
  envio_c =  round(1000000 * (60 * SAMPLING_FREQUENCY_ENVIO));
}
void modificacionVariableTiempo() {
	lectura_u = lectura_c - ( micros() - lectura_time);
 envio_u = envio_c - ( micros() - envio_time);
}

//------------------------------------//
//  FUNCION DE LECTURA DE MOVIMIENTOS //
//----------------------------------- //
int contador_rumia = 0;

int rumia_int[SAMPLES] ;
int vImag[SAMPLES] ;



void lectura_sensores() {
  int* datos ;
  datos  = lectura_movimiento();// lectura de los movimientos
  
  offax = offax + datos[0];
  offay = offay + datos[1];
  offaz = offaz + datos[2];

  //rumia_int[contador_rumia] = valor_micro;// vector de rumia
  
  vImag[contador_rumia] = 0; // vector de rumia
}
//------------------------------------//
//  FUNCION DE calculo de escena      //
//----------------------------------- //
//tiempo antes de 10 s entrada
int rumia = 0;
int caminar = 0;
int correr = 0;
int reposo = 0;
int comiendo = 0;

void calcula_escena() {
  offax = offax / SAMPLES;
  offay = offay / SAMPLES;
  offaz = offaz / SAMPLES;
  calcula_valores_medios();

  if (rumia_f()) {
    rumia++;
  }

  if (caminar_f()) {
    caminar++ ;
  }

  if (correr_f()) {
    correr++;
  }

  if (reposo_f()) {
    reposo++;
  }
}

float axMAX , ayMAX, azMAX, gxMAX, gyMAX;
float axMIN, ayMIN , azMIN , gxMIN , gyMIN;
float axMIN_p, ayMIN_p , azMIN_p , gxMIN_p , gyMIN_p;
float axMAX_p , ayMAX_p, azMAX_p, gxMAX_p, gyMAX_p;

int calculoMedia = 0;

void calcula_valores_medios() {

  if (calculoMedia < 25 ) {
    calculoMedia ++ ;
    //maximos
    if (axMAX_p < offax) {
      axMAX_p = offax;
    }
    if (ayMAX_p < offay) {
      ayMAX_p = offay;
    }
    if (azMAX_p < offaz) {
      azMAX_p = offaz;
    }

    //minimos
    if (axMIN_p > offax) {
      axMIN_p = offax;
    }
    if (ayMIN_p > offay) {
      ayMIN_p = offay;
    }
    if (azMIN_p > offaz) {
      azMIN_p = offaz;
    }
   
  }
  else {

    axMAX = axMAX_p;
    ayMAX = ayMAX_p;
    azMAX = azMAX_p;
   
    axMAX_p = offax;
    ayMAX_p = offay;
    azMAX_p = offaz;
   
    axMIN = axMIN_p;
    ayMIN = ayMIN_p;
    azMIN = azMIN_p;
  
    axMIN_p = offax;
    ayMIN_p = offay;
    azMIN_p = offaz;
   
    axMEDIA = (axMAX + axMIN) / 2;
    ayMEDIA = (ayMAX + ayMIN) / 2;
    azMEDIA = (azMAX + azMIN) / 2;
     
    calculoMedia = 0;
  }
}
//-----------------------------------//
//FUNCIONES de manipulacion  de datos//
//-----------------------------------//


//tiempo despues de 10 s//salida
int vector_u_escenas[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector para las ultimas 12 escenas

void manipulacion_datos() {
  int estado_actual = rumia;
  int estado = 1;

  if (estado_actual < caminar) {
    estado_actual = caminar;
    estado = 2;
  }
  if (estado_actual < correr) {
    estado_actual = correr;
    estado = 3;
  }
  if (estado_actual < reposo) {
    estado_actual = reposo;
    estado = 4;
  }

  for (int i = 1; i < 12; i++) {
	  vector_u_escenas[i] = vector_u_escenas[i - 1];
  }
  vector_u_escenas[0] = estado;

  if ( vector_u_escenas[0] = 1) {
    rumia_final++;
  } else if ( vector_u_escenas[0] = 2) {
    caminar_final++;
  } else if ( vector_u_escenas[0] = 3) {
    correr_final++;
  } else {
    reposo_final++;
  }
  rumia = 0;
  correr = 0;
  caminar = 0;
  reposo = 0;

}
//------------------------------------------------------------------//
//   Toma de GPS                                                    //
//------------------------------------------------------------------//
void tomaGPS_f() {

  tomaGPS();

}
//----------------------------------------------------------------------------------//
//                      PREPARACION DE ENVIO                                        //
//----------------------------------------------------------------------------------//
byte Datos[51];
int identificacion;

void preparacion_datos() {
  // identificacion 2
  Datos[0] = highByte(identificacion);
  Datos[1] = lowByte(identificacion);
  // escenas 10



  Datos[2] = highByte( rumia_final);
  Datos[3] = lowByte( rumia_final);
  Datos[4] = highByte(correr_final);
  Datos[5] = lowByte(correr_final);
  Datos[6] = highByte( caminar_final);
  Datos[7] = lowByte( caminar_final);
  Datos[8] = highByte(reposo_final);
  Datos[9] = lowByte(reposo_final);
  Datos[10] = highByte(comiendo_final);
  Datos[11] = lowByte(comiendo_final);
  // gps 8
  Datos[12] =0;
  Datos[13] =0;
  Datos[14] =0;
  Datos[15] =0;
  Datos[16] =0;
  Datos[17] =0;
  Datos[18] =0;
  Datos[19] =0;
  // bateria
  Datos[20] =0;
  // otros

  Datos[21] =0;
  Datos[22] =0;
  Datos[23] =0;
  Datos[24] =0;
  Datos[25] =0;

  rumia_final = 0;
  caminar_final = 0;
  correr_final = 0;
  reposo_final = 0;
  comiendo_final = 0;
}
//-------------------------------------------//
//    Envio de datos        //
//-------------------------------------------//


void envio_datos() {
  envio();
}

//-------------------------------------------//
//     Calculo del tiempo para Dormir        //
//-------------------------------------------//
//variables compartidas
int repetir = 0; // mide la posibilidad de repetir dormir
 
int ultima = 0;
//funcion
void calculatiempoDormir() {

  int suma_escenas = 0;// para la comprobacion de escenas
  for (int i = 0; i < 11; i++) {
	  vector_u_escenas[i] = vector_u_escenas[i + 1];
  
  }
  if (repetir == 0) {
    for (int i = 0; i < 12; i++) {
		suma_escenas = suma_escenas + vector_u_escenas[i];
    }
    if (suma_escenas == vector_u_escenas[0] * 12 ) {
      ultima = vector_u_escenas[11];
      dormir = 10;
      repetir = 1;
    }
  }
  else {
    if ( vector_u_escenas[11] == ultima ) {
      repetir ++;
      dormir = 10 * repetir;
    }
    else {
      repetir = 0;
	  dormir = 0;
    }
  }
}

void Dormir(int sec) {

  while (sec >= 8) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    sec -= 8;
  }
  if (sec >= 4) {
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
    sec -= 4;
  }
  if (sec >= 2) {
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
    sec -= 2;
  }
  if (sec >= 1) {
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
    sec -= 1;
  }
}
