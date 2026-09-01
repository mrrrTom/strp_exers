#include <iostream>
using namespace std;

void code(long* v, long* k) {
	unsigned long y = v[0], z = v[1], sum = 0,
		delta = 0x9e3779b9,
		n = 32;
	while (n-- > 0) {
		sum += delta;
		y += ((z<<4)+k[0])^(z+sum)^((z>>5)+k[1]);
		z += ((y<<4)+k[2])^(y+sum)^((y>>5)+k[3]);
		v[0]=y;
		v[1]=z;
	}
}

void decode(long* v, long*k) {
	unsigned long y = v[0], z = v[1], sum,
		delta = 0x9e3779b9,
		n = 32;
	sum = delta<<5;
	while (n-- > 0) {
		z -= ((y<<4)+k[2])^(y+sum)^((y>>5)+k[3]);
		y -= ((z<<4)+k[0])^(z+sum)^((z>>5)+k[1]);
		sum -= delta;
		v[0]=y;
		v[1]=z;
	}
}
int main (int argc, char *argv[]) {
	long int v [2] { 1, 2};
	long int k [4] { 1, 2, 3, 4};
	cout << "v0: " << v[0] << " v1: " << v[1] << endl;
	code(v, k);
	cout << "coded: " << v[0] << " " << v[1] << endl;
	decode(v, k);
	cout << "decoded: " << v[0] << " " << v[1] << endl;
	return 0;
}
