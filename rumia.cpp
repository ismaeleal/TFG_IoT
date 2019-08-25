
#include<Arduino.h>
#include "declaraciones.h"


bool rumia_analisis() {
  int i = 0;
  int j = 0;
  FFT.Windowing(rumia_int, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute( rumia_int, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude( rumia_int, vImag, SAMPLES);
  double peak = FFT.MajorPeak( rumia_int, SAMPLES, SAMPLING_FREQUENCY);
  for (int i = 1; i < Tamano_dato; i++) {
	  vector_runia[i] = vector_runia[i - 1];
  }
vector_runia[0] = peak;

  for (int i = 1; i <  Tamano_dato - 1; i++) {
    for (int j = 0; j < dato ; j++) {
       if ((vector_dato_rumia[j][0] == vector_runia[Tamano_dato ]) and (vector_dato_rumia[j][1] == vector_runia[i]) and (vector_dato_rumia[j][2] == (Tamano_dato - i))){
        return 1;
      } else {
        return 0;
      }
    }

  }
}
