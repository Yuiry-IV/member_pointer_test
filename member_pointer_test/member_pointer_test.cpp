// member_pointer_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

template<class TArg1>
class callback
{   
   typedef void (*t_ptr_arg1)(const TArg1 &);

   
   t_ptr_arg1 _ptr_arg1;
public:
   callback() : _ptr_arg1(0)
   {}

   void bind( t_ptr_arg1 in_ptr_arg1 )
   {      
      _ptr_arg1 = in_ptr_arg1;
   }

   void exec(const TArg1 &arg)
   {
      if (_ptr_arg1)
         (*_ptr_arg1)(arg);
   }
};

class A;

void foo(const int &b)
{
   std::cout <<b<< " test\n";
}


#include <filesystem>

void test(void)
{
   for (std::tr2::sys::directory_iterator i("D:\\p4\\"); i != std::tr2::sys::directory_iterator(); ++i )
   {
      if (!std::tr2::sys::is_directory(i->status()))
         continue;
      std::string s = i->path();
      if (std::string::npos != s.find("_products"))
         continue;
      if ( std::string::npos != s.find("0_DevDef") && (s.find("0_DevDef")+15)<s.size() )
      {
         s.erase(s.begin(), s.begin() + s.find("0_DevDef") + 15);
         std::cout <<s << "\n";
      }
   }
}

#include <map>
#include <codecvt>

typedef std::map<std::string, std::string> t_args_map;

t_args_map get_args(int argc, _TCHAR* argv[])
{
   // wide to UTF-8
   std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
   t_args_map args;
   std::string key, value;

   for (int i = 1; i < argc; i++)
   {
      if (key.empty() || key[0] != '-' )
         key = convert.to_bytes(argv[i]);
      else
      {
         value = convert.to_bytes(argv[i]);
      }
      if ( key[0]=='-' && !value.empty() )
      {
         args[key] = value;
         key.clear();
         value.clear();
      }
   }
   return args;
}

#include <algorithm>

void puts(_TCHAR *arg)
{
   std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
   std::cout << convert.to_bytes(arg)<<'\n';
}

bool modify_bool(const bool &b)
{
   bool r = !b;   
   return r;
}

int _tmain(int argc, _TCHAR* argv[])
{
   /*
   bool other = false;
   bool minus_other = modify_bool(other);
   bool not_other = modify_bool(other);

   std::cout << __LINE__ << ":" << other << std::endl;
   std::cout << __LINE__ << ":" << minus_other << std::endl;
   std::cout << __LINE__ << ":" << not_other << std::endl;

   std::cout << __LINE__ << ":" << (minus_other == bool(-minus_other)) << std::endl;
   std::cout << __LINE__ << ":" << (minus_other == -minus_other) << std::endl;

   std::cout << __LINE__ << ":" << (not_other == bool(~not_other)) << std::endl;
   std::cout << __LINE__ << ":" << (not_other == ~not_other) << std::endl;
   */
   for (int i = 0; i < argc; ++i)
   {
      puts(argv[i]);
   }

   std::cout << "-----------" << '\n';

   const t_args_map args( get_args(argc, argv) );

   std::for_each(args.begin(), args.end(), [](const std::pair<const std::string, std::string> &p){ std::cout <<p.first<<":"<< p.second << '\n'; });

   //test();
   return 0;

   callback<const int &> a;
   a.bind(foo);
   a.exec(100);
	return 0;
}

