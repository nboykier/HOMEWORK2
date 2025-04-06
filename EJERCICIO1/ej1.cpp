#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Reloj {
public:
    int horas;
    int minutos;
    int segundos;
    string tarde_manana;

    Reloj() {
        horas = 0;
        minutos = 0;
        segundos = 0;
        tarde_manana = "a.m.";
    }

    Reloj(int h) {
        if (h >= 0 && h <= 23) {
            horas = h;
            minutos = 0;
            segundos = 0;
            tarde_manana = (h < 12) ? "a.m." : "p.m."; //si es menor se asigna el primero, si es mayor o igual va a pm.
        } else {
            cout << "HORA INVALIDA" << endl;
            horas = minutos = segundos = 0;
            tarde_manana = "a.m.";
        }
    }

    Reloj(int h, int m) {
        if (h >= 0 && h <= 23 && m >= 0 && m <= 59) {
            horas = h;
            minutos = m;
            segundos = 0;
            tarde_manana = (h < 12) ? "a.m." : "p.m.";
        } else {
            cout << "HORA O MINUTO INVALIDO" << endl;
            horas = minutos = segundos = 0;
            tarde_manana = "a.m.";
        }
    }


    Reloj(int h, int m, int s) {
        if (h >= 0 && h <= 23 && m >= 0 && m <= 59 && s >= 0 && s <= 59) {
            horas = h;
            minutos = m;
            segundos = s;
            tarde_manana = (h < 12) ? "a.m." : "p.m.";
        } else {
            cout << "HORA, MINUTO O SEGUNDO INVALIDO" << endl;
            horas = minutos = segundos = 0;
            tarde_manana = "a.m.";
        }
    }

    Reloj(int h, int m, int s, string p_a) {
        if (h >= 0 && h <= 23 && m >= 0 && m <= 59 && s >= 0 && s <= 59 &&
            (p_a == "a.m." || p_a == "p.m.")) {
            horas = h;
            minutos = m;
            segundos = s;
            tarde_manana = p_a;
        } else {
            cout << "HORA, MINUTO, SEGUNDO O FORMATO INVALIDO" << endl;
            horas = minutos = segundos = 0;
            tarde_manana = "a.m.";
        }
    }

    void setHoras(int h) {
        if (h >= 0 && h <= 23) {
            horas = h;
            tarde_manana = (h < 12) ? "a.m." : "p.m.";
        } else {
            cout << "HORA INVALIDA" << endl;
        }
    }

    void setMinutos(int m) {
        if (m >= 0 && m <= 59) {
            minutos = m;
        } else {
            cout << "MINUTO INVALIDO" << endl;
        }
    }

    void setSegundos(int s) {
        if (s >= 0 && s <= 59) {
            segundos = s;
        } else {
            cout << "SEGUNDO INVALIDO" << endl;
        }
    }

    void setTardeManana(string p_a) {
        if (p_a == "a.m." || p_a == "p.m.") {
            tarde_manana = p_a;
        } else {
            cout << "Formato invalido (Debe ser 'a.m.' o 'p.m.')" << endl;
        }
    }

    int getHoras(){ 
        return horas;
    }
    int getMinutos(){
        return minutos;
    }
    int getSegundos(){
        return segundos;
    }
    string getTardeManana(){
        return tarde_manana;
    }

    void mostrar24Horas() {
        cout << setw(2) << setfill('0') << horas << ":"
             << setw(2) << setfill('0') << minutos << ":"
             << setw(2) << setfill('0') << segundos << endl;
    }

    void mostrarHorario() {
        int h = horas;
        string am_pm = tarde_manana;

        if (h>12)
        {
            h -= 12;
        }
        
        cout << setw(2) << setfill('0') << h << "h:"
             << setw(2) << setfill('0') << minutos << "m:"
             << setw(2) << setfill('0') << segundos << "s "
             << am_pm << endl;
    }
};

int main() {
    int opcion;
    int h, m, s;
    string am_pm;
    Reloj reloj;

    while (true) {
        cout << "\nMenú de opciones:\n";
        cout << "0. Iniciar sin parametros\n";
        cout << "1. Ingresar solo hora\n";
        cout << "2. Ingresar hora y minutos\n";
        cout << "3. Ingresar hora, minutos y segundos\n";
        cout << "4. Ingresar hora, minutos, segundos y a.m. o p.m.\n";
        cout << "5. Cambiar valores\n";
        cout << "6. Mostrar hora en formato 24 horas\n";
        cout << "7. Mostrar hora en formato con am o pm\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 0:
                reloj = Reloj();
                cout << "Reloj iniciado sin paraemtros: ";
                reloj.mostrarHorario();
                break;
            case 1:
                cout << "Ingrese hora: ";
                cin >> h;
                reloj = Reloj(h);
                reloj.mostrarHorario();
                break;
            case 2:
                cout << "Ingrese hora: ";
                cin >> h;
                cout << "Ingrese minutos: ";
                cin >> m;
                reloj = Reloj(h, m);
                reloj.mostrarHorario();
                break;
            case 3:
                cout << "Ingrese hora: ";
                cin >> h;
                cout << "Ingrese minutos: ";
                cin >> m;
                cout << "Ingrese segundos: ";
                cin >> s;
                reloj = Reloj(h, m, s);
                reloj.mostrarHorario();
                break;
            case 4:
                cout << "Ingrese hora: ";
                cin >> h;
                cout << "Ingrese minutos: ";
                cin >> m;
                cout << "Ingrese segundos: ";
                cin >> s;
                cout << "Ingrese a.m. o p.m.: ";
                cin >> am_pm;
                reloj = Reloj(h, m, s, am_pm);
                reloj.mostrarHorario();
                break;
            case 5:
                cout << "Ingrese hora: ";
                cin >> h;
                reloj.setHoras(h);
                cout << "Ingrese minutos: ";
                cin >> m;
                reloj.setMinutos(m);
                cout << "Ingrese segundos: ";
                cin >> s;
                reloj.setSegundos(s);
                cout << "Ingrese a.m./p.m.: ";
                cin >> am_pm;
                reloj.setTardeManana(am_pm);
                reloj.mostrarHorario();
                break;
            case 6:
                reloj.mostrar24Horas();
                break;
            case 7:
                reloj.mostrarHorario();
                break;
            case 8:
                return 0;
            default:
                cout << "Opción inválida." << endl;
        }
    }
}
