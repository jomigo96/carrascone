/*!
 * \file Castle.hpp
 * \brief Castle header file
 * \author João Gonçalves
 */

#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "MapItem.hpp"
#include <ostream>
#include "configs.hpp"

/*!
 * \class Castle
 * \brief
 * */
class Castle : public MapItem{

public:
	Castle();
	Castle(std::shared_ptr<Tile> tile, TypeIdentifier key);
	~Castle();

	std::ostream& myprint(std::ostream& os, const MapItem& item)const;

	void checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const& map);

private:

};
#endif /* CASTLE_HPP */
