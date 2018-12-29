#include "Serializable.h"

SerializationObject::SerializationObject(){
}

SerializationObject::SerializationObject(const std::vector<unsigned int>& v){
	int pos = 0;
	int next = v[pos];
	for (int i = pos + 1 ; i < pos + 1 + next; i++)
		data.push(v[i]);
	
	pos += next + 1; // pos is at amount of objects
	int objs = v[pos];
	pos++;
	for (int i = 0; i < objs ; i++){
		objects.push(SerializationObject(v, pos));
	}
}

SerializationObject::SerializationObject(const std::vector<unsigned int>& v, int &pos){
	// Warning: this code was copy pasted a little up
	int next = v[pos];
	for (int i = pos + 1 ; i < pos + 1 + next; i++)
		data.push(v[i]);
	
	pos += next + 1; // pos is at amount of objects
	int objs = v[pos];
	pos++;
	for (int i = 0; i < objs ; i++){
		objects.push(SerializationObject(v, pos));
	}
}

std::vector<unsigned int> SerializationObject::getData(){
	std::vector<unsigned int> v;
	v.push_back(data.size());
	while (!data.empty()){
		v.push_back(data.front());
		data.pop();
	}
	v.push_back(objects.size());
	while (!objects.empty()){
		for (const auto& ui : objects.front().getData())
			v.push_back(ui);
		objects.pop();
	}
	return v;
}

void SerializationObject::putDouble(double d){
	union { unsigned long long i; double d; } u;
	u.d = d;
	unsigned int st = u.i >> 32;
	unsigned int nd = (u.i << 32) >> 32;
	data.push(st);
	data.push(nd);
}

double SerializationObject::getDouble(){
	union { unsigned long long ull; double d;} u;
	unsigned long long st = data.front(); data.pop();
	st <<=  static_cast<unsigned long long>(32);
	unsigned long long nd = data.front(); data.pop();
	u.ull = st + nd;
	return u.d;
}

void SerializationObject::putInt(int i){
	union { unsigned int ui; int i; } u;
	u.i = i;
	data.push(u.ui);
}

int SerializationObject::getInt(){
	union { unsigned int ui; int i;} u;
	u.ui = data.front(); data.pop();
	return u.i;
}

void SerializationObject::putUInt(unsigned int ui){
	data.push(ui);
}

unsigned int SerializationObject::getUInt(){
	auto ui = data.front(); data.pop();
	return ui;
}

void SerializationObject::putObject(SerializationObject o){
	objects.push(o);
}

SerializationObject SerializationObject::getObject(){
	auto o = objects.front(); objects.pop();
	return o;
}

