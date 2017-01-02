/*
	[TSPGA]
	An Implementation of the Traveling Salesman Problem Solution in Three-dimensional space Using Genetic Algorithms.
	[Author : Imad Hsissou]
	[E-mail: imad.hsissou@gmail.com]
	[https://github.com/7bisso]
*/

#include "tsp-ga.hh"
#include <iostream>
#include <cstdlib>  	// srand(), atoi()
#include <ctime> 		// time()
#include <getopt.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void help();

int main(int argc, char **argv) {


	// Parsing Arguments

	int populationSize, numGenerations,
			keepPopulation, numMutations;

	int c;

	while(1) {
		static struct option long_options[] = {
			{"population",	required_argument,	0,	'p'},
			{"generation",	required_argument,	0,	'g'},
			{"keep",	required_argument,	0,	'k'},
			{"mutation",	required_argument,	0,	'm'},
			{"help",		no_argument,	0,	'h'},
			{0, 0, 0, 0}
		};

		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "p:g:k:m:h",
                       long_options, &option_index);
		/* Detect the end of the options. */
    	if (c == -1)
    	break;

    	switch(c)
    		{
    		case 'p':
    			populationSize = atoi(optarg); break;
    		case 'g':
    			numGenerations = atoi(optarg); break;
    		case 'k':
    			keepPopulation = atoi(optarg); break;
    		case 'm':
    			numMutations = atoi(optarg); break;
    		case 'h':
    			help(); exit(0);
    		default :
    			abort ();
    		}
    	}

    if(argc != 9) {
    	help();
    }

	// Setting Input

	srand (unsigned (time (0)));

	int pointsNumber;
	double inputX, inputY, inputZ;
	vector<Point> pointsCluster;

	// Points Input

	cin >> pointsNumber;

	for(int i = 0; i < pointsNumber; i++) {

		cin >> inputX >> inputY >> inputZ ;
		Point inputPoint {inputX, inputY, inputZ};
		pointsCluster.push_back(inputPoint);
		 
	}

	// Run Genetic Algorithm

	TSPGenome goodGenome = findAShortPath(pointsCluster, populationSize,numGenerations,
					keepPopulation, numMutations);
	vector<int> GOrder = goodGenome.getOrder();
	double GLength = goodGenome.getCircuitLength();

	cout << "Shortest Path Found : [";
	for(const auto& genome : GOrder) {
		cout << " " << genome;
	}
	cout << "]\nLength is : " << GLength << endl;

	return 0;
}

void help() {
    	cout <<
    		"Usage: ./tsp-ga [OPTIONS]\n"
    		"ALL OPTIONS ARE REQUIRED\n"
    		"where options are :\n"
    		"-p <value>, --population <value>\n"
    		"population is a positive integer specifying the population size.\n\n"

    		"-g <value>, --generation <value>\n"
    		"generations is a positive integer specifying how many generations to run the GA for.\n\n"

    		"-k <value>, --keep <value>\n"
    		"the number of the population that should be preserved from generation to generation.\n\n"

    		"-m <value>, --mutation <value>\n"
    		"specifies how many mutations to apply to each member of the population."
    		<< endl;
}
