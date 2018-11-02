#include "network.h"
#include <iostream>
#include "random.h"
#include <algorithm> 
#include <iterator> 


void Network::resize(const size_t& n)
{
	values.clear();
	
	for(size_t i(0); i < n ; i++)
	{
		values.push_back(RNG.normal());
	}
	
}



bool Network::add_link(const size_t& a, const size_t& b)
{
	if (a<this->size() and b<this->size() and a!=b)
	{
		if ( not(is_linked(a,b)))
		{
			std::pair<size_t,size_t> myPair1(a,b);
			std::pair<size_t,size_t> myPair2(b,a);
		
			links.insert(myPair1);
			links.insert(myPair2);
			
			return true; 
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false ;
	}


}


size_t Network::random_connect(const double& mean)
{
	size_t count(0);
	
	links.clear();
	
	size_t deg= RNG.poisson(mean);
	
	for (size_t i(0) ; i < this->size() ; i++)
	{
		for	( size_t j(0) ; j < deg ; j++)
		{
			if (add_link(i,RNG.uniform_double(0,this->size())))			
			{	
				++count;
			}	
		}
	}
	
	return count ;

}



size_t Network::set_values(const std::vector<double>& newVal)
{
	size_t count(0);
	
	this->resize(newVal.size());
		
	for(size_t i(0); i<newVal.size(); i++)
	{
		values[i]=newVal[i];
		count +=1;
	}
	
	return count;
	
	
}



size_t Network::size() const
{ 
		return values.size();
}


size_t Network::degree(const size_t &_n) const
{
	size_t deg = links.count(*(&_n));
	
	return deg;
	
}


double Network::value(const size_t &_n) const
{
	return values[*(&_n)];
}


std::vector<double> Network::sorted_values() const
{
	std::vector<double> sortedVec = values;
	
	std::sort(sortedVec.begin(), sortedVec.end());
	std::reverse(sortedVec.begin(), sortedVec.end());
	
	return sortedVec ;
}



std::vector<size_t> Network::neighbors(const size_t& n) const
{	
	std::vector<size_t> ngb ;
	
	for (auto itr = links.begin(); itr != links.end(); itr++)
	{   
		if (itr->first == n)         
		{
			ngb.push_back(itr->second);
		}
	}
		  
	return ngb ;
   
}




bool Network::is_linked(const size_t& a, const size_t& b)
{
	for (auto ngb : this->neighbors(a))
	{   
		if (ngb == b)
		{
			return true ;
		}
	}
	
	return false;
		
} 
