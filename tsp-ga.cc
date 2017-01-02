#include "tsp-ga.hh"
#include <iostream>
#include <algorithm> 	// std::random_shuffle(), std::iter_swap(), std::sort()
#include <set>		// std::set
#include <cstdlib>  	// rand()

using std::vector;
using std::set;
using std::cout;
using std::endl;

TSPGenome::TSPGenome(const int numPoints) {
/* takes the number of points that will be visited, and generates a random order
 to visit those points. The constructor simply push the numbers [0 1 2 3 ... numPoints-1] 
 into a vector, and then use the random_shuffle() algorithm to randomly permute the vector. */

	for(int i = 0; i < numPoints; ++i)
		tspgGenome.push_back(i);

	std::random_shuffle (tspgGenome.begin(), tspgGenome.end());
	tspgCircuitLength = -1;
}

TSPGenome::TSPGenome(const vector<int> &order) {
/* Initializes the genome from the specified visit order */

	tspgGenome = order;
	tspgCircuitLength = -1;
}

TSPGenome::~TSPGenome(){
	// no-op
}

void TSPGenome::computeCircuitLength(const vector<Point> &points) {
/* Computes the circuit length from traversing the 
	points in the order specified in the object */

	size_t sizeGenome = tspgGenome.size();
	tspgCircuitLength = points[tspgGenome.front()].distanceTo(points[tspgGenome.back()]);

	for(unsigned i = 0, j = 1; i < sizeGenome - 1; ++i, ++j) {
		tspgCircuitLength += points[tspgGenome[i]].distanceTo(points[tspgGenome[j]]);
	}
}

vector<int> TSPGenome::getOrder() const {
	return tspgGenome;
}

double TSPGenome::getCircuitLength() const {
	return tspgCircuitLength;
}

void TSPGenome::mutate() {
	/* mutates the genome by swapping two randomly-
		selected values in the order vector. */
	unsigned swapIndexA;
	unsigned swapIndexB;

	swapIndexA = rand() % tspgGenome.size();
	do {
		swapIndexB = rand() % tspgGenome.size();
	} while (swapIndexA == swapIndexB);

	std::iter_swap(tspgGenome.begin() + swapIndexA, tspgGenome.begin() + swapIndexB);
}

TSPGenome crossLink(const TSPGenome &GA, const TSPGenome &GB) {

	/*  used to vary the programming of a
		 chromosome from one generation to the next. */

	vector<int> _GA = GA.getOrder();
	vector<int> _GB = GB.getOrder();
	vector<int> offspringGenome;
	set<int> keepTrack;


	size_t sizeGenome = _GA.size();
	// generate a random index in range [2, .. , sizeGenome - 2]
	unsigned randomIndex = (rand() % (sizeGenome - 3)) + 2;

	// init offspringGenome and keepTrack
	for(unsigned i = 0; i < randomIndex; ++i) {
		offspringGenome.push_back(_GA.at(i));
		keepTrack.insert(_GA.at(i));
	}

	// crosslinking

	for(const auto& gene : _GB) {
		bool found = keepTrack.find(gene) != keepTrack.end();
		if (!found) {
			offspringGenome.push_back(gene);
		}
	}

	// generate TSPGenome object from offspringGenome the return object.
	TSPGenome Offspring(offspringGenome);
	return Offspring;
}

TSPGenome findAShortPath(const vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations) {
	// Generate an initial population of random genomes
	vector<TSPGenome> population;
	size_t sizeGenome = points.size();

	for(int i = 0; i < populationSize; ++i) {
		TSPGenome genome(sizeGenome);
		population.push_back(genome);
	}

	for(int gen = 0; gen < numGenerations * 10; ++gen){

		// Compute the circuit length for each member.
		for(TSPGenome& genome : population){
			genome.computeCircuitLength(points);
		}

		/* sort the TSP genomes by fitness. 
			(The "fittest" ones should be at the lowest indexes.) */
		std::sort(population.begin(), population.end(), isShorterPath);

		/*keep the top N fittest members of the population, and replace
			the remaining members with new genomes produced from the fittest ones (crosslinking) */

		for(int i = keepPopulation; i < populationSize; ++i){

			unsigned randomIndexA;
			unsigned randomIndexB;

			// range [0 .. keepPopulation - 1]
			randomIndexA = rand() % keepPopulation;
			do {
				randomIndexB = rand() % keepPopulation;
			} while (randomIndexA == randomIndexB);

			population[i] = crossLink(population[randomIndexA], population[randomIndexB]);
		}

		// Mutation time :D
		for(int i = 0; i < numMutations; ++i){

			unsigned randomIndex;

			randomIndex = 1 + rand() % (populationSize - 1);
			population[randomIndex].mutate();
		}

		if (gen % 10 == 0) {
        	cout << "Generation " << gen / 10 << ":  shortest path found "
            	<< population[0].getCircuitLength() << endl;
    	}

	}

	return population[0];
}

bool isShorterPath(const TSPGenome &GA, const TSPGenome &GB) {
	double fitnessGA = GA.getCircuitLength();
	double fitnessGB = GB.getCircuitLength();
	if(fitnessGA < fitnessGB)
		return true;
	else 
		return false; 
}
