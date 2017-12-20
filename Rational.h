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

	//friend std::istream& operator>>(std::istream & cin, Rational<Tint> R)
	//{
	//	

	//	return cin;
	//}

	Rational() : nom(0), denom(1) {}
	Rational(Tint P) : nom(P), denom(1) {}
	Rational(Tint P, Tint Q) : nom(P), denom(Q)
	{
		if (Q < 0) { Q = -Q; P = -P; } //Keeping Q positive
		Reduce(P, Q);
	}

	template <class T>
	Rational(Rational<T> rhs)
	{
		nom = rhs.nom;
		denom = rhs.denom;
	}

	~Rational() = default;



	//Might want to allocate memory here?
	template <class T>
	Rational& operator+=(const Rational<T>& rhs) const
	{
		Rational temp = Rational((nom*rhs.denom + denom*rhs.nom), denom*rhs.denom);
		Reduce(temp.nom, temp.denom);
		return temp;
	}

	//template <class T>
	//Rational& operator+=(const Tint& rhs) const
	//{
	//	return (this += Ratioanl(rhs));
	//}

	//Rational operator+=(const Tint& rhs) const
	//{
	//	Rational temp = Rational(rhs);
	//	return (this += temp);
	//}

	template<class T>
	Rational operator+(const Rational<T>& rhs) const { return (this += rhs); }

	//Rational operator+(const Tint& rhs) const
	//{
	//	Rational temp = Rational(rhs);
	//	//operator+= reduces this so don't have to worry about it
	//	return (this += temp);
	//}

	template<class T>
	bool operator==(const Rational<T> rhs) const //No changes so method is constant
	{
		return (nom == rhs.nom && denom == rhs.denom);
	}

	//bool operator==(const Tint& rhs) const
	//{
	//	if ((nom / denom) == rhs)
	//		return true;
	//	else
	//		return false;
	//}

	operator Tint() const
	{
		return nom / denom;
	}

	Rational& operator++()
	{
		nom += denom;
		Reduce(nom, denom);
		return *this;
	}

	Rational operator++(int rhs)
	{
		Tint old = nom;
		nom += denom;
		Rational temp = Rational(old, denom);
		Reduce(nom, denom);
		return temp;
	}



	Rational& operator-() { nom = -nom; }


};

