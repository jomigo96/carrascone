/*!
 * \file Cloister.hpp
 * \brief Cloister header file
 * \author João Gonçalves
 */

#ifndef CLOISTER_HPP
#define CLOISTER_HPP

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
	
	std::ostream& myprint(std::ostream& os, const Cloister& c)const;

private:

};
#endif /* CLOISTER_HPP */
