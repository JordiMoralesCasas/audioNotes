#include <stdio.h>
#include <iostream>
#include <string>
#include <complex>


#include <complex.h>
#undef complex

#include "../include/audio.h"
#include "../include/complex.h"

using std::string;


int main(int argc, char *argv[]) {
	if (argc > 3 || argc == 1) {
		std::cout << "Format accepted: \\final filename time\n"
				  << "   - filename: A WAV or AIFF audio file.\n"
				  << "   - time: Maximum length to process. "
				  << std::endl;
		return 1;
	}

	string filename(argv[1]);
	double time = atof(argv[2]);
	//int channel = 0; //TODO: Way to introduce which channel to use

	Audio audio = Audio(filename, time);
	audio.PrintPointsToFile(0, "pointsC1.txt");


	/*std::complex<double> **mat = new std::complex<double>*[4];
	for (int i = 0; i < 4; i++) {
		mat[i] = new std::complex<double>[4];
	}

	mat[0][0] = std::complex<double>(1,0); mat[0][1] = std::complex<double>(1,0); mat[0][2] = std::complex<double>(1,0); mat[0][3] = std::complex<double>(1,0);
	mat[1][0] = std::complex<double>(1,0); mat[1][1] = std::complex<double>(0,-1); mat[1][2] = std::complex<double>(-1,0); mat[1][3] = std::complex<double>(0,1.0);
	mat[2][0] = std::complex<double>(1,0); mat[2][1] = std::complex<double>(-1,0); mat[2][2] = std::complex<double>(1,0); mat[2][3] = std::complex<double>(-1,0);
	mat[3][0] = std::complex<double>(1,0); mat[3][1] = std::complex<double>(0, 1); mat[3][2] = std::complex<double>(-1,0); mat[3][3] = std::complex<double>(0, -1.0);

	double vec[4] = {8, 4, 8, 0};
	multCompMat(mat, 4, vec);*/

	audio.DFTMatrix();

	/*for (int i = 0; i < 10; i ++) {
		for (int j = 0; j < 10; j++) {
			std::cout << audio.dftMat[i][j] << " ";
		}
		std::cout << '\n';
	}*/

	return 0;
}
