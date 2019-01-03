#ifndef __BOTME_INC_SERIALIZABLE_H
#define __BOTME_INC_SERIALIZABLE_H

#include <vector>
#include <queue>

class SerializationObject{
	std::queue<unsigned int> data;
	std::queue<SerializationObject> objects;
public:
	SerializationObject();
	SerializationObject(const std::vector<unsigned int>&);
	SerializationObject(const std::vector<unsigned int>& , int &pos);

	std::vector<unsigned int> getData();

	void putDouble(double);
	void putInt(int);
	void putUInt(unsigned int);
	void putObject(SerializationObject);

	double getDouble();
	int getInt();
	unsigned int getUInt();
	SerializationObject getObject();
};

class Serializable{
protected:
	Serializable(){};

public:
	virtual SerializationObject serialize() const = 0;

};

#endif
