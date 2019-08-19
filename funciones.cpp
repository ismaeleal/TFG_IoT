#include<Arduino.h>
#include "rumia.h"
#include "Globales.h"
#include "pasos.h"
//------------------------------------------------------------------//
//   rumia                                                          //
//------------------------------------------------------------------//

int analisis = 50;
float porcentaje = 0.80;
bool analisis_rumia[50];


bool rumia_f() {

	int contador_rumia_suma = 0;
	for (int i = 1; i < analisis; i++) {
		analisis_rumia[i] = analisis_rumia[i - 1];
	}
	analisis_rumia[0] = rumia_analisis();

	for (int i = 0; i < analisis; i++) {
		contador_rumia_suma = contador_rumia_suma + analisis_rumia[i];
	}


	if (contador_rumia_suma > (analisis * porcentaje)) {
		return 1;
	}
	else {
		return 0;
	}
}

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

bool  caminar_f() {
	analisis_alta(offax, nuevo_caminarx, viejo_caminarx, axMEDIA, superior_caminarx, diferencia_caminarx, pre_decre_caminarx, pre_incre_caminarx, pre_a_caminarx, contador_caminarx, fin_caminarx, time_caminarx, time_caminar_finalx, time_valido_x);
	analisis_alta(offay, nuevo_caminary, viejo_caminary, ayMEDIA, superior_caminary, diferencia_caminary, pre_decre_caminary, pre_incre_caminary, pre_a_caminary, contador_caminary, fin_caminary, time_caminary, time_caminar_finaly, time_valido_y);
	analisis_alta(offaz, nuevo_caminarz, viejo_caminarz, azMEDIA, superior_caminarz, diferencia_caminarz, pre_decre_caminarz, pre_incre_caminarz, pre_a_caminarz, contador_caminarz, fin_caminarz, time_caminarz, time_caminar_finalz, time_valido_x);

	if (fin_caminarx or fin_caminary or fin_caminarz) {
		time_caminarx = time_caminarx - time_caminar_finalx;
		time_caminary = time_caminary - time_caminar_finaly;
		time_caminarz = time_caminarz - time_caminar_finalz;

		if ((time_caminarx > minimo_caminar and time_caminarx < maximo_caminar) or (time_caminary > minimo_caminar and time_caminary < maximo_caminar) or (time_caminarz > minimo_caminar and time_caminarz < maximo_caminar)) {
			return 1;

		}
		else {
			return 0;
		}
	}else {
		return 0;

	

	}
}
bool correr_f() {
	if (fin_caminarx or fin_caminary or fin_caminarz) {
		if ((time_caminarx > minimo_correr and time_caminarx < maximo_correr) or (time_caminary > minimo_correr and time_caminary < maximo_correr) or (time_caminarz > minimo_correr and time_caminarz < maximo_correr)) {
			return 1;

		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	
}
bool reposo_f() {
	//analisis_alta(ax, float nuevo, float viejo, float media, float superior, float diferencia, int pre_decre, int pre_incre, int pre_a, int contador, int fin, double time1, double time_final, time_valido_x);
	//analisis_alta(ay, float nuevo, float viejo, float media, float superior, float diferencia, int pre_decre, int pre_incre, int pre_a, int contador, int fin, double time1, double time_final, time_valido_y);
	//analisis_alta(az, float nuevo, float viejo, float media, float superior, float diferencia, int pre_decre, int pre_incre, int pre_a, int contador, int fin, double time1, double time_final, time_valido_z);
}
