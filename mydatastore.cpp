#include "mydatastore.h"
#include <set>
#include<iostream>
#include"util.h"
#include<map>
#include<deque>
#include<vector>
#include<string>
#include<ostream>

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    for(size_t i=0; i<prolist_.size();++i)
    {
        delete prolist_[i];
    }
    std::map<std::string,User*>::iterator it=userlist_.begin();
    while(it!=userlist_.end())
    {
        delete it->second;
        ++it;
    }
}
void MyDataStore::indexProduct_(Product*p)
{
    if(p==NULL)
    {
        return;
    }
    std::set<std::string>key=p->keywords();
    std::set<std::string>::iterator it=key.begin();
    while(it!=key.end())
    {
        index_[convToLower(*it)].insert(p);
        ++it;
    }
}
void MyDataStore::addProduct(Product* p)
{
    if(p==NULL)
    {
        return;
    }
    prolist_.push_back(p);
    indexProduct_(p);

}

void MyDataStore::addUser(User* u)
{
    if(u==NULL)
    {
        return;
    }
    userlist_[u->getName()]=u;
    if(cart_.find(u->getName())==cart_.end())
    {
        cart_[u->getName()]=std::deque<Product*>();
    }
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::set<Product*> Rset;
    if(terms.empty())
    {
        return lasthit_;
    }
    if(type==0)
    {
        std::map<std::string,std::set<Product*>>::iterator it1=index_.find(terms[0]);
        if(it1==index_.end())
        {
            return lasthit_;
        }
        Rset=it1->second;
        for(size_t i=1;i<terms.size()&&!Rset.empty();++i)
        {
            std::map<std::string, std::set<Product*>>::iterator it2=index_.find(terms[i]);
            if(it2==index_.end())
            {
                Rset.clear();
                break;
            }
            Rset=setIntersection(Rset, it2->second);
        }

    }
    else
    {
        for(size_t i=0;i<terms.size();++i)
        {
            std::map<std::string, std::set<Product*>>::iterator it3=index_.find(terms[i]);
            if(it3!=index_.end())
            {
                Rset=setUnion(Rset, it3->second);
            }
        }
    }
    std::map<std::string, Product*> order;
		for(std::set<Product*>::iterator it4=Rset.begin();it4!=Rset.end();++it4)
		{
			order[(*it4)->getName()]=*it4;
		}
		lasthit_.clear();
		for(std::map<std::string, Product*>::iterator itN=order.begin();itN!=order.end();++itN)
		{
			lasthit_.push_back(itN->second);
		}
		return lasthit_;
}

bool MyDataStore::addToCart(std::string username, int id)
{
    if(userlist_.find(username)==userlist_.end())
    {
        return false;
    }
    if(id<=0||static_cast<size_t>((id)-1)>lasthit_.size())
    {
        return false;
    }
    cart_[username].push_back(lasthit_[id]);
    return true;
}
bool MyDataStore::viewCart(std::string username, std::ostream& os)
{
    std::map<std::string, std::deque<Product*>>::iterator it=cart_.find(username);
    if(it==cart_.end())
    {
        return false;
    }
    const std::deque<Product*>& dq=it->second;
    for(size_t i=0; i<dq.size();++i)
    {
        os<<"Item "<<(i+1)<<"\n";
        os<<dq[i]->displayString()<<"\n\n";
    }
    return true;
}
bool MyDataStore::buyCart(std::string username)
{
    std::map<std::string, std::deque<Product*>>::iterator it=cart_.find(username);
    if(it==cart_.end())
    {
        return false;
    }
		std::map<std::string,User*>::iterator it2=userlist_.find(username);
    if(it2==userlist_.end())
		{
			return false;
		}
		User* user=it2->second;
    std::deque<Product*>& dq=it->second;
    std::deque<Product*> remaining;
    for(size_t i=0;i<dq.size();++i)
    {
        Product* p=dq[i];
        if(p->getQty()>0&&user->getBalance()>=p->getPrice())
        {
            user->deductAmount(p->getPrice());
            p->subtractQty(1);
        }
        else{
            remaining.push_back(p);
        }
    }
    dq.swap(remaining);
    return true;

}
void MyDataStore::dump(std::ostream& ofile)
{
    ofile<<"<products>\n";
    for(size_t i=0;i<prolist_.size();++i)
    {
        prolist_[i]->dump(ofile);
    }
    ofile<<"</products>\n";
    ofile<<"<users>\n";
    std::map<std::string, User*>::iterator it=userlist_.begin();
    for(;it!=userlist_.end();++it)
    {
        it->second->dump(ofile);
    }
    ofile<<"</users>\n";
}