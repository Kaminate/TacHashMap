#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cassert>

#include "tacHashMap.h"

int main()
{
  srand( 0 );
  std::unordered_map< std::string, std::string > myStdMap;

  TacHashMap< std::string, std::string > myTacMap;
  myTacMap.mHashFn = []( std::string s )
  {
    int result = 0;
    for( char c:s )
      result = result * 33 + c;
    return result;
  };

  std::vector< std::pair< std::string, std::string > > pairs;
  for( int i = 0; i < 100; ++i )
  {
    std::pair< std::string, std::string > myPair;
    myPair.first = std::to_string( rand() % 27 );
    myPair.second = std::to_string( rand() % 27 );
    pairs.push_back( myPair );
  }

  myTacMap.Clear();
  myStdMap.clear();
  for( int i = 0; i < 3000; ++i )
  {
    std::pair< std::string, std::string > myPair = pairs[ rand() % pairs.size() ];
    std::string key = myPair.first;
    std::string val = myPair.second;
    bool found;
    auto CompareMaps = [ & ]()
    {
      found = myStdMap.find( key ) != myStdMap.end();
      bool myTacFound = myTacMap.Contains( key );
      bool gucci = found == myTacFound && myTacMap.mSize == myStdMap.size();
      if( !gucci )
        __debugbreak();
    };
    CompareMaps();
    int choice = rand() % 4;
    switch( choice )
    {
    case 0: // fallthrough
    case 1: // ensure in map
      if( !found )
      {
        myStdMap[ key ] = val;
        myTacMap[ key ] = val;
      }
      break;
    case 2: // ensure not in map
      if( found )
      {
        myStdMap.erase( key );
        myTacMap.Remove( key );
      }
      break;
    case 3: // do nothing
      break;
    }
    CompareMaps();
  }

  std::cout << "finished" << std::endl;

  getchar();
}

