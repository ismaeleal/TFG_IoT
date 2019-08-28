
#include "Globales.h"
#include "funciones.h"
#include "envio.h"
#include "loop.h"
#include "pasos.h"
#include "rumia.h"

#include "arduinoFFT.h"

#define SAMPLING_FREQUENCY_TOMA 1000 // Hz
#define SAMPLING_FREQUENCY_ENVIO 15 //frecuencia de envio de datos en minutos
#define SAMPLING_FREQUENCY 128
#define timeEscena 10 //en segundos // cada 10 segundo se analiza una escena

// Variables para el control del tiempo
double lectura_u = 0;
double envio_u = 0;
double lectura_time = 0;
double envio_time = 0;

const uint16_t SAMPLES = 64; // frecuencia de rastreo y media en HZ
int contador_toma = 0; // contador para control de la cantidad de toma de muestra
double contador = 0; // cuantas veces de a tomado el samples para saber cuando llea a 
double valor_escena = ((SAMPLING_FREQUENCY_TOMA / SAMPLES) * timeEscena); // calculo para el tiempo de excena


int dormir = 0;
int repetir = 0; // mide la posibilidad de repetir dormir
int ultima = 0;// ultimo datos de antes de dormir

// FFT ( rumia analisis)
arduinoFFT FFT = arduinoFFT();

double rumia_int[SAMPLES];
double vImag[SAMPLES];
int vector_runia[4] = { 0,0,0,0 };
int Tamano_dato = 3;
const int dato = 100;
int vector_dato_rumia[dato][3];// vector para el analisis de la rumia rellenar con el sonido de romia

// rumia 
int analisis = 50;// positivos
bool analisis_rumia[50];
int contador_rumia_suma = 0;
float porcentaje = 0.80;// porcentaje para das positivo a rumia

// pasos

// variables  de tiempo
float offax, offay, offaz;
float axMEDIA, ayMEDIA, azMEDIA;

const int MPU_addr = 0x68; // I2C address of the MPU-6050

long tiempo_prev;
float dt;

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

int rumia_final = 0;
int caminar_final = 0;
int correr_final = 0;
int reposo_final = 0;
int comiendo_final = 0;


double lectura_c = 0;
double envio_c = 0;


int rumia = 0;
int caminar = 0;
int correr = 0;
int reposo = 0;
int comiendo = 0;


float axMAX, ayMAX, azMAX;
float axMIN, ayMIN, azMIN;
float axMIN_p, ayMIN_p, azMIN_p;
float axMAX_p, ayMAX_p, azMAX_p;

// calculo de media
int calculoMedia = 0;


//tiempo despues de 10 s//salida
int vector_u_escenas[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector para las ultimas 12 escenas

// Datos de envio 
byte Datos[51];
int identificacion;


// datos para el carculo de los pasos 
float minimo_caminar = 0;
float maximo_caminar = 0;
float minimo_correr = 0;
float maximo_correr = 0;
float  time_caminarx = 0;
float  time_caminar_finalx = 0;
float  time_caminary = 0;
float time_caminar_finaly = 0;
float  time_caminarz = 0;
float  time_caminar_finalz = 0;
int fin_caminarx = 0;
int fin_caminary = 0;
int fin_caminarz = 0;
float nuevo_caminarx = 0;
float nuevo_caminary = 0;
float nuevo_caminarz = 0;
float viejo_caminarx = 0;
float viejo_caminary = 0;
float viejo_caminarz = 0;
int pre_decre_caminarx = 0;
int pre_decre_caminary = 0;
int pre_decre_caminarz = 0;
int pre_incre_caminarx = 0;
int pre_incre_caminary = 0;
int pre_incre_caminarz = 0;
float superior_caminarx = 0;
float superior_caminary = 0;
float superior_caminarz = 0;
float diferencia_caminarx = 1;
float diferencia_caminary = 1;
float diferencia_caminarz = 1;
int pre_a_caminarx = 0;
int pre_a_caminary = 0;
int pre_a_caminarz = 0;
int contador_caminarx = 0;
int contador_caminary = 0;
int contador_caminarz = 0;
int time_valido_x = 27000000;
int time_valido_y = 27000000;
int time_valido_z = 27000000;
