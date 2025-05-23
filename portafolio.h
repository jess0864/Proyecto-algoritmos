#ifndef PORTAFOLIO_H
#define PORTAFOLIO_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // Necesario para std::sort y std::find

using namespace std;

class Portafolio {
private:
    string nombreUsuario;
    vector<string> activos;

public:
    Portafolio(string nombre) : nombreUsuario(nombre) {}

    void agregarActivo(const string& activo) {
        activos.push_back(activo);
        cout << "Activo '" << activo << "' agregado." << endl;
    }

    bool tieneActivo(const string& activo) const {
        for (const auto& a : activos) {
            if (a == activo) return true;
        }
        return false;
    }

    void mostrar() const {
        cout << "Portafolio de " << nombreUsuario << ":\n";
        if (activos.empty()) {
            cout << "(Vacío)\n";
        } else {
            for (const auto& a : activos) {
                cout << "- " << a << '\n';
            }
        }
    }

    const vector<string>& obtenerActivos() const {
        return activos;
    }

    // Nuevo método para eliminar un activo
    bool eliminarActivo(const string& activo) {
        auto it = std::find(activos.begin(), activos.end(), activo);
        if (it != activos.end()) {
            activos.erase(it);
            cout << "Activo '" << activo << "' eliminado." << endl;
            return true; // Devuelve true si el activo fue encontrado y eliminado
        }
        cout << "Activo '" << activo << "' no encontrado para eliminar." << endl;
        return false; // Devuelve false si el activo no se encontró
    }

    // Nuevo método para ordenar los activos (alfabéticamente)
    void ordenarActivos() {
        if (activos.empty()) {
            cout << "El portafolio está vacío, no hay nada que ordenar." << endl;
            return;
        }
        std::sort(activos.begin(), activos.end());
        cout << "Activos ordenados alfabéticamente." << endl;
    }
};

#endif