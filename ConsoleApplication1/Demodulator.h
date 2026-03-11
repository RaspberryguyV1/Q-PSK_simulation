#pragma once
#include <vector>
#include <bitset>
#include <cmath>
class Demodulator
{
public:
	Demodulator(int sampleRate, int symbolDuration, double frequency);
	std::vector<std::bitset<2>> demodulate(std::vector<double> signal);

private:
	std::bitset<2> currentSymbol;
	int whichQuarter;
	int sampleRate;
	int symbolDuration;
	double frequency;
	double X, Y;
	void getXYCoordinates(std::vector<double> signal);
	void defineQuarter();
	void translateQuarterToSymbol();
	int findBegginingOfSignal(const std::vector<double> &signal);
	
};


