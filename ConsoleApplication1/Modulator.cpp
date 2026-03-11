#include "Modulator.h"
#include <cmath> 
#include <iostream> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Modulator::Modulator(int fs, int duration, double freq) {
	sampleRate = fs;
	symbolDuration = duration;
	frequency = freq;
}

double Modulator::getPhaseShift(std::bitset<2> bits) {
	unsigned long val = bits.to_ulong();
	// Zwracamy k¹t w zale¿noœci od bitów
	// 00 -> 0 -> 45 stopni (PI/4)
	// 01 -> 1 -> 135 stopni (3*PI/4)
	// 10 -> 2 -> 225 stopni (5*PI/4)
	// 11 -> 3 -> 315 stopni (7*PI/4)
	if (val == 0) return 0.25 * M_PI; //00
	if (val == 1) return 0.75 * M_PI; //01
	if (val == 2) return 1.25 * M_PI; //10
	if (val == 3) return 1.75 * M_PI; //11
	return 0.0;
	
}

std::vector<double> Modulator::modulate(const std::vector<std::bitset<2>>& inputBits) {
	std::vector<double> signal;
	// Rezerwujemy pamiêæ: iloœæ_symboli * d³ugoœæ_jednego_symbolu
	signal.reserve(inputBits.size() * symbolDuration);

	int totalSamples = 0;

	for (size_t i = 0; i < inputBits.size(); i++)
	{
		double phase = getPhaseShift(inputBits[i]);

		for (int t = 0; t < symbolDuration; t++)
		{
			double timeInSeconds = (double)totalSamples / (double)sampleRate;
			double sample = 1.0 * std::sin(2 * M_PI * frequency * timeInSeconds + phase);
			signal.push_back(sample);
			totalSamples++;
		}
	}
	return signal;
}
