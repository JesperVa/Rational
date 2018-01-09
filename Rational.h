#pragma once
#include <iostream>
#include "GCD.h"
#include <climits>

template<typename Tint>
class Rational
{
public:
	Tint nom, denom;
	friend std::ostream& operator<<(std::ostream & cout, Rational<Tint> R)
	{
		cout << R.nom << '/' << R.denom;
		return cout;
	}

	friend std::istream& operator>>(std::istream& lhs, Rational<Tint>& rhs)
	{
		lhs >> rhs.nom;
		lhs >> rhs.denom;
		return lhs;
	}

	Rational() : nom(0), denom(1) {}
	Rational(Tint P) : nom(P), denom(1) {}
	Rational(Tint P, Tint Q) : nom(P), denom(Q)
	{
		if (Q < 0) { Q = -Q; P = -P; } //Keeping Q positive
		Reduce(P, Q);
	}

	template <class T>
	Rational(const Rational<T>& rhs)
	{
		nom = rhs.nom;
		denom = rhs.denom;
	}

	~Rational() = default;

	//Might want to allocate memory here?
	template <class T>
	Rational<Tint>& operator+=(const Rational<T>& rhs)
	{
		*this = Rational<Tint>((nom*rhs.denom + denom*rhs.nom), denom*rhs.denom);
		Reduce(nom, denom);
		return *this;
	}

	template <class T>
	Rational<Tint>& operator+=(const T& rhs) 
	{
		Rational<T> temp = Rational<T>(rhs);
		return (*this += temp);
	}

	template<class T>
	Rational<Tint> operator+(Rational<T>& rhs) const { return (Rational(nom, denom) += rhs); }

	template<class T>
	Rational<Tint> operator+(T& rhs) const { return (Rational(nom, denom) += rhs); }

	template<class T>
	bool operator==(const Rational<T> rhs) const //No changes so method is constant
	{
		auto t1 = nom / denom;
		auto t2 = rhs.nom / rhs.denom;
		return t1 == t2;
	}

	operator Tint() const
	{
		return nom / denom;
	}

	Rational<Tint>& operator++()
	{
		nom += denom;
		Reduce(nom, denom);
		return *this;
	}

	Rational<Tint> operator++(int rhs)
	{
		Tint old = nom;
		nom += denom;
		Rational temp = Rational(old, denom);
		Reduce(nom, denom);
		return temp;
	}

	Rational<Tint>& operator-() { nom = -1 * nom; return *this; }
};

