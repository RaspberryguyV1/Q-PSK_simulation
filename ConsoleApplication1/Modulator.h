#pragma once
#include <vector>
#include <bitset>
#include <cmath>

class Modulator
{
private:
	int sampleRate;
	int symbolDuration;
	double frequency;
	

public:
	double getPhaseShift(std::bitset<2> bits);
	Modulator(int fs = 44100, int duration = 10, double freq = 1000.0);
	std::vector<double> modulate(const std::vector<std::bitset<2>>& inputBits);
};