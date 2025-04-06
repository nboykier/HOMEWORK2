#include <iostream>
#include <string>
using namespace std;

class CuentaBanco {
//protected para permitir acceso y uso desde subclases y no desde afuera.
protected:
    double balance;
    string titularCuenta;

public://public para poder usar desde fuera de la clase.
    CuentaBanco(string nombreTitular, double saldoInicial) {
        titularCuenta = nombreTitular;
        balance = saldoInicial;
    }

    void depositar(double cantidad) {
        if (cantidad > 0) {
            balance = balance + cantidad;
        }
    }
    //metodos virtuales que deben implementarse en las subclases.
    virtual void retirar(double cantidad) = 0;
    virtual void mostrarInfo() = 0;

    virtual ~CuentaBanco() {}
};

class CuentaCorriente;
class CajaDeAhorro : public CuentaBanco {
private://lo dejo en privado ya que es la unica clase que va a chequear la cantidad de consultas y usarlo.
    int cantidadConsultas;
public:
    CajaDeAhorro(string nombreTitular, double saldoInicial)
        : CuentaBanco(nombreTitular, saldoInicial) {
        cantidadConsultas = 0;
    }

    void retirar(double cantidad) override {
        if (cantidad > balance) {
            cout << "No se puede retirar más dinero del que hay en la cuenta de ahorro." << endl;
        } else {
            balance = balance - cantidad;
        }
    }

    void mostrarInfo() override {
        cout << "Tipo de cuenta: Caja de Ahorro" << endl;
        cout << "Titular: " << titularCuenta << endl;
        cout << "Balance: $" << balance << endl;

        cantidadConsultas = cantidadConsultas + 1;

        if (cantidadConsultas > 2) {
            balance = balance - 20.0;
            cout << "Se ha descontado $20 por exceso de consultas." << endl;
        }
    }

    //uso friend para permitir acceso a CuentaCorriente.
    friend class CuentaCorriente;
};

class CuentaCorriente : public CuentaBanco {
private:
    CajaDeAhorro* cajaAhorro;

public:
    CuentaCorriente(string nombreTitular, double saldoInicial, CajaDeAhorro* caja)
        : CuentaBanco(nombreTitular, saldoInicial) {
        //llamo al constructor de cuentabanco antes porque mi clase cuentacorriente hereda desde cuentabanco. 
        cajaAhorro = caja;
    }

    void retirar(double cantidad) override {
        if (cantidad <= balance) {
            balance = balance - cantidad;
        } else {
            double faltante = cantidad - balance;

            if (cajaAhorro->balance >= faltante) {
                cout << "Usando fondos de la Caja de Ahorro para completar el retiro." << endl;
                cajaAhorro->balance = cajaAhorro->balance - faltante;
                balance = 0.0;
            } else {
                cout << "No hay fondos suficientes ni en la cuenta corriente ni en la caja de ahorro." << endl;
            }
        }
    }

    void mostrarInfo() override {
        cout << "Tipo de cuenta: Cuenta Corriente" << endl;
        cout << "Titular: " << titularCuenta << endl;
        cout << "Balance: $" << balance << endl;
    }
};

int main() {
    //creo caja de ahorro con $50 para juan perez.
    CajaDeAhorro* caja = new CajaDeAhorro("Juan Perez", 100.0);

    //creo cuenta corriente con $50 de juan perez.
    CuentaCorriente* corriente = new CuentaCorriente("Juan Perez", 50.0, caja);

    //muestro info de caja de ahorro varias veces.
    for (int i = 0; i < 4; i++) {
        cout << "Consulta " << (i + 1) << " a Caja de Ahorro:" << endl;
        caja->mostrarInfo();
        cout << endl;
    }

    //pruebo retiro cuando no es suficiente con cuenta.
    cout << "Intentando retirar $70 de Cuenta Corriente" << endl;
    corriente->retirar(70.0);
    corriente->mostrarInfo();
    caja->mostrarInfo();
    cout << endl;

    //pruebo un retiro cuando no hay en ninguna.
    cout << "Intentando retirar $100 de Cuenta Corriente" << endl;
    corriente->retirar(100.0);
    corriente->mostrarInfo();
    caja->mostrarInfo();
    return 0;
}
