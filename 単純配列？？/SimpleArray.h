#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <memory>

//not debug complete.
//this is deep copyable Array.

#define DF 1 //debug flag.

template<class T>
class SimpleArray {
public:

	typedef T ValueType;

	SimpleArray(const SimpleArray<T>& In) {//same to SimpleArrat::operator =(const SimpleArray&).
		Alloc(In.Size());
		std::copy_n(&In[0], In.Size(), P);

		if (DF) { std::cout << "Construct SimpleArray." << std::endl; }
	}
	SimpleArray(std::size_t N) {
		Alloc(N);
		if (DF) { std::cout << "Construct SimpleArray." << std::endl; }
	}
	SimpleArray(const std::initializer_list<T>& In) {
		Alloc(In.size());
		std::copy_n(In.begin(), In.size(), P);
		if (DF) { std::cout << "Construct SimpleArray." << std::endl; }
	}
	virtual ~SimpleArray() {
		DeAlloc();
		if (DF) { std::cout << "Destruct SimpleArray." << std::endl; }
	}

	bool Alloc(std::size_t N) {
		DeAlloc();
		P = new T[N]{ 0, };
		if (P) { L = N; }
		return P ? true : false;
	}
	bool DeAlloc() {
		delete[] P;
		P = nullptr;
		L = 0;
		return true;
	}
	std::size_t Size() const {
		return L;
	}
	/** /
	SimpleArray Duplicate() const{
		return *this;
	}
	/**/
	/** /
		SimpleArray Send() {
			SimpleArray<T> In;

			In.P = P;
			In.L = L;

			this->P = nullptr;
			this->L = 0;

			return In;
		}
	/**/
	const T& operator[](std::size_t Idx) const {
		if (Idx >= L) { throw std::out_of_range("OutOfRange in SimpleArray::operator[]."); }
		return P[Idx];
	}
	T& operator[](std::size_t Idx) {
		if (Idx >= L) { throw std::out_of_range("OutOfRange in SimpleArray::operator[]."); }
		return P[Idx];
	}
	const SimpleArray<T>& operator =(const SimpleArray<T>& In) {//same to SimpleArrat::SimpleArray(const SimpleArray&).
		Alloc(In.Size());
		std::copy_n(&In[0], In.Size(), P);
		return In;
	}
	T* begin() const {
		return P;
	}
	T* begin() {
		return P;
	}
	T* end() const {
		return (P + L);
	}
	T* end() {
		return (P + L);
	}

protected:
	T* P = nullptr;
	std::size_t L = 0;
};

template<class T> using SharedArray = std::shared_ptr<SimpleArray<T>>;//if you need ShallowCopy.it fit this.

template<class T>
SharedArray<T> MakeArray(const std::initializer_list<T>& In) {
	return std::make_shared<SimpleArray<T>>(In);
}

template<class T>
bool ShowArrayA(const SimpleArray<T>& In) {

	for (std::size_t i = 0; i < In.Size(); i++) {
		std::cout << In[i] << ',';
	}
	std::cout << std::endl;
	return true;
}

template<class T>
bool ShowArrayB(const SimpleArray<T>& In) {

	for (auto o : In) {
		std::cout << o << ',';
	}
	std::cout << std::endl;
	return true;
}