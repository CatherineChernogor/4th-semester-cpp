#pragma once
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;

template<class T> class Complex {

public:

	T re;
	T im;

	Complex();
	Complex(T _re, T _im);
	Complex(const Complex<T>& n);

	//~Complex();

	Complex<T>& operator =(const Complex<T>& n);
	Complex<T>& operator +=(const Complex<T>& n);
	Complex<T> operator +(const Complex<T>& n) const;
	Complex<T>& operator -=(const Complex<T>& n);
	Complex<T> operator -(const Complex<T>& n) const;
	Complex<T> operator *(const Complex<T>& n) const;
	Complex<T> operator /(const Complex<T>& n) const;

	Complex<T> pow(int p);
	double module();
	double phase();

	template <class> friend ostream& operator <<(ostream& out, Complex<T>& n);
};

template <class T> Complex<T>::Complex() {
	this->re = 0;
	this->im = 0;
}
template <class T> Complex<T>::Complex(T _re, T _im) {
	this->re = _re;
	this->im = _im;
}
template <class T> Complex<T>::Complex(const Complex<T>& n) {
	this->re = n.re;
	this->im = n.im;
}

template <class T> Complex<T>& Complex<T>::operator =(const Complex<T>& n) {
	this->re = n.re;
	this->im = n.im;
	return *this;
}
template <class T> Complex<T>& Complex<T>::operator +=(const Complex<T>& n) {
	this->re += n.re;
	this->im += n.im;
	return *this;
}
template <class T> Complex<T> Complex<T>::operator +(const Complex<T>& n) const {
	Complex<T> res(*this);
	return res += n;
}
template <class T> Complex<T>& Complex<T>::operator -=(const Complex<T>& n) {
	this->re -= n.re;
	this->im -= n.im;
	return *this;
}
template <class T> Complex<T> Complex<T>::operator -(const Complex<T>& n) const {
	Complex<T> res(*this);
	return res -= n;
}
template <class T> Complex<T> Complex<T>::operator *(const Complex<T>& n) const {
	Complex<T> res;
	res.re = (this->re * n.re) - (this->im * n.im);
	res.im = (this->re * n.im) + (this->im * n.re);
	return res;
}
template <class T> Complex<T> Complex<T>::operator /(const Complex<T>& n) const {
	Complex<T> res;
	double conjugate = n.re * n.re + n.im * n.im;
	res.re = (this->re * n.re + this->im * n.im) / conjugate;
	res.im = (n.re * this->im - this->re * n.im) / conjugate;
	return res;
}
template <class T> ostream& operator <<(ostream& out, Complex<T>& n) {
	if (n.re) out << n.re;
	else out << 0;

	if (n.im >= 0) out << '+';

	out << n.im << 'i';

	return out;
}

template <class T> Complex<T> Complex<T>::pow(int deg) {

	if (deg == 0) {
		return Complex(1, 0);
	}
	else {
		Complex<T> res(*this);
		for (int i = 1; i < deg; i++) {
			res = res * *this;
		}
		return res;
	}
}

template <class T> double Complex<T>::module() {
	return sqrt(this->re * this->re + this->im * this->im);
}
template <class T> double Complex<T>::phase() {
	return 180 * atan(this->im / this->re) / PI;
}