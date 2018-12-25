#include "Serializable.h"

void serializeDouble(double d){
	union { unsigned long long i; double d; } u;
	u.d = d;
	unsigned int st = u.i >> 32;
	unsigned int nd = (u.i << 32) >> 32;
}
