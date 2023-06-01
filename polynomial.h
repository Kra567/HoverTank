#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>
#include <optional>
#include <QDataStream>
#include <string>
#include <QVariant>
#include <qvariant.h>
#include <complex>

class Polynomial{
private:
    std::vector<double> coeffs_;
    Polynomial* derivative_;
public:
    ~Polynomial();
    Polynomial();
    Polynomial(const std::vector<double>&);
    friend Polynomial operator+(const Polynomial&,const Polynomial&);
    friend Polynomial operator*(const Polynomial&,const Polynomial&);
    double operator[](int) const;
    friend Polynomial operator*(double,const Polynomial&);
    Polynomial derivative();
    std::complex<double> operator()(std::complex<double>);
    double operator()(double) const;

    std::vector<double> findRoots();
    friend QDebug operator<<(QDebug,const Polynomial &point);

};

#endif //POLYNOMIAL_H
