#include "utests/SerializableTests.h"

constexpr static double d1 = 0.2345677771;
constexpr static double d2 = 0.11235623423;
constexpr static int i1 = -1000000000;
const auto o1 = UnitTestSerialization(0);
const auto o2 = UnitTestSerialization(1);
const auto o3 = UnitTestSerialization(2);

SerializationObject UnitTestSerialization::serialize() const {
	SerializationObject so;
	if (dataType == 0){
		so.putInt(dataType);
		so.putDouble(d1);
	}else if (dataType == 1){
		so.putInt(dataType);
		so.putDouble(d1);
		so.putInt(i1);
		so.putDouble(d2);
	}else if (dataType == 2){
		so.putInt(dataType);
		so.putDouble(d1);
		so.putInt(i1);
		so.putObject(o1.serialize());
		so.putObject(o2.serialize());
	}else{ 
		so.putInt(dataType);
		so.putDouble(d2);
		so.putDouble(d1);
		so.putInt(i1);
		so.putObject(o3.serialize());
		so.putObject(o2.serialize());
		so.putObject(o3.serialize());
	}
	return so;
}

UnitTestSerialization::UnitTestSerialization(SerializationObject so, bool &success){
	success = false;
	dataType = so.getInt();
	if (dataType == 0){
		if (d1 == so.getDouble())
			success = true;
	}else if (dataType == 1){
		if (d1 == so.getDouble()
				&& i1 == so.getInt()
				&& d2 == so.getDouble())
			success = true;
	}else if (dataType == 2){
		bool success1 , success2;
		UnitTestSerialization(so.getObject(), success1);
		UnitTestSerialization(so.getObject(), success2);
		if (d1 == so.getDouble()
				&& i1 == so.getInt()
			&& success1 && success2)
			success = true;
	}else {
		bool suc1, suc2, suc3;
		UnitTestSerialization(so.getObject(), suc1);
		UnitTestSerialization(so.getObject(), suc2);
		UnitTestSerialization(so.getObject(), suc3);
		if (d2 == so.getDouble() 
				&& d1 == so.getDouble()
				&& i1 == so.getInt()
				&& suc1 && suc2 && suc3)
			success = true;
	}
}
