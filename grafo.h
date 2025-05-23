#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

class Grafo {
private:
    map<string, vector<string>> adyacencia;

public:
    void agregarRelacion(const string& activo1, const string& activo2) {
        adyacencia[activo1].push_back(activo2);
        adyacencia[activo2].push_back(activo1); // No dirigido
    }

    vector<string> obtenerVecinos(const string& activo) const {
        auto it = adyacencia.find(activo);
        if (it != adyacencia.end()) {
            return it->second;
        }
        return {};
    }

    vector<string> recomendacionesBFS(const string& activoInicial, const set<string>& yaPosee, int profundidad = 2) const {
        vector<string> recomendaciones;
        set<string> visitado;
        queue<pair<string, int>> cola;

        cola.push({activoInicial, 0});
        visitado.insert(activoInicial);

        while (!cola.empty()) {
            auto [actual, nivel] = cola.front();
            cola.pop();

            if (nivel > 0 && yaPosee.find(actual) == yaPosee.end()) {
                recomendaciones.push_back(actual);
            }

            if (nivel < profundidad) {
                for (const auto& vecino : obtenerVecinos(actual)) {
                    if (visitado.find(vecino) == visitado.end()) {
                        visitado.insert(vecino);
                        cola.push({vecino, nivel + 1});
                    }
                }
            }
        }

        return recomendaciones;
    }

    vector<string> recomendacionesDesdePortafolio(const vector<string>& activosUsuario, int profundidad = 2) const {
        set<string> yaPosee(activosUsuario.begin(), activosUsuario.end());
        set<string> recomendacionesUnicas;

        for (const auto& activo : activosUsuario) {
            vector<string> nuevas = recomendacionesBFS(activo, yaPosee, profundidad);
            for (const auto& rec : nuevas) {
                recomendacionesUnicas.insert(rec);
            }
        }

        return vector<string>(recomendacionesUnicas.begin(), recomendacionesUnicas.end());
    }
};

#endif