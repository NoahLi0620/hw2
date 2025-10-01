#include "book.h"
#include "product.h"
#include "util.h"
#include<iomanip>
#include<sstream>

Book::Book( const std::string name, double price, int qty,const std:: string ISBN, const std:: string Author):Product
("book",name,price,qty), ISBN_(ISBN), Author_(Author)
{

}

std::set<std::string> Book::keywords() const 
{
   std::set<std::string> bookname=parseStringToWords(getName());
	 std::set<std::string> authorname=parseStringToWords(Author_);
	 std::set<std::string> tempout1=setUnion(bookname,authorname);
	 std::set<std::string> isbnnum;
	 isbnnum.insert(ISBN_);
	 std::set<std::string>out=setUnion(isbnnum,tempout1);
	 return out;
   

	 
	
	 
}
std::string Book:: displayString() const 
{
 std::stringstream dis;
 dis<<getName()<<"\n";
 dis<<"Author: "<<Author_<<" ISBN: "<<ISBN_<<"\n";
 dis<<getPrice()<<" "<<getQty()<<" left.";
 return dis.str();
}
void Book:: dump(std::ostream& os) const 
{
 os<<"book\n";
 os<<getName()<<"\n";
 os<<getPrice()<<"\n";
 os<<getQty()<<"\n";
 os<<ISBN_<<"\n";
 os<<Author_<<"\n";
}

