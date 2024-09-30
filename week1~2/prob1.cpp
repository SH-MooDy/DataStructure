#include<iostream>
#include<cmath>
using namespace std;

int main() {
	int* n = new int;
	cin >> *n;

	int* arr = new int[*n];
	for (int* i = arr; i < arr + *n; i++) {
		cin >> *i;
	}

	//최대최소값
	int* min = arr, * max = arr; // 최대 최솟값을 구할때 min, max 변수 초기설정 신경쓰기
	for (int* i = arr; i < arr + *n; i++) {
		if (*i < *min) { min = i; }
		if (*i > *max) { max = i; }
	}

	//평균값
	double* avg = new double;
	*avg = 0.0;
	for (int* i = arr; i < arr + *n; i++) {
		*avg += *i;
	}
	*avg /= *n;

	//표준편차
	double* variance = new double;
	*variance = 0.0;
	for (int* i = arr; i < arr + *n; i++) {
		*variance += pow(*i - *avg, 2);
	}
	*variance /= *n;
	double* stdDeviation = new double;
	*stdDeviation = sqrt(*variance);

	cout << *min << " " << *max << " " << *avg << " " << *stdDeviation << endl;
	delete n;
	delete[] arr;
	delete avg;
	delete variance;
	delete stdDeviation;
	return 0;
}