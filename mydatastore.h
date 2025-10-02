#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include<map>
#include<deque>
#include "product.h"
#include "user.h"
#include "datastore.h"



class MyDataStore : public DataStore{
    public:
    MyDataStore();
    ~MyDataStore();
     void addProduct(Product* p) override;
    void addUser(User* u) override;

    
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    
    void dump(std::ostream& ofile)override ;
    bool addToCart(std::string username, int id);
    bool viewCart(std::string username, std::ostream& os);
    bool buyCart(std::string username);
    void indexProduct_(Product* p);
    private:
    std::vector<Product*> prolist_;
    std::map<std::string, User*> userlist_;
    std::map<std::string, std::deque<Product*>> cart_;
    std::map<std::string, std::set<Product*>> index_;
    std::vector<Product*> lasthit_;
};
#endif