#include "Demodulator.h"
#include <cmath>
#include <iostream>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
Demodulator::Demodulator(int sampleRate, int symbolDuration, double frequency) {
	this->sampleRate = sampleRate;
	this->symbolDuration = symbolDuration;
	this->frequency = frequency;
	this->X = 0.0;
	this->Y = 0.0;
	this->whichQuarter = 0;
}

void Demodulator::getXYCoordinates(std::vector<double> signal) {
	this->X = 0;
	this->Y = 0;
	for (int i = 0; i < signal.size(); i++)
	{
		double t = (double)i / this->sampleRate;

		this->X += signal[i] * std::cos(2 * M_PI * frequency * t);
		this->Y += signal[i] * std::sin(2 * M_PI * frequency * t);
	}
}

void Demodulator::defineQuarter() {
	if (this->X >= 0 && this->Y >= 0) this->whichQuarter = 0; //00
	if (this->X >= 0 && this->Y < 0) this->whichQuarter = 1; //01
	if (this->X < 0 && this->Y < 0) this->whichQuarter = 2; //10
	if (this->X < 0 && this->Y >= 0) this->whichQuarter = 3; //11
}
void Demodulator::translateQuarterToSymbol() {
		this->currentSymbol = std::bitset<2>(this->whichQuarter);
}
int Demodulator::findBegginingOfSignal(const std::vector<double> &signal) {
	int N = this->symbolDuration;
	if (signal.size() < 3 * N) return -1;
	std::bitset<2> wzorzec = 2;

	for (int i = 0; i <= (int)signal.size()-(3*N); i++)
	{
		bool match = true;
		for (int k = 0; k < 3; k++)
		{
			std::vector<double> fragment;
			int offset = i + (k * N);
			for (int j = 0; j < N; j++)
			{
				fragment.push_back(signal[offset + j]);
			}
			getXYCoordinates(fragment);
			defineQuarter();
			translateQuarterToSymbol();
			if (this->currentSymbol != wzorzec)
			{
				match = false;
				break;
			}
		}	
		if (match) return i;
	}
	return -1;
}


std::vector<std::bitset<2>> Demodulator::demodulate(std::vector<double> signal) {
	std::vector<std::bitset<2>> wynik;

	int start = findBegginingOfSignal(signal);
	if (start == -1) return wynik;

	for (int i = start; i +this->symbolDuration <= signal.size(); i+=this->symbolDuration)
	{
		std::vector<double> fragment;
		fragment.reserve(this->symbolDuration);
		for (int j = 0; j < this->symbolDuration; j++)
		{
			fragment.push_back(signal[i + j]);
		}
		getXYCoordinates(fragment);
		defineQuarter();
		translateQuarterToSymbol();
		wynik.push_back(this->currentSymbol);

		
		start += this->symbolDuration;
	}
	return wynik;
}