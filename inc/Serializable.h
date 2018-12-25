#ifndef __BOTME_INC_SERIALIZABLE_H
#define __BOTME_INC_SERIALIZABLE_H

class Serializable{
protected:
	Serializable();

	void serializeDouble(double);
	void serializeInt(int);
	void serializeUInt(unsigned int);
	void addSerialiable(Serializable *);

	double getDouble();
	int getInt();
	unsigned int getUInt();
	Serializable* getSerializable();

public:
	virtual void serialize() = 0;
	virtual void deserialize() = 0;

};

#endif
