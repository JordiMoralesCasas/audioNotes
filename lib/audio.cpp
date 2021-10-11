#include <iostream>
#include <fstream>
#include <cmath>

#include "../include/audio.h"
#include "../include/AudioFile-master/AudioFile.h"

using std::cout;
using std::endl;
using std::complex;

/**
 * Constructor of the Audio class
 *
 * @param filename name of the audio file. It should be WAV or AIFF format.
 */
Audio::Audio(string filename, double givenTime)
{
	audioData.load(filename);

	SetNumSamples(givenTime);

	InitializeTimeMatrix();
}

void Audio::SetNumSamples(double givenTime)
{
	double originalTime = audioData.getLengthInSeconds();
	int originalSamples = audioData.getNumSamplesPerChannel();

	if (givenTime >= originalTime) {
		timeInSeconds = originalTime;
		numSamples = originalSamples;
	}
	else {
		timeInSeconds = givenTime;
		numSamples = 0;

		while (numSamples*(originalTime / originalSamples) < timeInSeconds)
			numSamples++;

		numSamples--;
	}
}

void Audio::InitializeTimeMatrix()
{
	/// Allocate space
	timeMatrixChannel = new double**[2];
	for (int channel = 0; channel < 2; channel++) {
		timeMatrixChannel[channel] = new double*[numSamples];
		for (int sample = 0; sample < numSamples; sample++) {
			timeMatrixChannel[channel][sample] = new double[2];
		}
	}

	/// Fill matrix
	for (int channel = 0; channel < 2; channel++) {
		for (int sample = 0; sample < numSamples; sample++) {
			timeMatrixChannel[channel][sample][0] = sample*(timeInSeconds / numSamples); //Current time
			timeMatrixChannel[channel][sample][1] = audioData.samples[channel][sample];	//Current sample
		}
	}
}


/**
 * Writes the x and y representation of the audio waveform on a given file.
 *
 * @param channel the sample channel.
 * @param outputFile name of the file where the function writes on.
 */
void Audio::PrintPointsToFile(int channel, string outputFile)
{
	std::ofstream file;

	file.open(outputFile);
	for (int i = 0; i < numSamples; i++)
		file << timeMatrixChannel[channel][i][0] //Current time
			 << " "
			 << timeMatrixChannel[channel][i][1] //Current sample
			 << std::endl;

	file.close();
}

void Audio::DFTMatrix()
{
	dftMat = new complex<double>*[numSamples];
	for (int i = 0; i < numSamples; i++) {
		dftMat[i] = new complex<double>[numSamples];
	}

	complex<double> i(0, 1);
	complex<double> r(2*M_PI / numSamples, 0);
	complex<double> w = std::exp(-i*r);
	complex<double> pow_w;

	for (int i = 0; i < numSamples; i++) {
		dftMat[0][i] = dftMat[i][0] = 1;
	}

	for (int row = 1; row < numSamples; row++) {
		pow_w = pow(w, row);
		for (int col = 1; col < numSamples; col++) {
			if (col >= row) { //Its a diagonal matrix
				dftMat[row][col] = dftMat[row][col-1] * pow_w;
			}
			else {
				dftMat[row][col] = dftMat[col][row];
			}
		}
	}
}

void multCompMat(complex<double>** mat, int nrows, double* vec)
{

    complex<double> *res = new std::complex<double>[nrows];

    for (int i = 0; i < nrows; i++) {
        res[i] = 0;
        for (int k = 0; k < nrows; k++) {
                res[i] = res[i] + mat[i][k] * vec[k];
        }
    }

	for (int i = 0; i < nrows; i++) {
		std::cout << res[i] << ' ';
	}
	std::cout << '\n';
}
