#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Estudiante {
private:
    string nombre;  
    int legajo;  
    vector<pair<string, float>> cursos;//uso esto para que un vector sean pares de distintos tipos.
public:
    Estudiante(string nombre, int legajo){
        this->nombre = nombre;
        this->legajo = legajo;
    };
    
    string obtenerNombre() const {
        return nombre;
    }

    int obtenerLegajo() const {
        return legajo;
    }

    void agregarCursos() {
        string respuesta;
        string curso;
        float nota;

        do {
            //uso do-while para que si o si el alumno tenga al menos un curso enlistado.
            cout << "Ingresar nombre del curso/materia: ";
            cin.ignore();
            getline(cin, curso);

            cout << "Ingresar la nota final: ";
            cin >> nota;
            cin.ignore();

            //agrego a la lista de cursos.
            cursos.push_back(make_pair(curso, nota));

            cout << "Quiere ingresar otro curso?: ";
            getline(cin, respuesta);
        } while (respuesta == "si" || respuesta == "Si" || respuesta == "SI" || respuesta == "sI");
    };

    float obtenerPromedio(){
        float suma = 0.0;
        int cantidad_de_cursos = cursos.size();

        for (int i = 0; i < cantidad_de_cursos; i++)
        {
            suma += cursos[i].second;//second en mi vector de cursos es la nota, no le damos importancia a que materia es.
        }
        float promedio = suma / cantidad_de_cursos;
        return promedio;
    };
};

class Curso{
public:
    string nombre_curso;
    vector<Estudiante*> estudiantes;
    
    Curso(string nombre) {
        nombre_curso = nombre;
    }

    void agregarEstudiante(Estudiante& e) {
        estudiantes.push_back(&e);//paso por referencia porque quiero almacenar punteros, es decir direcciones y se hace por referencia.
    }

    void sacarEstudiante(int legajo) {
        for (int i = 0; i < estudiantes.size(); i++) {
            if (estudiantes[i]->obtenerLegajo() == legajo) {
                delete estudiantes[i];//aca libero memoria antes de borrar el puntero para no tener leaks.
                estudiantes.erase(estudiantes.begin() + i); //esto me sirve porque el begin hace un iterador desde el principio en estudiantes, si yo pongo erase(i) no podia porque .erase no es con indices.
                return;
            }
        }
        cout << "No se encontró el estudiante" << endl;
    }

    void buscarLegajo(int legajo){
        for (int j = 0; j < estudiantes.size(); j++){
            if (estudiantes[j]->obtenerLegajo() == legajo)
            {
                cout << "El alumno esta en el curso" << endl;
                return;
            }
        }
        cout << "El alumno no esta en el curso" << endl;
    }

    void estaCompleto() {
        int cantidad_de_estudiantes = estudiantes.size();
    
        if (cantidad_de_estudiantes > 20) {
            cout << "El curso tiene más gente de la permitida" << endl;
        } else if (cantidad_de_estudiantes == 20) {
            cout << "El curso está lleno" << endl;
        } else {
            cout << "El curso no está lleno" << endl;
        }
    }

    Curso(const Curso& otro) {
        //aca hago el constructor de la copia
        //el parametro que recibe lo pasamos por referencia para evitar copias innecesarias de cosas.
        nombre_curso = otro.nombre_curso; //aca asigno la variable de nombre_curso que es como se llamara nuestra copia. 

        for (Estudiante* e : otro.estudiantes) {
            estudiantes.push_back(e);
            //aca recorro y voy copiando los estudiantes al nuevo curso.
            //no hago una deep copy para no estar creando nuevos objetos, porque la consigna dice que simplemente
            //debo copiar un curso sin modificarle nada, es por eso que copio lo que apuntan los punteros.
            //hago shallow copy porque como nos estan pidiendo literalmente
            //copiar los cursos entonces si el curso del cual lo copiamos se modifica la copia tambien tiene que modificarse.
            //al ser una shallow copy lo que yo hice fue hacer que mi curso de copia tenga los mismos punteros 
            //a Estudiante que mi curso. 
        }
    }
};

