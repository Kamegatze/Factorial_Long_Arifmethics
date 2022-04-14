#include "pch.h"
#include "MathFactorial.h"
#include <vector>
#include <cstring>
#include <wchar.h>
#include <mutex>

constexpr int base = 10;
// lenght of the long number for which naive multiplication
// will be called in the Karatsuba function
constexpr unsigned int len_f_naive = 64;
// One digit size for numbers with bases multiple of ten
//constexpr int dig_size = 10;
// How much zeroes have to be in the number
//constexpr int add_zero = base / dig_size;

namespace MathFactorial {

    vector<long long> AddZero(vector<long long> a, vector<long long> b)
    {
        if (a.size() > b.size())
        {
            vector<long long> MassA(a.size());
            for (int i = a.size() - b.size(), j = 0; i < a.size(); i++, j++)
            {
                MassA.at(i) = b.at(j);
            }
            return MassA;
        }
        else
        {
            vector<long long> MassA(b.size());
            for (int i = b.size() - a.size(), j = 0; i < b.size(); i++, j++)
            {
                MassA.at(i) = a.at(j);
            }
            return MassA;
        }
    }

    CString ConvertVectorToString(vector<char> a)
    {
        wchar_t* res = new wchar_t[a.size()];
        memset(res, 0, sizeof(wchar_t) * a.size());
        for (auto i = 0; i < a.size(); i++)
        {
            res[i] = a[i];
        }
        return res;
    }

    vector<long long> TruncationOfZeros(vector<long long> a)
    {
        auto flag = 0;
        for (auto i = 0; i < size(a); i++)
        {
            if (a.at(i) == 0)
            {
                flag++;
            }
            else
            {
                break;
            }
        }
        vector<long long> mass(size(a) - flag);
        for (auto i = 0; i < size(mass); i++)
        {
            mass.at(i) = a.at(flag);
            flag++;
        }
        return mass;
    }

    void extend_vec(vector<long long>& v, size_t len)
    {
        while (len & (len - 1)) {
            ++len;
        }
        v.resize(len);
    }

    long long ConvertionFromSimbolToNumber(wchar_t a)
    {
        if (a == '0')
            return 0;
        else if (a == '1')
            return 1;
        else if (a == '2')
            return 2;
        else if (a == '3')
            return 3;
        else if (a == '4')
            return 4;
        else if (a == '5')
            return 5;
        else if (a == '6')
            return 6;
        else if (a == '7')
            return 7;
        else if (a == '8')
            return 8;
        else if (a == '9')
            return 9;
    }

    wchar_t ConvertionFromNumberToSimbol(long long a)
    {
        if (a == 0)
            return wchar_t('0');
        else if (a == 1)
            return wchar_t('1');
        else if (a == 2)
            return wchar_t('2');
        else if (a == 3)
            return wchar_t('3');
        else if (a == 4)
            return wchar_t('4');
        else if (a == 5)
            return wchar_t('5');
        else if (a == 6)
            return wchar_t('6');
        else if (a == 7)
            return wchar_t('7');
        else if (a == 8)
            return wchar_t('8');
        else if (a == 9)
            return wchar_t('9');
    }

    vector<long long> ConvertFromMassSimbolToMassValue(CString a)
    {
        vector<long long>mass(a.GetLength(), 0);
        for (int i = 0; i < a.GetLength(); i++)
        {
            mass[i] = ConvertionFromSimbolToNumber(a[i]);
        }
        mass = TruncationOfZeros(mass);
        return mass;
    }

    CString ConvertFromMassValueToMassSimbol(vector<long long> a)
    {
        vector<char>mass(a.size() + 1, 0);
        for (int i = 0; i < a.size(); i++)
        {
            mass[i] = ConvertionFromNumberToSimbol(a[i]);
        }
        char temp;
        mass[a.size()] = '\0';
        CString res = ConvertVectorToString(mass);
        return res;
    }

    vector<long long> naive_mul(const vector<long long>& x, const vector<long long>& y)
    {
        auto len = x.size();
        vector<long long> res(2 * len);
        for (auto i = 0; i < len; ++i) {
            for (auto j = 0; j < len; ++j) {
                res[i + j] += x[i] * y[j];
            }
        }
        return res;
    }

    vector<long long> finalize(vector<long long>& res)
    {
        for (auto i = 0; i < res.size() - 1; ++i) {
            res[i + 1] += res[i] / base;
            res[i] = res[i] % base;
        }
        return res;
    }

