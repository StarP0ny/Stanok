#include <Arduino.h>

const int NUM_READ = 10;  // количество усреднений для средних арифм. фильтров

//фильтр Калмана
float _err_measure = 0.8;  // примерный шум измерений
float _q = 0.1;   // скорость изменения значений 0.001-1, варьировать самому

// бегущее среднее арифметическое
float runMiddleArifm(float newVal) {  // принимает новое значение
  static byte idx = 0;                // индекс
  static float valArray[NUM_READ];    // массив
  valArray[idx] = newVal;             // пишем каждый раз в новую ячейку
  if (++idx >= NUM_READ) idx = 0;     // перезаписывая самое старое значение
  float average = 0;                  // обнуляем среднее
  for (int i = 0; i < NUM_READ; i++) {
    average += valArray[i];           // суммируем
  }
  return (float)average / NUM_READ;   // возвращаем
}
// оптимальное бегущее среднее арифметическое
float runMiddleArifmOptim(float newVal) {
  static int t = 0;
  static float vals[NUM_READ];
  static float average = 0;
  if (++t >= NUM_READ) t = 0; // перемотка t
  average -= vals[t];         // вычитаем старое
  average += newVal;          // прибавляем новое
  vals[t] = newVal;           // запоминаем в массив
  return ((float)average / NUM_READ);
}
//фильтр Калмана
float simpleKalman(float newVal) {
  float _kalman_gain, _current_estimate;
  static float _err_estimate = _err_measure;
  static float _last_estimate;
  _kalman_gain = (float)_err_estimate / (_err_estimate + _err_measure);
  _current_estimate = _last_estimate + (float)_kalman_gain * (newVal - _last_estimate);
  _err_estimate =  (1.0 - _kalman_gain) * _err_estimate + fabs(_last_estimate - _current_estimate) * _q;
  _last_estimate = _current_estimate;
  return _current_estimate;
}