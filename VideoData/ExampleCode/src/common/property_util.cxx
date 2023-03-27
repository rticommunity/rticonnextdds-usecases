/****************************************************************************
(c) 2005-2021 Copyright, Real-Time Innovations, Inc.  All rights reserved.                                    
RTI grants Licensee a license to use, modify, compile, and create derivative 
works of the Software.  Licensee has the right to distribute object form 
only for use with RTI products.  The Software is provided 'as is', with no
arranty of any type, including any warranty for fitness for any purpose. RTI
is under no obligation to maintain or support the Software.  RTI shall not
be liable for any incidental or consequential damages arising out of the 
use or inability to use the software.
*****************************************************************************/
#include <iostream>
#include <fstream>
#include "property_util.h"

PropertyUtil::PropertyUtil(std::string filename)
{
   std::string s;
   std::ifstream cin(filename);
   while (std::getline(cin, s)) _config[s.substr(0, s.find('='))] = s.substr(s.find('=') + 1);

}

std::string PropertyUtil::getStringProperty(std::string property)
{
   std::string str = "";
   if (_config[property].empty())
      return str;
   else
       return _config[property];
}

int PropertyUtil::getIntProperty(std::string property)
{
   int val = 0;
   if (_config[property].empty())
      return val;
   else
      return std::stoi(_config[property]);
}

long PropertyUtil::getLongProperty(std::string property)
{
   long val = 0;
   if (_config[property].empty())
      return val;
   else {
      std::string st = _config[property];
      return std::stol(st);
   }
}

double PropertyUtil::getDoubleProperty(std::string property)
{
   double val = 0.0;
   if (_config[property].empty())
      return val;
   else
      return std::stod(_config[property]);
}

float PropertyUtil::getFloatProperty(std::string property)
{
   float val = 0.0;
   if (_config[property].empty())
      return val;
   else
      return std::stof(_config[property]);
}