    vector<long long> karatsuba_mul(vector<long long>& x, vector<long long>& y)
    {
        auto n = max(x.size(), y.size());
        extend_vec(x, n);
        extend_vec(y, n);

        auto len = x.size();
        vector<long long> res(2 * len);
        if (len <= len_f_naive) {
            return naive_mul(x, y);
        }

        auto k = len / 2;

        vector<long long> Xr{ x.begin(), x.begin() + k };
        vector<long long> Xl{ x.begin() + k, x.end() };
        vector<long long> Yr{ y.begin(), y.begin() + k };
        vector<long long> Yl{ y.begin() + k, y.end() };

        vector<long long> P1 = karatsuba_mul(Xl, Yl);
        vector<long long> P2 = karatsuba_mul(Xr, Yr);

        vector<long long> Xlr(k);
        vector<long long> Ylr(k);

        for (auto i = 0; i < k; ++i) {
            Xlr[i] = Xl[i] + Xr[i];
            Ylr[i] = Yl[i] + Yr[i];
        }

        vector<long long> P3 = karatsuba_mul(Xlr, Ylr);

        // Вычитание переменной С из суммы А и B
        for (auto i = 0; i < len; ++i) {
            P3[i] -= P2[i] + P1[i];
        }
        // в res положили B
        for (auto i = 0; i < len; ++i) {
            res[i] = P2[i];
        }
        // возведение в степень А * base^2
        for (auto i = len; i < 2 * len; ++i) {
            res[i] = P1[i - len];
        }
        // Умножение С*base и сложение с res
        for (auto i = k; i < len + k; ++i) {
            res[i] += P3[i - k];
        }
        return res;
    }

    vector<long long> Addtion(vector<long long> a, vector<long long> b)
    {
        if (a.size() == 0 && b.size() != 0) {
            return b;
        }
        else if (a.size() != 0 && b.size() == 0) {
            return a;
        }
        else if (a.size() == 0 && b.size() == 0) {
            vector<long long> res(1, 0);
            return res;
        }
        char carry = 0;
        vector<long long>MassC(size(a) * size(b) + size(a), 0);
        vector<long long> MassA(size(a) + size(b));
        vector<long long> MassB(size(b) + size(a));
        if (size(b) > size(a))
        {
            /*a = ReverseVector(a);
            b = ReverseVector(b);*/
            vector<long long> c = a;
            auto iter = a.begin();
            for (auto i = 0; i < size(a); i++)
            {
                MassA.at(i) = *iter;
                iter++;
            }
            iter = b.begin();
            for (auto i = 0; i < size(b); i++)
            {
                MassB.at(i) = *iter;
                iter++;
            }
        }
        else if (size(b) < size(a))
        {
            /*a = ReverseVector(a);
            b = ReverseVector(b);*/
            auto iter = a.begin();
            for (auto i = 0; i < size(a); i++)
            {
                MassA.at(i) = *iter;
                iter++;
            }
            iter = b.begin();
            for (auto i = 0; i < size(b); i++)
            {
                MassB.at(i) = *iter;
                iter++;
            }
        }
        else
        {
            /*a = ReverseVector(a);
            b = ReverseVector(b);*/
            auto iter = a.begin();
            for (auto i = 0; i < size(a); i++)
            {
                MassA.at(i) = *iter;
                iter++;
            }
            iter = b.begin();
            for (auto i = 0; i < size(b); i++)
            {
                MassB.at(i) = *iter;
                iter++;
            }
        }
        for (int i = 0; i < size(MassA); i++)
        {
            MassC[i] = MassA[i] + MassB[i] + carry;
            carry = MassC[i] / 10;
            MassC[i] = MassC[i] % 10;
        }
        reverse(MassC.begin(), MassC.end());
        MassC = TruncationOfZeros(MassC);
        reverse(MassC.begin(), MassC.end());
        return MassC;
    }

    long long ConvertFromVectorToInt(vector<long long> a) {
        reverse(a.begin(), a.end());
        long long Number = 0;
        long long temp = 1;
        for (int i = 0; i < a.size(); i++) {
            Number += a.at(i) * temp;
            temp *= 10;
        }
        return Number;
    }

    vector<long long> ConvertFromIntToVector(long long a) {
        vector <long long> vec;
        long long size = 0;
        long long temp = 1;
        for (int i = 0; i >= 0; i++) {
            if (a / temp == 0) {
                size = i;
                break;
            }
            temp *= 10;
        }
        long long Number = a;
        int Digits = 0;
        temp = 10;
        //temp = (long)(pow(10, (size / 2)));
        for (int i = 0; i < size; i++) {
            Digits = Number % temp;
            vec.push_back(Digits);
            Number -= Digits;
            Number /= temp;
        }
        reverse(vec.begin(), vec.end());
        return vec;
    }

    vector<long long> factorialTwoHalf(vector<long long> begin, vector<long long> end) {
        reverse(begin.begin(), begin.end());
        vector<long long> res(pow(end.size(), end.size()), 0);
        res.at(0) = 1;
        vector<long long> count = begin;
        vector<long long> one(1, 1);
        while (true) {
            res = karatsuba_mul(res, count);
            finalize(res);
            reverse(res.begin(), res.end());
            res = TruncationOfZeros(res);
            reverse(res.begin(), res.end());

            reverse(count.begin(), count.end());
            count = TruncationOfZeros(count);
            if (count == end) {
                break;
            }
            reverse(count.begin(), count.end());
            count = Addtion(count, one);
        }
        reverse(res.begin(), res.end());
        res = TruncationOfZeros(res);
        reverse(res.begin(), res.end());
        return res;
    }

