# attenuation_dev

Development of ns-3 module for mmWave rain attenuation.

Classes:
  1) Control: contains essential information for the Model, like location coordinates, frequency etc.
  2) RainSimulator: class that contains simulated rain rate values and the corresponding rain attenuation for a year.
  
  
Progress: 100% 

Run: g++ -g -std=c++11 -w test_main.cpp RainAttenuation.cpp RainGenerator.cpp control.cpp -o test_main

The code contained here is supplementary to the Master's Thesis "Impact of Rainfall on mmWave Radio Link" by Stavros Sykiotis, TU Berlin.
