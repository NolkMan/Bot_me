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
	Serializable();

public:
	virtual SerializationObject serialize() = 0;

};

class UnitTestSerialization : public Serializable{
	const static double d1 = 0.2345677771;
	const static double d2 = 0.11235623423;
	const static int i1 = -1000000000;
	const static auto o1 = UnitTestSerialization(0);
	const static auto o2 = UnitTestSerialization(1);
	const static auto o3 = UnitTestSerialization(2);
	int dataType;
public:
	UnitTestSerialization(int dataType):dataType(dataType){}
	UnitTestSerialization(const SerializationObject&);
	SerializationObject serialize(){
		SerializationObject so;
		if (dataType == 0){
			so.putDouble(d1);
		}else if (dataType == 1){
			so.putDouble(d1);
			so.putInt(i1);
			so.putDouble(d2);
		}else if (dataType == 2){
			so.putDouble(d1);
			so.putInt(i1);
			so.putObject(o1.serialize());
			so.putObject(o2.serialize());
		}else{ 
			so.putDouble(d2);
			so.putDouble(d1);
			so.putInt(i1);
			so.putObject(o3.serialize());
			so.putObject(o2.serialize());
			so.putObject(o3.serialize());
		}
		return so;
	}
};

#endif