    vector<long long> factorial(vector<long long> a) {
        if (a.size() < 3 && ConvertFromVectorToInt(a) != 0 && a.at(0) != 45) {
            reverse(a.begin(), a.end());
            vector<long long> res(pow(a.size(), a.size()), 0);
            res.at(0) = 1;
            vector<long long> count(a.size(), 0);
            count.at(0) = 1;
            vector<long long> one(1, 1);
            while (true) {
                res = karatsuba_mul(res, count);
                finalize(res);
                reverse(res.begin(), res.end());
                res = TruncationOfZeros(res);
                reverse(res.begin(), res.end());

                reverse(count.begin(), count.end());
                count = TruncationOfZeros(count);
                reverse(count.begin(), count.end());
                if (count == a) {
                    break;
                }
                count = Addtion(count, one);
            }
            reverse(res.begin(), res.end());
            res = TruncationOfZeros(res);
            return res;
        }
        else if (ConvertFromVectorToInt(a) == 0) {
            vector<long long> one{ 1 };
            return one;
        }
        else if(a.at(0) == 45) {
            vector<long long> res{ 0 };
            return res;
        }
        else {
            long long NumberEnd = ConvertFromVectorToInt(a);
            long long NumberHalf = NumberEnd / 2; //50
            long long NumberOneHalfEnd = NumberHalf / 2; // 25
            long long NumberOneBeginOtherHalf = NumberOneHalfEnd + 1; // 26
            long long NumberTwoBeginOtherHalf = NumberHalf + 1; // 51
            long long NumberHalfEnd = NumberHalf + NumberOneHalfEnd; // 75
            long long NumberThreeBeginOtherHalf = NumberHalfEnd + 1; // 76

            vector<long long> numberHalf = ConvertFromIntToVector(NumberHalf); // 50
            vector<long long> numberTwoBeginOtherHalf = ConvertFromIntToVector(NumberTwoBeginOtherHalf); // 51
            vector<long long> numberOneHalfEnd = ConvertFromIntToVector(NumberOneHalfEnd);// 25
            vector<long long> numberOneBeginOtherHalf = ConvertFromIntToVector(NumberOneBeginOtherHalf); //26
            vector<long long> numberHalfEnd = ConvertFromIntToVector(NumberHalfEnd); // 75
            vector<long long> numberThreeBeginOtherHalf = ConvertFromIntToVector(NumberThreeBeginOtherHalf);//76

            std::mutex Mutex;
            vector<long long> resOneHalf;
            thread thOne([&resOneHalf, &numberHalf, &numberOneBeginOtherHalf, &Mutex]() {
                Mutex.lock();
                resOneHalf = factorialTwoHalf(numberOneBeginOtherHalf, numberHalf);
                Mutex.unlock();
            });

            vector <long long> resTwoHalf;
            thread thTwo([&resTwoHalf, &numberTwoBeginOtherHalf, &numberHalfEnd, &Mutex]() {
                Mutex.lock();
                resTwoHalf = factorialTwoHalf(numberTwoBeginOtherHalf, numberHalfEnd);
                Mutex.unlock();
            });

            vector <long long> resThreeHalf;
            thread thThree([&resThreeHalf, &numberThreeBeginOtherHalf, &a, &Mutex]() {
                Mutex.lock();
                resThreeHalf = factorialTwoHalf(numberThreeBeginOtherHalf, a);
                Mutex.unlock();
            });

            vector<long long> res(pow(numberOneHalfEnd.size(), numberOneHalfEnd.size()), 0);
            res.at(0) = 1;
            vector<long long> count(numberOneHalfEnd.size(), 0);
            count.at(0) = 1;
            vector<long long> one(1, 1);
            while (true) {
                res = karatsuba_mul(res, count);
                finalize(res);
                reverse(res.begin(), res.end());
                res = TruncationOfZeros(res);
                reverse(res.begin(), res.end());

                reverse(count.begin(), count.end());
                count = TruncationOfZeros(count);
                if (count == numberOneHalfEnd) {
                    break;
                }
                reverse(count.begin(), count.end());
                count = Addtion(count, one);
            }
            reverse(res.begin(), res.end());
            res = TruncationOfZeros(res);
            reverse(res.begin(), res.end());

            thOne.join();
            thTwo.join();
            thThree.join();

            res = karatsuba_mul(res, resOneHalf);
            finalize(res);

            res = karatsuba_mul(res, resTwoHalf);
            finalize(res);

            res = karatsuba_mul(res, resThreeHalf);
            finalize(res);

            reverse(res.begin(), res.end());
            res = TruncationOfZeros(res);
            return res;
        }
    }
}