#include <vector>
#include <cstring>
#include <wchar.h>
#include <xatomic.h>
#include <string>
#include <thread>
#pragma once

using namespace std;

namespace MathFactorial {
	vector<long long> AddZero(vector<long long> a, vector<long long> b);
	CString ConvertVectorToString(vector<char>a);
	vector<long long> TruncationOfZeros(vector<long long> a);
	void extend_vec(vector<long long>& v, size_t len);
	long long ConvertionFromSimbolToNumber(wchar_t a);
	wchar_t ConvertionFromNumberToSimbol(long long a);
	vector<long long> ConvertFromMassSimbolToMassValue(CString a);
	CString ConvertFromMassValueToMassSimbol(vector<long long>a);
	vector<long long> naive_mul(const vector<long long>& x, const vector<long long>& y);
	vector<long long> finalize(vector<long long>& res);
	vector<long long> karatsuba_mul(vector<long long>& x, vector<long long>& y);
	vector<long long> Addtion(vector<long long> a, vector<long long> b);
	long long ConvertFromVectorToInt(vector<long long> a);
    vector<long long> ConvertFromIntToVector(long long a);
    vector<long long> factorialTwoHalf(vector<long long> begin, vector<long long> end);
    vector<long long> factorial(vector<long long> a);
      
}