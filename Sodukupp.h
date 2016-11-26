#ifndef SODUKUPP_H
#define SODUKUPP_H
#include <cstdlib>
#include <map>
#include <vector>
#include "Set/Set.h"
#include "Coord/Coord.h"

class Soduku {
	public:
		Soduku(std::string, int);
		~Soduku();
	private:
		std::vector<std::vector<Coord>> allunits;
		std::map<Coord, std::vector<std::vector<Coord>>> units;
		std::map<Coord, Set<Coord>> peers;
		std::map<Coord, Set<int>> values;
		std::map<Coord, int> puzzle;
		int gridSize;
		int n;
		void init(std::string);
		void init_data_structures();
		void init_grid(std::string);
		int string2int(std::string);
		bool solve();
		bool assign(Coord, int);
		bool eliminate(Coord, int);
		void print();


};
#endif