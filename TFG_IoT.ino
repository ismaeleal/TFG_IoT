


#include "Globales.h"
#include "funciones.h"
#include "envio.h"
#include "loop.h"
#include "pasos.h"
#include "rumia.h"

#define timeEscena 10 //en segundos // cada 10 segundo se analiza una escena
int contador = 0;
int contador_rumia = 0;
void setup() {
	setup_modificaciones();
	setup_movimiento();
}
void loop() {
	modificacionVariableTiempo();//modificacion de variables de tiempo
	if (lectura_u <= 0) {
		lectura_sensores();// lectura de sensores
		contador_rumia++;
		lectura_time = micros();



		if (contador_rumia == SAMPLES) {
			contador_rumia = 0;
			contador++;
			calcula_escena();
			if (contador > timeEscena * 100) {
				manipulacion_datos(); // manipulacion de datos
				calculatiempoDormir();
				contador = 0;
			}
		}
	}
	if (envio_u <= 0) {
		tomaGPS_f();
		preparacion_datos();
		envio_datos();
		envio_time = micros();
	}
	if (dormir > 0) {
		Dormir();
	}
}