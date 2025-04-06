#include <iostream>
#include <string>
using namespace std;

class Numero {
public:
    virtual Numero* suma(Numero* otro) = 0;
    virtual Numero* resta(Numero* otro) = 0;
    virtual Numero* multiplicacion(Numero* otro) = 0;
    virtual Numero* division(Numero* otro) = 0;
    virtual string toString() = 0;
    virtual ~Numero() {}
};

class Entero : public Numero //entero es una derivada de numero.
{
private:
    int valor;

public:
    Entero(int v) {
        valor = v;
    }

    int getValor() {
        return valor;
    }

    Numero* suma(Numero* otro) override {
        Entero* otroEntero = dynamic_cast<Entero*>(otro);
        int resultado = valor + otroEntero->getValor();
        return new Entero(resultado);
    }

    Numero* resta(Numero* otro) override {
        Entero* otroEntero = dynamic_cast<Entero*>(otro);
        int resultado = valor - otroEntero->getValor();
        return new Entero(resultado);
    }

    Numero* multiplicacion(Numero* otro) override {
        Entero* otroEntero = dynamic_cast<Entero*>(otro);
        int resultado = valor * otroEntero->getValor();
        return new Entero(resultado);
    }

    Numero* division(Numero* otro) override {
        Entero* otroEntero = dynamic_cast<Entero*>(otro);
        int divisor = otroEntero->getValor();

        if (divisor == 0) {
            cout << "Error: división por cero." << endl;
            return new Entero(0);
        }

        int resultado = valor / divisor;
        return new Entero(resultado);
    }

    string toString() override {
        return to_string(valor);
    }
};

class Real : public Numero {
private:
    double valor;
public:
    Real(double v) {
        valor = v;
    }

    double getValor() {
        return valor;
    }

    Numero* suma(Numero* otro) override {
        Real* otroReal = dynamic_cast<Real*>(otro);
        double resultado = valor + otroReal->getValor();
        return new Real(resultado);
    }

    Numero* resta(Numero* otro) override {
        Real* otroReal = dynamic_cast<Real*>(otro);
        double resultado = valor - otroReal->getValor();
        return new Real(resultado);
    }

    Numero* multiplicacion(Numero* otro) override {
        Real* otroReal = dynamic_cast<Real*>(otro);
        double resultado = valor * otroReal->getValor();
        return new Real(resultado);
    }

    Numero* division(Numero* otro) override {
        Real* otroReal = dynamic_cast<Real*>(otro);
        double divisor = otroReal->getValor();

        if (divisor == 0.0) {
            cout << "Error: división por cero." << endl;
            return new Real(0.0);
        }

        double resultado = valor / divisor;
        return new Real(resultado);
    }

    string toString() override {
        return to_string(valor);
    }
};

class Complejo : public Numero {
private:
    double real;
    double imaginario;

public:
    Complejo(double r, double i) {
        real = r;
        imaginario = i;
    }

    double getReal() {
        return real;
    }

    double getImaginario() {
        return imaginario;
    }

    Numero* suma(Numero* otro) override {
        Complejo* otroComplejo = dynamic_cast<Complejo*>(otro);
        double nuevaReal = real + otroComplejo->getReal();
        double nuevoImaginario = imaginario + otroComplejo->getImaginario();
        return new Complejo(nuevaReal, nuevoImaginario);
    }

    Numero* resta(Numero* otro) override {
        Complejo* otroComplejo = dynamic_cast<Complejo*>(otro);
        double nuevaReal = real - otroComplejo->getReal();
        double nuevoImaginario = imaginario - otroComplejo->getImaginario();
        return new Complejo(nuevaReal, nuevoImaginario);
    }

    Numero* multiplicacion(Numero* otro) override {
        Complejo* otroComplejo = dynamic_cast<Complejo*>(otro);
        double nuevaReal = (real * otroComplejo->getReal()) - (imaginario * otroComplejo->getImaginario());
        double nuevoImaginario = (real * otroComplejo->getImaginario()) + (imaginario * otroComplejo->getReal());
        return new Complejo(nuevaReal, nuevoImaginario);
    }

    Numero* division(Numero* otro) override {
        Complejo* otroComplejo = dynamic_cast<Complejo*>(otro);
        double a = real;
        double b = imaginario;
        double c = otroComplejo->getReal();
        double d = otroComplejo->getImaginario();

        double denominador = c * c + d * d;

        if (denominador == 0.0) {
            cout << "Error: división por cero." << endl;
            return new Complejo(0.0, 0.0);
        }

        double nuevaReal = (a * c + b * d) / denominador;
        double nuevoImaginario = (b * c - a * d) / denominador;

        return new Complejo(nuevaReal, nuevoImaginario);
    }

    string toString() override {
        string resultado = to_string(real);
        if (imaginario >= 0) {
            resultado += "+";
        }
        resultado += to_string(imaginario) + "i";
        return resultado;
    }
};

int main() {
    //pruebo con enteros
    Entero* e1 = new Entero(10);
    Entero* e2 = new Entero(4);
    Numero* resultadoEntero = e1->suma(e2);
    cout << "Suma de enteros: " << resultadoEntero->toString() << endl;
    delete resultadoEntero;
    resultadoEntero = e1->resta(e2);
    cout << "Resta de enteros: " << resultadoEntero->toString() << endl;
    delete resultadoEntero;
    resultadoEntero = e1->multiplicacion(e2);
    cout << "Multiplicacion de enteros: " << resultadoEntero->toString() << endl;
    delete resultadoEntero;
    resultadoEntero = e1->division(e2);
    cout << "Division de enteros: " << resultadoEntero->toString() << endl;
    delete resultadoEntero;

    //pruebo con reales
    Real* r1 = new Real(5.5);
    Real* r2 = new Real(2.0);
    Numero* resultadoReal = r1->suma(r2);
    cout << "Suma de reales: " << resultadoReal->toString() << endl;
    delete resultadoReal;
    resultadoReal = r1->resta(r2);
    cout << "Resta de reales: " << resultadoReal->toString() << endl;
    delete resultadoReal;
    resultadoReal = r1->multiplicacion(r2);
    cout << "Multiplicacion de reales: " << resultadoReal->toString() << endl;
    delete resultadoReal;
    resultadoReal = r1->division(r2);
    cout << "Division de reales: " << resultadoReal->toString() << endl;
    delete resultadoReal;

    //pruebo con complejos
    Complejo* c1 = new Complejo(3, 2);
    Complejo* c2 = new Complejo(1, -1);
    Numero* resultadoComplejo = c1->suma(c2);
    cout << "Suma de complejos: " << resultadoComplejo->toString() << endl;
    delete resultadoComplejo;
    resultadoComplejo = c1->resta(c2);
    cout << "Resta de complejos: " << resultadoComplejo->toString() << endl;
    delete resultadoComplejo;
    resultadoComplejo = c1->multiplicacion(c2);
    cout << "Multiplicacion de complejos: " << resultadoComplejo->toString() << endl;
    delete resultadoComplejo;
    resultadoComplejo = c1->division(c2);
    cout << "Division de complejos: " << resultadoComplejo->toString() << endl;
    delete resultadoComplejo;
    return 0;
}
