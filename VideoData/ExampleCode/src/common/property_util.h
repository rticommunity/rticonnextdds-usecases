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

#include <string>
#include <map>

typedef std::map<const std::string, std::string> CfgMap;

class PropertyUtil {

private:
    CfgMap _config;
    
public:
    PropertyUtil(std::string filename);

    std::string getStringProperty(std::string property);
    int getIntProperty(std::string property);
    long getLongProperty(std::string property);
    double getDoubleProperty(std::string property);
    float getFloatProperty(std::string property);

    CfgMap getPropertyMap(void) { return _config; }

};
