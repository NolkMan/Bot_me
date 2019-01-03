#ifndef __BOTME_INC_UTESTS_SERTESTS_H
#define __BOTME_INC_UTESTS_SERTESTS_H

#include "Serializable.h"

class UnitTestSerialization : public Serializable{
	int dataType;
public:
	UnitTestSerialization(int dataType):dataType(dataType){}
	UnitTestSerialization(SerializationObject so, bool &success);

	SerializationObject serialize() const;
};

#endif
