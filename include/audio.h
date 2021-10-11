#include <stdio.h>
#include <iostream>
#include <string>
#include <complex>

#include "../include/AudioFile-master/AudioFile.h"

using std::string;
using std::complex;

class Audio
{
private:
	AudioFile<double> audioData; //AudioFile object
	double*** timeMatrixChannel; //Tridimentional array [channel][sample][component]
	double timeInSeconds;
	int numSamples;


public:

	complex<double>** dftMat;
	//Constructor
	Audio(string filename, double givenTime);

	void SetNumSamples(double time);

	void InitializeTimeMatrix();

	//Writes to a file the x and y coordinates
	void PrintPointsToFile(int channel, string outputFile = "points.txt");

	void DFTMatrix();
};


void multCompMat(complex<double>** mat2, int nrows, double* vec);