int main() {
    vector<Estudiante> estudiantes;
    vector<Curso> cursos;
    int opcion;

    do {
        cout << "\nMenu de opciones:\n";
        cout << "1. Crear Estudiante\n";
        cout << "2. Crear Curso\n";
        cout << "3. Inscribir Estudiante en Curso\n";
        cout << "4. Desinscribir Estudiante de Curso\n";
        cout << "5. Verificar si un Estudiante está en Curso\n";
        cout << "6. Verificar si el Curso está completo\n";
        cout << "7. Ver determinado curso\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombre;
                int legajo;

                cout << "Ingrese el nombre del estudiante: ";
                cin.ignore();
                getline(cin, nombre);

                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;

                estudiantes.push_back(Estudiante(nombre, legajo));
                estudiantes.back().agregarCursos();
                break;
            }
            case 2: {
                string nombreCurso;
                cout << "Ingrese el nombre del curso: ";
                cin.ignore();
                getline(cin, nombreCurso);
                cursos.push_back(Curso(nombreCurso));
                break;
            }
            case 3: {
                int legajo;
                string nombreCurso;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;

                cout << "Ingrese el nombre del curso: ";
                cin.ignore();
                getline(cin, nombreCurso);

                Curso* cursoEncontrado = nullptr;
                for (Curso& curso : cursos) {
                    if (curso.nombre_curso == nombreCurso) {
                        cursoEncontrado = &curso;
                        break;
                    }
                }

                if (cursoEncontrado) {
                    Estudiante* estudianteEncontrado = nullptr;
                    for (Estudiante& e : estudiantes) {
                        if (e.obtenerLegajo() == legajo) {
                            estudianteEncontrado = &e;
                            break;
                        }
                    }

                    if (estudianteEncontrado) {
                        cursoEncontrado->agregarEstudiante(*estudianteEncontrado);
                        cout << "Estudiante inscrito en el curso." << endl;
                    } else {
                        cout << "Estudiante no encontrado." << endl;
                    }
                } else {
                    cout << "Curso no encontrado." << endl;
                }
                break;
            }
            case 4: {
                int legajo;
                string nombreCurso;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;

                cout << "Ingrese el nombre del curso: ";
                cin.ignore();
                getline(cin, nombreCurso);

                Curso* cursoEncontrado = nullptr;
                for (Curso& curso : cursos) {
                    if (curso.nombre_curso == nombreCurso) {
                        cursoEncontrado = &curso;
                        break;
                    }
                }

                if (cursoEncontrado) {
                    cursoEncontrado->sacarEstudiante(legajo);
                } else {
                    cout << "Curso no encontrado." << endl;
                }
                break;
            }
            case 5: {
                int legajo;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;

                string nombreCurso;
                cout << "Ingrese el nombre del curso: ";
                cin.ignore();
                getline(cin, nombreCurso);

                Curso* cursoEncontrado = nullptr;
                for (Curso& curso : cursos) {
                    if (curso.nombre_curso == nombreCurso) {
                        cursoEncontrado = &curso;
                        break;
                    }
                }

                if (cursoEncontrado) {
                    cursoEncontrado->buscarLegajo(legajo);
                } else {
                    cout << "Curso no encontrado." << endl;
                }
                break;
            }
            case 6: {
                string nombreCurso;
                cout << "Ingrese el nombre del curso: ";
                cin.ignore();
                getline(cin, nombreCurso);

                Curso* cursoEncontrado = nullptr;
                for (Curso& curso : cursos) {
                    if (curso.nombre_curso == nombreCurso) {
                        cursoEncontrado = &curso;
                        break;
                    }
                }

                if (cursoEncontrado) {
                    cursoEncontrado->estaCompleto();
                } else {
                    cout << "Curso no encontrado." << endl;
                }
                break;
            }
            case 7: {
                string nombreCurso;
                cout << "Ingrese el nombre del curso: ";
                cin.ignore();
                getline(cin, nombreCurso);
            
                Curso* cursoEncontrado = nullptr;
                for (Curso& curso : cursos) {
                    if (curso.nombre_curso == nombreCurso) {
                        cursoEncontrado = &curso;
                        break;
                    }
                }
            
                if (cursoEncontrado) {
                    if (cursoEncontrado->estudiantes.empty()) {
                        cout << "El curso no tiene estudiantes inscritos." << endl;
                    } else {
                        cout << "Estudiantes en el curso " << nombreCurso << ":" << endl;
                        for (Estudiante* e : cursoEncontrado->estudiantes) {
                            cout << "Nombre: " << e->obtenerNombre() 
                                 << ", Legajo: " << e->obtenerLegajo() 
                                 << ", Promedio: " << e->obtenerPromedio() << endl;
                        }
                    }
                } else {
                    cout << "Curso no encontrado." << endl;
                }
                break;
            }
            case 8:
                cout << "Fin" << endl;
                break;
        }
    } while (opcion != 8);
    return 0;
}