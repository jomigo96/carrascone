/*!
 * \file Cloister.hpp
 * \brief Cloister header file
 * \author João Gonçalves
 */

#ifndef CLOISTER_HPP
#define CLOISTER_HPP

#include "configs.hpp"
#include "MapItem.hpp"
#include <ostream>


/*!
 * \class Cloister
 * \brief
 * */
class Cloister : public MapItem{

public:
	Cloister();
	Cloister(std::shared_ptr<Tile> tile, TypeIdentifier key);
	~Cloister();

	std::ostream& myprint(std::ostream& os, const MapItem& item)const;

	void checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const& map);

	void giveRemainingPoints(std::map<Cell, std::shared_ptr<Tile>> const& map);

private:

};
#endif /* CLOISTER_HPP */
