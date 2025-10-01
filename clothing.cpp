#include "clothing.h"
#include "product.h"
#include "util.h"
#include<iomanip>
#include<sstream>

Clothing::Clothing(const std::string name, double price, int qty,const std:: string size, const std:: string brand):Product
("clothing",name,price,qty), size_(size), brand_(brand)
{

}

std::set<std::string> Clothing::keywords() const 
{
   std::set<std::string> clothname=parseStringToWords(getName());
	 std::set<std::string> brandname=parseStringToWords(brand_);
	 std::set<std::string> tempout1=setUnion(clothname,brandname);
	 return tempout1;
   

	 
	
	 
}
std::string Clothing:: displayString() const 
{
 std::stringstream dis;
 dis<<getName()<<"\n";
 dis<<"Size: "<<size_<<" Brand: "<<brand_<<"\n";
 dis<<getPrice()<<" "<<getQty()<<" left.";
 return dis.str();
}
void Clothing:: dump(std::ostream& os) const 
{
 os<<"clothing\n";
 os<<getName()<<"\n";
 os<<getPrice()<<"\n";
 os<<getQty()<<"\n";
 os<<size_<<"\n";
 os<<brand_<<"\n";
}
