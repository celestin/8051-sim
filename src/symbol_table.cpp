#include <fstream>
#include <iostream>
#include "symbol_table.hpp"
#include <map>

static SymbolTable symbolTable;

void SymbolTable::ParseFile(const std::string &fileName)
{
  std::string line;
  std::ifstream file;
  int symbolCount = 0;

  file.open(fileName);
  while (std::getline(file, line))
  {
    std::string address;
    std::string count;
    std::string name;

    int wordCount = 0;
    int start;
    bool inWord = false;
    for (int i = 0; i <= line.length(); i++)
    {
      if (line[i] == ' ' || i == line.length())
      {
        if (inWord)
        {
          inWord = false;
          if (wordCount == 1)
          {
            address = line.substr(start, i-start);
          }
          else if (wordCount == 2)
          {
            count = line.substr(start, i-start);
          }
          else if (wordCount == 3)
          {
            name = line.substr(start, i-start);
          }
        }
      }
      else if (!inWord)
      {
        inWord = true;
        start = i;
        wordCount++;
      }
    }
    if (wordCount == 3 && name[0] == '_' && name[name.length()-1] == ':')
    {
      name = name.substr(1, name.length()-2);
      std::uint16_t a = stoi(address, nullptr, 16);
      addressMap[a] = name;
      symbolMap[name] = a;
      symbolCount++;
    }
  }
  std::cout << "Found " << symbolCount << " symbols in " << fileName << std::endl;
}

void SymbolTable::LookupSymbol(const std::string &symbolName, std::uint16_t &address, bool &found)
{
  if (symbolMap.find(symbolName) != symbolMap.end())
  {
    address = symbolMap[symbolName];
    found = true;
  }
  else
  {
    found = false;
  }
}

#include <iostream>

void SymbolTable::LookupAddress(const std::uint16_t address, std::string &symbolName, bool &found)
{
  if (addressMap.find(address) != addressMap.end())
  {
    symbolName = addressMap[address];
    found = true;
  }
  else
  {
    found = false;
  }
}

void SymbolTable::RegisterSymbol(std::uint16_t address, std::string name)
{
  addressMap[address] = name;
  symbolMap[name] = address;
}

SymbolTable *SymbolTable::GetInstance()
{
  return &symbolTable;
}

