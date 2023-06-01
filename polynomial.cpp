#include "polynomial.h"

Polynomial::~Polynomial()
{
    if (derivative_ != nullptr){
        delete derivative_;
    }
}

Polynomial::Polynomial()
{
    coeffs_ = {0};
    derivative_ = nullptr;
}

Polynomial::Polynomial(const std::vector<double> & coeffs)
{
    coeffs_ = coeffs;
    derivative_ = nullptr;
}


Polynomial operator+(const Polynomial & poly0,const Polynomial& poly1)
{
    int new_size = std::max(poly0.coeffs_.size(),poly1.coeffs_.size());
    std::vector<double> res_coeffs(new_size,0);
    for (int i = 0;i < new_size;i++){
        res_coeffs[i] += poly0[i] + poly1[i];
    }
    while ((res_coeffs.back() == 0) && (res_coeffs.size()) > 1){
        res_coeffs.pop_back();
    }

    return Polynomial(res_coeffs);
}

Polynomial operator*(const Polynomial& poly0,const Polynomial & poly1)
{
    int new_deg = poly0.coeffs_.size()-1+ poly1.coeffs_.size()-1;
    std::vector<double> new_coeffs(new_deg + 1,0);
    for (int i = 0; i < poly0.coeffs_.size();i++){
        for (int j = 0;j < poly1.coeffs_.size();j++){
            new_coeffs[i+j] += poly0.coeffs_[i]*poly1.coeffs_[j];
        }
    }
    //qDebug() << "0k";
    return Polynomial(new_coeffs);
}

double Polynomial::operator[](int idx) const
{
    if (idx >= coeffs_.size()){
        return 0;
    }
    else{
        return coeffs_[idx];
    }
}




Polynomial Polynomial::derivative()
{
    if (derivative_ == nullptr){
        std::vector<double> der_coeffs;
        if (coeffs_.size() == 1){
            der_coeffs = {1};
        }
        else{
            for (int i = 1;i < coeffs_.size();i++){
                der_coeffs.push_back(i * coeffs_[i]);
            }
        }
        derivative_ = new Polynomial(der_coeffs);
    }
    return *derivative_;
}

double Polynomial::operator()(double a) const
{
    double res = 0;
    double x = 1;
    for (int i = 0;i < coeffs_.size();i++){
        res += x*coeffs_[i];
        x *= a;
    }
    return res;
}

std::vector<double> Polynomial::findRoots()
{
    double eps = 1.0/1000000.0;


    //result preparations
    std::vector<double> res;
    Polynomial poly;

    for (int i = 0;i < coeffs_.size();i++){
        if (abs(coeffs_[i]) > eps){
            //qDebug() << std::vector<double>(coeffs_.begin()+i,coeffs_.end());
            poly = Polynomial(std::vector<double>(coeffs_.begin()+i,coeffs_.end()));
            if (i > 0){
                res.push_back(0);
            }
            break;
        }
    }



    // start points
    int n = poly.coeffs_.size()-1;
    double rad = std::pow(abs(poly.coeffs_.back()/poly.coeffs_.front()),1.0/(double)n);
    //qDebug() << rad;
    double theta = 2*M_PI/(double)n;
    double c = theta/4.0;
    std::vector<std::complex<double>> old_sol;
    for (int k = 0; k < n;k++){
        old_sol.push_back(std::polar(rad,k*theta+c));
    }


    // iterating
    std::vector<std::complex<double>> new_sol = old_sol;
    for (int iter = 0;iter < 100;iter++){
        for (int k = 0;k < n;k++){
            // summing
            std::complex<double> sum = 0;
            for (int j = 0;j < n;j++){
                if (j != k){
                    sum += 1.0/(new_sol[k] - new_sol[j]);
                }
            }
            // coeff
            std::complex<double> coeff = poly(new_sol[k])/poly.derivative()(new_sol[k]);

            new_sol[k] -= coeff/(1.0 - coeff*sum);
        }
        old_sol = new_sol;
    }

    // redsulting
    for (auto sol : new_sol){
        if (abs(sol.imag()) < eps){
            res.push_back(sol.real());
        }
    }
    return res;
}

std::complex<double> Polynomial::operator()(std::complex<double> a){
    std::complex<double> res = 0;
    std::complex<double> x = 1;
    for (int i = 0;i < coeffs_.size();i++){
        res += x*coeffs_[i];
        x *= a;
    }
    return res;
}

QDebug operator<<(QDebug stream, const Polynomial &poly){
    QString res =QVariant(poly.coeffs_[0]).toString();
    for (int i = 1; i < poly.coeffs_.size();i++){
        res += " + ";
        res += QVariant(poly.coeffs_[i]).toString()+"*x";
        if (i >= 2){
            res += "^"+ QVariant(i).toString();
        }
    }

    stream << res;
    return stream;
}

Polynomial operator*(double a,const Polynomial& poly){
    std::vector<double> new_coeffs = poly.coeffs_;
    for (auto& coeff : new_coeffs){
        coeff*= a;
    }
    return Polynomial(new_coeffs);
}
