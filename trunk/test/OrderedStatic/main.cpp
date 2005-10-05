////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2005 Peter K�mmel
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author makes no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// $Header:

// define to test the OrderedStatic template
#define TEST_ORDERED_STATIC

// define to see a runtime crash when not using OrderedStatic
//#define LOKI_CLASS_LEVEL_THREADING

#include "loki/Functor.h"
#include <iostream>

#ifdef TEST_ORDERED_STATIC
#include "loki/OrderedStatic.h"
#endif 

struct L1
{
	L1(){std::cout << "create L1: " << this << "\n";}
	~L1(){std::cout << "delete L1: " << this <<" \n";}
};

struct L2
{
	L2(){std::cout << "create L2 \n";}
	~L2(){std::cout << "delete L2 \n";}
};

int f()
{
	std::cout << "f called \n";
	return 0;
}

std::string func();


#ifdef TEST_ORDERED_STATIC

Loki::OrderedStatic<1,L1> l1;
Loki::OrderedStatic<2,L2> l2;

Loki::OrderedStatic<1, std::string, std::string(*)() >			s1( &func ); 
Loki::OrderedStatic<2, std::string, LOKI_TYPELIST_1(char *) >	s2( "s2" ); 

Loki::OrderedStatic<1, Loki::Functor<int>, LOKI_TYPELIST_1( int(*)() ) >  f1(f); 

#else

L1 l1;
L2 l2;

std::string s1( func() ); 
std::string s2("s2"); 

Loki::Functor<int> f1(f);

#endif


std::string func()
{
#ifdef TEST_ORDERED_STATIC
	return *s2;
#else
	return s2;
#endif
}


int main()
{	
	
#ifdef TEST_ORDERED_STATIC

	Loki::OrderedStaticManager::Instance().createObjects();
	
	(*f1)();

	std::cout << "s1 = " << (*s1).c_str() << "\n";
	std::cout << "s2 = " << (*s2).c_str() << "\n";
	
	std::string s("text11");
	*s1=s;
	std::cout << "s1 = " << (*s1).c_str() << "\n";
	
#else

	f1();
	
	std::cout << "s1 = " << s1.c_str() << "\n";
	std::cout << "s2 = " << s2.c_str() << "\n";

#endif

	return 0;
}

