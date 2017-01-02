# TSPGA
An Implementation of the Traveling Salesman Problem Solution in Three-dimensional space Using Genetic Algorithms.

### Usage
```
Usage: ./tsp-ga [OPTIONS] < [TEST FILE]
eg. ./tsp-ga --population 1000 --generation 400 --keep 100 --mutation 900 < test-30.txt

ALL OPTIONS ARE REQUIRED
where options are :
-p <value>, --population <value>
population is a positive integer specifying the population size.

-g <value>, --generation <value>
generations is a positive integer specifying how many generations to run the GA for.

-k <value>, --keep <value>
the number of the population that should be preserved from generation to generation.

-m <value>, --mutation <value>
specifies how many mutations to apply to each member of the population.
```

##Results

With an input of 12 points (cities), a brute-force solution takes about **6 minutes 20 seconds** to complete. The best order is [0 9 10 11 1 4 6 2 8 3 7 5], and the distance is 47.6887.

Here is an example output from running the TSPGA algorithm on the same input (12 cities). It can reliably find the best path in less than **one second**.

```
imad@user:~$ ./tsp-ga --population 1000 --generation 10 --keep 100 --mutation 900 < test-12.txt
Generation 0:  shortest path is 58.9193
Generation 1:  shortest path is 47.6887
Generation 2:  shortest path is 47.6887
Generation 3:  shortest path is 47.6887
Generation 4:  shortest path is 47.6887
Generation 5:  shortest path is 47.6887
Generation 6:  shortest path is 47.6887
Generation 7:  shortest path is 47.6887
Generation 8:  shortest path is 47.6887
Generation 9:  shortest path is 47.6887
Shortest Path Found : [0 9 10 11 1 4 6 2 8 3 7 5]
Length is : 47.6887
```



