#include "movie.h"
#include "product.h"
#include "util.h"
#include<iomanip>
#include<sstream>

Movie::Movie(const std::string name, double price, int qty,const std:: string genre, const std:: string rating):Product
("movie",name,price,qty), genre_(genre), rating_(rating)
{

}

std::set<std::string> Movie::keywords() const 
{
   std::set<std::string> out=parseStringToWords(getName());
	 out.insert(convToLower(genre_));
	 return out;
	
   

	 
	
	 
}
std::string Movie:: displayString() const 
{
 std::stringstream dis;
 dis<<getName()<<"\n";
 dis<<"Genre: "<<genre_<<" Rating: "<<rating_<<"\n";
 dis<<getPrice()<<" "<<getQty()<<" left.";
 return dis.str();
}
void Movie:: dump(std::ostream& os) const 
{
 os<<"movie\n";
 os<<getName()<<"\n";
 os<<getPrice()<<"\n";
 os<<getQty()<<"\n";
 os<<genre_<<"\n";
 os<<rating_<<"\n";
}
