#ifndef TSPG_H
#define TSPG_H

#include "Point.hh"
#include <vector>

class TSPGenome {

	std::vector<int> tspgGenome;
	double 		tspgCircuitLength;
 
public:
	// Constructors

	/* Takes the number of points that will be visited,
	  and generates a random order to visit those points.  */
	TSPGenome(int numPoints);

	/* Initializes the genome from the specified visit order */
	TSPGenome(const std::vector<int> &order);

	//Destructor
	~TSPGenome();

	//Member functions

	/* Computes the circuit length from traversing the points in 
		the order specified in the object */
	void computeCircuitLength(const std::vector<Point>& points);

	// Returns the genome's current visit order i.e. TSPGenome::tspgGenome
	std::vector<int> getOrder() const;

	// Returns the circuit length
	double getCircuitLength() const;

	// mutation implementation
	void mutate();
	
};

TSPGenome crossLink(const TSPGenome &gA, const TSPGenome &gB);

TSPGenome findAShortPath(const std::vector<Point> &points, // Original return type : TSPGenome
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations);

bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2);

#endif
