#ifndef JsonSerializable_H
#define JsonSerializable_H

#include <ArduinoJson.h>

class JsonSerializable {
    public:      
      inline virtual void setAttribute(String attribute) { _attribute = attribute; };     
 
      virtual StaticJsonDocument<200> getJson() = 0;
    
    protected:
      String _attribute;

      inline virtual StaticJsonDocument<200> getBasicJsonDocument() 
      { 
        StaticJsonDocument<200> doc; 
        doc["attrib"] = _attribute; 
        doc["time"] = millis();
        return doc;
      };
};
#endif
