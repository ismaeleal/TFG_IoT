

#include "declaraciones.h"



void setup() {
	setup_modificaciones();// configuracion  de variable 
	setup_movimiento();// inicializacion  de sensores de movimiento
}

void loop() {
	modificacionVariableTiempo();
	if (lectura_u <= 0) {
		lectura_sensores();
		contador_toma++;
		lectura_time = micros();
		if (contador_toma == SAMPLES) {
			contador_toma = 0;
			contador++;
			calcula_escena();
			if (contador > valor_escena ) {
				manipulacion_datos(); 
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